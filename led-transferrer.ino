#include <vector>

const int GPIO_PIN_LED_RED = 4;
const int GPIO_PIN_LED_BLUE = 14;
const int speed = 10;  // pause in miliseconds between bits
const String data = "Test";
std::vector<bool> dataInBinary;

std::vector<bool> convertStringToBinary(String text) {
  std::vector<bool> rawData;
  rawData.reserve(text.length() * 8 + 8); // 1 char = 8 bits; 8 bits of CRC

  for (char c : text) {
    for (int i = 7; i >= 0; --i) {
      rawData.push_back((c >> i) & 1);
    }
  }

  // CRC-8 (8 bits)
  uint8_t crc = 0;
  for (char c : text) {
    crc ^= c;  // XOR bytes
    for (int j = 0; j < 8; j++) {
      crc = (crc & 0x80) ? (crc << 1) ^ 0x07 : (crc << 1);
    }
  }

  for (int i = 7; i >= 0; --i) {
    rawData.push_back((crc >> i) & 1);
  }

  // Manchester encode
  std::vector<bool> data;
  data.reserve(rawData.size() * 2);

  for (bool bit : rawData) {
    data.push_back(bit);
    data.push_back(!bit);
  }

  return data;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(GPIO_PIN_LED_RED, OUTPUT);
  pinMode(GPIO_PIN_LED_BLUE, OUTPUT);
  dataInBinary = convertStringToBinary(data);
}

void sendBinaryStartTransaction() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(GPIO_PIN_LED_RED, HIGH);
    digitalWrite(GPIO_PIN_LED_BLUE, HIGH);
    delay(100);
    digitalWrite(GPIO_PIN_LED_RED, LOW);
    digitalWrite(GPIO_PIN_LED_BLUE, LOW);
    delay(100);
  }
  delay(500);
}

void sendBinaryEndTransaction() {
  digitalWrite(GPIO_PIN_LED_RED, LOW);
  digitalWrite(GPIO_PIN_LED_BLUE, LOW);
  delay(2000);
}

void sendBinaryData(const std::vector<bool>& data) {
  sendBinaryStartTransaction();

  for (size_t i = 0; i < data.size(); i += 2) {
    bool bit0 = data[i];
    bool bit1 = data[i + 1];

    int redVal = bit0 ? HIGH : LOW;
    int blueVal = bit1 ? HIGH : LOW;

    digitalWrite(GPIO_PIN_LED_RED, redVal);
    digitalWrite(GPIO_PIN_LED_BLUE, blueVal);
    delay(speed);
  }

  sendBinaryEndTransaction();
}

void loop() {
  // put your main code here, to run repeatedly:

  sendBinaryData(dataInBinary);
}
