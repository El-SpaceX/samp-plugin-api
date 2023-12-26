#ifndef _API_H_
#define _API_H_

#include <unordered_map>
#include <string>

#include <samp-ptl/ptl.h>
#include <cpp-httplib/httplib.h>
#include "script.hpp"

namespace APIServer 
{
    
    using namespace httplib;
    using PublicPtr = std::shared_ptr<ptl::Public>;
    using Token = std::string;

    class API 
    {
    private:
        struct TokenInfo
        {
            int iRatelimit;
            std::chrono::steady_clock::time_point lastTime;
            unsigned int iRequests;
        };

        Server server;
        std::unordered_map<std::string, PublicPtr> handlers;
        std::unordered_map<Token, TokenInfo> tokens;


        std::string sIP = "localhost";
        int iPort = 8080;
        bool bTokenRequired = false;


        std::thread thread_s;

        //handlers pointers
        Request* pReqTemp = nullptr; 
        Response* pResTemp = nullptr;

        void handle_request(const Request& req, Response& res);
        inline std::string GetBasePath(const std::string& path);
    public:
        enum class TokenVerify
        {
            TOKEN_INVALID,
            RATELIMIT_EXCEEDED,
            OK
        };

        bool StartServer(const std::string &host, const int port);
        bool StopServer();
       

        //token & ratelimit verify
        inline TokenVerify CheckToken(const Request& req);
        inline TokenVerify CheckRatelimit(const Token& token);

        inline bool IsAPIRunning() {
            return this->server.is_running();
        }

        inline Response* GetCurrentResponseTemp() 
        { 
            return this->pResTemp;
        }
        inline void SetCurrentResponseTemp(Response* res) 
        { 
            this->pResTemp = res;
        }
       
        inline Request* GetCurrentRequestTemp() 
        { 
            return this->pReqTemp;
        }
        inline void SetCurrentRequestTemp(Request* req) 
        { 
            this->pReqTemp = req; 
        }

        inline void AddHandler(const std::string& pattern, PublicPtr &publicPtr) 
        {  
            this->handlers[pattern] = publicPtr;
        }
        inline void RemoveHandler(const std::string& pattern) 
        { 
            this->handlers.erase(pattern);
        }

        inline void ToggleTokenRequired(bool toggle) 
        { 
            this->bTokenRequired = toggle;
        }
        inline bool GetTokenRequired() 
        { 
            return this->bTokenRequired; 
        }
        inline bool ExistsToken(const Token& token) 
        { 
            return this->tokens.find(token) != this->tokens.end();
        }

        inline void AddToken(const Token& token, int ratelimit) 
        {
            this->tokens[token] = { ratelimit, std::chrono::steady_clock::now(), 0};
        }

        inline void RemoveToken(const Token& token) 
        { 
            this->tokens.erase(token);
        }

        inline void SetRateLimit(const Token& token, int ratelimit) 
        {
            const auto it = this->tokens.find(token);
            if (it != this->tokens.end())
            {
                it->second.iRatelimit = ratelimit;
            }
        }

        inline int GetRateLimit(const Token& token) 
        {
            const auto it = this->tokens.find(token);
            if (it != this->tokens.end())
            {
                return it->second.iRatelimit;
            }
            return 0;
        }

    };
    extern API api;
    
};
#endif