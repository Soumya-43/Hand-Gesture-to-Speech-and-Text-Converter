#include <Wire.h>
#include <MPU6050.h>
#include <WiFi.h>
#include <WiFiManager.h>
#include <Firebase_ESP_Client.h>

// FLEX PINS
#define F1 34
#define F2 32

// Firebase
#define API_KEY "FIREBASE_API"
#define DATABASE_URL "FIREBASE_DATABASE_URL"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

MPU6050 mpu;

// FLEX BASELINE (only for flex1)
int b1;

// STATES
int s1 = 0;   // toggle flex1
int s2 = 0;   // threshold flex2

bool r1 = true;

// SENTENCE SYSTEM
String sentence = "";
String lastStableWord = "";

// ===== TIMING SYSTEM =====
String candidateWord = "";
unsigned long candidateTimer = 0;

String stableWord = "";
unsigned long stableTimer = 0;

bool gestureLocked = false;

const int HOLD_TIME = 400;
const int DEBOUNCE_TIME = 150;

// ===== FLEX1 (TOGGLE ±20) =====
void updateFlex1(int val){
  if (val < 12000) s1 = 0;
  else s1 = 1;
}

// ===== FLEX2 UPDATE (THRESHOLD) =====
void updateFlex2(int val) {
  if (val!=0 && val < 1300) s2 = 1;
  else s2 = 0;
}

void setup() {
  Serial.begin(115200);

  Wire.begin(21,22);
  mpu.initialize();

  WiFiManager wm;
  wm.autoConnect("Gesture_Device_AP");

  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  Firebase.signUp(&config, &auth, "", "");
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  delay(3000);

  // CALIBRATION
  Serial.println("Calibrating Flex1...");
  delay(2000);

  b1 = analogRead(F1);
  Serial.print("Baseline F1: ");
  Serial.println(b1);
}

void loop() {

  // ===== FLEX READ =====
  int f1 = analogRead(F1);
  int f2 = analogRead(F2);

  updateFlex1(f1);
  updateFlex2(f2);

  // ===== MPU READ =====
  int16_t ax, ay, az;
  int16_t gx, gy, gz;

  mpu.getMotion6(&ax,&ay,&az,&gx,&gy,&gz);

  String ori;

  if (ay > 8000) ori = "RIGHT";
  else if (ay < -8000) ori = "LEFT";
  else if (ax > 8000) ori = "UP";
  else if (ax < -8000) ori = "DOWN";
  else ori = "FLAT";

  String word = "";

  // ===== WORD MAPPING =====

  if (!s1 && !s2) { //00
    if (ori == "FLAT") word = "DEAR";
    else if (ori == "RIGHT") word = "I";
    else if (ori == "LEFT") word = "GO";
    else if (ori == "UP") word = "HELP";
    else if (ori == "DOWN") word = "THERE";
  }

  else if (s1 && !s2) {   //10
    if (ori == "FLAT") word = "SOME";
    // else if (ori == "RIGHT") word = "THERE";
    else if (ori == "LEFT") word = "GIVE";
    else if (ori == "UP") word = "ME";
    else if (ori == "DOWN") word = "GIVE";
  }

  else if (!s1 && s2) {    //01
    if (ori == "FLAT") word = "SEND";
    else if (ori == "RIGHT") word = "NEED";
    else if (ori == "LEFT") word = "PLEASE";
    else if (ori == "UP") word = "ME";
    else if (ori == "DOWN") word = "FOOD";
  }

  else if (s1 && s2) {     //11
    if (ori == "RIGHT") word = "MEDS";
    else if (ori == "LEFT") word = "MONEY";
    else if (ori == "UP") word = "PLEASE";
    else if (ori == "DOWN") word = "WATER";
  }

  // ===== SERIAL DEBUG =====
  Serial.print("Flex Raw: ");
  Serial.print(f1); Serial.print(" ");
  Serial.print(f2);

  Serial.print(" | States: ");
  Serial.print(s1); Serial.print(" ");
  Serial.print(s2);

  Serial.print(" | Orientation: ");
  Serial.print(ori);

  Serial.print(" | Word: ");
  Serial.println(word);

  if (word != candidateWord) {
    candidateWord = word;
    candidateTimer = millis();
  }

  if ((millis() - candidateTimer) > DEBOUNCE_TIME) {

    if (candidateWord != stableWord) {
      stableWord = candidateWord;
      stableTimer = millis();
    }
  }

  if (!gestureLocked && (millis() - stableTimer) > HOLD_TIME && stableWord != lastStableWord) {

    Serial.println("Accepted: " + stableWord);

    if (stableWord == "SEND") {

      Firebase.RTDB.setString(&fbdo, "/gesture/word", sentence);
      Serial.println("SENTENCE: " + sentence);

      sentence = "";
    }
    else {
      sentence += stableWord + " ";
    }

    lastStableWord = stableWord;
    gestureLocked = true;
  }

  if (stableWord != lastStableWord) {
    gestureLocked = false;
  }

  delay(400);
}
