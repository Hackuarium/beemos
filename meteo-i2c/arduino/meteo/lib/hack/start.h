void checkParameters();

void start() {
  Serial.begin(9600);
  setupParameters();
  checkParameters(); // setup automatically the default parameter after install boot loader
  nilSysBegin();
    #ifdef WIRE_SLAVE
    startWireSlave();
    #endif
}