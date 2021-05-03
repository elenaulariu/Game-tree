#ifndef _MINIMAX_H
#define _MINIMAX_H
#include <stdio.h>

typedef struct minimax_node{
    int value;
    int end;
    int level; 
    struct minimax_node* children[11];
} minimax_node;

minimax_node* init_minimax(int children);

void create_minimax_tree(FILE *fin, minimax_node *tree, int children);

void complete_minimax_tree(minimax_node *tree, int level);

void print_minimax_tree(minimax_node *tree, int k, FILE *fout);

void print_minimax_tree1(minimax_node *tree, int k);

void destroy_minimax(minimax_node *tree);


#endif