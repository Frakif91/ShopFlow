# FAIT AVEC IA

# Compilation de tous les modules du projet en langage C (pas de C++).
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g

SOURCES = main.c utils.c produit.c client.c commande.c statistique.c initialisation.c
OBJETS = $(SOURCES:.c=.o)

shopflow: $(OBJETS)
	$(CC) $(CFLAGS) -o shopflow $(OBJETS)

# Chaque source depend de ses headers partages ; make recompilera le projet si besoin.
main.o: main.c types.h utils.h produit.h client.h commande.h statistique.h initialisation.h
utils.o: utils.c utils.h types.h
produit.o: produit.c produit.h utils.h types.h
client.o: client.c client.h commande.h utils.h types.h
commande.o: commande.c commande.h client.h produit.h utils.h types.h
statistique.o: statistique.c statistique.h produit.h client.h utils.h types.h
initialisation.o: initialisation.c initialisation.h commande.h produit.h client.h utils.h types.h

clean:
	rm -f $(OBJETS) shopflow

.PHONY: clean
