#ifndef stack_h
#define stack_h

#include <stdio.h>
#include <stdbool.h>
#include "tensor.h"

typedef enum { SV_TENSOR, SV_STRING } ValueType;

typedef struct {
    ValueType type;
    union {
        Tensor *tensor;
        char *string;
    } as;
} StackValue;

typedef struct {
    int top; // indice dell'ultimo elemento inserito nello stack
    int dim; // dimensione di default dello stack 16
    StackValue *values; // array di StackValue
} Stack; 

Stack initiaze_stack(); // inizializza lo stack, setta top a -1 e dim a 0
bool is_empty(Stack *s); // restituisce true se lo stack è vuoto, false altrimenti
bool is_full(Stack *s); // restituisce true se lo stack è pieno, false altrimenti
int resize_stack(Stack *s); // 0-> resta come e, 1 -> dimezzato , 2 -> raddoppiato
void push_tensor(Stack *s, Tensor *t); // inserisce un tensor nello stack
void push_string(Stack *s, char *str); // inserisce una stringa nello stack (prende ownership)
StackValue pop_value(Stack *s);  // rimuove e restituisce il valore in cima
StackValue peek_value(Stack *s); // restituisce il valore in cima senza rimuoverlo
// wrapper di compatibilità
void push(Stack *s, Tensor *t);
Tensor* pop(Stack *s);
Tensor* peek(Stack *s);

#endif
