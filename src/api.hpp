#ifndef _API_H_
#define _API_H_

#include <unordered_map>
#include <string>

#include <samp-ptl/ptl.h>
#include <cpp-httplib/httplib.h>
#include "script.hpp"

namespace APIServer {
    
    using namespace httplib;
    using PublicPtr = std::shared_ptr<ptl::Public>;
    using Token = std::string;

    class API {
    private:
        struct s_TokenInfo {
            int iRatelimit;
            std::chrono::steady_clock::time_point lastTime;
            unsigned int iRequests;
        };

        Server server;
        std::unordered_map<std::string, PublicPtr> handlers;
        std::unordered_map<Token, s_TokenInfo> tokens;


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
        enum TOKEN_CHECK {
            TOKEN_INVALID,
            RATELIMIT_EXCEEDED,
            OK
        };


        API() {}
        bool StartServer(const std::string &host, const int port);
        bool StopServer();
       

        //token & ratelimit verify
        inline TOKEN_CHECK CheckToken(const Request& req);
        inline TOKEN_CHECK CheckRatelimit(const Token& token);

        inline bool IsAPIRunning() {return server.is_running(); };

        inline Response* GetCurrentResponseTemp() { return pResTemp; };
        inline void SetCurrentResponseTemp(Response* res) { pResTemp = res; };
        
        inline Request* GetCurrentRequestTemp() { return pReqTemp; };
        inline void SetCurrentRequestTemp(Request* req) { pReqTemp = req; };

        inline void AddHandler(const std::string pattern, PublicPtr &publicPtr) {  handlers[pattern] = publicPtr; }
        inline void RemoveHandler(const std::string pattern) { handlers.erase(pattern); }

        inline void ToggleTokenRequired(bool toggle) { bTokenRequired = toggle;  }
        inline bool GetTokenRequired() { return bTokenRequired; }
        inline bool ExistsToken(Token token) { return tokens.find(token) != tokens.end(); }

        inline void AddToken(Token token, int ratelimit) {
            tokens[token] = { ratelimit, std::chrono::steady_clock::now(), 0};
        }

        inline void RemoveToken(Token token) { tokens.erase(token); }

        inline void SetRateLimit(Token token, int ratelimit) 
        {
            auto it = tokens.find(token);
            if (it != tokens.end()) {
                it->second.iRatelimit = ratelimit;
            }
        }

        inline int GetRateLimit(Token token) 
        {
            auto it = tokens.find(token);
            if (it != tokens.end()) {
                return it->second.iRatelimit;
            }
            return 0;
        }

    };
    extern API api;
    
};
#endif