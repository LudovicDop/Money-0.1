#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "moneyMainFunction.h"

/*Déclaration de ma fonction sepMonth*/
/*Permet de recevoir des dates au format char puis des les retourner dans la structure date (int)*/
date sepMonth(char *dateUti){

    /*Déclaration de mes variables*/
    date dateDeDepart;
    char dateAuFormatChar[20];
    const char *separateur;
    char *strToken;
    int buffer;
    int i = 0;
    /*Initialisation de mes variables*/
    strToken = malloc(sizeof(100));
    separateur = malloc(sizeof(2));
    separateur = "/";

        /*Traitement de la date dateUti entrée par l'utilisateur de la fonction*/
        strcpy(dateAuFormatChar,dateUti);

        /*Séparation du char dateAuFormatChar en trois parties jour, mois & annee*/
        /*On demande le premier tocken*/
        strToken = strtok(dateAuFormatChar,separateur);

        while(strToken != NULL){

            /*Je convertis strToken en un int stocké dans buffer*/
            sscanf(strToken,"%d",&buffer);

            /*J'intègre la date fragmentée stockée dans buffer dans la structure date*/
            switch (i)
            {
            case 0:
                dateDeDepart.jour = buffer;
                break;

            case 1:
                dateDeDepart.mois = buffer;
                break;

            case 2:
                dateDeDepart.annee = buffer;
                break;  

            default:
                EXIT_FAILURE;
                break;
            }

            /*On demande le tocken suivant*/
            strToken = strtok(NULL,separateur);

            /*J'incrémente i pour affecter une autre variable de ma structure*/
            i++;
        }

        /*Je libère la mémoire allouée à mes variables*/
        free(strToken);

    /*Retourne 0 si aucune erreur n'est constaté durant le lancement du programme*/
    return dateDeDepart;
}

int nombreDeJourDansUnMois(date moisSource){

    /*Déclaration de mes variables*/
    int listeMois_31[7] = {1,3,5,7,8,10,12};
    int listeMois_30[4] = {4,6,9,11};
    int listeMois_28_29[2] = {2};
    int result;

    /*Je regarde si moisSource fait partie des mois contenant 31 jours*/
    for(int i = 0; i < 7;i++){
        if(moisSource.mois == listeMois_31[i]){
            result = 31;
        }
    }

    /*Je regarde si moisSource fait partie des mois contenant 30 jours*/
    for(int i = 0; i < 4;i++){
        if(moisSource.mois == listeMois_30[i]){
            result = 30;
        }
    }

    /*Je regarde si moisSource fait partie des mois contenant 28/29 jours*/
    for(int i = 0; i < 2;i++){
        if(moisSource.mois == listeMois_28_29[i]){
            result = 28;
        }
    }

    return result;

}


/*Fonction final permettant de calculer la différence en mois entre deux dates*/
int diffMonth(date dateLaPlusAncienne,date dateLaPlusRecente){
    
    /*Déclaration de mes variables*/
    int annee;
    int mois;
    int jour_1;
    int nombreDeJourDansUnMoisDebut = nombreDeJourDansUnMois(dateLaPlusAncienne);
    int nombreDeJourDansUnMoisFin = nombreDeJourDansUnMois(dateLaPlusRecente);
    int moisDeDepart = dateLaPlusAncienne.mois;
    int moisDeFin = dateLaPlusRecente.mois;

    /*On calcule la différence entre les années uniquement*/
    annee =  dateLaPlusRecente.annee - dateLaPlusAncienne.annee;

    /*On prend le mois le plus élevé puis on calcul la différence en prenant en compte les années dans le calcul*/
    /*Si le mois de la date de fin est plus élevé que le mois de la date de départ*/
    if(moisDeFin >= moisDeDepart){

        /*On fait la différence entre les mois de la date de fin et les mois de la date de départ*/
        mois =  moisDeFin - moisDeDepart;

        /*On calcul le nombre de mois dans X année(s)*/
        annee = annee * 12;

        /*Si année est > à 0*/
        if(annee > 0){

            /*On ajoute les années au mois*/
            mois = annee + mois;
        }

    }
    /*Si le mois de la date de départ est plus élevé que le mois de la date de fin*/
    if(moisDeDepart > moisDeFin){

        /*On fait la différence entre les mois de la date de départ et les mois de la date de fin*/
        mois =  moisDeDepart - moisDeFin;
        /*On ajoute les années au mois de départ*/
        mois = annee * 12 - mois;
    }

    /*On soustrait le jour le plus récent (en observant la date au complet) au jour la plus ancien*/
    jour_1 = dateLaPlusRecente.jour - dateLaPlusAncienne.jour;

    /*Si le résultat est négatif cela signifie qu'il faudra soustraire un mois dans le résultat puis calculer les jours restants*/
    if(jour_1 < 0){
        jour_1 = jour_1 + nombreDeJourDansUnMoisFin + nombreDeJourDansUnMoisDebut - nombreDeJourDansUnMoisFin;
        mois = mois - 1;
    }

    
    //printf("Il y a %d mois et %d jours de decallage!\n",mois,jour_1);
    return mois;
}

/*Déclaration de ma fonction putInOrder*/
/*Permet de comparer deux dates et voir qui est la plus ancienne des deux*/

int putInOrder(date dateDeDebut,date dateDeFin){

    /*Je déclare mes variables*/
    int mois = 0;
    
    /*On vérifie quelle date est la plus ancienne*/
    /*On compare les années*/
    if(dateDeDebut.annee < dateDeFin.annee){
        mois = diffMonth(dateDeDebut,dateDeFin);
    }
    if(dateDeDebut.annee > dateDeFin.annee){
        mois = diffMonth(dateDeFin,dateDeDebut);
    }
    /*Si les années sont identiques*/
    if(dateDeDebut.annee == dateDeFin.annee){
        /*Alors on passe à la comparaison des mois*/
        if(dateDeDebut.mois < dateDeFin.mois){
           mois = diffMonth(dateDeDebut,dateDeFin);
        }
        if(dateDeDebut.mois > dateDeFin.mois){
           mois = diffMonth(dateDeFin,dateDeDebut);
        }
        /*Si les mois sont identiques on compare les jours*/
        if(dateDeDebut.mois == dateDeFin.mois){
            if(dateDeDebut.jour < dateDeFin.jour){
                mois = diffMonth(dateDeDebut,dateDeFin);
            }
            if(dateDeDebut.jour > dateDeFin.jour){
                mois = diffMonth(dateDeFin,dateDeDebut);
            }
            /*Si les jours sont égaux alors les deux dates sont identiques*/
            if(dateDeDebut.jour == dateDeFin.jour){
                mois = 0;
                //printf("Les deux dates sont identiques!\n");
            }
        }
    }

    return mois;
   
}



