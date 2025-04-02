#define BLYNK_TEMPLATE_ID "TMPL8FyFih3v"
#define BLYNK_DEVICE_NAME "Smart Pedometer"
#define BLYNK_AUTH_TOKEN "SUS76MY0GzU1173jteLIw_72rKrpvwwM"
// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

int x,y;
int count =0;
float calories;
float distance;

const int xanalog = 35;
const int yanalog = 34;

char auth[] = BLYNK_AUTH_TOKEN;

//const char* ssid     = "ipan";
//const char* pass = "hahahaha";
char ssid[] = "V2029";
char pass[] = "";

BlynkTimer timer;
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void sendSensor(){

x = analogRead(xanalog);
y = analogRead(yanalog);
if ( x >= 1900 && y>=2100)
//if ( x >= 2000 && y>=1850)
{ count++;
//MySerial.print(count);
delay(200);
}
if ( x <= 1750 && y<=2100)
{
count++;
// MySerial.print(count);
delay(200);
}
//calories = (count * 50)/1000; // This value is taken depending upon my weight and height.
//distance = (count * 60)/10000; // My step it is on average 60cm.

calories = count * 0.050; // This value is taken depending upon my weight and height.
distance = count * 0.0006;


Blynk.virtualWrite(V0, x);
Blynk.virtualWrite(V1, y);
Blynk.virtualWrite(V2, count);
Blynk.virtualWrite(V3, calories);
Blynk.virtualWrite(V4, distance);

Serial.println("Value X :");
Serial.println(x);

Serial.println("Value Y :");
Serial.println(y);

Serial.println("Steps :");
Serial.println(count);

Serial.println("Calorie :");
Serial.println(calories);

Serial.println("Steps :");
Serial.println(distance);

}

void setup()
{
  // Debug console
  Serial.begin(115200);
  WiFi.mode(WIFI_STA); // SETS TO STATION MODE!
  WiFi.begin(ssid, pass);
   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }

  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(200L, sendSensor);
}


void loop()
{
  sendSensor();
  display.clearDisplay();
  display.print("Value X :");
  display.print(x);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Value Y :");
  display.print(y);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  display.print("Steps :");
  display.print(count);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.print("Calories :");
  display.print(calories);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 30);
  display.print("Distance :");
  display.print(distance);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 40);
  display.display(); 
  Blynk.run();
  timer.run();
}

