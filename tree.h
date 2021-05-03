#ifndef _TREE_H
#define _TREE_H
#include <stdio.h>

typedef struct tree_node {
    char value[3][3];
    int end;
    int level;
    struct tree_node* parent; 
    struct tree_node* children[9];
} tree_node;

tree_node* init_tree(char value[][3]);

int numberofchoices(tree_node *tree);

void end_of_game(tree_node *tree, char player[]);

void insert(tree_node *tree, char player[], int w);

void swap(char player[]);

void create_tree(tree_node *tree, char player[]);

void and_or_tree(tree_node *tree);

void print_and_or_tree(tree_node *tree, int k, FILE *fout);

void print_tree(tree_node *tree, int k, FILE *fout);

void print_tree1(tree_node *tree, int k);

void destroy_tree(tree_node *tree);

#endif