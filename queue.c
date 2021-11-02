#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

queue* init_queue() {
    queue* q=malloc(sizeof(queue));
    q->front=NULL;
    q->back=NULL;
    q->size=0;
    return q;
}

void enqueu(queue *q, minimax_node *tree) {
    node *newnode=malloc(sizeof(node));
    newnode->tree=tree;
    newnode->next=NULL;
    if(q->front==NULL && q->back==NULL) {
        q->front=newnode;
        q->back=newnode;
    }
    else {
        q->back->next=newnode;
        q->back=newnode;
    }
    q->size++;
}

void dequeue(queue *q) {
    if(q->front==NULL) return;
    if(q->front==q->back) {
        free(q->front);
        q->front=NULL;
        q->back=NULL;
        q->size=0;
    }
    else {
        node *temp=q->front;
        q->front=q->front->next;
        q->size--;
    }
}

minimax_node* front(queue* q) {
    if(q->front==NULL) return NULL;
    return q->front->tree;
}