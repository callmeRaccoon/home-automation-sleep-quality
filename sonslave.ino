#include <ESP8266WiFi.h>
#include <espnow.h>

float nemSon;
int bayrak=0;
typedef struct struct_message {

  float nem;

} struct_message;

// Create a struct_message called myData
struct_message myData;

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received: ");
  Serial.println(len);
  Serial.print("Nem: ");
  Serial.println(myData.nem);

  nemSon = myData.nem;

}

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  pinMode(D0, OUTPUT);
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
  Serial.print("neden calismiyorsun");
}

void loop() {

  delay(4000);
  if (nemSon < 60.00 && bayrak==0) {
    digitalWrite(D0, HIGH);
    delay(200);
    digitalWrite(D0, LOW);
    delay(200);
    bayrak=1;
    Serial.print("Döngü başarılı");
  }
if (nemSon > 60.00 && bayrak==1) {
    digitalWrite(D0, HIGH);
    delay(500);
    digitalWrite(D0, LOW);
    bayrak=0;
}

}
