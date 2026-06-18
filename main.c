#include "stack.h"
#include "tensor.h"
#include "ops.h"
#include <stdlib.h>


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
  int dim_working_file;
 FILE *f = fopen(filename, "r");
  if(f == NULL){
    printf("Errore il file non esiste \n");
  }

  char *buffer;
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
        break;
  }

  } while (c != EOF);


};


int main(int argc, char *argv[])
{
  Stack s = initiaze_stack();
  //printf("var = %d\n", s.dim);
  s.top=15;
  //resize_stack(&s);
  //printf("var = %d\n", s.dim);
  Tensor t;
  t.ndim=10;
  t.size=1;
  push(&s, &t);
  //printf("%d\n", peek(&s).ndim);
  //printf("stack dim: %d\n", s.dim);
  char* filename=argv[1];
  scorri_file(&s,filename);
  


   return EXIT_SUCCESS;

}
