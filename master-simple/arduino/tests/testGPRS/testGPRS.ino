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
  SerialMon.print("Initializing modem...");
  if (!modem.restart()) {
    delay(10000);
  }
  if (!modem.waitForNetwork()) {
    delay(10000);
    return;
  }
  
  if (!modem.gprsConnect(apn, user, pass)) {
    delay(10000);
    return;
  }

  if (!client.connect(server, 80)) {
    SerialMon.println(" fail");
    delay(10000);
    return;
  }

  // Make a HTTP GET request:
  client.print(String("GET ") + resource + " HTTP/1.0\r\n");
  client.print(String("Host: ") + server + "\r\n");
  client.print("Connection: close\r\n\r\n");

  // Skip all headers
  client.find("\r\n\r\n");

  // Read data
  unsigned long timeout = millis();
  unsigned long bytesReceived = 0;
  while (client.connected() && millis() - timeout < 10000L) {
    while (client.available()) {
      char c = client.read();
      //SerialMon.print(c);
      bytesReceived += 1;
      timeout = millis();
    }
  }

  client.stop();
  SerialMon.println("Server disconnected");

  modem.gprsDisconnect();
  SerialMon.println("GPRS disconnected");

  SerialMon.println();
  SerialMon.println("************************");
  SerialMon.print  (" Received: ");
  SerialMon.print(bytesReceived);
  SerialMon.println(" bytes");
  SerialMon.print  (" Test:     ");
  SerialMon.println((bytesReceived == 13) ? "PASSED" : "FAILED");
  SerialMon.println("************************");

  // Do nothing forevermore
  while (true) {
    delay(1000);
  }
}

