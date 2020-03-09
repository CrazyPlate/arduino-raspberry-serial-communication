extern int pinRead(int pin) {
  int value;
  if (pin <= 13 && pin > 1) {
    value = digitalRead(pin);
    return value;
  } else if (pin > 13 && pin <= 19) {
    value = analogRead(pin) + 10;
    return value;
  } else {
    return -1;
  }
}