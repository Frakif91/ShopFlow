#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

// Renvoie le nombre de caracteres avant le caractere de fin '\0'
int longueurChaine(const char *texte) {
    int i = 0;
    while (texte[i] != '\0') {
        i++;
    }
    return i;
}

// Copie une chaine sans depasser la place disponible
void copierChaine(char *destination, const char *source, int capacite) {
    int i = 0;
    if (capacite <= 0) {
        return;
    }
    while (source[i] != '\0' && i < capacite - 1) {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
}

// Compare deux chaines : resultat 0 si elles sont identique
int comparerChaines(const char *a, const char *b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) {
            return (unsigned char)a[i] - (unsigned char)b[i];
        }
        i++;
    }
    return (unsigned char)a[i] - (unsigned char)b[i];
}

// Convertit une lettre ASCII en minuscule, sans utiliser ctype.h
static char minuscule(char c) {
    if (c >= 'A' && c <= 'Z') {
        return (char)(c - 'A' + 'a');
    }
    return c;
}

// Recherche un mot dans un texte sans tenir compte des majuscules/minuscules
int contientMot(const char *texte, const char *mot) {
    int i, j;
    if (mot[0] == '\0') {
        return 1;
    }
    for (i = 0; texte[i] != '\0'; i++) {
        j = 0;
        while (mot[j] != '\0' && texte[i + j] != '\0' &&
               minuscule(texte[i + j]) == minuscule(mot[j])) {
            j++;
        }
        if (mot[j] == '\0') {
            return 1;
        }
    }
    return 0;
}

// Renvoie 1 si une chaine ne contient que des espaces, ou est vide
int texteEstVide(const char *texte) {
    int i = 0;
    while (texte[i] != '\0') {
        if (texte[i] != ' ' && texte[i] != '\t' && texte[i] != '\n' && texte[i] != '\r') {
            return 0;
        }
        i++;
    }
    return 1;
}

/* Le sujet demande que l'adresse contienne au moins le caractere '@'. */
int emailValide(const char *email) {
    int i;
    for (i = 0; email[i] != '\0'; i++) {
        if (email[i] == '@') {
            return i > 0 && email[i + 1] != '\0';
        }
    }
    return 0;
}

/* Un numero de telephone est compose de dix chiffres. */
int telephoneValide(const char *telephone) {
    int i;
    if (longueurChaine(telephone) != 10) {
        return 0;
    }
    for (i = 0; telephone[i] != '\0'; i++) {
        if (telephone[i] < '0' || telephone[i] > '9') {
            return 0;
        }
    }
    return 1;
}

/* Le code postal est lui aussi forme de cinq chiffres. */
int codePostalValide(const char *codePostal) {
    int i;
    if (longueurChaine(codePostal) != 5) {
        return 0;
    }
    for (i = 0; codePostal[i] != '\0'; i++) {
        if (codePostal[i] < '0' || codePostal[i] > '9') {
            return 0;
        }
    }
    return 1;
}

void lireTexte(const char *message, char *destination, int capacite) {
    char ligne[512];
    int taille;
    int c;
    if (capacite <= 0) {
        return;
    }
    while (1) {
        printf("%s", message);
        if (fgets(ligne, sizeof(ligne), stdin) == NULL) {
            /* En cas de fin d'entree, on fournit une chaine vide plutot que de reutiliser l'ancienne. */
            destination[0] = '\0';
            return;
        }
        taille = longueurChaine(ligne);
        if (taille > 0 && ligne[taille - 1] == '\n') {
            ligne[taille - 1] = '\0';
        } else {
            /* Si la ligne depasse le tampon temporaire, on jette son surplus. */
            c = getchar();
            if (c != '\n' && c != EOF) {
                do {
                    c = getchar();
                } while (c != '\n' && c != EOF);
                printf("Saisie trop longue. Recommencez.\n");
                continue;
            }
        }
        taille = longueurChaine(ligne);
        if (taille >= capacite) {
            printf("Saisie trop longue : maximum %d caracteres. Recommencez.\n", capacite - 1);
            continue;
        }
        if (texteEstVide(ligne)) {
            printf("La saisie ne doit pas etre vide. Recommencez.\n");
            continue;
        }
        copierChaine(destination, ligne, capacite);
        return;
    }
}

/* Lit un entier en verifiant qu'il ne reste aucun caractere non numerique. */
int lireEntier(const char *message) {
    char ligne[100];
    char *fin;
    long valeur;
    while (1) {
        lireTexte(message, ligne, sizeof(ligne));
        valeur = strtol(ligne, &fin, 10);
        while (*fin == ' ' || *fin == '\t' || *fin == '\r') {
            fin++;
        }
        if (fin != ligne && *fin == '\0' && valeur >= -2147483647L - 1L && valeur <= 2147483647L) {
            return (int)valeur;
        }
        printf("Entree invalide : saisissez un nombre entier.\n");
    }
}

/* Encadre une saisie entiere entre deux limites incluses. */
int lireEntierEntre(const char *message, int minimum, int maximum) {
    int valeur;
    do {
        valeur = lireEntier(message);
        if (valeur < minimum || valeur > maximum) {
            printf("La valeur doit etre comprise entre %d et %d.\n", minimum, maximum);
        }
    } while (valeur < minimum || valeur > maximum);
    return valeur;
}

/* Lit un reel en acceptant le point comme separateur decimal. */
float lireReelEntre(const char *message, float minimum, float maximum) {
    char ligne[100];
    char *fin;
    float valeur;
    while (1) {
        lireTexte(message, ligne, sizeof(ligne));
        valeur = strtof(ligne, &fin);
        while (*fin == ' ' || *fin == '\t' || *fin == '\r') {
            fin++;
        }
        /* valeur != valeur permet aussi de refuser NaN sans ajouter une autre bibliotheque. */
        if (fin != ligne && *fin == '\0' && valeur == valeur &&
            valeur >= minimum && valeur <= maximum) {
            return valeur;
        }
        printf("Saisissez un nombre compris entre %.2f et %.2f (point decimal).\n", minimum, maximum);
    }
}

// Repondre (1/o/O) pour oui et (0/n/N) pour non.
int lireOuiNon(const char *message) {
    char reponse[20];
    while (1) {
        lireTexte(message, reponse, sizeof(reponse));
        if (reponse[0] == 'o' || reponse[0] == 'O' || reponse[0] == '1') {
            return 1;
        }
        if (reponse[0] == 'n' || reponse[0] == 'N' || reponse[0] == '0') {
            return 0;
        }
        printf("Repondez par oui/non (o/n).\n");
    }
}

// Une annee bissextile a 366 jours ; les annees seculaires doivent etre divisibles par 400.
// DEF <seculaire> : une annee divisible par 100 mais pas par 400 n'est pas bissextile.
int anneeBissextile(int annee) {
    return (annee % 400 == 0) || (annee % 4 == 0 && annee % 100 != 0);
}

// Verifie l'annee, le mois et le nombre de jours reel du mois.
int dateValide(Date date) {
    int joursParMois[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (date.annee < 2000 || date.annee > 2100 || date.mois < 1 || date.mois > 12) {
        return 0;
    }
    if (date.mois == 2 && anneeBissextile(date.annee)) {
        joursParMois[2] = 29;
    }
    return date.jour >= 1 && date.jour <= joursParMois[date.mois];
}

// Demande les trois composantes jusqu'a obtenir une date possible.
Date saisirDate(void) {
    Date date;
    do {
        printf("Date de commande (annee de 2000 a 2100) :\n");
        date.jour = lireEntierEntre("  Jour : ", 1, 31);
        date.mois = lireEntierEntre("  Mois : ", 1, 12);
        date.annee = lireEntierEntre("  Annee : ", 2000, 2100);
        if (!dateValide(date)) {
            printf("Cette date n'existe pas. Recommencez.\n");
        }
    } while (!dateValide(date));
    return date;
}

// Demande une adresse complete et controle le code postal.
Adresse saisirAdresse(void) {
    Adresse adresse;
    lireTexte("Rue et numero : ", adresse.rue, sizeof(adresse.rue));
    lireTexte("Ville : ", adresse.ville, sizeof(adresse.ville));
    do {
        lireTexte("Code postal (5 chiffres) : ", adresse.codePostal, sizeof(adresse.codePostal));
        if (!codePostalValide(adresse.codePostal)) {
            printf("Le code postal doit contenir exactement cinq chiffres.\n");
        }
    } while (!codePostalValide(adresse.codePostal));
    lireTexte("Pays : ", adresse.pays, sizeof(adresse.pays));
    return adresse;
}


#pragma region Test Unitaires
// Tests unitaires simples, a appeler depuis un programme de test.
// fait avec IA pour la rapidité.

bool printSuccess = true;

void test_anneeBissextile(void) {
    assert(anneeBissextile(2000) == 1);
    assert(anneeBissextile(2004) == 1);
    assert(anneeBissextile(2100) == 0);
    assert(anneeBissextile(2023) == 0);
    if(printSuccess) printf("test_anneeBissextile passed\n");
}

void test_dateValide(void) {
    Date date;
    date.annee = 2024; date.mois = 2; date.jour = 29;
    assert(dateValide(date) == 1);
    date.annee = 2023;
    assert(dateValide(date) == 0);
    date.annee = 2024; date.mois = 4; date.jour = 31;
    assert(dateValide(date) == 0);
    date.mois = 13; date.jour = 1;
    assert(dateValide(date) == 0);
    date.mois = 1; date.annee = 1999;
    assert(dateValide(date) == 0);
    if(printSuccess) printf("test_dateValide passed\n");
}

void test_codePostalValide(void) {
    assert(codePostalValide("75001") == 1);
    assert(codePostalValide("00000") == 1);
    assert(codePostalValide("7500") == 0);
    assert(codePostalValide("750001") == 0);
    assert(codePostalValide("75A01") == 0);
    if(printSuccess) printf("test_codePostalValide passed\n");
}

#pragma endregion Fin Tests Unitaires