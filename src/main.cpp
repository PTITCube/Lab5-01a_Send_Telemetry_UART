/**
 * VÍ DỤ 5-1a: GỬI DỮ LIỆU TẦM XA BẰNG MODULE LORA (UART THUẦN)
 */
#include <Arduino.h>

#include <PTITCube.h>

PTIT_CDH cdh;

// Chân giao tiếp với module LoRa E32
#define LORA_RX 26
#define LORA_TX 27
#define LORA_M0 25
#define LORA_M1 35

void setup() {
    cdh.begin(115200);
    while (!cdh) { delay(10); }

    cdh.println("\n[VỆ TINH] Khởi tạo module LoRa phát dữ liệu...");
    Serial2.begin(9600, SERIAL_8N1, LORA_RX, LORA_TX);
    
    // Cấu hình chân Mode (M0=0, M1=0: Chế độ hoạt động bình thường Transparent Mode)
    pinMode(LORA_M0, OUTPUT);
    pinMode(LORA_M1, OUTPUT);
    digitalWrite(LORA_M0, LOW);
    digitalWrite(LORA_M1, LOW);

    cdh.println("[COM] LoRa Module OK");
}

void loop() {
    static int counter = 0;
    counter++;

    String payload = "PACKET #" + String(counter) + " - CUBESAT TELEMETRY DATA";
    
    cdh.print("Đang phát xuống mặt đất: ");
    cdh.println(payload);
    
    // Đẩy trực tiếp chuỗi vào UART2 (LoRa) để phát sóng đi
    Serial2.println(payload);
    
    delay(2000);
}

