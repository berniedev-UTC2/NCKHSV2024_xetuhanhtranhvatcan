// Khai báo chân kết nối
const int ENA = 2;
const int IN1 = 3;
const int IN2 = 4;
const int IN3 = 5;
const int IN4 = 6;
const int ENB = 7;

// Khởi tạo chương trình
void setup() {
  // Thiết lập chế độ đầu ra cho các chân điều khiển động cơ
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
  
  // Khởi động Serial để gửi dữ liệu đến máy tính
  Serial.begin(9600);
  
  // Khởi tạo giá trị ngẫu nhiên cho bộ sinh số ngẫu nhiên
  randomSeed(analogRead(A0));
}

// Hàm di chuyển xe đi tới
void moveForward() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

// Hàm di chuyển xe lùi lại
void moveBackward() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

// Hàm rẽ trái
void turnLeft() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

// Hàm rẽ phải
void turnRight() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, 255);
  analogWrite(ENB, 255);
}

// Hàm dừng xe
void stopMoving() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void loop() {
  // Khởi tạo giá trị ngẫu nhiên từ -1 đến 1
  int randomValue = random(-1, 2);
  
  // Kiểm tra giá trị ngẫu nhiên
  if (randomValue == -1) {
    // Di chuyển lùi lại trong một khoảng thời gian ngắn
    moveBackward();
    delay(500);
    stopMoving();
    
    // Rẽ trái
    turnLeft();
    delay(500);
    stopMoving();
  } else if (randomValue == 1) {
    // Di chuyển đi tới trong một khoảng thời gian ngắn
    moveForward();
    delay(500);
    stopMoving();
    
    // Rẽ phải
    turnRight();
    delay(500);
    stopMoving();
  } else {
    // Di chuyển thẳng
    moveForward();
  }
}
