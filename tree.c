#include "tree.h"

#include <stdio.h>
#include <stdlib.h>

// Initializeaza un arbore.
tree_node *init_tree(char value[][3])
{
    int i, j;
    tree_node *node = calloc(1, sizeof(tree_node));
    node->end = 0;
    node->level = 0;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            node->value[i][j] = value[i][j];
        }
    }
    for (i = 0; i < numberofchoices(node); i++)
        node->children[i] = NULL;
    return node;
}

// Returneaza numarul de optiuni pe care le poate avea un jucator.
int numberofchoices(tree_node *tree)
{
    int index = 0, i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (tree->value[i][j] == '-')
                index++;
        }
    }
    return index;
}

// Stabileste daca un nod este nod terminal, si cine este castigatorul jocului.
void end_of_game(tree_node *tree, char player[])
{
    int k;
    for (k = 0; k < 3; k++)
    {
        if (tree->value[k][0] == tree->value[k][1] && tree->value[k][0] == tree->value[k][2])
        {
            if (tree->value[k][0] == player[0])
                tree->end = 1;
            else if (tree->value[k][0] == player[1])
                tree->end = -1;
        }
        if (tree->value[0][k] == tree->value[1][k] && tree->value[0][k] == tree->value[2][k])
        {
            if (tree->value[0][k] == player[0])
                tree->end = 1;
            else if (tree->value[0][k] == player[1])
                tree->end = -1;
        }
    }
    if (tree->value[0][0] == tree->value[1][1] && tree->value[0][0] == tree->value[2][2])
    {
        if (tree->value[0][0] == player[0])
            tree->end = 1;
        else if (tree->value[0][0] == player[1])
            tree->end = -1;
    }
    if (tree->value[0][2] == tree->value[1][1] && tree->value[0][2] == tree->value[2][0])
    {
        if (tree->value[0][2] == player[0])
            tree->end = 1;
        else if (tree->value[0][2] == player[1])
            tree->end = -1;
    }
}

// Insereaza intr-un arbore toate miscarile posibile ale unui jucator.
void insert(tree_node *tree, char player[], int w)
{
    int i, j, index = numberofchoices(tree), k = 0;
    tree_node *newNode[index];
    for (i = 0; i < index; i++)
    {
        newNode[i] = init_tree(tree->value);
    }
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            if (tree->end == 0 && tree->value[i][j] == '-')
            {
                newNode[k]->value[i][j] = player[w];
                newNode[k]->level = tree->level + 1;
                tree->children[k] = newNode[k];
                // Verifica daca jocul s-a terminat.
                end_of_game(newNode[k], player);
                k++;
            }
        }
    }
}

// Creeaza arborele de joc.
void create_tree(tree_node *tree, char player[])
{
    if (tree == NULL || tree->end != 0)
        return;
    int i, j, index = 0, l;
    // Daca nivelul nodului este par, jucatorul care muta este primul, altfel muta cel de-al doilea.
    if (tree->level % 2 == 0)
        insert(tree, player, 0);
    else
        insert(tree, player, 1);
    while (tree->children[index] != NULL)
    {
        create_tree(tree->children[index], player);
        index++;
    }
}

// Creeaza arborele si-sau.
void and_or_tree(tree_node *tree)
{
    int index = 0, ok;
    if (tree == NULL)
        return;
    // Daca jocul nu este castigat de primul jucator, valoarea lui end este, nodul este fals.
    if (tree->children[0] == NULL)
    {
        if (tree->end != 1)
            tree->end = 0;
        return;
    }
    // Daca nivelul nodului este par nodul este adevarat daca cel putin un fiu este adevarat.
    if (tree->level % 2 == 0)
    {
        ok = 0;
        while (tree->children[index] != NULL)
        {
            and_or_tree(tree->children[index]);
            if (tree->children[index]->end == 1)
                ok = 1;
            index++;
        }
        if (ok == 1)
            tree->end = 1;
        else
            tree->end = 0;
    }
    // Daca nivelul nodului este impar nodul este adevarat doar daca toti fii au valoarea adevarat(1).
    if (tree->level % 2 == 1)
    {
        ok = 0;
        while (tree->children[index] != NULL)
        {
            and_or_tree(tree->children[index]);
            if (tree->children[index]->end == 0)
                ok = 1;
            index++;
        }
        if (ok == 0)
            tree->end = 1;
        else
            tree->end = 0;
    }
}

// Afiseaza intr-un fisier dat arborele si-sau (Afiseaza T daca valoarea lui end este 1, si F daca este 0).
void print_and_or_tree(tree_node *tree, int k, FILE *fout)
{
    if (tree == NULL)
        return;
    int index = 0, l;
    for (l = 0; l < k; l++)
        fputc('\t', fout);
    if (tree->end == 1)
        fputc('T', fout);
    else
        fputc('F', fout);
    fputc('\n', fout);
    k++;
    while (tree->children[index] != NULL)
    {
        print_and_or_tree(tree->children[index], k, fout);
        index++;
    }
}

// Afiseaza arborele de joc (tabla de X si O).
void print_tree(tree_node *tree, int k, FILE *fout)
{
    if (tree == NULL)
        return;
    int i, j, index = 0, l;
    for (i = 0; i < 3; i++)
    {
        for (l = 0; l < k; l++)
            fputc('\t', fout);
        for (j = 0; j < 3; j++)
        {
            fputc(tree->value[i][j], fout);
            if (j != 2)
                fputc(' ', fout);
        }
        fputc('\n', fout);
    }
    fputc('\n', fout);
    k++;
    while (tree->children[index] != NULL)
    {
        print_tree(tree->children[index], k, fout);
        index++;
    }
}

// Elibereaza memoria arborelui.
void destroy_tree(tree_node *tree)
{
    if (tree == NULL)
    {
        return;
    }
    int index = 0;
    while (tree->children[index] != NULL)
    {
        destroy_tree(tree->children[index]);
        index++;
    }
    free(tree);
}