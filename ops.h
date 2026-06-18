#ifndef OPS_H
#define OPS_H

#include "stack.h"
#include "tensor.h"

int somma(Stack *s);
int differenza(Stack *s);
int prodotto(Stack *s);

int maggiore_confronto(Stack *s);
int minore_confronto(Stack *s);
int uguaglianza_confronto(Stack *s);

int and_logico(Stack *s);
int or_logico(Stack *s);
int negazione_logica(Stack *s);

int maschera(Stack *s);

int prodotto_matrici(Stack *s);
int prodotto_intero_matrici(Stack *s);
int convoluzione(Stack *s);

int reshape(Stack *s);
int ravel(Stack *s);
int get_dim(Stack *s);

int tensor_random(Stack *s);

int relu(Stack *s);
int min(Stack *s);
int max(Stack *s);


int somma_tensore(Stack *s);
int fill(Stack *s);

int print_tensor(Stack *s);
int dup(Stack *s);
int swap(Stack *s);
int over(Stack *s);
int drop(Stack *s);

int read_pgm(Stack *s, char *filename);
int write_pgm(Stack *s, char *filename);
int read_from_file_tensor(Stack *s, char *filename);
int salva_tensore_su_file(Stack *s, char *filename);

#endif 
