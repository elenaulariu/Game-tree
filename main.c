#include "tree.h"
#include "minimax.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *fin, *fout;
    fin = fopen(argv[2], "rt");
    fout = fopen(argv[3], "wt");
    // Se rezolva prima cerinta.
    if (strcmp(argv[1], "-c1") == 0)
    {
        char value[3][3];
        char player[2];
        int i, j;
        // Se initializeaza primul jucator.
        player[0] = fgetc(fin);
        fgetc(fin);
        // Cel de-al doilea jucator isi ia valoarea in functie de cea a primului.
        if (player[0] == 'X')
            player[1] = 'O';
        else
            player[1] = 'X';
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                value[i][j] = fgetc(fin);
                fgetc(fin);
            }
        }
        // Se initializeaza arborele.
        tree_node *tree = init_tree(value);
        // Se creeaza arborele de joc.
        create_tree(tree, player);
        // Se afiseaza arborele.
        print_tree(tree, 0, fout);
        destroy_tree(tree);
    }
    // Se rezolva cea de-a doua cerinta.
    if (strcmp(argv[1], "-c2") == 0)
    {
        char value[3][3];
        char player[2];
        int i, j;
        // Se initializeaza primul jucator.
        player[0] = fgetc(fin);
        fgetc(fin);
        // Cel de-al doilea jucator isi ia valoarea in functie de cea a primului.
        if (player[0] == 'X')
            player[1] = 'O';
        else
            player[1] = 'X';
        for (i = 0; i < 3; i++)
        {
            for (j = 0; j < 3; j++)
            {
                value[i][j] = fgetc(fin);
                fgetc(fin);
            }
        }
        // Se initializeaza arborele.
        tree_node *tree = init_tree(value);
        // Se creeaza arborele de joc.
        create_tree(tree, player);
        // Se creeaza arborele si-sau.
        and_or_tree(tree);
        // Se afiseaza arborele si-sau.
        print_and_or_tree(tree, 0, fout);
        destroy_tree(tree);
    }
    // Se rezolva cea de-a treia cerinta.
    if (strcmp(argv[1], "-c3") == 0)
    {
        int level;
        fscanf(fin, "%d", &level);
        fgetc(fin);
        int children;
        fscanf(fin, "(%d)", &children);
        fgetc(fin);
        // Se initilalizeaza arborele.
        minimax_node *tree = init_minimax(children);
        tree->level = 0;
        tree->nrchildren = children;
        // Se initialize coada.
        queue *q = init_queue();
        // Se adauga radacina arborelui in coada.
        enque(q, tree);
        // Se initializeaza fii fiecarui nod si se adauga valoriile in nodurile frunza.
        create_minimax_tree(fin, tree, q);
        // Se completeaza valoriile fiecarui nod.
        complete_minimax_tree(tree, level);
        // Se afiseaza valoriile nodurilor in fisierul dat.
        print_minimax_tree(tree, fout);
        destroy_minimax(tree);
        free(q);
    }
    fclose(fin);
    fclose(fout);
}