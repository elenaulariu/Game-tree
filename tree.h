#ifndef _TREE_H
#define _TREE_H
#include <stdio.h>

typedef struct tree_node
{
    char value[3][3];              // retine tabla de X si O
    int end;                       // este 0 daca jocul nu s-a terminat sau nu are castigator, 1 daca castiga jucatorul care incepe si -1 in caz contrar
    int level;                     // nivelul nodului in arbore
    struct tree_node *children[9]; // pointer catre fii nodului
} tree_node;

// Initializeaza un arbore.
tree_node *init_tree(char value[][3]);

// Returneaza numarul de optiuni pe care le poate avea un jucator.
int numberofchoices(tree_node *tree);

// Stabileste daca un nod este nod terminal, si cine este castigatorul jocului.
void end_of_game(tree_node *tree, char player[]);

// Insereaza intr-un arbore toate miscarile posibile ale unui jucator.
void insert(tree_node *tree, char player[], int w);

// Creeaza arborele de joc.
void create_tree(tree_node *tree, char player[]);

// Creeaza arborele si-sau.
void and_or_tree(tree_node *tree);

// Afiseaza intr-un fisier dat arborele si-sau.
void print_and_or_tree(tree_node *tree, int k, FILE *fout);

// Afiseaza arborele de joc (tabla de X si O).
void print_tree(tree_node *tree, int k, FILE *fout);

// Elibereaza memoria arborelui.
void destroy_tree(tree_node *tree);

#endif