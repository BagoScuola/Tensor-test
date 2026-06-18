#include "stack.h"
#include "tensor.h"
#include <stdlib.h>
#include <stdbool.h>
#define BASE_DIM 16

//struct normale = . | puntatore a struct si usa ->
Stack initiaze_stack(){

  Stack s;
  s.top=-1;
  s.dim=BASE_DIM;
  s.values = malloc(sizeof(StackValue) * s.dim);
  return s;
};

bool is_empty(Stack *s){
  if (s->top == -1) {
    return true;
  } else {
    return false;
  }
};


bool is_full(Stack *s){
  if ((s->top +1) == s->dim) {
    return true;
  } else {
    return false;
  }
};



int resize_stack(Stack *s){

  float rapporto;
  rapporto = (s->top+1) / (float)s->dim ;

  if (is_full(s)) {
    s->values = realloc(s->values, sizeof(StackValue) * (s->dim*2));
    s->dim = s->dim*2;
    return 2;
  } else if (rapporto <= 0.25 && s->dim > BASE_DIM ) {
    s->values = realloc(s->values, sizeof(StackValue) * (s->dim/2));
    s->dim = s->dim/2;
    return 1;
  } else {
    return 0;
  }

}; // se top 1/4 della dim dello stack dimezziamo, se stack è pieno raddoppiamo


void push_tensor(Stack *s, Tensor *t){
  int code;
  code = resize_stack(s);
  s->top += 1;
  s->values[s->top].type = SV_TENSOR;
  s->values[s->top].as.tensor = t;
};

void push_string(Stack *s, char *str){
  int code;
  code = resize_stack(s);
  s->top += 1;
  s->values[s->top].type = SV_STRING;
  s->values[s->top].as.string = str;
};

StackValue pop_value(Stack *s){
  if (is_empty(s)) {
    printf("Error: Stack underflow\n");
    exit(EXIT_FAILURE);
  }
  StackValue sv = s->values[s->top];
  s->top--;
  int code = resize_stack(s);
  return sv;
};

StackValue peek_value(Stack *s){
  if (is_empty(s)) {
    printf("Error: Stack is_empty\n");
    exit(EXIT_FAILURE);
  }
  return s->values[s->top];
};

// wrapper di compatibilità
void push(Stack *s, Tensor *t){
  push_tensor(s, t);
};

Tensor* pop(Stack *s){
  StackValue sv = pop_value(s);
  if (sv.type != SV_TENSOR) {
    printf("Error: tipo errato nello stack, atteso Tensor\n");
    exit(EXIT_FAILURE);
  }
  return sv.as.tensor;
};

Tensor* peek(Stack *s){
  StackValue sv = peek_value(s);
  if (sv.type != SV_TENSOR) {
    printf("Error: tipo errato nello stack, atteso Tensor\n");
    exit(EXIT_FAILURE);
  }
  return sv.as.tensor;
};
