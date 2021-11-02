#include "minimax.h"

#include <stdio.h>
#include <stdlib.h>

// Initializeaza o coada.
queue *init_queue()
{
    queue *q = malloc(sizeof(queue));
    q->front = NULL;
    q->back = NULL;
    q->size = 0;
    return q;
}

// Adauga un element nou in coada.
void enque(queue *q, minimax_node *tree)
{
    node *newnode = malloc(sizeof(node));
    newnode->tree = tree;
    newnode->next = NULL;
    if (q->front == NULL && q->back == NULL)
    {
        q->front = newnode;
        q->back = newnode;
    }
    else
    {
        q->back->next = newnode;
        q->back = newnode;
    }
    q->size++;
}

// Sterge si dezaloca ultimul element din coada.
void dequeue(queue *q)
{
    if (q->front == NULL)
        return;
    if (q->front == q->back)
    {
        free(q->front);
        q->front = NULL;
        q->back = NULL;
        q->size = 0;
    }
    else
    {
        node *temp = q->front;
        q->front = q->front->next;
        free(temp);
        q->size--;
    }
}

// Returneaza elementul din varful cozii.
minimax_node *front(queue *q)
{
    if (q->front == NULL)
        return NULL;
    return q->front->tree;
}

// Initializeaza un arbore minimax.
minimax_node *init_minimax(int children)
{
    int i;
    minimax_node *node = calloc(1, sizeof(minimax_node));
    node->value = 0;
    node->end = 0;
    node->visited = 0;
    for (i = 0; i < children; i++)
    {
        node->children[i] = NULL;
    }
    return node;
}

// Creeaza arborele recursiv.
void create_minimax_tree(FILE *fin, minimax_node *tree, queue *q)
{
    if (q->size == 0)
        return;
    // Scoatem primul element din coada.
    minimax_node *temp = front(q);
    dequeue(q);
    int i, *current_children = calloc(temp->nrchildren, sizeof(int)), k = 0, value;
    minimax_node *newNode[temp->nrchildren];
    char c;
    // Marcam nodul ca fiind vizitat.
    temp->visited = 1;
    // Pentru fiecare copil al nodului verificam daca este nod terminal, sau nu. Daca da ii atribuim valoarea din fisier. Daca nu il initializam.
    for (i = 0; i < temp->nrchildren; i++)
    {
        c = fgetc(fin);
        if (c == '(')
        {
            fscanf(fin, "%d)", &current_children[i]);
            newNode[i] = init_minimax(current_children[i]);
            temp->children[i] = newNode[i];
            temp->children[i]->nrchildren = current_children[i];
            temp->children[i]->level = temp->level + 1;
        }
        else if (c == '[')
        {
            fscanf(fin, "%d]", &value);
            newNode[i] = init_minimax(current_children[i]);
            newNode[i]->value = value;
            newNode[i]->end = 1;
            temp->children[i] = newNode[i];
            temp->children[i]->nrchildren = current_children[i];
            temp->children[i]->level = temp->level + 1;
        }
        fgetc(fin);
    }
    // Daca nodul nu a mai fost vizitat si nu este nod terminal il adaugam in coada si il marcam ca vizitat.
    for (i = 0; i < temp->nrchildren; i++)
    {
        if (temp->children[i]->visited == 0 && temp->children[i]->nrchildren != 0)
        {
            temp->children[i]->visited = 1;
            enque(q, temp->children[i]);
        }
    }
    create_minimax_tree(fin, tree, q);
    free(current_children);
}

// Atribuie fiecarui nod din arbore, valoarea cea mai mica sau cea mai mare a fiilor sai.
void complete_minimax_tree(minimax_node *tree, int level)
{
    int i = 0;
    if (tree->end == 1 || tree->level == level - 1)
        return;
    // Apelam recursiv functia pentru fiecare fiu al nodului.
    while (tree->children[i] != NULL)
    {
        complete_minimax_tree(tree->children[i], level);
        i++;
    }
    i = 0;
    // Atribuim nodului valoarea primului sau fiu.
    tree->value = tree->children[0]->value;
    // Daca nodul este par, parcurgem toti fii nodului, si ii atribuim valoarea maxima.
    if (tree->level % 2 == 0)
    {
        while (tree->children[i] != NULL)
        {
            if (tree->value < tree->children[i]->value)
            {
                tree->value = tree->children[i]->value;
            }
            i++;
        }
    }
    // Daca nodul este impar, parcurgem toti fii nodului, si ii atribuim valoarea minima.
    if (tree->level % 2 != 0)
    {
        while (tree->children[i] != NULL)
        {
            if (tree->value > tree->children[i]->value)
            {
                tree->value = tree->children[i]->value;
            }
            i++;
        }
    }
}

// Afiseaza elementele din arbore intr-un fisier dat.
void print_minimax_tree(minimax_node *tree, FILE *fout)
{
    if (tree == NULL)
        return;
    int index = 0, l;
    for (l = 0; l < tree->level; l++)
        fputc('\t', fout);
    fprintf(fout, "%d\n", tree->value);
    while (tree->children[index] != NULL && tree->end != 1)
    {
        print_minimax_tree(tree->children[index], fout);
        index++;
    }
}

// Elibereaza memoria arborelui.
void destroy_minimax(minimax_node *tree)
{
    if (tree == NULL)
    {
        return;
    }
    int index = 0;
    while (tree->children[index] != NULL)
    {
        destroy_minimax(tree->children[index]);
        index++;
    }
    free(tree);
}