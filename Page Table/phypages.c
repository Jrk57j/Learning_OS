#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include "pagetable.h"

struct node *head;
struct node *current;
struct node *tail;
struct node *previous;

/*
        struct node{
        //signed or unsigned long or int
        int page;
        //signed or unsigned long or int
        int frame;
        struct node *next;
        struct node *previous;

    };
*/

/*

    there are clearly some gaps to fill here, but im thinking something along the lines of dis. 

*/
//insert first
void insert(int page, int frame){
    struct node *tempNode = (struct node*) malloc(sizeof(struct node));
    tempNode-> page = page;
    tempNode-> frame = frame;
    tempNode -> next = head; 
    head = tempNode;
}

void isNull(){
    return head == NULL;
}
//move the current node to the head 

/**
 * 
 * 
 *          head --> node1 --> node2 --> node3--> tail
 *                            ***
 *                   ^point -----------^that(node1 to node3)
 *       to this<---------------^make that (node2 to head)
 *          head to node1
 * */
void  move_to_head(struct node *head, struct node *current, struct node *previous){
    struct node *tempNode = (struct node*) malloc(sizeof(struct node));
    current = tempNode; 
    previous = current->next; 
    current = head;
    head = head->next;
}

void add_next(){
    //struct *node tempNode = (struct node*) malloc(sizeof(struct node));
    if(head->next == NULL){
        insert()
    }
}

