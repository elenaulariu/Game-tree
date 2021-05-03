#include "minimax.h"

#include <stdio.h>
#include <stdlib.h>

minimax_node* init_minimax(int children) {
    int i;
    minimax_node* node=calloc(1, sizeof(minimax_node));
    //node->level=level;
    node->value=0;
    node->end=0;
    //node->children=(minimax_node**) malloc(children*sizeof(minimax_node*));
    for(i=0; i<children; i++) {
        node->children[i]=NULL;
    }
    return node;
}

void create_minimax_tree(FILE *fin, minimax_node *tree, int children) {
    int i, *current_children=calloc(children,sizeof(int)), k=0, value;
    minimax_node *newNode[children];
    char c;
    printf("%d", tree->level);
    for(i=0; i<children; i++) {
        c=fgetc(fin);
        if(c=='(') {
            fscanf(fin, "%d)", &current_children[i]);
            fgetc(fin);
            newNode[i]=init_minimax(current_children[i]);
            newNode[i]->level=tree->level+1;
            tree->children[i]=newNode[i];
            
        }
        else if(c=='[') {
            fscanf(fin, "%d]", &value);
            fgetc(fin);
            newNode[i]=init_minimax(current_children[i]);
            newNode[i]->level=tree->level+1;
            newNode[i]->value=value;
            newNode[i]->end=1;
            tree->children[i]=newNode[i];
        }
    }
    for(i=0; i<children; i++) {
        create_minimax_tree(fin, tree->children[i], current_children[i]);
    }
    free(current_children);
}

void complete_minimax_tree(minimax_node *tree, int level) {
    int i=0;
    if(tree->end==1 || tree->level==level) return;
    while(tree->children[i]!=NULL) {
        complete_minimax_tree(tree->children[i], level);
        i++;
    }
    i=0;
    tree->value=tree->children[0]->value;
    if(tree->level%2==1) {
        //tree->value=tree->children[0]->value;
        while(tree->children[i]!=NULL) {
            //complete_minimax_tree(tree->children[i], level);
            if(tree->value<tree->children[i]->value) {
                tree->value=tree->children[i]->value;
            }
            i++;
        }
    }
    if(tree->level%2==0) {
        //tree->value=tree->children[0]->value;
        while(tree->children[i]!=NULL) {
            //complete_minimax_tree(tree->children[i], level);
            if(tree->value>tree->children[i]->value) {
                tree->value=tree->children[i]->value;
            }
            i++;
        }
    }
}

void print_minimax_tree(minimax_node *tree, int k, FILE *fout) {
    if(tree==NULL) return;
    int index=0, l;
    for(l=0; l<k; l++) fputc('\t', fout);
    fprintf(fout, "%d\n", tree->value);
    k++;
    while (tree->children[index]!=NULL && tree->end!=1) {
        print_minimax_tree(tree->children[index], k, fout);
        index++;
    }
    
}
void print_minimax_tree1(minimax_node *tree, int k) {
    if(tree==NULL) return;
    int index=0, l;
    for(l=0; l<tree->level; l++) printf("\t");
    printf("%d\n", tree->value);
    k++;
    if(tree->end==1) return;
    while (tree->children[index]!=NULL && tree->end!=1) {
        print_minimax_tree1(tree->children[index], k);
        index++;
    }
    
}

void destroy_minimax(minimax_node *tree) {
    if (tree == NULL) {
        return;
    }  
    int index=0;
    while(tree->children[index]!=NULL) {
        destroy_minimax(tree->children[index]);
        index++;
    }
    free(tree);
}