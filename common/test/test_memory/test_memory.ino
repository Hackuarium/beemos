#include <SST.h>
#include <SPI.h>
#include <avr/io.h>

SST sst = SST('F', 4); // A3 is F4


boolean wr;



#define ADDRESS_BEG   0x000000
#define ADDRESS_MAX   0x080000  // http://www.sst.com/dotAsset/40498.pdf&usd=2&usg=ALhdy294tEkn4s_aKwurdSetYTt_vmXQhw
#define SECTOR_SIZE       4096 // anyway the size of the sector is also hardcoded in the library !!!!

#define LINE_SIZE 64 // should be a divider of the SECTOR_SIZE


// ======================================================================================= //

void setup()
{
  // waiting 10s before starting the FORMATTING
  delay(10000);
  Serial.begin(9600);
  setupMemory(sst);
  delay(50);
  Serial.print("FlashID: ");
  sst.printFlashID(&Serial);

  Serial.println('Starting formatting');





  for (long i = 0; i < ADDRESS_MAX; i++) {
    if (i % SECTOR_SIZE == 0) { // should erase the sector
      Serial.print("Formatting sector: ");
      Serial.println(i / SECTOR_SIZE);
      sst.flashSectorErase(i / SECTOR_SIZE);
    }

    if (true) { // do we want to write and read the flash ?
      if (i % LINE_SIZE == 0) printLine(i);
      if (i % LINE_SIZE == 0) writeLine(i);
      if (i % LINE_SIZE == 0) printLine(i);
    }
  }
}

// ======================================================================================= //



void loop()
{

}


void printLine(long address) {

  Serial.print("Read Address: ");
  Serial.print(address);
  Serial.print(" : ");
  sst.flashReadInit(address);
  for (byte j = 0; j < LINE_SIZE; j++) {
    byte oneByte = sst.flashReadNextInt8();
    Serial.print(oneByte, HEX);
    Serial.print(" ");
    address++;
  }
  sst.flashReadFinish();
  Serial.println("");
}

void writeLine(long address) {
  Serial.print("Write Address: ");
  Serial.print(address);
  Serial.print(" : ");
  sst.flashWriteInit(address);
  for (byte j = 0; j < LINE_SIZE; j++) {
    sst.flashWriteNextInt8(j);
    Serial.print(j, HEX);
    Serial.print(" ");
    address++;
  }
  sst.flashReadFinish();
  Serial.println("");
}



void setupMemory(SST sst) {
  SPI.begin();
  
  sst.init();
}











