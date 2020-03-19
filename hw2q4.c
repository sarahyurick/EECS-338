# include <stdio.h>
# include <stdlib.h>
# include <string.h>
void main() {
  char mystring[1000], mystring2[1000];
  int mins; float secs;
  int result; FILE *fptr;
  float mycounter = 0;
  float mycounter2 = 0;
  fptr = fopen("top.snapshot.3.c", "r");
  fscanf(fptr,"%s",mystring);

  int i;
  int nl;
  int j;
  for (i=1; i<=75; i++) fscanf(fptr,"%s",mystring); // line 1

  for (nl=1; nl<=300; nl++) {
    result = fscanf(fptr,"%s",mystring2); // this should be a 1
    if (result == EOF) break;
    fscanf(fptr,"%s",mystring); // this should be the string root
    if (strcmp(mystring,"root")==0) {
      printf("%s ",mystring2);
      printf("%s ",mystring);
      for (j=1; j<=10; j++) {
        fscanf(fptr,"%s",mystring); // this should be the string root
        if (j==8) {
          printf("MEM=%s ",mystring);
          mycounter += atof(mystring);
          printf("MEM=%f ",atof(mystring));
        } else if (j==9) {
          sscanf(mystring,"%d:%f",&mins,&secs);
          printf("MINS=%d ",mins);
          printf("SECS=%f ",secs);
          printf("TOTALSECS=%f ",60*((float) mins)+secs);
          mycounter2 += 60*((float) mins)+secs;
        } else printf("%s ",mystring);
      }
      printf("\n");
    }
  }
  printf("total memory is %4.2f%% \n", mycounter);
  printf("total cpu is %4.2f secs \n", mycounter2);
}
