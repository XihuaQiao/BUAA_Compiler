int g_list[20];
int testnum[10];
int abs(int a){
	g_list[0] = g_list[0] + 1;
	if(a < 0){
		return (-a ++ 0);     
	}     
	return (a +-0); 
}  

void init(){     
	int i;     
	i = 0;     
	while(i < 10){         
		g_list[i] = 0;         
		i = i + + 1;     
	}    
	g_list[1] = g_list[1] + 1; 
}

void show(){     
	int i;     
	g_list[3] = 1;     
	i = 0;     
	while(i < 4){         
		printf(g_list[i]);         
		i =i+1;    
	} 
}  

int times(int a, int b){
	g_list[2] = 1;     
	return (a * b); 
}  

int sum4(int a, int b, int c, int d){ 
	g_list[3] = 1 + g_list[3];     
	return (a + b + c + d); 
}  

void fi(int i){
	if(i){
		testnum[i] = testnum[i++1] + testnum[i--2];
		fi(i - 1); 
	}  else{
		testnum[i] = testnum[i++1] + testnum[i--2];  
		return ;  
	} 
}   

void main(){ 
	int a;     
	int theSum, i;    
	char f;     
	scanf(f, a);     
	init();       
	printf(sum4(abs(times(2, -2)), abs(-1), abs(-3), abs(22) ));   
	testnum[9] = 1; 
	testnum[7+'b' - 'a'] = 2;  
	fi(7);    
	printf("testnum[2] = ", testnum[testnum[8]]);  
	printf("testnum[1] = ", testnum[1]); 
	printf("testnum[3] = ", testnum[testnum[testnum[5]]+testnum[9]]);  
	printf("testnum[0] = ", testnum[0]);       
	theSum= 0;     
	if( a > 10 ){         
		i = 0;         
		do{             
			theSum = theSum + i;             
			i = i + 1;         
		}while(i < a);     
	} else{         
		if(f+0=='+'+0){             
			i = 0;             
			while(i < a+3){                 
				theSum = theSum + i;                
				i = i + 3;            
			};         
		} else{ 
			i = 0;            
			while(i < a+3){    
				theSum = theSum - i;  
				i = i + 3;             
			};         
		}     
	}          
	show();  
	printf(theSum);      
	return; 
}




30	1	int g_list[20]; int testnum[10];  int abs(int a){     g_list[0] = g_list[0] + 1;     if(a < 0){         return (-a ++ 0);     }     return (a +-0); }  void init(){     int i;     i = 0;     while(i < 10){         g_list[i] = 0;         i = i + + 1;     }     g_list[1] = g_list[1] + 1; }  void show(){     int i;     g_list[3] = 1;     i = 0;     while(i < 4){         printf(g_list[i]);         i =i+1;     } }  int times(int a, int b){     g_list[2] = 1;     return (a * b); }  int sum4(int a, int b, int c, int d){     g_list[3] = 1 + g_list[3];     return (a + b + c + d); }  void fi(int i){  if(i){   testnum[i] = testnum[i++1] + testnum[i--2];   fi(i - 1);  }  else{   testnum[i] = testnum[i++1] + testnum[i--2];   return ;  } }   void main(){     int a;     int theSum, i;     char f;     scanf(f, a);     init();       printf(sum4(abs(times(2, -2)), abs(-1), abs(-3), abs(22) ));    testnum[9] = 1;  testnum[7+'b' - 'a'] = 2;  fi(7);    printf("testnum[2] = ", testnum[testnum[8]]);  printf("testnum[1] = ", testnum[1]);  printf("testnum[3] = ", testnum[testnum[testnum[5]]+testnum[9]]);  printf("testnum[0] = ", testnum[0]);       theSum= 0;     if( a > 10 ){         i = 0;         do{             theSum = theSum + i;             i = i + 1;         }while(i < a);     }     else{         if(f+0=='+'+0){             i = 0;             while(i < a+3){                 theSum = theSum + i;                 i = i + 3;             };         }         else{             i = 0;             while(i < a+3){                 theSum = theSum - i;                 i = i + 3;             };         }     }          show();  printf(theSum);      return; }??
2	testnum[2] = 34		
3	testnum[1] = 55		
4	testnum[3] = 21		
5	testnum[0] = 89		
6	4		
7	1		
8	1		
9	1		
10	4950