#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) 
{
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() 
{
    List * new = (List *)malloc(sizeof(List));
    new->head = NULL;
    new->tail = NULL;
    new->current = NULL;
    return new;
}

void * firstList(List * list) 
{
    if (list->head == NULL) return NULL;
    Node * aux = list->head;
    list->current = aux;
    return aux->data;
}

void * nextList(List * list) {
    if (list->current == NULL || list->current->next == NULL) return NULL;
    list->current = list->current->next;
    return list->current->data;
}

void * lastList(List * list) {
    if (list->tail == NULL) return NULL;
    list->current = list->tail;
    return list->tail->data;
}

void * prevList(List * list) {
    if (list->current == NULL || list->current->prev == NULL) return NULL;
    list->current = list->current->prev;
    return list->current->data;
}

void pushFront(List * list, void * data) {
    Node *new = createNode(data);
    new->next = list->head;
    new->prev = NULL;
    if (list->head != NULL) list->head->prev = new;
    list->head = new;
    if (list->tail == NULL) list->tail = new;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node *new = createNode(data);
    if (list->current == NULL)
    {
        pushFront(list, data);
        return;
    }
    new->next = list->current->next;
    new->prev = list->current;
    if (list->current->next != NULL) list->current->next->prev = new;
    list->current->next = new;
    if (list->current == list->tail) list->tail = new;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    Node *actual = list->current;

    if (actual == NULL) return NULL;
    if (actual->prev != NULL) 
        actual->prev->next = actual->next;
    if (actual->next != NULL)
        actual->next->prev = actual->prev;
    if (actual == list->head) list->head = actual->next;
    if (actual == list->tail) list->tail = actual->prev;
    void *data = actual->data;
    
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}