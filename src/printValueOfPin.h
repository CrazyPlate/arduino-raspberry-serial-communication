extern int printValueOfPin(int valueOfPin, int crcCalc) {
    if (valueOfPin >= 10) {
    Serial.print("A");
    crcCalc += 65;

    valueOfPin -= 10;

    int thousands = valueOfPin / 1000;
    valueOfPin %= 1000;
    int hundreds = valueOfPin / 100;
    valueOfPin %= 100;
    int tens = valueOfPin / 10;
    valueOfPin %= 10;
    int unity = valueOfPin;

    Serial.print(thousands);
    crcCalc += 48 + thousands;
    Serial.print(hundreds);
    crcCalc += 48 + hundreds;
    Serial.print(tens);
    crcCalc += 48 + tens;
    Serial.print(unity);
    crcCalc += 48 + unity;                
    } else if (valueOfPin < 10) {
    Serial.print("D");
    crcCalc += 68;
    Serial.print(valueOfPin);
    crcCalc += valueOfPin + 48;
    }
    return crcCalc;
}