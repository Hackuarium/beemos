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

#include "TinyGSM/TinyGsmClient.h"

const char apn[]  = "gprs.swisscom.ch";  // sunrise or gprs.swisscom.ch
const char user[] = "";
const char pass[] = "";

#define SerialMon Serial

// Set serial for AT commands (to the module)
// Use Hardware Serial on Mega, Leonardo, Micro
#define SerialAT Serial1


TinyGsm modem(SerialAT);
TinyGsmClient client(modem);

const char server[] = "www.cheminfo.org";
const char resource[] = "/hello.txt?a=ABCDEFGHIJKLMNOPQRSTUVWXYZ&b=ABCDEFGHIJKLMNOPQRSTUVWXYZ&c=ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int success = 0;
int trial = 0;

void setup() {
  SerialMon.begin(19200);
  delay(10);

  SerialAT.begin(19200);
  delay(3000);
}

void loop() {
  delay(10000);
  trial++;
  long start = millis();
  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  SerialMon.println("Initializing modem...");
  if (!modem.restart()) {
    SerialMon.println("Could not restart");
    return;
  }

  SerialMon.println("Restarted");
  if (!modem.waitForNetwork()) {
    SerialMon.println("Could not join network");
    return;
  }

  SerialMon.println("On network");
  if (!modem.gprsConnect(apn, user, pass)) {
    SerialMon.println("Could not connect to GPRS");
    return;
  }

  SerialMon.println("GPRS connected");
  delay(5000);
  if (!client.connect(server, 80)) {
    SerialMon.println("Could not connect to server");
    return;
  }

  // Make a HTTP GET request:
  client.print("GET ");
  client.print(resource);
  client.println(" HTTP/1.0");
  client.print("Host: ");
  client.println(server);
  client.println("");

  delay(10);

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
        SerialMon.print(c);
        bytesReceived += 1;
        timeout = millis();
      }
    }
  }
  if (bytesReceived == 13) {
    success++;
  }
  SerialMon.println(bytesReceived);
  client.stop();
  modem.gprsDisconnect();
  SerialMon.println("GPRS disconnected");

  SerialMon.print("TOTAL TIME: ");
  SerialMon.print((millis() - start) / 1000);
  SerialMon.println(" s");
  SerialMon.print("Nb success: ");
  SerialMon.println(success);
  SerialMon.print("Nb failure: ");
  SerialMon.println(trial - success);


}

