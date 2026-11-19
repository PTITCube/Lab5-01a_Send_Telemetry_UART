/**
 * VÍ DỤ 5-1a: GỬI DỮ LIỆU TẦM XA BẰNG MODULE LORA (UART THUẦN)
 */
#include <Arduino.h>
#include <PTITCube.h>

PTIT_CDH cdh;

void setup() {
    cdh.begin(115200);

    Serial1.begin(9600, SERIAL_8N1, LORA_RX_PIN, LORA_TX_PIN);

    pinMode(LORA_M0_PIN, OUTPUT);
    pinMode(LORA_M1_PIN, OUTPUT);
    pinMode(LORA_AUX_PIN, INPUT);
    digitalWrite(LORA_M0_PIN, LOW);
    digitalWrite(LORA_M1_PIN, LOW);

    cdh.println("[COM] LoRa TX ready.");
}

void loop() {
    static int counter = 0;
    counter++;

    String payload = "PACKET #" + String(counter) + " - CUBESAT TELEMETRY";
    cdh.println("[TX] " + payload);

    Serial1.println(payload);
    delay(2000);
}
