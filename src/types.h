#ifndef TYPES_H
#define TYPES_H

/*
   Ce fichier contient les structures partagees par les modules.
   Les tableaux qui peuvent grandir sont representes par un pointeur,
   un nombre d'elements utilises et une capacite allouee en memoire.
*/

#define TAILLE_NOM_BOUTIQUE 50
#define TAILLE_RUE 80
#define TAILLE_VILLE 50
#define TAILLE_CODE_POSTAL 6
#define TAILLE_PAYS 50
#define TAILLE_REFERENCE 12
#define TAILLE_DESIGNATION 60
#define TAILLE_CATEGORIE 30
#define TAILLE_NOM 50
#define TAILLE_PRENOM 50
#define TAILLE_EMAIL 80
#define TAILLE_TELEPHONE 15
#define TAILLE_STATUT 20

#define FRAIS_PORT 5.90f
#define TAUX_TVA 20.0f

/* Date de commande, avec une validation adaptee au mois et aux annees bissextiles. */
typedef struct {
    int jour;                 /* Jour du mois, par exemple 23. */
    int mois;                 /* Mois de 1 a 12. */
    int annee;                /* Annee comprise entre 2000 et 2100. */
} Date;

/* Adresse conservee dans le profil client et copiee dans chaque commande. */
typedef struct {
    char rue[TAILLE_RUE];             /* Numero et nom de la voie. */
    char ville[TAILLE_VILLE];         /* Ville de livraison ou de residence. */
    char codePostal[TAILLE_CODE_POSTAL]; /* Cinq chiffres et le caractere final \0. */
    char pays[TAILLE_PAYS];           /* Pays associe a l'adresse. */
} Adresse;

/* Produit du catalogue. actif vaut 1 si le produit est disponible dans le catalogue. */
typedef struct {
    char reference[TAILLE_REFERENCE];       /* Identifiant unique, conserve meme apres desactivation. */
    char designation[TAILLE_DESIGNATION];   /* Nom lisible du produit. */
    char categorie[TAILLE_CATEGORIE];       /* Famille du produit. */
    float prixUnitaireHT;                   /* Prix d'une unite, avant TVA. */
    int quantiteStock;                      /* Quantite encore disponible a la vente. */
    int seuilAlerte;                        /* Seuil utilise pour afficher une alerte de stock. */
    int actif;                              /* 1 = actif, 0 = suppression logique. */
} Produit;

/* Une ligne garde le nom et le prix du produit tels qu'ils etaient lors de la vente. */
typedef struct {
    char refProduit[TAILLE_REFERENCE];     /* Reference vers le catalogue. */
    char designation[TAILLE_DESIGNATION];   /* Libelle copie au moment de la commande. */
    int quantite;                           /* Nombre d'unites achetees. */
    float prixUnitaireHT;                   /* Prix copie au moment de la vente. */
    float sousTotalHT;                      /* Quantite multipliee par le prix unitaire. */
} LigneCommande;

/* Les lignes sont allouees dynamiquement, car leur nombre n'est pas connu d'avance. */
typedef struct {
    int numero;                       /* Numero unique attribue automatiquement par la boutique. */
    int idClient;                     /* Identifiant du client qui possede la commande. */
    Date dateCommande;                /* Date de creation de la commande. */
    char statut[TAILLE_STATUT];       /* EN_COURS, EXPEDIEE, LIVREE ou ANNULEE. */
    int nbLignes;                     /* Nombre de lignes réellement utilisees. */
    int capaciteLignes;               /* Nombre de lignes pour lesquelles la memoire est reservee. */
    LigneCommande *lignes;            /* Tableau alloue avec malloc/realloc. */
    float montantBrutHT;              /* Somme des lignes avant remise. */
    float tauxRemise;                 /* 0, 5, 10 ou 15 pour cent. */
    float montantRemise;              /* Valeur en euros de la remise. */
    float montantHT;                  /* Montant apres remise, avant TVA. */
    float montantTVA;                 /* TVA appliquee au montant HT apres remise. */
    float montantTTC;                 /* HT + TVA + frais de port. */
    float fraisPort;                  /* 0 ou 5,90 euros, sans TVA. */
    Adresse adresseLivraison;         /* Copie de l'adresse client au moment de l'achat. */
} Commande;

/* Chaque client possede son historique dynamique de commandes. */
typedef struct {
    int idClient;                       /* Identifiant unique attribue par la boutique. */
    char nom[TAILLE_NOM];               /* Nom de famille. */
    char prenom[TAILLE_PRENOM];         /* Prenom. */
    char email[TAILLE_EMAIL];           /* Adresse email unique dans tous les enregistrements. */
    char telephone[TAILLE_TELEPHONE];   /* Numero compose de dix chiffres. */
    Adresse adresse;                    /* Adresse actuelle du client. */
    int pointsFidelite;                 /* Total des points de commandes non annulees. */
    int nbCommandes;                    /* Nombre d'elements dans le tableau commandes. */
    int capaciteCommandes;              /* Places reservees dans le tableau commandes. */
    Commande *commandes;                /* Historique de commandes alloue dynamiquement. */
    int actif;                          /* 1 = client actif, 0 = client desactive. */
} Client;

/* Structure racine : tous les modules travaillent a partir de la Boutique. */
typedef struct {
    char nom[TAILLE_NOM_BOUTIQUE];   /* Nom affiche dans l'application. */
    Produit *produits;               /* Tableau principal du catalogue. */
    int nbProduits;                  /* Nombre de produits existants, actifs ou non. */
    int capaciteProduits;            /* Taille actuellement reservee pour produits. */
    Client *clients;                 /* Tableau de tous les clients. */
    int nbClients;                   /* Nombre de clients enregistres. */
    int capaciteClients;             /* Taille actuellement reservee pour clients. */
    int numeroSuivant;               /* Prochain numero de commande a attribuer. */
    int idClientSuivant;             /* Prochain identifiant client a attribuer. */
} Boutique;

#endif
