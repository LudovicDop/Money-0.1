//
//  main.c
//  Money-0.1
//
//  Created by Ludovic Doppler on 06/08/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include "moneyMainFunction.h"
#include <time.h>
#define MAX_NAME_SIZE 256
#define FLUSH while(getchar() != '\n');
int main(int argc, const char * argv[]) {

    char choice = 'Q';
    do  {
        printf("Do you want to create a new account ? (Y/N) or leave with (Q) \n");
        scanf("%s",&choice);
        if(choice == 'Y' || choice == 'y'){
            char name[50];
            char amount[1000];
            
            printf("What's your name ? \n");
            scanf("%s",name);
            
            printf("How many money do you have today ? \n");
            scanf("%s",amount);
            
            initialisationNouveauCompte(amount,name);
        }
        if(choice == 'N' || choice == 'n')
        {
            char login[100];
            char *finalName = NULL;
            char *extension = ".txt";
            printf("Login : \n");
            scanf("%s",login);
            finalName = concat(login, extension);
            reading(finalName,login);
            char choice2 = ' ';
            printf("Do you want to add something ? (Y/N)\n");
            scanf("%s",&choice2);
            if(choice2 == 'y' || choice2 == 'Y'){
                int money;
                char *why = malloc(sizeof(why));
                printf("How much :  ");
                scanf("%d", &money);
                FLUSH
                printf("Comment : ");

                if(fgets(why, MAX_NAME_SIZE, stdin)){
                  
                    strremove(why, "\n");
                   
		    
                }else{
                    printf("error");
                }
                
                addAmount(finalName,login,money,why);
              
                
            }
        }

    }while((choice != 'Q' && choice != 'q'));
    
    
    exit(EXIT_SUCCESS);
    
    
    
    return 0;
}
