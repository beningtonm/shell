#include <stdio.h>

int main(){
    // Initialize String buffer
    char line[1024];

     printf("Mini Cat Program (Ctrl-D to quit) \n");


    while(1){
        printf("Enter a string... \n");
        printf("minicat: ");
        if(fgets(line, sizeof(line), stdin) == NULL){
            puts("");
            break;
        }
        puts(line);
    }

}