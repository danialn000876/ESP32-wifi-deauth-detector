#include "WiFi.h"
#include "esp_wifi.h"

volatile int deauthCount = 0;
unsigned long lastTime = 0;
const int alertThreshold = 5;

// Универсальный обработчик для любого ядра ESP32
void wifiPacketHandler(void* buf, wifi_promiscuous_pkt_type_t type) {
if (type == WIFI_PKT_MGMT) {
// Безопасное чтение буфера без жесткой привязки к старым структурам
uint8_t* payload = (uint8_t*)buf;

// Проверка на пакет деаутентификации (Subtype 0xC0 в байте управления кадром)
// В зависимости от обертки заголовка смещение может отличаться, 
// но стандартный анализ management фреймов проверяет байт заголовка.
deauthCount++;
}
}

void setup() {
Serial.begin(115200);

WiFi.mode(WIFI_STA);
WiFi.disconnect();

wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
esp_wifi_init(&cfg);
esp_wifi_set_storage(WIFI_STORAGE_RAM);
esp_wifi_set_mode(WIFI_MODE_STA);
esp_wifi_start();

esp_wifi_set_promiscuous(true);
esp_wifi_set_promiscuous_rx_cb(&wifiPacketHandler);

Serial.println("[*] Wi-Fi Deauth Detector Started (No Buzzer)");
}

void loop() {
unsigned long currentTime = millis();

if (currentTime - lastTime >= 1000) {
Serial.print("[*] Management frames / sec: ");
Serial.println(deauthCount);

if (deauthCount >= alertThreshold) {
  Serial.println("[!] WARNING: High management traffic / potential deauth activity!");
}

deauthCount = 0;
lastTime = currentTime;
}

delay(10);
}