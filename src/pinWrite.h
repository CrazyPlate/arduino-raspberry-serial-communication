extern void pinWrite(int frameLength, char inputData[], char charHolder[], int pin) {
  int incomingData;
  boolean isAnalogValue;
  if ((int)charHolder[5] == 65) {
    isAnalogValue = true;
    digitalWrite(13,HIGH);
  } else if ((int)charHolder[5] == 68) {
    isAnalogValue = false;
  }
  for (int i = 0; i < frameLength - 8; i++) {
    inputData[i] = charHolder[i+6];
  }
  incomingData = (int)atoi(inputData);
  if (isAnalogValue) {
    analogWrite(pin, incomingData);
  } else {
    digitalWrite(pin, incomingData);
  }
}