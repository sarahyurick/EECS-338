# include <stdio.h>
# include <string.h>
void main() {
  char mystring[1000];
  char mystring2[1000];
  FILE *fptr;
  fptr = fopen("top.snapshot.3.c", "r");
  fscanf(fptr,"%s",mystring);
  int i;
  int nl;
  int j;
  for (i=1; i<=75; i++) fscanf(fptr,"%s",mystring); // line 1
  for (nl=1; nl<=30000; nl++) {
    fscanf(fptr,"%s",mystring2); // this should be a 1
    fscanf(fptr,"%s",mystring); // this should be the string root
    if (strcmp(mystring,"root")==0) {
      printf("%s ",mystring2);
      printf("%s ",mystring);
      for (j=1; j<=10; j++) {
        fscanf(fptr,"%s",mystring); // this should be the string root
        printf("%s ",mystring);
      }
      printf("\n");
    }
  }
}
