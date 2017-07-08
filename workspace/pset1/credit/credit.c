#include <stdio.h>


int main(void){
    int inint;
    int digits = 0;
    int evencumsum = 0;
    int oddcumsum = 0;
    printf("What is your credit card number?");
    scanf("%d",&inint);

    while(inint > 0){
        
        int rem = inint%10;
        
        if (digits%2 == 0){
            evencumsum+=rem;
        }else{
            int tmp = rem*2;
            while(tmp > 0){
                oddcumsum+=(tmp%10);
                tmp/=10;
            }
        }
        
        digits++;
        inint/=10;
    }
    
    if((oddcumsum+evencumsum)%10 == 0){
        printf("Credit Card Number is Valid!");
    }else{
        printf("Womp Womp: Credit Card Number in Invalid!");
    }
    
    

}