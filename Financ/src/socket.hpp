#ifndef FINANC_SOCKET_HPP
#define FINANC_SOCKET_HPP

#include <string>
#include <memory>
#include <vector>
#include <functional>
#include <future>
#include "Fegn.hpp"

namespace Financ {
    // WebSocket sunucusu
    class SocketServer {
    private:
        std::string host;
        int port;
        bool isRunning;
        
        // Bağlantı yöneticisi
        std::map<std::string, std::shared_ptr<Fegn::WebSocketClient>> connections;
        
        // Olay yöneticileri
        std::function<void(const std::string&)> onConnect;
        std::function<void(const std::string&)> onDisconnect;
        std::function<void(const std::string&, const std::string&)> onMessage;
        
    public:
        SocketServer(const std::string& host = "localhost", int port = 8080)
            : host(host), port(port), isRunning(false) {}
        
        // Sunucuyu başlat
        void start() {
            isRunning = true;
            // Sunucu başlatma işlemleri
        }
        
        // Sunucuyu durdur
        void stop() {
            isRunning = false;
            // Sunucu durdurma işlemleri
        }
        
        // Bağlantı yönetimi
        void onConnect(const std::function<void(const std::string&)>& callback) {
            onConnect = callback;
        }
        
        void onDisconnect(const std::function<void(const std::string&)>& callback) {
            onDisconnect = callback;
        }
        
        void onMessage(const std::function<void(const std::string&, const std::string&)>& callback) {
            onMessage = callback;
        }
        
        // Mesaj gönderme
        void broadcast(const std::string& message) {
            for (auto& connection : connections) {
                connection.second->send(message);
            }
        }
        
        void sendTo(const std::string& clientId, const std::string& message) {
            if (connections.find(clientId) != connections.end()) {
                connections[clientId]->send(message);
            }
        }
        
        // Sunucu durumu
        bool isRunning() const {
            return isRunning;
        }
        
        size_t getConnectionCount() const {
            return connections.size();
        }
    };
    
    // WebSocket sunucusu istemcisi
    class SocketClient {
    private:
        std::shared_ptr<SocketServer> server;
        std::string clientId;
        
    public:
        SocketClient(std::shared_ptr<SocketServer> server, const std::string& clientId)
            : server(server), clientId(clientId) {}
        
        void send(const std::string& message) {
            server->sendTo(clientId, message);
        }
        
        void disconnect() {
            server->onDisconnect(clientId);
        }
    };
}

#endif // FINANC_SOCKET_HPP
