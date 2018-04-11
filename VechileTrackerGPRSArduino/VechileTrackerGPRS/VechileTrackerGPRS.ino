#include <TinyGPS++.h>
#include <gprs.h>

#define SOFT_RX 10
#define SOFT_TX 11

#define IP "103.14.120.48"// thingspeak.com ip

GPRS gprs(SOFT_RX, SOFT_TX);
TinyGPSPlus gps;

void setup() {
  Serial.begin(9600);
  Serial.print("Smart Vechile Traker\r\n");
  gprs.preInit(9600);
  while(0 != gprs.init()) {
      delay(1000);
      Serial.println("GSM ERROR");
  }

  while(!gprs.join("airtelgprs.com")) {  //change "cmnet" to your own APN
      Serial.println("gprs join network error");
      delay(2000);
  }
  // successful DHCP
  Serial.print("IP Address is ");
  Serial.println(gprs.getIPAddress());

  Serial.println(F("Latitude   Longitude   Date       Time     Speed"));
  Serial.println(F("(deg)      (deg)                           (KMH)"));
  Serial.println(F("------------------------------------------------"));
}

void uploadData(){  
  if(0 == gprs.connectTCP(IP, 80)) {
      Serial.println("connection success");
  }else{
      Serial.println("connection error");
  }

  String cmd = "GET http://peastech.in/sensor.php?";
  cmd += "lat=";   
  cmd += gps.location.lat();
  cmd += "&lag=";   
  cmd += gps.location.lng();
  cmd += "\r\n\r\n";
  cmd += "Host: peastech.in\r\n";
  cmd += "Accept: text/html,application\r\n";
  cmd += "Referer: http://peastech.in/sensor.php?json";
  cmd += "lat=";   
  cmd += gps.location.lat();
  cmd += "&lag=";   
  cmd += gps.location.lng();
  cmd += "\r\n";
  cmd += "User-Agent: Mozilla/5.0 (Windows NT 10.0; WOW64; rv:49.0) Gecko/20100101 Firefox/49.0\r\n\r\n";
  

  char buff[100];
  cmd.toCharArray(buff, 100);

  Serial.println("Sending...");
  gprs.sendTCPData(buff);
  //gprs.serialDebug();
  gprs.closeTCP();
  gprs.shutTCP();
}

void loop() {
  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
  printDateTime(gps.date, gps.time);
  printFloat(gps.speed.kmph(), gps.speed.isValid(), 6, 2);

  Serial.println();
  
  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
    Serial.println(F("No GPS data received: check wiring"));
  
  uploadData();

  delay(5000);
}

static void smartDelay(unsigned long ms){
  unsigned long start = millis();
  do{
    while (Serial.available())
      gps.encode(Serial.read());
  } while (millis() - start < ms);
}

static void printFloat(float val, bool valid, int len, int prec){
  if (!valid){
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else{
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len){
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartDelay(0);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t){
  if (!d.isValid()){
    Serial.print(F("********** "));
  }
  else{
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    Serial.print(sz);
  }
  
  if (!t.isValid()){
    Serial.print(F("******** "));
  }
  else{
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serial.print(sz);
  }

  //printInt(d.age(), d.isValid(), 5);
  smartDelay(0);
}

static void printStr(const char *str, int len){
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartDelay(0);
}

