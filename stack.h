#ifndef stack_h
#define stack_h

#include <stdio.h>
#include <stdbool.h>
#include "tensor.h"


typedef struct {
    int top; // indice dell'ultimo elemento inserito nello stack
    int dim; // dimensione di default dello stack 16
    Tensor **tensor_pointers; // array di puntatori a tensor 
} Stack; 

Stack initiaze_stack(); // inizializza lo stack, setta top a -1 e dim a 0
bool is_empty(Stack *s); // restituisce true se lo stack è vuoto, false altrimenti
bool is_full(Stack *s); // restituisce true se lo stack è pieno, false altrimenti
int resize_stack(Stack *s); // 0-> resta come e, 1 -> dimezzato , 2 -> raddoppiato
void push(Stack *s, Tensor *t); // inserisce un puntatore a tensor nello stack, se lo stack è pieno non fa nulla
Tensor* pop(Stack *s); // restituisce un puntatore a tensor e lo rimuove, se lo stack è vuoto restituisce NULL 
Tensor* peek(Stack *s); // restituisce un puntatore a tensor senza rimuoverlo

#endif
