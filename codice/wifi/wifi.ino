#include "WiFiS3.h"

const char* ssid = "iPhone di Federico";      // senza spazi!
const char* password = "fonz1234";

void setupWifi() {
  // Controlla se il modulo WiFi è presente
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("❌ Modulo WiFi non trovato!");
    while (true);
  }

  // Mostra firmware version
  String fv = WiFi.firmwareVersion();
  Serial.print("Firmware WiFi: ");
  Serial.println(fv);

  // Scansiona reti disponibili
  Serial.println("Reti disponibili:");
  int n = WiFi.scanNetworks();
  for (int i = 0; i < n; i++) {
    Serial.print("  - ");
    Serial.println(WiFi.SSID(i));
  }

  // Tenta connessione
  Serial.print("Connessione a: ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  int tentativi = 0;
  while (WiFi.status() != WL_CONNECTED && tentativi < 20) {
    delay(500);
    Serial.print(".");
    tentativi++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Connesso!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.print("\n❌ Fallito. Stato: ");
    Serial.println(WiFi.status());
  }
}

void setup() {
  Serial.begin(115200);
  while (!Serial);
  setupWifi();
}

void loop() {}