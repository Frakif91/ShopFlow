/**
*  ShopFlow types header file
*  Created on the 23rd of October 2026
*  by Mathis Moity-Manzer (mathis.moity-manzer@efrei.net)
*/

typedef struct Date {
    int jour; // 1 <= X <= 31
    int moi; // 1 <= X <= 12
    int annee; // 2000 <= annee <= 2100
};

typedef struct Adresse {
    char rue[80]; // 79 car max + non vide
    char ville[50]; // non vide
    char codePostal[6]; // c'est des chiffre (5 chiffres)
    char pays[50]; // non vide
};

typedef struct Produit {
    char reference[12]; // Unique non vide
    char designation[60]; // Non vide, Libbele
    char categorie[30]; // Famille de produit
    float prixUnitaireHT; // X > 0
    int quantiteStock; // X >= 0
    int seuilAlerte; // X >= 0
    int actif; // boolean, (statue du produit)
};
