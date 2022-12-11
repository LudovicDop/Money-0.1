#include <stdlib.h>
#include <stdio.h>

/*
L'objectif de cette fonction est la même que pour un strtok classique mais dans le sens inverse
 c'est à dire supprimer ce qui viens avant le delimiteur
*/
void strtokReverse(char *stringAModifSource,char *adresseDest,char delimiteur){
        
        /*Déclaration & Initialisation de mes variables*/
        char *stringAModifSourceCar = malloc(sizeof(stringAModifSource));
        char *adresseDestCar = malloc(sizeof(adresseDest));

        /*On place les pointeurs sur la premier caractère*/
        stringAModifSourceCar = &stringAModifSource[0];
        adresseDestCar = &adresseDest[0];
        
        /*Tant que nous ne sommes pas arrivé à fin de la chaîne de caractère on continue*/
        while(*stringAModifSourceCar != delimiteur){ 
    
            /*Je stocke la première valeur de stringAModifSourceCar dans adresseDestCar*/
            *stringAModifSourceCar = *stringAModifSourceCar;

            /*Je passe à l'adresse suivante*/
            stringAModifSourceCar = &stringAModifSourceCar[1];
        }

        /*On continue de lire la chaine de caracteres tant que l'on n'est pas arrrivé a la fin*/
        while(*stringAModifSourceCar != '\0'){
            
            /*On recupère la valeur de stringAModifSourceCar dans adresseDestCar*/
            *adresseDestCar = *stringAModifSourceCar;

            /*On passe à l'adresse suivante*/
            stringAModifSourceCar = &stringAModifSourceCar[1];
            adresseDestCar = &adresseDestCar[1];

            /*On signe la fin de la chaîne*/
            *adresseDestCar = '\0';

        }
        /*Je libère la mémoire*/
        free(stringAModifSourceCar);
    }