/**************************************************************

   To run this tool you need StreamDebugger library:
     https://github.com/vshymanskyy/StreamDebugger
     or from http://librarymanager/all#StreamDebugger

   TinyGSM Getting Started guide:
     http://tiny.cc/tiny-gsm-readme

 **************************************************************/

// Select your modem:
#define TINY_GSM_MODEM_SIM800


// Increase the buffer
#define TINY_GSM_RX_BUFFER 64

#include "libino/TinyGSM/TinyGsmClient.h"

const char apn[]  = "gprs.swisscom.ch";  // sunrise or gprs.swisscom.ch
const char user[] = "";
const char pass[] = "";


TinyGsm modem(Serial1);
TinyGsmClient client(modem);

const char server[] = "www.cheminfo.org";
const char resource[] = "/hello.txt?a=ABCDEFGHIJKLMNOPQRSTUVWXYZ&b=ABCDEFGHIJKLMNOPQRSTUVWXYZ&c=ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int success = 0;
int trial = 0;


NIL_WORKING_AREA(waThreadGSM, 200);
NIL_THREAD(ThreadGSM, arg) {
  Serial1.begin(19200);
  nilThdSleepMilliseconds(6000);


  while (TRUE) {
    nilThdSleepMilliseconds(3000);
    trial++;
    long start = millis();
    Serial.print(1);
    if (!modem.restart()) {
      Serial.print(0);
      return;
    }
       Serial.print(2);
    if (!modem.waitForNetwork()) {
        Serial.print(0);
      return;
    }

    Serial.println("On network");
    if (!modem.gprsConnect(apn, user, pass)) {
      return;
    }

    nilThdSleepMilliseconds(5000);
    if (!client.connect(server, 80)) {
      return;
    }

    // Make a HTTP GET request:
    client.print("GET ");
    client.print(resource);
    client.println(" HTTP/1.0");
    client.print("Host: ");
    client.println(server);
    client.println("");

    nilThdSleepMilliseconds(10);

    boolean inHeader = true;
    int headerCounter = 0;

    // Read data
    unsigned long timeout = millis();
    unsigned long bytesReceived = 0;
    while (client.connected() && millis() - timeout < 10000L) {
      while (client.available()) {
        char c = client.read();
        if (inHeader) {
          if (c == '\r' || c == '\n') { // looking for \r\n\r\n
            headerCounter++;
            if (headerCounter == 4) inHeader = false;
          }
          else headerCounter = 0;
        } else {
          Serial.print(c);
          bytesReceived += 1;
          timeout = millis();
        }
      }
    }
    if (bytesReceived == 13) {
      success++;
    }
    Serial.println(bytesReceived);
    client.stop();
    modem.gprsDisconnect();

    Serial.print("TOTAL TIME: ");
    Serial.print((millis() - start) / 1000);
    Serial.println(" s");
    Serial.print(F("Nb success: "));
    Serial.println(success);
    Serial.print(F("Nb failure: "));
    Serial.println(trial - success);
  }
}

