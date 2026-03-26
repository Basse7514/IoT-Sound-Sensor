/************ BLYNK INFO ************/
#define BLYNK_TEMPLATE_ID "TMPL2zE5AK6u2"
#define BLYNK_TEMPLATE_NAME "Led"
#define BLYNK_AUTH_TOKEN "gCfXwyjfFcl5FQDOb-YUE8AgBCbLV0zT"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

/************ WIFI ************/
char ssid[] = "Bassel";            // your WiFi SSID
char pass[] = "bassel2003";     // your WiFi password

/************ RGB PINS ************/
const int RED_PIN   = 25;
const int GREEN_PIN = 26;
const int BLUE_PIN  = 27;

/************ SYSTEM STATES ************/
bool systemOn = true;     // V0
bool autoMode = true;     // V4

int rManual = 0;
int gManual = 0;
int bManual = 0;

/************ FUNCTIONS ************/
void setColor(int r, int g, int b) {
  r = constrain(r, 0, 255);
  g = constrain(g, 0, 255);
  b = constrain(b, 0, 255);

  analogWrite(RED_PIN,   r);
  analogWrite(GREEN_PIN, g);
  analogWrite(BLUE_PIN,  b);
}

/************ BLYNK WRITE FUNCTIONS ************/
BLYNK_WRITE(V0) {   // Power ON / OFF
  systemOn = param.asInt();
  if (!systemOn) {
    setColor(0, 0, 0);
  }
}

BLYNK_WRITE(V4) {   // Auto / Manual
  autoMode = param.asInt();
}

BLYNK_WRITE(V1) { rManual = param.asInt(); }
BLYNK_WRITE(V2) { gManual = param.asInt(); }
BLYNK_WRITE(V3) { bManual = param.asInt(); }

/************ SETUP ************/
void setup() {
  Serial.begin(115200);

  pinMode(RED_PIN,   OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN,  OUTPUT);

  setColor(0, 0, 0);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  Serial.println("ESP32 RGB + Blynk Ready");
}

/************ LOOP ************/
void loop() {
  Blynk.run();

  // 🔹 AUTO MODE (Python → Serial)
  if (systemOn && autoMode && Serial.available()) {
    String line = Serial.readStringUntil('\n');
    line.trim();

    int c1 = line.indexOf(',');
    int c2 = line.indexOf(',', c1 + 1);
    if (c1 == -1 || c2 == -1) return;

    int r = line.substring(0, c1).toInt();
    int g = line.substring(c1 + 1, c2).toInt();
    int b = line.substring(c2 + 1).toInt();

    setColor(r, g, b);
  }

  // 🔹 MANUAL MODE (Blynk RGB)
  if (systemOn && !autoMode) {
    setColor(rManual, gManual, bManual);
  }
}
