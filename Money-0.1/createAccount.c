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
#include <unistd.h>
#include "moneyMainFunction.h"

#if defined(__APPLE__) && defined(__MACH__)
#define PATH "/Users/ludovicdoppler/Desktop/Money-0.1/Money-0.1/account_file/"
#endif
#if defined(_WIN32) || defined(WIN32) 
#define PATH "C:/Users/Ludov/Desktop/Money-0.1/Money-0.1/account_file/"
#endif
#ifdef linux
#define PATH "/home/debian/Desktop/Money-0.1/Money-0.1/account_file/"
#endif

//#define PATH "/Users/ludovicdoppler/Desktop/Money-0.1/Money-0.1/account_file/"
char* concat(const char *s1,const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

/*Permet de mettre à jour la date de la dernière utilisation du logiciel dans configMonth*/
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

    time_t now = time(NULL); //Chargement de la date actuelle
    struct tm *tm_time = localtime(&now);
    char *tmp = malloc(sizeof(tmp));
    char test;

    rewind(fileMonth);
        
    fprintf(fileMonth,"Last update :%d/%d/%d #0# \n",tm_time->tm_mday,tm_time->tm_mon + 1,tm_time->tm_year+1900);
    fclose(fileMonth);
                                             
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

    }


    fclose(fileMonth);
    fclose(tmpFile);

    if(remove(finalNameParam) == 0){
       
    }else{
        exit(EXIT_FAILURE);
    }
    if(rename(tmpFinalNameParam,nomRename2) == 0){
       
    }else{
        exit(EXIT_FAILURE);
    }

}

void initialisationNouveauCompte(char *valeurDuCompte,char *name)
{
    char *extension = ".txt";
    char *nameAccount; //Nom du compte
    char *moneyValue; //Argent de base sur le compte
    char *finalName;
    char *finalNameParam;
    char buffer[200];
    char *cheminForSystem = malloc(200);
    finalName = concat(name, extension);
    moneyValue = valeurDuCompte; // Récupération des valeurs entrer par l'utilisateur
    nameAccount = finalName;
    strcpy(valeurDuCompte,concat(valeurDuCompte," #0#"));
    if(nameAccount)
    {
        FILE *fileAccount = NULL; //Creation du fichier vide
        char *chemin = PATH; //Chemin de stockage

        // strcpy(cheminForSystem,strtok(chemin,"/"));
        // snprintf(buffer,200,"cd %s && mkdir account_file",cheminForSystem);
        // printf("%s",buffer);
        // sleep(5);
        // system(buffer);
        
        char *s = concat(chemin, nameAccount); //Concaténation du chemin puis du nom du fichier en question
        fileAccount = fopen(s, "r"); //On lit le fichier pour voir s'il existe ou non
        
        printf("        ***Creation of the new account in progress...***\n");
        if(fileAccount == NULL) //Si le fichier n'existe pas
        {
            //fclose(fileAccount);
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

char *reading(char *nameAccount,char *usr,int silentMode)
{
    char *tmp = malloc(150);
    char *name = malloc(200);
    char *comment = malloc(200);
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
        while(fgets(tmp, 150, fileAccount) != NULL);
        char d[2] = " ";
        comment = strtok(tmp,d);

        if(silentMode == 0){
        printf("\n             *** Loading bank account *** \n\n");
        printf("             %s do you have => %s $\n\n",usr,tmp);
        }

        fclose(fileAccount); //MODIF ICI

        //free(name);

        return tmp;
        
    }
    
}

char *lectureDeLaDerniereLigne(char *usr){
    
    FILE *fileAccount = NULL;
    char *chemin = PATH;
    char *s = concat(chemin,usr);
    char delimiteur[5] = ".txt";
    strcpy(s,concat(s,delimiteur));
    char *tmp = malloc(500);
    
    fileAccount = fopen(s,"r");

    if(fileAccount){

        while(fgets(tmp,500,fileAccount) != NULL);
        fclose(fileAccount);

        /*Je retourne la dernière transaction*/
        return tmp;
    }
}

char *lectureDeLaDerniereLignePourAbonnement(char *usr){
    
    FILE *fileAccount = NULL;
    char *chemin = PATH;
    char *s = concat(chemin,usr);
    char extention[5] = ".txt";
    char param[13] = "_configMonth";
    strcpy(s,concat(s,param));
    strcpy(s,concat(s,extention));
    char *tmp = malloc(500);
    
    fileAccount = fopen(s,"r");

    if(fileAccount){

        while(fgets(tmp,500,fileAccount) != NULL);
        fclose(fileAccount);

        /*Je retourne la dernière transaction*/
        return tmp;
    }
}

void addAmount(char *nameAccount,char *usr,int amountAdd,char *why,int silentMode)
{

    char *name;
    name = nameAccount;
    
    char *tmp = reading(nameAccount, usr,silentMode);
    char *tmp2 = malloc(500);
    strcpy(tmp2,lectureDeLaDerniereLigne(usr));
    FILE *fileAccount = NULL;
    char *chemin = PATH; //Chemin de stockage
    char *s = concat(chemin, name);
    char delimiteur[2] = "#";
    char *numeroTransaction = malloc(500);
    char *numeroTransactionFinal = malloc(500);
    int tmpIntNumeroTransac = 0;

    fileAccount = fopen(s, "a");
    int x;
    sscanf(tmp, "%d",&x);
    int result = x + amountAdd;
    char c[100];
    sprintf(c, "%d",result);
    char *cNewWithReturn = concat("\n", c);
    
    /*Je recupère l'ancien numéro de transaction*/
    strcpy(numeroTransaction,tmp2);
    strtokReverse(numeroTransaction,numeroTransactionFinal,'#',1);
    strcpy(numeroTransactionFinal,strtok(numeroTransactionFinal,"#"));
    sscanf(numeroTransactionFinal,"%d",&tmpIntNumeroTransac);
    /*Et j'incrémente ce dernier*/
    tmpIntNumeroTransac++;

    /*Je recherche la date actuelle*/
    time_t now = time(NULL); 
    struct tm *tm_time = localtime(&now);
    
    fprintf(fileAccount, cNewWithReturn);

    fprintf(fileAccount, " =>  %d + %d ( Reason : %s ) %d/%d/%d #%d#",x,amountAdd,why,tm_time->tm_mday,tm_time->tm_mon + 1,tm_time->tm_year-100,tmpIntNumeroTransac);

    if(silentMode == 0){
    printf("         *** %s do you have now %d $ ***\n\n",usr,result);
    }
    fclose(fileAccount);

    free(tmp);
    free(tmp2);
    free(numeroTransaction);
    free(numeroTransactionFinal);
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

void month(char *nom,char *date,int somme, char *name){
        
        FILE *fileAccount = NULL;
        char *chemin = PATH; //Chemin de stockage
        char param[13] = "_configMonth";
        char *extension = ".txt";
        char *s = concat(chemin, name); //Concaténation du chemin puis du nom du fichier en question
        char *s2 = concat(s,param);
        char *s3 = concat(s2,extension);
        char *tmp2 = malloc(500);
        char *numeroTransaction = malloc(500);
        char *numeroTransactionFinal = malloc(500);
        int tmpIntNumeroTransac = 0;
        fileAccount = fopen(s3, "a"); //On lit le fichier pour voir s'il existe ou non
        strcpy(tmp2,lectureDeLaDerniereLignePourAbonnement(name));

        /*Je recupère l'ancien numéro de transaction*/
        strcpy(numeroTransaction,tmp2);
        strtokReverse(numeroTransaction,numeroTransactionFinal,'#',1);
        strcpy(numeroTransactionFinal,strtok(numeroTransactionFinal,"#"));
        sscanf(numeroTransactionFinal,"%d",&tmpIntNumeroTransac);
        /*Et j'incrémente ce dernier*/
        tmpIntNumeroTransac++;
        printf("ici : %s\n",numeroTransactionFinal);

         fprintf(fileAccount,"%s:%s:%d #%d# \n",nom,date,somme,tmpIntNumeroTransac);
         

         free(numeroTransaction);
         free(numeroTransactionFinal);
         free(tmp2);
         fclose(fileAccount);
}

int compteLesLignes(char *usr){
    FILE *fileAccount = NULL;
    char *chemin = PATH;
    char param[13] = "_configMonth";
    char *extension = ".txt";
    char *s = concat(chemin, usr); //Concaténation du chemin puis du nom du fichier en question
    char *s2 = concat(s,param);
    char *s3 = concat(s2,extension);
    fileAccount = fopen(s3,"r");
    char tmp = fgetc(fileAccount);
    char *string;
    while(tmp != ':'){
        tmp = fgetc(fileAccount);
    }

    rewind(fileAccount);

    int newline_counter = 0;

    char ch = getc(fileAccount);
    do{
    if (ch == '\n') ++newline_counter;
    } while ((ch = getc(fileAccount)) != EOF);

    fclose(fileAccount);

    return newline_counter;

}

    typedef struct date2 date2;
    struct date2{
        char day[100];
        char month[100];
        char year[100];
        char name[100];
        char amount[100];
        char numeroDeTransaction[100];
    };

    date2 test[100];

/*Cette fonction permet de mettre à jour les abonnements mensuels dans le compte correspondant*/
void addSubscription(char *nomUtilisateur){
    /*Déclaration de mes variables*/
    FILE *file = NULL; //crash ici si j'ajoute un autre FILE
    FILE *fileToAdd = NULL;
    date dateDeDepart,dateDeFin;
    char *chemin = malloc(sizeof(PATH));
    strcpy(chemin,PATH);
    char extensionDuFichierConfigMonthTxt[18] = "_configMonth.txt";
    char extensionDuFichierToAdd[100] = ".txt";
    char cheminFinalVersConfigMonth[1000];
    char cheminFinalVersToAdd[1000];
    char currentDate[20];
    char abonnementDate[20];
    char bufferDateActuelle[200];
    char bufferAbonnementMensuel[200];
    char ch = getc(file);
    char separateur[2] = ":";
    int verificationDesLignes = compteLesLignes(nomUtilisateur);
    int mois;
    int calculDuMultiplicateurDePaye;
    int convertirTestAmountEnInt = 0;
    char pseudoTxt[100];
    char phraseTypeAddAbonnement[500];
    char bufferMonth[30];
    /*Je concat nomUtilisateur avec l'extension du fichier configMonth.txt*/

    strcpy(cheminFinalVersConfigMonth,concat(nomUtilisateur,extensionDuFichierConfigMonthTxt));
    strcpy(cheminFinalVersConfigMonth,concat(chemin,cheminFinalVersConfigMonth));

    strcpy(cheminFinalVersToAdd,concat(nomUtilisateur,extensionDuFichierToAdd));
    strcpy(cheminFinalVersToAdd,concat(chemin,extensionDuFichierToAdd));

    strcpy(pseudoTxt,concat(nomUtilisateur,extensionDuFichierToAdd));

    /*Je passe en mode lecture sur mon fichier X_configMonth.txt*/
    file = fopen(cheminFinalVersConfigMonth,"r");

    /*Si il n'y a aucun problème de lecture alors je continue*/
    if(file){

        /*On parcourt le fichier x_configMonth.txt avec le char ch, tant qu'il n'est pas égal à ":" on continue*/
        while(ch != ':'){
            ch = getc(file);
        }
        /*Lecture de la première ligne de mon  fichier X_configMonth.txt pour obtenir la date actuelle (en partant de ":") et stocker dans buffer*/
        fgets(bufferDateActuelle,100,file);

        /*Tant que i est < au nombres d'abonnements on continue*/
        for(int i = 1;i<verificationDesLignes;i++){

            /*On parcourt le fichier x_configMonth.txt avec le char ch, tant qu'il n'est pas égal à ":" on continue*/
            /*On actualise la variable ch pour éviter de stocker le ":" précédent et pouvoir passer dans le boucle while*/
            ch = getc(file);

            while(ch != ':'){
                
                ch = getc(file);
            }

            /*On s'occupe maintenant de récupérer les abonnements mensuels on passe donc à la ligne suivante*/
            fgets(bufferAbonnementMensuel,100,file);

            /*J'enlève ce qui viens après les ":" pour récupérer uniquement la date*/
            strcpy(bufferAbonnementMensuel,strtok(bufferAbonnementMensuel,separateur));
            
            /*On récupère les dates des différents abonnements pour les séparers dans une variable date*/
            dateDeDepart = sepMonth(bufferDateActuelle);
            dateDeFin = sepMonth(bufferAbonnementMensuel);

            /*On récupère les mois de différence entre la date actuelle et la dernière actualisation de l'abonnement X*/
            mois = putInOrder(dateDeDepart,dateDeFin);
            sscanf(test[i].amount,"%d",&convertirTestAmountEnInt);

            calculDuMultiplicateurDePaye = mois * convertirTestAmountEnInt;
    
            sprintf(bufferMonth,"%d",mois);

            strcpy(phraseTypeAddAbonnement,"Ceci viens de votre abonnement ");
            strcpy(phraseTypeAddAbonnement,concat(phraseTypeAddAbonnement,test[i].name));
            strcpy(phraseTypeAddAbonnement,concat(phraseTypeAddAbonnement," pour une durée de "));
            strcpy(phraseTypeAddAbonnement,concat(phraseTypeAddAbonnement,bufferMonth));
            strcpy(phraseTypeAddAbonnement,concat(phraseTypeAddAbonnement," mois!"));
            
            /*On ajoute une somme d'argent dans le compte current uniquement si le montant est différent de 0*/
            if(calculDuMultiplicateurDePaye != 0)
                addAmount(pseudoTxt,nomUtilisateur,calculDuMultiplicateurDePaye,phraseTypeAddAbonnement,1);
        }
    }
    /*Si il y a un problème de lecture je ferme le programme*/
    else{
        exit(EXIT_FAILURE);
    }

    /*Je ferme le fichier*/
    fclose(fileToAdd);
    fclose(file);

    /*Je libère la mémoire*/
    free(chemin);
    
    char *dateSend = malloc(150);
    char *dateMoisEtAnnee = malloc(150);

    dateSend = strcpy(dateSend,strtok(bufferDateActuelle," \n"));
    strcpy(dateMoisEtAnnee,dateSend);
    dateMoisEtAnnee = strcpy(dateMoisEtAnnee,strtok(dateMoisEtAnnee,"/"));
    /*J'appel ma fonction pour mettre le fichier x_configMonth.txt à jour au niveau des dates des abonnements mensuels*/
    mettreAJourLesAbonnementsMensuelsDates(nomUtilisateur,dateSend,dateMoisEtAnnee);

    free(dateSend);
    free(dateMoisEtAnnee);
}

void updateMonth(char *usr){

    FILE *fileAccount,*fileTmp = NULL;
    char *chemin = PATH;
    char param[14] = "_configMonth";
    char paramTmp[17] = "_configMonthTmp";
    char *extension = ".txt";


    
    char *s =  malloc(100);
    char *sTmp =  malloc(100);
    char *s2 = malloc(100);
    char *s2Tmp =  malloc(100);
    char *s3 =  malloc(100);
    char *s3Tmp =  malloc(100);

    s = concat(chemin, usr); //Concaténation du chemin puis du nom du fichier en question
    sTmp = concat(chemin, usr);
    s2 = concat(s,param);
    s2Tmp = concat(s, paramTmp);
    s3 = concat(s2,extension);
    s3Tmp = concat(s2Tmp, extension);
    
    fileAccount = fopen(s3,"r");
    fileTmp = fopen(s3Tmp, "w");
    char tmp = fgetc(fileAccount);

    while(tmp != ':'){
        tmp = fgetc(fileAccount);
    }
  
    char tmp2[100];
    fgets(tmp2,100,fileAccount);
    
    char d[2] = "/";
    int i = 0;
    char *day = strtok(tmp2,d);
    rewind(fileAccount);
    while(tmp != '/' || i != 1){
        tmp = fgetc(fileAccount);
        if(tmp == '/'){
            i++;
        }
    }
    int dayInt;
    sscanf(day,"%d",&dayInt);

     fgets(tmp2,100,fileAccount);
    char *month = strtok(tmp2,d);

    rewind(fileAccount);
    while(tmp != '/' || i != 3){
        tmp = fgetc(fileAccount);
        if(tmp == '/'){
            i++;
        }
    }

    int monthInt;
    sscanf(month,"%d",&monthInt);

     fgets(tmp2,100,fileAccount);
     char *year = strtok(tmp2,d);

    int yearInt;
    sscanf(year,"%d",&yearInt);
    
    rewind(fileAccount);
    fgets(tmp2,100,fileAccount);
    
    int verificationDesLignes1 = compteLesLignes(usr);
    
    if(verificationDesLignes1 > 1){
         
        int nameI = 0;
        
        for(int i = 1;i < verificationDesLignes1+1;i++){
            fgets(tmp2,100,fileAccount);
            char *nameStr = strtok(tmp2,":");
            strcpy(test[i].name,nameStr);
        }
        
        rewind(fileAccount);
        
        
        int z = 0;
        char *testt;
        int dayI = 0;
        testt = fgets(tmp2,100,fileAccount);
        
        
        while(tmp != EOF){
            
            while(tmp != ':'){
                tmp = fgetc(fileAccount);
            }
            dayI++;
            testt = fgets(tmp2,100,fileAccount);
            tmp = fgetc(fileAccount);
            char *dayStr = strtok(tmp2,"/");
            strcpy(test[dayI].day,dayStr);
            
        }
        
        rewind(fileAccount);
        char *fgetsMonth = fgets(tmp2,100,fileAccount);
        int tmpMonth = 0;
        tmp = fgetc(fileAccount);
        int monthI = 0;
        
        while(tmp != EOF){
            tmpMonth = 0;
            while(tmp != '/' && tmpMonth < 2){
                tmp = fgetc(fileAccount);
                if(tmp == '/'){
                    tmpMonth++;
                }
            }
            monthI++;
            fgetsMonth = fgets(tmp2,100,fileAccount);
            tmp = fgetc(fileAccount);
            char *monthStr = strtok(tmp2,"/");
            strcpy(test[monthI].month,monthStr);
        }
        
        rewind(fileAccount);
        char *fgetsYear = fgets(tmp2,100,fileAccount);
        int tmpYear = 0;
        tmp = fgetc(fileAccount);
        int yearI = 0;
        
        while(tmp != EOF){
            tmpYear = 0;
            while(tmp != '/' || tmpYear < 2){
                tmp = fgetc(fileAccount);
                if(tmp == '/'){
                    tmpYear++;
                }
            }
            yearI++;
            fgetsYear = fgets(tmp2,100,fileAccount);
            tmp = fgetc(fileAccount);
            char *yearStr = strtok(tmp2,":");
            strcpy(test[yearI].year,yearStr);
        }
        
        rewind(fileAccount);
        char *fgetsAmount = fgets(tmp2,100,fileAccount);
        int tmpAmount = 0;
        tmp = fgetc(fileAccount);
        int amountI = 0;
     
        while(amountI < verificationDesLignes1-1){
            tmpAmount = 0;
            while(tmp != ':' || tmpAmount < 2){
                tmp = fgetc(fileAccount);
                if(tmp == ':'){
                    tmpAmount++;
                }
            }
            amountI++;

            fgetsAmount = fgets(tmp2,100,fileAccount);

            char *amountStr = strtok(tmp2," ");
            strcpy(test[amountI].amount,amountStr);
        }
        /*Dans cette partie je recherche le numero de la transaction*/
        rewind(fileAccount);
        
        char *tmpfgets = malloc(100);
        char *fgetsNumeroDeLaTransaction = malloc(100);
        char *buffer = malloc(100);
        char *numeroDeTransactionFinal = malloc(100);
        char tmpNumeroDeLaTransaction;
    
        for(int i = 0;i < verificationDesLignes1;i++){

            tmpNumeroDeLaTransaction = ' ';
            
            while(tmpNumeroDeLaTransaction != '#'){

                tmpNumeroDeLaTransaction = fgetc(fileAccount);
            }

        fgetsNumeroDeLaTransaction = fgets(buffer,100,fileAccount);
        strcpy(numeroDeTransactionFinal,strtok(buffer,"#"));

        strcpy(test[i].numeroDeTransaction,numeroDeTransactionFinal);
        }
        
        free(tmpfgets);
        free(fgetsNumeroDeLaTransaction);
        free(buffer);
        free(numeroDeTransactionFinal);

        fclose(fileAccount);
        fclose(fileTmp);
        
        printf("Nombre d'abonnements mensuels : %d\n\n",verificationDesLignes1-1);

        fileAccount = fopen(s3,"r");
        rewind(fileAccount);
        fgets(tmp2, 100,fileAccount);
       
        for(int i = 1;i<verificationDesLignes1;i++){
            
            int xDay[100];
            sscanf(test[i].day,"%d",&xDay[i]);
            int xMonth[100];
            sscanf(test[i].month,"%d",&xMonth[i]);
            int xYear[100];
            sscanf(test[i].year,"%d",&xYear[i]);
            int xAmount[100];
            sscanf(test[i].amount,"%d",&xAmount[i]);

            printf("** Subscription number %s : %d/%d/%d %s:%d$ **\n",test[i].numeroDeTransaction,xDay[i],xMonth[i],xYear[i],test[i].name,xAmount[i]);
            
    
        }
    }

        fclose(fileAccount);
     
        free(s); 
        free(sTmp);    
        free(s2);  
        free(s2Tmp);   
        free(s3);
        free(s3Tmp);   

        /*J'appel ma fonction addSubscription pour pouvoir mettre à jour les abonnements mensuels dans le compte correspondant*/
        addSubscription(usr);
}

void mettreAJourLesAbonnementsMensuelsDates(char *usr,char *dateActuelle,char *dateMoisEtAnnee){
    /*Déclaration de mes variables*/
    FILE *fileMonth,*fileMonthTmp;
    date dateDeDepart,dateDeFin;
    char chemin[58] = PATH;
    char extension[18] = "_configMonth.txt";
    char extensionTmp[21] = "_configMonthTmp.txt";
    char cheminFinalPourFopen[100];
    char cheminFinalPourFopenTmp[100];
    char buffer[151];
    char *nameTmpConfigMonth;
    char delimiteur[2] = ":";
    char *fgetsBuffer;
    char *currentDateLastUpdate;
    char *dateTmpConfigMonth;
    char *moneyTmpConfigMonth;
    char *finalTmpConfigMonth;
    int moisSiJeDoisMettreAJour;
    char *nomFinalNew = malloc(100);
    char ch;
    int i = 0;

    /*Initialisation de mes variables*/
    /*Chemin pour accéder au fichier X_configMonth.txt*/
    strcpy(cheminFinalPourFopen,concat(chemin,usr));
    strcpy(cheminFinalPourFopen,concat(cheminFinalPourFopen,extension));
    strcpy(nomFinalNew,concat(usr,extension));
    /*Chemin pour accéder au fichier X_configMonthTmp.txt*/
    strcpy(cheminFinalPourFopenTmp,concat(chemin,usr));
    strcpy(cheminFinalPourFopenTmp,concat(cheminFinalPourFopenTmp,extensionTmp));

    fgetsBuffer = malloc(150);
    nameTmpConfigMonth = malloc(150);
    dateTmpConfigMonth = malloc(150);
    moneyTmpConfigMonth = malloc(150);
    finalTmpConfigMonth = malloc(150);
    currentDateLastUpdate = malloc(150);

    /*Début de la lecture au fichier X_configMonth.txt*/
    fileMonth = fopen(cheminFinalPourFopen,"r");

    /*Début de la lecture du fichier X_configMonthTmp.txt*/
    fileMonthTmp = fopen(cheminFinalPourFopenTmp,"w+");

    /*Si la lecture du fichier X_configMonth.txt est valide alors je continue*/
    if(fileMonth && fileMonthTmp){
        fgetsBuffer = fgets(buffer,150,fileMonth);
        fprintf(fileMonthTmp,fgetsBuffer);
        int i = 0;
        while((fgetsBuffer = fgets(buffer,150,fileMonth)) != NULL){
            i++;
            nameTmpConfigMonth = strtok(fgetsBuffer,delimiteur);
            currentDateLastUpdate = strtok(NULL,delimiteur);
            moneyTmpConfigMonth = strtok(NULL,"\n");

            dateDeDepart = sepMonth(dateActuelle);
            dateDeFin = sepMonth(currentDateLastUpdate);

            moisSiJeDoisMettreAJour = putInOrder(dateDeDepart,dateDeFin);

            finalTmpConfigMonth = strcpy(finalTmpConfigMonth,concat(nameTmpConfigMonth,":"));

            /*Je mets la date mois/année à jour pour éviter de recharger un prix supplémentaire*/
            if(moisSiJeDoisMettreAJour>0){

                char *stringAModifDate = malloc(sizeof(dateActuelle));
                char *dest = malloc(sizeof(currentDateLastUpdate));
                char delimiteur = '/';

                strcpy(stringAModifDate,dateActuelle);
                strtokReverse(stringAModifDate,dest,delimiteur,0);

                finalTmpConfigMonth = strcpy(finalTmpConfigMonth,concat(finalTmpConfigMonth,test[i].day));
                finalTmpConfigMonth = strcpy(finalTmpConfigMonth,concat(finalTmpConfigMonth,dest));
            }
            /*Si il n'y a pas de mois de différence alors je ne change rien*/
            else{
                finalTmpConfigMonth = strcpy(finalTmpConfigMonth,concat(finalTmpConfigMonth,currentDateLastUpdate));
            }
            /*Fin de la chaine pour integrer la somme d'argent pour les abonnements*/
            finalTmpConfigMonth = strcpy(finalTmpConfigMonth,concat(finalTmpConfigMonth,":"));
            finalTmpConfigMonth = strcpy(finalTmpConfigMonth,concat(finalTmpConfigMonth,moneyTmpConfigMonth));
            finalTmpConfigMonth = strcpy(finalTmpConfigMonth,concat(finalTmpConfigMonth,"\n"));

            /*Je rédige dans le tmp file*/
            fprintf(fileMonthTmp,finalTmpConfigMonth);     

        }
    }
    else{
        exit(EXIT_FAILURE);
    }

    /*Je libère la mémoire*/
    free(fgetsBuffer);
    /*Je ferme le fichier*/
    fclose(fileMonthTmp);
    fclose(fileMonth);
    /*Je remplace le fichier month par tmp*/

    if(remove(cheminFinalPourFopen) == 0){

    }else{
        //exit(EXIT_FAILURE);
        printf("echec! remove\n");
    }
    if(rename(cheminFinalPourFopenTmp,cheminFinalPourFopen) == 0){
   
    }else{
        //exit(EXIT_FAILURE);
        printf("echec! rename %s %s\n",cheminFinalPourFopenTmp,cheminFinalPourFopen);
    }
}
/*Cette fonction permet de supprimer une transaction cibler dans le compte courant de l'utilisateur X*/
int removeSomethingCurrentAccount(char *usr,int numeroDeLaTransactionASupr){

    /*Déclaration de mes variables*/
    FILE *fileAccount,*fileAccountTmp = NULL;
    char extension[5] = ".txt";
    char chemin[100] = PATH;
    char cheminFinal[200];
    char cheminFinalTmp[200];
    char buffer[500] = "";
    char tmpName[7] = "__tmp";
    char *valeurASoustraireEnChar = malloc(500);
    int valeurASoustraire;
    char *nomApresRenameNormal = malloc(20);
    char *finalNameWithExtension = malloc(100);
    char msgDeSuppression[100] = "Suppression de la transaction ";
    char numeroDeLaTransactionEnChar[100];

    /*J'initialise le chemin vers le bon fichier*/
    strcpy(cheminFinal,concat(chemin,usr));
    strcpy(cheminFinal,concat(cheminFinal,extension));

    strcpy(finalNameWithExtension,concat(usr,extension));

    sprintf(numeroDeLaTransactionEnChar,"%d",numeroDeLaTransactionASupr);
    strcpy(msgDeSuppression,concat(msgDeSuppression,numeroDeLaTransactionEnChar));


    strcpy(cheminFinalTmp,concat(chemin,usr));
    strcpy(cheminFinalTmp,concat(cheminFinalTmp,tmpName));
    strcpy(cheminFinalTmp,concat(cheminFinalTmp,extension));

    strcpy(nomApresRenameNormal,concat(usr,extension));
    /*Je passe le fichier en mode lecture seul*/
    fileAccount = fopen(cheminFinal,"r");
    fileAccountTmp = fopen(cheminFinalTmp,"w");
    /*Je vérifie que le fichier est correction ouvert*/
    if(fileAccount && fileAccountTmp){
        
        char *tmp = malloc(100);
        char *tmpNext = malloc(100);
        char *numero = malloc(100);

        sprintf(numero,"%d",numeroDeLaTransactionASupr);
        strcpy(numero,concat("#",numero));
        strcpy(numero,concat(numero,"#"));

        while(strstr(buffer,numero) == NULL && tmp != NULL){

            fprintf(fileAccountTmp,buffer);
            tmp = fgets(buffer,500,fileAccount);
            if(strstr(buffer,numero) != NULL){
                break;
            }
        }
        
        if(tmp == NULL){
            fclose(fileAccount);
            fclose(fileAccountTmp);
            remove(cheminFinalTmp);
            printf("\nTransaction introuvable!\n");
            return 1;
        }

        printf("Vous avez selectionne la transaction suivante : \n%s\n",buffer);
        printf("Supression en cours...\n");
        sleep(1.5);
        printf("3\n");
        sleep(1);
        printf("2\n");
        sleep(1);
        printf("1\n");
        sleep(1);
        printf("Votre transaction a bien ete supprimer!\n\n");
        strcpy(valeurASoustraireEnChar,strtok(buffer,"("));
        strtokReverse(valeurASoustraireEnChar,valeurASoustraireEnChar,'+',1);

        sscanf(valeurASoustraireEnChar,"%d",&valeurASoustraire);
        valeurASoustraire = valeurASoustraire * -1;

        addAmount(finalNameWithExtension,usr,valeurASoustraire,msgDeSuppression,0);
        
        tmp = fgets(buffer,500,fileAccount);
        tmp = fgets(buffer,500,fileAccount);

        while(tmp != NULL && buffer != NULL){

            tmp = fgets(buffer,500,fileAccount);
            fprintf(fileAccountTmp,buffer);
        }
        
        fclose(fileAccount);
        fclose(fileAccountTmp);
        remove(cheminFinal);
        rename(cheminFinalTmp,cheminFinal);

        free(valeurASoustraireEnChar);
        free(nomApresRenameNormal);
        free(finalNameWithExtension);
        free(tmp);
        free(tmpNext);
        free(numero);
        
        return 0;
    }else{

        printf("error\n");
    }
}

int removeSomethingAbonnement(char *usr,int numeroDeLAbonnement){

    /*Déclaration de mes variables*/
    FILE *fileMonth, *fileMonthTmp = NULL;
    char extension[18] = "_configMonth.txt";
    char extensionTmp[21] = "_configMonthTmp.txt";
    char chemin[100] = PATH;
    char cheminFinal[100];
    char cheminFinalTmp[100];
    char buffer[100];
    char *bufferNumeroAbonnementEnChar = malloc(100);
    char *tmp = malloc(200);
    char nouveauNomApresRename[50];
    /*Initialisation du chemin vers le fichier des abonnements mensuels*/
    strcpy(cheminFinal,concat(chemin,usr));
    strcpy(cheminFinal,concat(cheminFinal,extension));

    strcpy(cheminFinalTmp,concat(chemin,usr));
    strcpy(cheminFinalTmp,concat(cheminFinalTmp,extensionTmp));

    /*Ouverture en mode lecture seul*/
    fileMonth = fopen(cheminFinal,"r");
    fileMonthTmp = fopen(cheminFinalTmp,"w");


    sprintf(bufferNumeroAbonnementEnChar,"%d",numeroDeLAbonnement);
    strcpy(bufferNumeroAbonnementEnChar,concat("#",bufferNumeroAbonnementEnChar));
    strcpy(bufferNumeroAbonnementEnChar,concat(bufferNumeroAbonnementEnChar,"#"));
    
    strcpy(nouveauNomApresRename,concat(usr,extension));

    if(numeroDeLAbonnement == 0){
        fclose(fileMonth);
        fclose(fileMonthTmp);
        printf("Vous ne pouvez pas supprimer ceci !\n");
        return 1;
    }
    /*Je vérifie si le fichier est bien ouvert*/
    if(fileMonth && fileMonthTmp){
        
        while(strstr(buffer,bufferNumeroAbonnementEnChar) == NULL && tmp != NULL){

            fprintf(fileMonthTmp,buffer);
            tmp = fgets(buffer,500,fileMonth);

            if(strstr(buffer,bufferNumeroAbonnementEnChar) != NULL){
                break;
            }

        }

        if(strstr(buffer,"#0#")){
            fclose(fileMonth);
            fclose(fileMonthTmp);
            remove(cheminFinalTmp);
            printf("Il est impossible de supprimer ce fichier!\n");
            return 1;
        }

        if(tmp == NULL){
            fclose(fileMonth);
            fclose(fileMonthTmp);
            remove(cheminFinalTmp);
            printf("\nAbonnement introuvable!\n");
            return 1;
        }

        printf("Vous avez selectionne l'abonnement suivant : \n%s\n",buffer);
        printf("Supression en cours...\n");
        sleep(1.5);
        printf("3\n");
        sleep(1);
        printf("2\n");
        sleep(1);
        printf("1\n");
        sleep(1);
        printf("Votre transaction a bien ete supprimer!\n\n");

        tmp = fgets(buffer,500,fileMonth);

        while(tmp != NULL){

            fprintf(fileMonthTmp,buffer);
            tmp = fgets(buffer,500,fileMonth);
            
        }

        fclose(fileMonthTmp);
        fclose(fileMonth);

        remove(cheminFinal);
        rename(cheminFinalTmp,cheminFinal);
        return 0;
    }else{

        printf("echec");
    }

}

int validationTransaction(char *usr,int numeroDeLaTransactionAverifier){

    /*Déclaration de mes variables*/
    FILE *fileAccount,*fileTmp = NULL;
    char extension[6] = ".txt";
    char tmpFile[6] = "_tmp";
    char finalTmpPath[150];
    char chemin[200] = PATH;
    char cheminFinal[250];
    char *tmp = malloc(250);
    char *buffer = malloc(150);
    char tmpChar;
    char haschtag[2] = "#";
    int verificationDuNombreDeLigne = compteLesLignes(usr);
    char *numeroDeTransaction = malloc(200);
    char *transactionDejaVerifier = malloc(200);

    /*Initialisation de mes variables*/
    strcpy(cheminFinal,concat(chemin,usr));
    strcpy(cheminFinal,concat(cheminFinal,extension));

    sprintf(numeroDeTransaction,"%d",numeroDeLaTransactionAverifier);
    strcpy(numeroDeTransaction,concat(haschtag,numeroDeTransaction));
    strcpy(numeroDeTransaction,concat(numeroDeTransaction,haschtag));

    strcpy(finalTmpPath,concat(chemin,usr));
    strcpy(finalTmpPath,concat(finalTmpPath,tmpFile));
    strcpy(finalTmpPath,concat(finalTmpPath,extension));

    strcpy(transactionDejaVerifier,concat(numeroDeTransaction,"!"));

    fileAccount = fopen(cheminFinal,"r");
    fileTmp = fopen(finalTmpPath,"w");

    if(numeroDeLaTransactionAverifier == 0){

        printf("Impossible de verifier cette transaction!\n");
        fclose(fileAccount);
        fclose(fileTmp);
        remove(finalTmpPath);
        return 1;
    }

    if(fileAccount && fileTmp){

            tmp = fgets(buffer,200,fileAccount);
            while(strstr(buffer,numeroDeTransaction) == NULL && tmp != NULL){
            
                fprintf(fileTmp,buffer);
                tmp = fgets(buffer,200,fileAccount);
            }

            if(strstr(buffer,transactionDejaVerifier) != NULL){
                printf("La transaction est deja verifier !\n");
                fclose(fileAccount);
                fclose(fileTmp);
                remove(finalTmpPath);
                return 1;
            }

            if(tmp == NULL){

                printf("Le numero de cette transaction n existe pas!\n");
                fclose(fileAccount);
                fclose(fileTmp);
                remove(finalTmpPath);
                return 1;
        
            }

            strcpy(buffer,strtok(buffer,"\n"));
            strcpy(buffer,concat(buffer,"!"));
            strcpy(buffer,concat(buffer,"\n"));
            fprintf(fileTmp,buffer);
            
            tmp = fgets(buffer,200,fileAccount);
            while(tmp != NULL && buffer != NULL){
                tmp = fgets(buffer,200,fileAccount);
                fprintf(fileTmp,buffer);
            }
        
           printf("ici : %s\n",buffer);    

           fclose(fileAccount);
           fclose(fileTmp);
           remove(cheminFinal);
           rename(finalTmpPath,cheminFinal);

           free(tmp);
           free(buffer);
           free(numeroDeTransaction);

           return 0;  
    }else{

        printf("echec\n");
        return 1;
    }
}





