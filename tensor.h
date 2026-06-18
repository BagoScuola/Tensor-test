#ifndef TENSOR_H
#define TENSOR_H 
#define MAX_DIM 2

#include <stdlib.h>
#include <stdio.h> // fare un header per le lib????
#include <sys/types.h> // per off_t

typedef struct Tensor {
    int ndim; // 1D or 2D
    int shape[MAX_DIM]; // dimensioni del tensore, se 1D shape[0] è la lunghezza, se 2D shape[0] è il numero di righe e shape[1] è il numero di colonne
    int size; // numero totale degli elementi
    float *data; // puntatore all array 
    int refcount; // se d o u
    //FILE *fp; // file pointer per il salvataggio su file, LO FARA LA FUNZIONE MADRE
    //off_t offset; // per skippare i metadati nella lettura delle immagini da file, LO FARA LA FUNZIONE MADRE
} Tensor;

//int initialize_tensor(Tensor *t, int ndim, int *shape, float *data); // inizializza un tensore con le dimensioni specificate, alloca la memoria per i dati e setta refcount a 1
Tensor* create_tensor(int ndim, int *shape, int size);
Tensor *initialize_tensor(FILE *f,int mode); // mode 0 se è file 1 se da operazioni
int tensor_delete(Tensor *t); // dealloca la memoria del tensore
int increment_refcount(Tensor *t); // aggiorna il refcount del tensore, 
int decrement_refcount(Tensor *t); // aggiorna il refcount del tensore,  se refcount arriva a 0 dealloca il tensore

#endif
