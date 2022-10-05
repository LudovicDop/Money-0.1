//
//  createAccount.c
//  Money-0.1
//
//  Created by Ludovic Doppler on 06/08/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <assert.h>
#include <stdbool.h>


#if defined(__APPLE__) && defined(__MACH__)
#define PATH "/Users/ludovicdoppler/Desktop/Money-0.1/Money-0.1/account_file/"
#else
#define PATH "C:/Users/Ludov/Desktop/Money-0.1/Money-0.1/account_file/"
#endif

//#define PATH "/Users/ludovicdoppler/Desktop/Money-0.1/Money-0.1/account_file/"
char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}


void update(char *name){
    FILE *fileMonth, *tmpFile = NULL;
    char *chemin = PATH;
    char *s = concat(chemin,name);
    char param[13] = "_configMonth";
    char tmpParam[13] = "___temp"; //TMP
    char *finalNameParam = NULL;
    char *tmpFinalNameParam = NULL;
    char *extension = ".txt";
    char *nomRename = concat(s,param);
    char *nomRename2 = concat(nomRename,extension);
    char *finalName = concat(s,param);
    char *tmpFinalName = concat(s,tmpParam); //TMP
    finalNameParam = concat(finalName,extension);
    tmpFinalNameParam = concat(tmpFinalName,extension);
    fileMonth = fopen(finalNameParam,"a");
    fclose(fileMonth);
    fileMonth = fopen(finalNameParam,"r+");
    //tmpFile = fopen(tmpFinalNameParam, "w");

    time_t now = time(NULL); //Chargement de la date actuelle
    struct tm *tm_time = localtime(&now);
    char *tmp = malloc(sizeof(tmp));
    char test;

    rewind(fileMonth);
        
    fprintf(fileMonth,"Last update : %d/%d/%d ",tm_time->tm_mday,tm_time->tm_mon + 1,tm_time->tm_year-100);
    //ici bug @  
    fclose(fileMonth);

    //first second

    char curr;
    int del,line_number = 0;

    del = 3;

    fileMonth = fopen(finalNameParam,"r");
    tmpFile = fopen(tmpFinalNameParam, "w");

    curr = getc(fileMonth);
    
    if(curr!=EOF){
            int i = 0;
           while(curr != 'L'){
            i++;
            curr = getc(fileMonth);
           
        }
    }
        
    while (curr != EOF)
    {


            putc(curr,tmpFile);
            curr = getc(fileMonth);
            if(curr == EOF) break;

       /* if(del == line_number){
            line_number++;
            printf("tac");
        }*/
    }


    fclose(fileMonth);
    fclose(tmpFile);

    //if(remove(finalNameParam) == 0) printf("=> %s avec succes!",finalNameParam) ;
    remove(finalNameParam);
    rename(tmpFinalNameParam,nomRename2);
    



}

void initialisationNouveauCompte(char *valeurDuCompte,char *name)
{
    char *extension = ".txt";
    char *nameAccount; //Nom du compte
    char *moneyValue; //Argent de base sur le compte
    char *finalName = NULL;
    char *finalNameParam = NULL;
    finalName = concat(name, extension);
    moneyValue = valeurDuCompte; // Récupération des valeurs entrer par l'utilisateur
    nameAccount = finalName;
    
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
                update(name);
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

char *reading(char *nameAccount,char *usr)
{
    char *tmp = malloc(sizeof(tmp));
    char *name = malloc(sizeof(name));

    name = nameAccount;
   
    FILE *fileAccount = NULL;
    char *chemin = PATH; //Chemin de stockage
    char *s = concat(chemin, name);
    
    
    fileAccount = fopen(s, "r");
    
    if(fileAccount == NULL){
        printf("             *** Nothing has been found ! *** \n\n");
        return NULL;
    }
    else{
        while(fgets(tmp, 100, fileAccount) != NULL);
        char d[] = " ";
        char *comment = strtok(tmp,d);
        printf("             *** Loading bank account *** \n\n");
        printf("             %s do you have => %s $\n\n",usr,tmp);
        return tmp;
        
    }
    



   //free(tmp);
  // free(name);
}

void addAmount(char *nameAccount,char *usr,int amountAdd,char *why)
{
    
    char *name;
    name = nameAccount;
    
    char *tmp = reading(nameAccount, usr);
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
    
    time_t now = time(NULL); //Chargement de la date actuelle
    struct tm *tm_time = localtime(&now);
    
    fprintf(fileAccount, cNewWithReturn); //HERE
    
    fprintf(fileAccount, " =>  %d + %d ( Reason : %s ) %d/%d/%d",x,amountAdd,why,tm_time->tm_mday,tm_time->tm_mon + 1,tm_time->tm_year-100);
    printf("         *** %s do you have now %d $ ***\n\n",usr,result);

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








