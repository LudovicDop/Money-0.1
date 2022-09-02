//
//  createAccount.c
//  Money-0.1
//
//  Created by Ludovic Doppler on 06/08/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define PATH "/Users/ludovicdoppler/Desktop/Money-0.1/Money-0.1/account_file/"
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void initialisationNouveauCompte(char *nomDuCompte,char *valeurDuCompte,char *name)
{
    char *nameAccount; //Nom du compte
    char *moneyValue; //Argent de base sur le compte
    
    nameAccount = nomDuCompte; // Récupération des valeurs entrer par l'utilisateur
    moneyValue = valeurDuCompte; // Récupération des valeurs entrer par l'utilisateur
    
    if(nameAccount)
    {
        FILE *fileAccount = NULL; //Creation du fichier vide
        char *chemin = PATH; //Chemin de stockage
        char *s = concat(chemin, nameAccount); //Concaténation du chemin puis du nom du fichier en question
        fileAccount = fopen(s, "r"); //On lit le fichier pour voir s'il existe ou non
        fclose(fileAccount);
        printf("        ***Creation of the new account in progress...***\n");
        if(fileAccount == NULL) //Si le fichier n'existe pas
        {
            fileAccount = fopen(s, "a"); //Creation du fichier s'il n'existe pas
            fclose(fileAccount);
            if(fileAccount)
            {
                printf("                    **Well, welcome %s !**\n\n",name);
                
                fileAccount = fopen(s, "w");
                fprintf(fileAccount, valeurDuCompte);
                fclose(fileAccount);
            }
            else{
                exit(EXIT_FAILURE);
            }
        }
        else
        {
            printf("          *** Error this account already exists! ***\n");
        }
        
    }
}

const char* reading(char *nameAccount,char *usr)
{
    char *name;
    char *tmp = malloc(sizeof(tmp));
    name = nameAccount;
    
    FILE *fileAccount = NULL;
    char *chemin = PATH; //Chemin de stockage
    char *s = concat(chemin, name);
    
    fileAccount = fopen(s, "r");
    
    char *comment;
    while(fgets(tmp, 100, fileAccount) != NULL);
    
    strtok_r(tmp, " ", &comment);
    printf("            *** Loading bank account *** \n\n");
    printf("             %s do you have => %s €\n\n",usr,tmp);
    
    return tmp;
}

void addAmount(char *nameAccount,char *usr,int amountAdd,char *why)
{
    char *name;
    name = nameAccount;
    char **tmp = reading(nameAccount, usr);
    
    FILE *fileAccount = NULL;
    char *chemin = PATH; //Chemin de stockage
    char *s = concat(chemin, name);
    
    //reading(nameAccount, usr);
    
    fileAccount = fopen(s, "a");
    int x;
    sscanf(tmp, "%d",&x);
    int result = x + amountAdd;
    char c[100];
    sprintf(c, "%d",result);
    char *cNewWithReturn = concat("\n", c);
    //fileAccount = fopen(s, "w");

    
    fprintf(fileAccount, cNewWithReturn); //HERE
    fprintf(fileAccount, " =>  %d + %d ( Reason : %s )",x,amountAdd,why);
    printf("         *** %s do you have now %d ***\n\n",usr,result);
    fclose(fileAccount);
    
}

char *strremove(char *str, const char *sub) {
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}

