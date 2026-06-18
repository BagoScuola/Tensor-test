#include "tensor.h"
#include <ctype.h>

// la funzione prende in input una stringa e controlla che sia formattata correttamente, cioè che non ci siano lettere o caratteri non accettati e che alla fine del numero non ci siano altri caratteri strani
int check_string(char *s){
  int i=0;
  int n_before=0;
  int n_after=0;

  if (s[i] == '+' || s[i] == '-'){
    i++;
  }

  while(isdigit(s[i])){
    n_before++;
    i++;
  }
  

  if (s[i] == '.') {
    i++;

    while(isdigit(s[i])){
      n_after++;
      i++;
    }
    
  }

  if (s[i] != '\0') {
    return 0;
  }


  if (n_before + n_after == 0) {
    return 0;
  }
  
  return 1;
}



Tensor *initialize_tensor(FILE *f,int mode){

  Tensor *t = malloc(sizeof(Tensor));

  t->ndim=1;
  t->size=0;
  t->refcount=1;
  
  int capacity=2;
  int count=0;

  t ->data = malloc(sizeof(float)*capacity);

  if (mode == 3) {
    return t;
  }

  int spazio,c;

  while (1){
    spazio=0;
    while ((c = fgetc(f)) == ' '){
      spazio++; }
  
    if (c == EOF){
    free(t->data);
    free(t);
    exit(EXIT_FAILURE);
    }
    
    if (spazio == 0){
      free(t->data);
      free(t);
      exit(EXIT_FAILURE);
    }
    
    if (c == ']'){
      break;
    }
      
  char buffer[256];
  int len = 0;

  while (c != EOF && c != ' ' && c != ']'){
    if (len >= 255) {
        free(t->data);
        free(t);
        exit(EXIT_FAILURE);
      }
      buffer[len] = (char)c;
      len++;

      c = fgetc(f);

    }
  if (c == EOF || c == ']') {
    free(t->data);
    free(t);
    exit(EXIT_FAILURE);
  }

  buffer[len] = '\0';

  if (!check_string(buffer)) {
      free(t->data);
      free(t);
      exit(EXIT_FAILURE);
  }
  
  if (count == capacity) {
      capacity*=2;
      t ->data = realloc(t->data, sizeof(float)*capacity);
  }
  
  t->data[count] = strtof(buffer,NULL);
  count++;
  ungetc(c,f); // questo per "rimuovere" l ultimo spazio letto

  }

  if (count == 0) {
    free(t->data);
    free(t);
    exit(EXIT_FAILURE);
  }
  t -> size = count;
  return t;
};

int decrement_refcount(Tensor *t){

  t->refcount-=1;

  if (t->refcount == 0) {
    free(t->data);
  }

  free(t);
  return 0;

};


Tensor* create_tensor(int ndim, int *shape, int size) {
    //  Alloca lo spazio per il Tensore
    Tensor *t = (Tensor *)malloc(sizeof(Tensor));
    if (t == NULL) return NULL;

    t->ndim = ndim;
    t->size = size;
    t->refcount = 1; 

    for (int i = 0; i < ndim; i++) {
        t->shape[i] = shape[i];
    }

    t->data = (float *)malloc(sizeof(float) * size);
    if (t->data == NULL) {
        free(t);
        return NULL;
    }

    return t;
}
