#include <PID_v1.h>

// Khai báo tất cả các chân để điều khiển động cơ và cảm biến đường đi như mã gốc
int stop_distance = 15; // Khoảng cách phát hiện vật cản
const int trig = 2;
const int echo = 4;
#define m1 6 
#define m2 7
#define m3 8
#define m4 9
#define e1 5
#define e2 10
#define ir1 A0
#define ir2 A1 
#define ir3 A2
#define ir4 A3

// Khai báo các biến toàn cục
unsigned long time;
int distance;
int F = 65; //PWM_go
int T = 130; // PWM_turn1
int T1 = 180; // PWM_vatcan_turn2  
int F1 = 150; // PWM_quaduong

// Khai báo đối tượng PID
double Setpoint, Input, Output;
PID myPID(&Input, &Output, &Setpoint, 2, 5, 1, DIRECT);

void setup() {
 Serial.begin(9600);
 pinMode(m1, OUTPUT);
 pinMode(m2, OUTPUT);
 pinMode(m3, OUTPUT);
 pinMode(m4, OUTPUT);
 pinMode(e1, OUTPUT);
 pinMode(e2, OUTPUT);
 pinMode(ir1, INPUT);
 pinMode(ir2, INPUT);
 pinMode(ir3, INPUT);
 pinMode(ir4, INPUT);
 pinMode(trig, OUTPUT);
 pinMode(echo, INPUT);

 // Khởi tạo PID với các tham số thích hợp (K_p, K_i, K_d)
 Setpoint = 0; // Điểm đặt cho error = 0 (đường thẳng)
 myPID.SetOutputLimits(-255, 255); // Giới hạn tốc độ động cơ từ -255 đến 255
}

void loop() {
 // Đọc giá trị cảm biến đường đi
 int s1 = digitalRead(ir1);
 int s2 = digitalRead(ir2);
 int s3 = digitalRead(ir3);
 int s4 = digitalRead(ir4);
 
 // Tính toán error dựa trên giá trị cảm biến
 int error = (s1 * 3 + s2 * 1 + s3 * -1 + s4 * -3);
 
 // Cập nhật Input cho PID
 Input = error;
 
 // Tính toán Output từ PID
 myPID.Compute();
 
 // Kiểm tra khoảng cách đến vật cản
 checkDistance();
 
 // Điều khiển động cơ dựa trên Output từ PID
 motorControl(Output);
}

void checkDistance() {
 //Phát xung từ chân trig, có độ rộng là 10ms
 digitalWrite(trig, 0); //Tắt chân trig
 delayMicroseconds(2);
 digitalWrite(trig, 1); //bật chân trig để phát xung
 delayMicroseconds(10); //Xung có độ rộng là 10 microsecond
 digitalWrite(trig, 0);
 //Chân echo sẽ nhận xung phản xạ lại
 //Và đo độ rộng xung cao ở chân echo
 time = pulseIn(echo, HIGH);
 //Tính khoảng cách đến vật thể (Đơn vị đo là cm)
 //Tốc độ của âm thanh trong không khí là 340 m/s, tương đương 29,412 microSeconds/cm,
 //Do thời gian được tính từ lúc phát tín hiệu tới khi sóng âm phản xạ lại,
 //vì vậy phải chia cho 2
 distance = int(time / 2 / 29.412);
 // In lên Serial kết quả
 Serial.print("Khoảng cách: ");
 Serial.print(distance);
 Serial.println("cm");
 delay(100);

 if (distance < stop_distance) {
   analogWrite(e1, T); //you can adjust the speed of the motors from 0-255
   analogWrite(e2, T);
   digitalWrite (m1, 0); // stop
   digitalWrite(m2, 0);
   digitalWrite (m3, 0);
   digitalWrite(m4, 0);
   delay(250);
   analogWrite(e1, T); // turn right 
   analogWrite(e2, T);
   digitalWrite (m1, 0);
   digitalWrite(m2, 1);
   digitalWrite (m3, 1);
   digitalWrite(m4, 0);
   delay(350);
   analogWrite(e1, T); //you can adjust the speed of the motors from 0-255
   analogWrite(e2, T);
   digitalWrite (m1, 0); // cho xe robot xoay sang trái
   digitalWrite(m2, 1);
   digitalWrite (m3, 0);
   digitalWrite(m4, 1);
   delay(700);
   digitalWrite (m1, 1);
   digitalWrite(m2, 0);
   digitalWrite (m3, 0);
   digitalWrite(m4, 1);
   delay(300);
   analogWrite(e1, T); //you can adjust the speed of the motors from 0-255
   analogWrite(e2, T);
   digitalWrite (m1, 0); //cho xe robot đi thẳng 1 đoạn
   digitalWrite(m2, 1);
   digitalWrite (m3, 0);
   digitalWrite(m4, 1);
   delay(500);
   digitalWrite (m1, 1);
   digitalWrite(m2, 0);
   digitalWrite (m3, 0);
   digitalWrite(m4, 1);
   delay(400);
   analogWrite(e1, T); //you can adjust the speed of the motors from 0-255
   analogWrite(e2, T);
   digitalWrite (m1, 0); // cho xe robot xoay phải 1 đoạn
   digitalWrite(m2, 1);
   digitalWrite (m3, 0);
   digitalWrite(m4, 1);
   delay(900);
   digitalWrite (m1, 0);
   digitalWrite(m2, 1);
   digitalWrite (m3, 1);
   digitalWrite(m4, 0);
   delay(150);
   analogWrite(e1, T); //you can adjust the speed of the motors from 0-255
 }
}

void motorControl(int output) {
 // Chuyển đổi Output thành tốc độ động cơ
 int rightMotorSpeed = F + output;
 int leftMotorSpeed = F - output;
 
 // Giới hạn tốc độ động cơ trong khoảng [-255, 255]
 rightMotorSpeed = constrain(rightMotorSpeed, -255, 255);
 leftMotorSpeed = constrain(leftMotorSpeed, -255, 255);
 
 // Điều khiển động cơ
 analogWrite(e1, abs(rightMotorSpeed)); 
 analogWrite(e2, abs(leftMotorSpeed));
 
 digitalWrite(m1, rightMotorSpeed > 0 ? 1 : 0);
 digitalWrite(m2, rightMotorSpeed > 0 ? 0 : 1);
 digitalWrite(m3, leftMotorSpeed > 0 ? 1 : 0);
 digitalWrite(m4, leftMotorSpeed > 0 ? 0 : 1);
}
