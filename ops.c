#include "ops.h"


int somma(Stack *s){


  //Controllo che ci siano abbastanza elementi nello stack
if (s->top < 1){
    printf("Lo stack non ha abbastanza elementi\n");
    exit(EXIT_FAILURE);
  }


  //Prendo gli elementi da sommare (con controllo tipo)
  StackValue va = pop_value(s);
  StackValue vb = pop_value(s);

  if (va.type != SV_TENSOR || vb.type != SV_TENSOR) {
    printf("Errore: somma richiede due tensori\n");
    exit(EXIT_FAILURE);
  }

  Tensor *a = va.as.tensor;
  Tensor *b = vb.as.tensor;


  //Controllo che la dimensione dei tensori sia la stessa
  if (a->ndim != b->ndim) {
    printf("Le dimensioni dei tensori sono diverse\n");
    exit(EXIT_FAILURE);
 }


  // Controllo che anche la shape sia la stessa
  for (int i = 0; i < a->ndim; i++) {
      if (a->shape[i] != b->shape[i]) {
          fprintf(stderr, "La Shape dei tesnori è incompatibile %d\n", i);
          exit(EXIT_FAILURE);
      }
  }

  //Creo il tensore "risultato"
 Tensor *res = create_tensor(a->ndim, a->shape, a->size);


    //Riduzione dell'indirezione: Estraendo i puntatori (data_a, data_b, ecc.) e la dimensione (total_elements) in variabili locali, eviti che la CPU debba "entrare" nella struttura Tensor a ogni iterazione del ciclo. Questo semplifica il lavoro del compilatore e riduce i tempi di accesso 
    float *data_a = a->data;
    float *data_b = b->data;
    float *data_res = res->data;
    int total_elements = a->size;

    #pragma omp parallel for
    for (int i = 0; i < total_elements; i++) {
        data_res[i] = data_a[i] + data_b[i];
    }

      //pusho il nuovo tensore nello stack
     push_tensor(s, res);

    // Rilasciamo i riferimenti degli operandi consumati
    decrement_refcount(a);
    decrement_refcount(b);

    return 0;
};
