#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

double pulse, frequency, capacitance, inductance, inductance_mH;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // Address 0x3C for 128x64
  display.display();
  delay(2000);  // Pause for 2 seconds
  
  Serial.begin(115200);
  pinMode(11, INPUT);
  pinMode(13, OUTPUT);
  Serial.println("Hi there!");
  delay(1000);
  
}

void loop() {
  digitalWrite(13, HIGH); 
  delay(5);
  digitalWrite(13, LOW);
  delayMicroseconds(100);
  pulse = pulseIn(11, HIGH, 5000);
  
  //if (pulse > 0.1) {
    // Insert your used capacitance value here. Currently using 2uF. Delete this line after that
    capacitance = 2.25E-6;
    
    frequency = 1.E6 / (2 * pulse);
    inductance = 1. / (capacitance * frequency * frequency * 4. * 3.14159 * 3.14159);
    inductance *= 1E6;
    inductance_mH = inductance / 1000;
    
    // Serial print
    Serial.print("High for uS:");
    Serial.print(pulse);
    Serial.print("\tfrequency Hz:");
    Serial.print(frequency);
    Serial.print("\tinductance uH:");
    Serial.println(inductance);
    delay(10);

    // OLED print
    display.clearDisplay();
  display.setTextSize(2);      
  display.setTextColor(SSD1306_WHITE); 
  display.setCursor(0,0);     
  display.println("Inductance");
  display.print(inductance);
  display.println("uH");
  display.println(" ");
  display.print(inductance_mH);
  display.println("mH");
  display.display();
  delay(200);
  //}
}
