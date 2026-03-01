#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "Melody.h"

LiquidCrystal_I2C lcd(0x27,16,2);

// 定义引脚
const int trigPin = 2;  // Trig引脚连接到数字引脚9
const int echoPin = 3; // Echo引脚连接到数字引脚10

// 定义变量
//long duration;  // 声波往返时间
float distance;   // 计算出的距离

void setup() {
  tone(8, NOTE_A5, 50);     // 无源蜂鸣器接到数字引脚8，初始化播放A5调0.05秒
  lcd.init();               // initialize the lcd 
  lcd.backlight();
  pinMode(trigPin, OUTPUT); // 设置trigPin为输出
  pinMode(echoPin, INPUT);  // 设置echoPin为输入
  Serial.begin(9600);       // 启动串口通信
}

void loop() {
  // 清空trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // 发送10微秒的高电平脉冲触发测距
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // 读取echoPin返回声波的往返时间
  //duration = pulseIn(echoPin, HIGH);
  
  // 计算距离（声速约为340m/s，往返需要除以2）
  // 距离(cm) = 时间(μs) × 0.034 / 2
  //distance = duration * 0.034 / 2;
  distance = pulseIn(echoPin, HIGH)/58.31;
  
  // 输出结果到I2C 1602 LCD
  lcd.home();
  lcd.print("Dis: ");
  lcd.print(distance);
  lcd.print("cm ");

  //蜂鸣警报器，当（30 <距离< 100 cm）时，响警报A6|（距离< 30 cm）时，响警报B6
  while(distance > 30.00 && distance < 100.00){
      tone(8,NOTE_D7,500);
      break;}
  while(distance <= 30.00){
      tone(8,NOTE_B6,500);
      break;}

  delay(500); // 延迟0.5秒再进行下次测量
}
