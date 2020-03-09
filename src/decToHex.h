extern void decToHex(int n, char *result) {    
    char hexNum[100];
      
    int i = 0;
    while (n != 0) {
        int temp  = 0; 
        temp = n % 16; 

        if (temp < 10) { 
            hexNum[i] = temp + 48; 
            i++; 
        } else { 
            hexNum[i] = temp + 55; 
            i++; 
        }
        n = n/16; 
    }  
    result[0] = hexNum[1];
    result[1] = hexNum[0];
    result[2] = '\0';
} 