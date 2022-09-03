//
//  moneyMainFunction.h
//  Money-0.1
//
//  Created by Ludovic Doppler on 06/08/2022.
//

#ifndef moneyMainFunction_h
#define moneyMainFunction_h

/* Mes fonctions */

void initialisationNouveauCompte(char *nomDuCompte,char *name,char *amount);
char* concat(const char *s1, const char *s2);
void reading(char *nameAccount,char *usr);
void addAmount(char *nameAccount,char *usr,int amountAdd,char *why);
char *strremove(char *str, const char *sub);


#endif /* moneyMainFunction_h */
