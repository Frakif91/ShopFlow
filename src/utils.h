#include "types.h"
#ifndef UTILS_H
#define UTILS_H

#include "types.h"

/* Petites fonctions de chaines ecrites ici pour ne pas utiliser string.h. */
int longueurChaine(const char *texte);
void copierChaine(char *destination, const char *source, int capacite);
int comparerChaines(const char *a, const char *b);
int contientMot(const char *texte, const char *mot);
int texteEstVide(const char *texte);
int emailValide(const char *email);
int telephoneValide(const char *telephone);
int codePostalValide(const char *codePostal);

/* Fonctions de saisie. Elles recommencent la lecture si la valeur est incorrecte. */
void lireTexte(const char *message, char *destination, int capacite);
int lireEntier(const char *message);
int lireEntierEntre(const char *message, int minimum, int maximum);
float lireReelEntre(const char *message, float minimum, float maximum);
int lireOuiNon(const char *message);

/* Saisie et verification des deux structures reutilisees dans plusieurs modules. */
Date saisirDate(void);
Adresse saisirAdresse(void);
void afficherAdresse(const Adresse *adresse);
int dateValide(Date date);
int anneeBissextile(int annee);

#endif
