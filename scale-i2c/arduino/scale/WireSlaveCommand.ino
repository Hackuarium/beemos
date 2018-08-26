int wireSlaveCommand(uint8_t command, long value) {
  int weight = getParameter(PARAM_WEIGHT);
  switch (command) {
    case 16: // Q - define the empty level
      setAndSaveParameter(PARAM_WEIGHT_OFFSET, weight);
      return weight;
    case 17: // R - define the weight one kg over the tare
      setAndSaveParameter(PARAM_WEIGHT_FACTOR, weight - getParameter(PARAM_WEIGHT_OFFSET));
      return weight;
    case 18: // S - low level
      setAndSaveParameter(PARAM_WEIGHT_FACTOR, weight - getParameter(PARAM_WEIGHT_OFFSET));
      return weight;
    case 19: // T - high level
      setAndSaveParameter(PARAM_WEIGHT_MAX, weight);
      return weight;
  }
  return 0;
}
