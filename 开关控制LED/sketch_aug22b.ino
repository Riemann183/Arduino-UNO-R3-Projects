const int ledPin = 8;   // LED 在 D8
const int btnPin = 2;   // 按钮在 D2

bool ledOn = false;     // 默认关

int buttonState = HIGH;       // 去抖后的稳定状态（INPUT_PULLUP: 未按=HIGH）
int lastReading = HIGH;       // 上一次原始读数
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 30; // 防抖时间 30ms，可在 20~50 之间调整

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP); // 内部上拉：未按=HIGH，按下=LOW
  digitalWrite(ledPin, LOW);
}

void loop() {
  int reading = digitalRead(btnPin);

  // 检测到读数变化，开始计时以等待稳定
  if (reading != lastReading) {
    lastDebounceTime = millis();
  }

  // 超过防抖时间，认为状态稳定
  if (millis() - lastDebounceTime > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      // 只在“按下”的瞬间（由HIGH->LOW）切换LED
      if (buttonState == LOW) {
        ledOn = !ledOn;
        digitalWrite(ledPin, ledOn ? HIGH : LOW);
      }
    }
  }

  lastReading = reading;
}