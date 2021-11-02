#ifndef _MINIMAX_H
#define _MINIMAX_H
#include <stdio.h>

typedef struct minimax_node
{
    int value;                         // retine valoarea nodului
    int end;                           // este 1 daca nodul este nod terminal si 0 in rest
    int visited;                       // este 1 daca nodul a fost vizitat si 0 in rest
    int level;                         // retine nivelul nodului in arbore
    int nrchildren;                    // retine numarul de fii al nodului
    struct minimax_node *children[11]; // pointeri catre fii nodului
} minimax_node;

typedef struct node
{
    minimax_node *tree; // pointer catre nodul arborelui minimax retinut in nod
    struct node *next;  // pointer catre nodul urmator
} node;

typedef struct queue
{
    int size;    // dimensiunea cozii
    node *front; // pointer catre primul nod din coada
    node *back;  // pointer catre ultimul nod din coada
} queue;

// Initializeaza o coada.
queue *init_queue();

// Adauga un element in coada.
void enque(queue *q, minimax_node *tree);

// Sterge si dezaloca ultimul element din coada.
void dequeue(queue *q);

// Returneaza elementul din varful cozii.
minimax_node *front(queue *q);

// Initializeaza un arbore minimax.
minimax_node *init_minimax(int children);

// Creeaza arborele recursiv.
void create_minimax_tree(FILE *fin, minimax_node *tree, queue *q);

// Atribuie fiecarui nod din arbore, valoarea cea mai mica sau cea mai mare a fiilor sai.
void complete_minimax_tree(minimax_node *tree, int level);

// Afiseaza elementele din arbore intr-un fisier dat.
void print_minimax_tree(minimax_node *tree, FILE *fout);

// Elibereaza memoria arborelui.
void destroy_minimax(minimax_node *tree);

#endif