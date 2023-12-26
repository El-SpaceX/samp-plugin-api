#include "api.hpp"


namespace APIServer {
    
    API api;

    inline std::string API::GetBasePath(const std::string& path) 
    {
        const size_t pos = path.find('/', 1);
        if (pos != std::string::npos) {
            return path.substr(0, pos + 1);
        }
        return "/";
    }



    inline API::TokenVerify API::CheckRatelimit(const Token& token) {

        //-1 == no limit
        TokenInfo& tokenInfo = tokens[token];

        if (tokenInfo.iRatelimit == -1) {
            return TokenVerify::OK;
        }

        const auto now = std::chrono::steady_clock::now();
        const auto diference = std::chrono::duration_cast<std::chrono::minutes>(now - tokenInfo.lastTime);
        if (diference > std::chrono::minutes(1)) {
            tokenInfo.iRequests = 0;
            tokenInfo.lastTime = std::chrono::steady_clock::now();
            return TokenVerify::OK;
        }

        
        tokenInfo.iRequests++;
        if (tokenInfo.iRequests > static_cast<unsigned int>(tokenInfo.iRatelimit)) {
            return TokenVerify::RATELIMIT_EXCEEDED;
        }

        return TokenVerify::OK;
    }

   

    inline API::TokenVerify API::CheckToken(const Request& req) {

        if (!this->GetTokenRequired())
            return TokenVerify::OK;

        if (!this->tokens.empty()) {
            if (req.has_header("Authorization")) {
                const Token token = req.get_header_value("Authorization");
                if (this->ExistsToken(token)) {
                    return CheckRatelimit(token);
                }
            }
        }
        return TokenVerify::TOKEN_INVALID;
    }

    void API::handle_request(const Request& req, Response& res) {

        const auto it = this->handlers.find(this->GetBasePath(req.path));
        if (it != this->handlers.end()) {

            //token and ratelimit verify
            const TokenVerify allowed = this->CheckToken(req);
            if (allowed != TokenVerify::OK) {
                res.status = allowed == TokenVerify::RATELIMIT_EXCEEDED ? 429 : 401;
                return;
            }

            this->SetCurrentRequestTemp(const_cast<Request*>(&req));
            this->SetCurrentResponseTemp(&res);

            
            //executes the callback to handle the response.
            const cell ret = it->second->Exec(req.remote_addr, req.remote_port);



            this->SetCurrentRequestTemp(nullptr);
            this->SetCurrentResponseTemp(nullptr);
            res.status = ret;
        }
        else {
            res.status = 404;
        }
    }

    bool API::StartServer(const std::string& host, int port) {
        if (this->IsAPIRunning())
            return false;

        this->sIP = host;
        this->iPort = port;

        //separate thread for the API
        this->thread_s = std::thread([&]() {
            server.Get("/.*", [&](const Request& req, Response& res) {
                    handle_request(req, res);
                });
            server.listen(sIP, iPort);
            });
        return true;
    }

    bool API::StopServer() 
    {
        if (!this->IsAPIRunning())
            return 0;


        this->server.stop();
        return 1;
    }
}
