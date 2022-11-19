// Template ID, Device Name and Auth Token are provided by the Blynk.Cloud
// See the Device Info tab, or Template settings
#define BLYNK_TEMPLATE_ID           "TMPLy9uHj_RC"
#define BLYNK_DEVICE_NAME           "Smart Light"
#define BLYNK_AUTH_TOKEN            "ZFsjHAcgl5d0DLyyMee7SHWXIHVzWa1u"

// Comment this out to disable prints and save space
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = "ZFsjHAcgl5d0DLyyMee7SHWXIHVzWa1u";
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = ""; // Wi-Fi Name.
char pass[] = ""; // Password.

int led = 27; //Led 1 connection to Board
int led1 = 26; //Led 2 connection to Board
int led2 = 25; //Led 3 connection to Board


int ldr = 34; //LDR connection to Board

int ir = 33; //IR Sensor 1 connection to Board
int ir1 = 32; //IR Sensor 2 connection to Board
int ir2 = 35; //IR Sensor 3 connection to Board

int proxy1 = 0;
int proxy2 = 0;
int proxy3 = 0;

BlynkTimer timer;
bool buttonMode = 0;

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void myTimerEvent()
{
  int ldrStatus = analogRead (ldr);
  Serial.print("LDR Val: "); Serial.println(ldrStatus);
  if (buttonMode == 0) {
    if (ldrStatus <= 500)
    {
      //    digitalWrite(led, HIGH);
      //    digitalWrite(led1, HIGH);
      //    digitalWrite(led2, HIGH);

      proxy1 = digitalRead(ir);
      proxy2 = digitalRead(ir1);
      proxy3 = digitalRead(ir2);


      if (proxy1 == LOW)
      {
        digitalWrite(led, HIGH);
      }
      else
      {
        digitalWrite(led, LOW);
      }
      if (proxy2 == LOW)
      {
        digitalWrite(led1, HIGH);
      }
      else
      {
        digitalWrite(led1, LOW);
      }
      if (proxy3 == LOW)
      {
        digitalWrite(led2, HIGH);
      }
      else
      {
        digitalWrite(led2, LOW);
      }
    }
    else
    {
      digitalWrite(led, LOW);
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
    }
  }

  Blynk.virtualWrite(V4, ldrStatus); //Send ldr value
  Blynk.virtualWrite(V5, proxy1);
  Blynk.virtualWrite(V6, proxy2);
  Blynk.virtualWrite(V7, proxy3);
}


BLYNK_WRITE(V1) // Check status button 1 of blynk
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable

  if (pinValue == 1) {
    buttonMode = 1;
    digitalWrite(led, HIGH);
  }
  else{
    buttonMode = 0;
    digitalWrite(led, HIGH);
  }
}


BLYNK_WRITE(V2) // Check status button 2 of blynk
{
  int pinValue = param.asInt(); // assigning incoming value from pin V2 to a variable

  if (pinValue == 1) {
    buttonMode = 1;
    digitalWrite(led1, HIGH);
  }
  else{
    buttonMode = 0;
    digitalWrite(led1, HIGH);
  }
}


BLYNK_WRITE(V3) // Check status button 3 of blynk
{
  int pinValue = param.asInt(); // assigning incoming value from pin V3 to a variable

  if (pinValue == 1) {
    buttonMode = 1;
    digitalWrite(led2, HIGH);
  }
  else{
    buttonMode = 0;
    digitalWrite(led2, HIGH);
  }
}

void setup()
{
  Serial.begin(9600);
  Serial.print("SYSTEM STARTING");
  pinMode (led, OUTPUT);
  pinMode (led1, OUTPUT);
  pinMode (led2, OUTPUT);
  pinMode (ldr, INPUT);
  pinMode (ir, INPUT);
  pinMode (ir1, INPUT);
  pinMode (ir2, INPUT);

  delay(10);

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);

}
void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
