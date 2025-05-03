# Financ

Financ, Wholf dilinde WebSocket sunucusu oluşturmak için kullanılan güçlü bir kütüphanedir.

## Özellikler

- WebSocket sunucusu oluşturma
- Bağlantı yönetimi
- Mesaj gönderme ve alma
- Olay yönetimi
- Performans optimizasyonları

## Kurulum

```wholf
fort import "Financ"
```

## Kullanım

### Temel Kullanım

```wholf
// WebSocket sunucusu başlat
fegn Financ {
    startServer: ("localhost", 8080) => {
        Console.log("Sunucu başlatıldı")
    }
}
```

### Özel Kullanım

```wholf
// Özel sunucu başlat
fegn Financ {
    startServer: ("localhost", 8080) => {
        Console.log("Sunucu başlatıldı")
    },
    
    // Bağlantı yönetimi
    onConnect: (clientId) => {
        Console.log("Yeni bağlantı: " + clientId)
    },
    
    onDisconnect: (clientId) => {
        Console.log("Bağlantı kesildi: " + clientId)
    },
    
    onMessage: (clientId, message) => {
        Console.log("Mesaj alındı: " + clientId + ": " + message)
    }
}
```

### Mesaj Gönderme

```wholf
// Tüm istemcilere mesaj gönder
fegn Financ {
    broadcast: ("Merhaba") => {
        Console.log("Mesaj gönderildi")
    }
}

// Belirli istemciye mesaj gönder
fegn Financ {
    sendTo: ("client1", "Merhaba") => {
        Console.log("Mesaj gönderildi")
    }
}
```

## Lisans

MIT License
