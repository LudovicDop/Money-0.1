//
//  moneyMainFunction.h
//  Money-0.1
//
//  Created by Ludovic Doppler on 06/08/2022.
//

#ifndef moneyMainFunction_h
#define moneyMainFunction_h

/* Mes fonctions */
void update(char *name);
char *strremove(char *str, const char *sub);
void addAmount(char *nameAccount,char *usr,int amountAdd,char *why);
char* concat(const char *s1, const char *s2);
char *reading(char *nameAccount,char *usr);
void initialisationNouveauCompte(char *name,char *amount);
void month(char *nom,char *date,int somme,char *name);

#endif /* moneyMainFunction_h */
