#ifndef FINANC_HPP
#define FINANC_HPP

#include "socket.hpp"

namespace Financ {
    // Financ sunucusu
    class FinancServer {
    private:
        std::shared_ptr<SocketServer> socketServer;
        
    public:
        FinancServer(const std::string& host = "localhost", int port = 8080)
            : socketServer(std::make_shared<SocketServer>(host, port)) {}
        
        // Sunucuyu başlat
        void start() {
            socketServer->start();
            Console.log("Financ sunucusu başlatıldı");
        }
        
        // Sunucuyu durdur
        void stop() {
            socketServer->stop();
            Console.log("Financ sunucusu durduruldu");
        }
        
        // Bağlantı yönetimi
        void onConnect(const std::function<void(const std::string&)>& callback) {
            socketServer->onConnect(callback);
        }
        
        void onDisconnect(const std::function<void(const std::string&)>& callback) {
            socketServer->onDisconnect(callback);
        }
        
        void onMessage(const std::function<void(const std::string&, const std::string&)>& callback) {
            socketServer->onMessage(callback);
        }
        
        // Mesaj gönderme
        void broadcast(const std::string& message) {
            socketServer->broadcast(message);
        }
        
        void sendTo(const std::string& clientId, const std::string& message) {
            socketServer->sendTo(clientId, message);
        }
        
        // Sunucu durumu
        bool isRunning() const {
            return socketServer->isRunning();
        }
        
        size_t getConnectionCount() const {
            return socketServer->getConnectionCount();
        }
    };
    
    // Financ sunucusu başlatma
    void startServer(const std::string& host = "localhost", int port = 8080) {
        auto server = std::make_shared<FinancServer>(host, port);
        
        // Bağlantı yönetimi
        server->onConnect([](const std::string& clientId) {
            Console.log("Yeni bağlantı: " + clientId);
        });
        
        server->onDisconnect([](const std::string& clientId) {
            Console.log("Bağlantı kesildi: " + clientId);
        });
        
        server->onMessage([](const std::string& clientId, const std::string& message) {
            Console.log("Mesaj alındı: " + clientId + ": " + message);
        });
        
        // Sunucuyu başlat
        server->start();
    }
}

#endif // FINANC_HPP
