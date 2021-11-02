#ifndef _QUEUE_H
#define _QUEUE_H

typedef struct minimax_node{
    int value;
    int end;
    int visited;
    int level; 
    struct minimax_node* children[11];
} minimax_node;

typedef struct node{
    minimax_node *tree;
    struct node *next;
}node;

typedef struct queue {
    int size;
    node *front;
    node *back;
}queue;

queue* init_queue();
void enque(queue *q, minimax_node *tree);
void dequeue(queue *q);
minimax_node* front(queue *q);

#endif