int wireSlaveCommand(uint8_t command, long value) {
  int weight = getParameter(PARAM_WEIGHT);
  switch (command) {
    case 52: // BA - define the empty level
      setAndSaveParameter(PARAM_WEIGHT_OFFSET, weight);
      return weight;
    case 53: // BB - define the weight one kg over the tare
      setAndSaveParameter(PARAM_WEIGHT_FACTOR, weight - getParameter(PARAM_WEIGHT_OFFSET));
      return weight;
    case 54: // BC - low level
      setAndSaveParameter(PARAM_WEIGHT_FACTOR, weight - getParameter(PARAM_WEIGHT_OFFSET));
      return weight;
    case 55: // BD - high level
      setAndSaveParameter(PARAM_WEIGHT_MAX, weight);
      return weight;
  }
  return ERROR_VALUE;
}
