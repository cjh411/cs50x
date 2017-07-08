#include <stdio.h>
#include <string.h>
int main(void){
    int ht;
    printf("What is the pyramid height? ");
    scanf("%d",&ht);
    while(0>ht || 23<ht){
        printf("Please enter a number between 0 and 23");
        scanf("%d",&ht);
    }

        
    for(int i = 0; i < ht; i++){
        int thresh = ht - i-1;
        for(int j = 0; j<ht; j++){
            if(j < thresh ){
                printf(" ");
            }else{
                printf("#");
            }
        }
        printf("  ");
        
        for(int j = 0; j<ht; j++){
            if(j < i+1 ){
                printf("#");
            }else{
                printf(" ");
            }
        }
        printf("\n");
 
    
    }
}
