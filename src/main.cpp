/**
 * VÍ DỤ 5-1a: GỬI DỮ LIỆU TẦM XA BẰNG MODULE LORA (UART THUẦN)
 * Các chân GPIO sử dụng trực tiếp từ định nghĩa chuẩn trong PTITCube.h
 */
#include <Arduino.h>
#include <PTITCube.h>

PTIT_CDH cdh;

void setup() {
    cdh.begin(115200);
    while (!cdh) { delay(10); }

    cdh.println("\n[VỆ TINH] Khởi tạo module LoRa phát dữ liệu...");
    
    // Cấu hình chân UART1 theo chuẩn phần cứng PTITCube.h
    Serial1.begin(9600, SERIAL_8N1, LORA_RX_PIN, LORA_TX_PIN);
    
    // Cấu hình chân Mode (M0=0, M1=0: Chế độ hoạt động bình thường Transparent Mode)
    pinMode(LORA_M0_PIN, OUTPUT);
    pinMode(LORA_M1_PIN, OUTPUT);
    pinMode(LORA_AUX_PIN, INPUT);
    digitalWrite(LORA_M0_PIN, LOW);
    digitalWrite(LORA_M1_PIN, LOW);
}

void loop() {
    static int counter = 0;
    counter++;

    String payload = "PACKET #" + String(counter) + " - CUBESAT TELEMETRY DATA";
    
    cdh.print("Đang phát xuống mặt đất: ");
    cdh.println(payload);
    
    // Đẩy trực tiếp chuỗi vào UART1 (LoRa) để phát sóng đi
    Serial1.println(payload);
    
    delay(2000);
}
