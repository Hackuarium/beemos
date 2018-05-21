void checkParameters();
void initParameters();

void start() {
  Serial.begin(9600);
  setupParameters();
  checkParameters(); // setup automatically the default parameter after install boot loader
  initParameters();
  nilSysBegin();
    #ifdef THR_WIRE_SLAVE
    startWireSlave();
    #endif
}