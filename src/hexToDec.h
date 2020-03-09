extern int hexToDec(char hexVal[]) {
    int len = strlen(hexVal);
    int base = 1; 
    int decVal = 0; 
      
    for (int i = len-1; i >= 0; i--) {    
        if (hexVal[i] >= '0' && hexVal[i] <= '9') {
            decVal += (hexVal[i] - 48)*base; 
            base = base * 16; 
        } else if ( hexVal[i] >= 'A' && hexVal[i] <= 'F') {
            decVal += (hexVal[i] - 55)*base;
            base = base*16; 
        } 
    } 
    return decVal; 
}