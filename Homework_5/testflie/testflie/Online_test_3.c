\n1606	
const int _begini = 0, _endi = +18, testfg = -6; const char lowera = 'a', lowerz = 'z', capitalZ = 'Z';  int random_name1, random_name2;  int fibic(int a){     const int return1 = 2;     if(a > return1){         return (fibic(a-1) + fibic(a-2));     }     else{         return (1);     } }  int abs(int kk){     if(kk < 0){         return (-kk);     }     return (kk); }  char plus(){     char plussy;     plussy = '+';     return (plussy); }  int sum4(int a, int b, int c, int d){     return (a + b + c + d); }  void main() {     const int maxFibic = 13;     const char chartimes = '*';     int cal, toPrinti;     char outch, underline;         scanf(toPrinti, outch, cal);  printf("\n", toPrinti);     if(cal){         printf("input cal != 0, abs(cal) = ", abs(cal));     }       if(cal >= maxFibic + 1){         cal = maxFibic;     }  underline = '_';     printf(outch);     printf(plus());     printf("+-*/", underline);      cal = abs(cal);     printf("abs(-7) = ", abs(-7));     printf("fibic val = ",fibic(cal));      printf("(expect 91)sum4=", sum4(1, sum4(2, sum4(3, 4, 5, 6), 7, 8), 9, sum4(10, 11, 12, 13)));     if(sum4(1, 2, 3, 4)!=10){         printf("1 + 2 + 3 + 4 != 10");     }     else{         printf("1 + 2 + 3 + 4 == 10");     }     if(lowerz - lowera == capitalZ - 'A'){   printf("Congratulations!");  }  else{   printf("Wrong");  } }  ??
2	input cal != 0, abs(cal) = 99		
3	0		
4	+		
5	+-*/_		
6	abs(-7) = 7		
7	fibic val = 233		
8	(expect 91)sum4=91		
9	1 + 2 + 3 + 4 == 10		
10	Congratulations!


const int _begini = 0, _endi = +18, testfg = -6; 
const char lowera = 'a', lowerz = 'z', capitalZ = 'Z';
int random_name1, random_name2;
int fibic(int a){    
    const int return1 = 2;     
    if(a > return1){         
        return (fibic(a-1) + fibic(a-2));    
    } else{         
        return (1);     
    } 
}  

int abs(int kk){     
    if(kk < 0){         
        return (-kk);     
    }     
    return (kk); 
}  

char plus(){     
    char plussy;     
    plussy = '+';     
    return (plussy); 
}  

int sum4(int a, int b, int c, int d){    
    return (a + b + c + d); 
}  

void main() {     
    const int maxFibic = 13;     
    const char chartimes = '*';     
    int cal, toPrinti;     
    char outch, underline;         
    scanf(toPrinti, outch, cal);  
    printf("\n", toPrinti);     
    if(cal){         
        printf("input cal != 0, abs(cal) = ", abs(cal));    
    }       
    if(cal >= maxFibic + 1){         
        cal = maxFibic;     
    }  
    underline = '_';     
    printf(outch);     
    printf(plus());     
    printf("+-*/", underline);      
    cal = abs(cal);     
    printf("abs(-7) = ", abs(-7));     
    printf("fibic val = ",fibic(cal));      
    printf("(expect 91)sum4=", sum4(1, sum4(2, sum4(3, 4, 5, 6), 7, 8), 9, sum4(10, 11, 12, 13)));     
    if(sum4(1, 2, 3, 4)!=10){         
        printf("1 + 2 + 3 + 4 != 10");     
    } else{         
        printf("1 + 2 + 3 + 4 == 10");     
    }     
    if(lowerz - lowera == capitalZ - 'A'){  
        printf("Congratulations!");  
    }  else{  
        printf("Wrong");  
    }


}