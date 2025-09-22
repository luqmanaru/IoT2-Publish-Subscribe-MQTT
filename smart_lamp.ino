#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi configuration
const char* ssid = "YOUR_WIFI_SSID";       // Ganti dengan nama WiFi Anda
const char* password = "YOUR_WIFI_PASSWORD"; // Ganti dengan password WiFi Anda

// MQTT broker (gratis)
const char* mqtt_server = "test.mosquitto.org";

// Inisialisasi
WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Menghubungkan ke ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi terkoneksi");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Menghubungkan ke MQTT...");
    if (client.connect("ESP8266Client_Hanif")) {
      Serial.println("terhubung");
    } else {
      Serial.print("gagal, rc=");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void setup() {
  pinMode(LED_BUILTIN, OUTPUT); // Pakai LED internal untuk simulasi
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Simulasi publish ON/OFF tiap 5 detik
  long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    String pesan = (digitalRead(LED_BUILTIN) == LOW) ? "OFF" : "ON";
    client.publish("smartHome/hanif/kamarTidur/lampu", pesan.c_str());
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); // Toggle status lampu
    Serial.println("Mengirim: " + pesan);
  }
}
