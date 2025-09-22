# IoT2-Publish-Subscribe-MQTT

Implementasi sistem kontrol lampu pintar menggunakan protokol MQTT untuk perangkat IoT hemat bandwidth.

## 📖 Deskripsi
Proyek ini merupakan solusi **smart home** berbasis protokol **MQTT** yang dirancang untuk lingkungan dengan koneksi terbatas. Menggunakan ESP8266 sebagai publisher, sistem ini mengontrol status lampu (ON/OFF) melalui mekanisme **publish-subscribe** dan broker MQTT publik.

## ✨ Fitur Utama
- Kontrol lampu real-time via MQTT
- Hemat bandwidth (header hanya 2 byte)
- Stabil di jaringan lemah/putus-nyambung
- Simulasi dengan LED built-in ESP8266
- Topik kustom unik: `smartHome/hanif/kamarTidur/lampu`

## 🛠️ Komponen
| Komponen       | Spesifikasi          |
|----------------|----------------------|
| Mikrokontroler | ESP8266 (NodeMCU)    |
| Protokol       | MQTT over TCP        |
| Broker         | test.mosquitto.org   |
| Topik          | `smartHome/.../lampu`|
| Payload        | `ON` / `OFF`         |

## 🚀 Cara Kerja
```mermaid
graph LR
A[ESP8266] -->|Publish ON/OFF| B[Broker MQTT]
B -->|Forward| C[Client Subscribe]
C -->|Kontrol Lampu| D[Aplikasi HP]
```

### Langkah-langkah:
1. **Koneksi**: ESP8266 terhubung ke WiFi → Broker MQTT.
2. **Publish**: Kirim status lampu (`ON`/`OFF`) ke topik setiap 5 detik.
3. **Subscribe**: Aplikasi HP (misal MQTT Dash) menerima data dan menampilkan status.
4. **Kontrol**: Perubahan status langsung mempengaruhi LED di ESP8266.

## ⚙️ Instalasi
1. **Prasyarat**:
   - Arduino IDE + Library `PubSubClient`
   - Board ESP8266
2. **Konfigurasi**:
   ```cpp
   const char* ssid = "YOUR_WIFI_SSID";       // Ganti dengan WiFi Anda
   const char* password = "YOUR_WIFI_PASSWORD"; // Ganti dengan password WiFi
   ```
3. **Upload**: Flash kode ke ESP8266.
4. **Testing**:
   - Buka Serial Monitor (baudrate: 115200)
   - Subscribe ke topik via [MQTT Explorer](https://mqtt-explorer.com/)

## 🔍 Analisis Teknis
### Perbandingan TCP/IP vs MQTT
| Parameter       | TCP/IP                     | MQTT                      |
|-----------------|----------------------------|---------------------------|
| Lapisan         | 4 lapisan (App, Transport, Internet, Network Access) | 1 lapisan (di atas TCP) |
| Header          | Besar (20-60 byte)         | Minimalis (2 byte)        |
| Model Komunikasi| Client-Server              | Publish-Subscribe         |
| Efisiensi       | Rendah (overhead besar)    | Tinggi (hemat bandwidth)  |
| Use Case        | Web browsing, file transfer| IoT, sensor, M2M         |

### Keunggulan MQTT untuk IoT
1. **Hemat Bandwidth**: Header kecil cocok untuk jaringan terbatas (satelit, LoRa).
2. **Stabilitas**: Support QoS (Quality of Service) untuk data kritis.
3. **Skalabilitas**: Satu broker melayani ribuan perangkat.
4. **Low-Power**: Cocok untuk perangkat baterai (sleep mode).

---
**luqmanaru**
