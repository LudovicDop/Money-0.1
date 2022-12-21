//
//  moneyMainFunction.h
//  Money-0.1
//
//  Created by Ludovic Doppler on 06/08/2022.
//

#ifndef moneyMainFunction_h
#define moneyMainFunction_h

/*Initialisation de ma structure date*/
    typedef struct date date;
        struct date{
            int jour;
            int mois;
            int annee;
        };

/* Mes fonctions */
void update(char *name);
char *strremove(char *str, const char *sub);
void addAmount(char *nameAccount,char *usr,int amountAdd,char *why,int silentMode);
char* concat(const char *s1, const char *s2);
char *reading(char *nameAccount,char *usr,int silentMode);
void initialisationNouveauCompte(char *name,char *amount);
void month(char *nom,char *date,int somme, char *name);
void updateMonth(char *usr);
void mettreAJourLesAbonnementsMensuelsDates(char *usr,char *dateActuelle,char *dateMoisEtAnnee);
void strtokReverse(char *stringAModifSource,char *adresseDest,char delimiteur,int incluOuNonDelimiteur);
/* Mes fonctions */
date sepMonth(char *date);
int nombreDeJourDansUnMois(date moisSource);
int putInOrder(date dateDeDebut,date dateDeFin);
int diffMonth(date dateLaPlusAncienne,date dateLaPlusRecente);
int removeSomethingCurrentAccount(char *usr,int numeroDeLaTransactionASupr);
int removeSomethingAbonnement(char *usr,int numeroDeLAbonnement);

#endif /* moneyMainFunction_h */
