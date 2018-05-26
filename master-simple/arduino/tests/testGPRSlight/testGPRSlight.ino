/**************************************************************
 *
 * To run this tool you need StreamDebugger library:
 *   https://github.com/vshymanskyy/StreamDebugger
 *   or from http://librarymanager/all#StreamDebugger
 *
 * TinyGSM Getting Started guide:
 *   http://tiny.cc/tiny-gsm-readme
 *
 **************************************************************/

// Select your modem:
#define TINY_GSM_MODEM_SIM800


// Increase the buffer
#define TINY_GSM_RX_BUFFER 64

#include <TinyGsmClient.h>

const char apn[]  = "sunrise";
const char user[] = "";
const char pass[] = "";

// Set serial for debug console (to the Serial Monitor, speed 115200)
#define SerialMon Serial

// Set serial for AT commands (to the module)
// Use Hardware Serial on Mega, Leonardo, Micro
#define SerialAT Serial1


TinyGsm modem(SerialAT);
TinyGsmClient client(modem);

const char server[] = "www.cheminfo.org";
const char resource[] = "/hello.txt";

void setup() {
  SerialMon.begin(19200);
  delay(10);

  // Set GSM module baud rate
  SerialAT.begin(19200);
  delay(3000);
}

void loop() {
  // Restart takes quite some time
  // To skip it, call init() instead of restart()
  SerialMon.println("Initializing modem...");
  if (!modem.restart()) {
    delay(10000);
  }
  SerialMon.println("Restarted");
  if (!modem.waitForNetwork()) {
    delay(10000);
    return;
  }
    SerialMon.println("On network");
  if (!modem.gprsConnect(apn, user, pass)) {
    delay(10000);
    return;
  }
  SerialMon.println("GPRS connected");
  if (!client.connect(server, 80)) {
    SerialMon.println(" fail");
    delay(10000);
    return;
  }

  // Make a HTTP GET request:
  client.print("GET ");
  client.print(resource);
  client.println(" HTTP/1.0");
  client.print("Host: ");
  client.println(server);
  client.println("");

  // Skip all headers
  client.find("\r\n\r\n");

  // Read data
  unsigned long timeout = millis();
  unsigned long bytesReceived = 0;
  while (client.connected() && millis() - timeout < 10000L) {
    while (client.available()) {
      char c = client.read();
      SerialMon.print(c);
      bytesReceived += 1;
      timeout = millis();
    }
  }

  client.stop();
  modem.gprsDisconnect();
  SerialMon.println("GPRS disconnected");



    delay(10000);
}

