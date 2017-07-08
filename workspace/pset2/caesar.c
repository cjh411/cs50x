#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[]){
    
    if (argc == 1 || argc>2){
        return 1;
    }else{
        int k = atoi(argv[1])%26;
        if(k<0){
            return 1;
        }else{
            printf("Plaintext: ");
            string inst = get_string();
            printf("Cipher Text: ");
            int n = 0;
            while(inst[n] != '\0'){
                if (inst[n] >= 65 && inst[n] <=90){
                    printf("%c", 65+(((inst[n]+k)%65)%26));
                }else if (inst[n] >= 97 && inst[n] <=122){
                    printf("%c", 97+(((inst[n]+k)%97)%26));
                }else{
                   printf("%c",inst[n]);
                }
                n++;
            }
        }
        
    }
    printf("%s","\n");
    return 0;
}