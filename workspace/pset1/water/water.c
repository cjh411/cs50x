#include <stdio.h>

int main(void){
    
    int time;
    printf("How long was your shower ");
    scanf("%d",&time);
    int bott = time*12;
    printf("You used %d bottles of water",bott);
}