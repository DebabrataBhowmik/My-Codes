#include <stdio.h>

int main(){
  double parLambda=1.0;
  double pargDark=2.0;
  double parMchi=3.0;
  double parMBX=4.0;
  double parMHS=5.0;

  FILE *fPtr;
  char *filename = "file_append.txt";
  fPtr = fopen(filename, "a");
  fprintf(fPtr, "%0.12lf %0.12lf %0.12lf %0.12lf %0.12lf \n",parLambda, pargDark, parMchi, parMBX, parMHS);
  fclose(fPtr);
}
