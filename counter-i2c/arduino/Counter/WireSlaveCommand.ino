int wireSlaveCommand(uint8_t command, long value) {
  switch (command) {
    case 52: // BA
      resetCounter();
      return 1;
  }
  return 0;
}
