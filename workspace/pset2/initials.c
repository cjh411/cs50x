#include <stdio.h>
#include <string.h>
#include <cs50.h>

int main(void){
    string inst;
    printf("What is your name?");
    inst  = get_string();
    int n = 0;
    char initils[10];
    int initind = 0;
    int prchspc = 1;
    while(inst[n]!='\0'){
        if(inst[n] == ' '){
            n++;
            prchspc = 1;
        }else if(prchspc == 1){
            initils[initind] = inst[n];
            n++;
            initind++;
            prchspc = 0;
        }else{
            n++;
        }
    }
    
    printf("%s\n",initils);
}