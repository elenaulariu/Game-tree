#include "tree.h"
#include "minimax.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[]) {
    FILE *fin, *fout;
    fin=fopen(argv[2], "rt");
    fout=fopen(argv[3], "wt");
    if(strcmp(argv[1], "-c1")==0) {
        char value[3][3];
        char player[2];
        int i, j;
        player[0]=fgetc(fin);
        fgetc(fin);
        if(player[0]=='X') player[1]='O';
        else player[1]='X';
        for(i=0; i<3; i++) {
            for(j=0; j<3; j++) {
                value[i][j]=fgetc(fin);
                fgetc(fin);
            }
        }
        /*for(i=0; i<3; i++) {
            for(j=0; j<3; j++) {
                printf("%c", value[i][j]);
            }
        }*/
        tree_node *tree=init_tree(value);
        create_tree(tree, player);
        print_tree(tree, 0, fout);
        destroy_tree(tree);
    }
    if(strcmp(argv[1], "-c2")==0) {
        char value[3][3];
        char player[2];
        int i, j;
        player[0]=fgetc(fin);
        fgetc(fin);
        if(player[0]=='X') player[1]='O';
        else player[1]='X';
        for(i=0; i<3; i++) {
            for(j=0; j<3; j++) {
                value[i][j]=fgetc(fin);
                fgetc(fin);
            }
        }
        /*for(i=0; i<3; i++) {
            for(j=0; j<3; j++) {
                printf("%c", value[i][j]);
            }
        }*/
        tree_node *tree=init_tree(value);
        create_tree(tree, player);
        and_or_tree(tree);
        print_tree1(tree, 0);
        print_and_or_tree(tree, 0, fout);
        destroy_tree(tree);
    }
    if(strcmp(argv[1], "-c3")==0) {
        int level=fgetc(fin)-'0';
        fgetc(fin);
        int children;
        fscanf(fin, "(%d)", &children);
        fgetc(fin);
        minimax_node *tree=init_minimax(children);
        tree->level=1;
        create_minimax_tree(fin, tree, children);
        complete_minimax_tree(tree, level);
        print_minimax_tree(tree, 0, fout);
        print_minimax_tree1(tree, 0);
        destroy_minimax(tree);
    }
    fclose(fin);
    fclose(fout);
}