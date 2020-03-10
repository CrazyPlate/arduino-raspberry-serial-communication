extern void RGBWrite(int frameLength, char inputData[], char charHolder[], int pin) {
    int incomingDataR;
    int incomingDataG;
    int incomingDataB;

    for (int i = 0; i < frameLength - 14; i++) {
        inputData[i] = charHolder[i+6];
    }
    incomingDataR = (int)atoi(inputData);

    for (int i = 0; i < frameLength - 14; i++) {
        inputData[i] = charHolder[i+9];
    }
    incomingDataG = (int)atoi(inputData);

    for (int i = 0; i < frameLength - 14; i++) {
        inputData[i] = charHolder[i+12];
    }
    incomingDataB = (int)atoi(inputData);
    
    analogWrite(3, incomingDataR);
    analogWrite(5, incomingDataG);
    analogWrite(6, incomingDataB);
}