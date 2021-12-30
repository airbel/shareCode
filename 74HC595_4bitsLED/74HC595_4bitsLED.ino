/*
 *編碼 1=4f,2=12,3=06,4=4c,5=24,6=20,7=0F,8=80,9=02,0=01
 *腳位1>a(1對應a) ,2>b (2對應b), 3>c ,4>b,5>d,6>f,7>g
 *參考： https://swf.com.tw/?p=1307
*/

const byte SEG_PIN[]={9,8};        // 7段顯示器的控制接腳
const byte NUM_OF_SEG = sizeof(SEG_PIN); // 7段顯示器的數量
int number=0;
byte digits[NUM_OF_SEG] = {0};

const byte dataPin = 2;    // 74HC595序列輸入
const byte latchPin = 3;   // 74HC595暫存器時脈」
const byte clockPin = 4;   // 74HC595序列時脈

unsigned long previousMillis = 0;
const long interval = 1000; 

const byte LEDs[] = {
    0x01, //0111 1101  0 
    0x4f, //0100 1111  1
    0x12, //0010 0000  2
    0x06, //0011 0011
    0x4c, //0101 1011
    0x24, //0101 1111
    0x20, //0111 0000
    0x0f, //0111 1111
    0x80,  //0111 0011
    0x04
};

void counter() {
  unsigned long currentMillis = millis();
  
  // 每隔1秒執行一次底下的條件式內容
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    
    if (++number > 9999) {  // number先加1，再比較
      number = 0;            // 若超過99則歸零
    }
    
   digits[0]= number % 10 ;       // 儲存個位數字
   digits[1]= (number / 10) % 10 ;  // 十位數字
   digits[2]= (number / 100) % 10 ; // 儲存百位數字
   digits[3]= (number / 1000) % 10 ; // 儲存百位數字

  }
}

void display(){
  byte num;

  // 逐一設定每個七段顯示器
  for (byte i=0; i<NUM_OF_SEG; i++){
    num = digits[i];

    digitalWrite(latchPin, LOW);
    shiftOut(dataPin, clockPin, LSBFIRST, LEDs[num]);    
    digitalWrite(latchPin, HIGH);
    
    digitalWrite(SEG_PIN[i], LOW);     // 點亮此顯示器
    delay(3);
    
    for (byte j=0; j<NUM_OF_SEG; j++) {
      digitalWrite(SEG_PIN[j], HIGH);  // 關閉所有顯示器
    }
    
  }

}


void setup() {
  // put your setup code here, to run once:
    pinMode(latchPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    //全亮0
    for (byte i=0; i<NUM_OF_SEG; i++) {
    pinMode(SEG_PIN[i], OUTPUT);
    digitalWrite(SEG_PIN[i], HIGH);

  }
}

void loop() {
  // put your main code here, to run repeatedly:
  counter();
  display();
}
