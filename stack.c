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
  s.tensor_pointers = malloc(sizeof(Tensor *) * s.dim);
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
    s->tensor_pointers = realloc(s->tensor_pointers, sizeof(Tensor *) * (s->dim*2));
    s->dim = s->dim*2;
    return 2;
  } else if (rapporto <= 0.25 && s->dim > BASE_DIM ) {
    s->tensor_pointers = realloc(s->tensor_pointers, sizeof(Tensor *) * (s->dim/2));
    s->dim = s->dim/2;
    return 1;
  } else {
    return 0;
  }

}; // se top 1/4 della dim dello stack dimezziamo, se stack è pieno raddoppiamo


void push(Stack *s, Tensor *t){
  int code;
  code = resize_stack(s);
  s->top +=1;
  s->tensor_pointers[s->top]= t;

};

Tensor* pop(Stack *s){
  if (is_empty(s)) {
    printf("Error: Stack is_empty \n");
    exit(EXIT_FAILURE);
  } else {
  Tensor *t = (s->tensor_pointers[s->top]);
  s->top-- ;
  int code=resize_stack(s);
  return t;
  }
};


Tensor* peek(Stack *s){
  if (is_empty(s)) {
    printf("Error: Stack is_empty \n");
    exit(EXIT_FAILURE);
  } else {
  Tensor *t = (s->tensor_pointers[s->top]);
  return t;
  }
};
