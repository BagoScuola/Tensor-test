#include "stack.h"
#include "tensor.h"
#include "ops.h"
#include <stdlib.h>
#include <string.h>


int get_working_file(FILE *f,char *working_file){

char c = fgetc(f);
int dim_working_file=0;
do {
  working_file[dim_working_file] = c;
  c = fgetc(f);
  dim_working_file++;
} while (c != '"');
  working_file[dim_working_file] = '\0';
  return dim_working_file;

};




void scorri_file(Stack *s,char *filename){

  char working_file[256];
  int dim_working_file = 0;
 FILE *f = fopen(filename, "r");
  if(f == NULL){
    printf("Errore il file non esiste \n");
    exit(EXIT_FAILURE);
  }

  char c;

  do {

  c = fgetc(f);

  switch (c) {
      case '[':
        push(s,initialize_tensor(f,0));
        //printf("writing tensor data:\n");
        //for (int i=0;i<t->size;i++) {
        //  printf("data[%d] = %f\n", i, t->data[i]);
        //}
        break;
      case '"':
        dim_working_file = get_working_file(f,working_file);
        //FILE * prova = fopen(working_file,"w");
        //printf("%s \n", working_file);
        break;
      case '\n':
        //casee
        break;
      case ' ':
        break;
      default:
        //operazione
        {
        char token[256];
        int len = 0;
        token[len++] = c;
        while ((c = fgetc(f)) != EOF && c != ' ' && c != '\n' && c != '\t') {
            if (len < 255) token[len++] = c;
        }
        token[len] = '\0';
        if (strcmp(token, "+") == 0 || strcmp(token, "somma") == 0) {
            somma(s);
        } else {
            printf("Errore: operazione non valida: %s\n", token);
            exit(EXIT_FAILURE);
        }
        }
        break;
  }

  } while (c != EOF);

  // scrivo il risultato sul file di output
  if (dim_working_file > 0) {
    Tensor *res = pop(s);
    FILE *fout = fopen(working_file, "w");
    if (fout == NULL) {
        printf("Errore aprendo il file di output\n");
        exit(EXIT_FAILURE);
    }
    fprintf(fout, "[ ");
    for (int i = 0; i < res->size; i++) {
        fprintf(fout, "%g ", res->data[i]);
    }
    fprintf(fout, "]\n");
    fclose(fout);
    decrement_refcount(res);
  }

};


int main(int argc, char *argv[])
{
  Stack s = initiaze_stack();
  char* filename=argv[1];
  scorri_file(&s,filename);


   return EXIT_SUCCESS;

}
