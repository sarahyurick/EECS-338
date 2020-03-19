# include <stdio.h>
# include <stdlib.h>
# include <string.h>
void main() {
  char mystring[1000], myotherstring[1000], mystring2[1000], mystring3[1000];
  int mins; float secs;
  int result; FILE *fptr, *fptr2;
  int result2;
  float pmem[32768], pcpu[32768], pmem2[32768], pcpu2[32768];
  int seenpid[32768];
  int seenpid2[32768];
  int i;
  int nl;
  int j;
  int rootonly = 0;

  // initializing array values to 0
  for (i=0; i<=32767; i++) {
    seenpid[i] = 0;
    seenpid2[i] = 0;
    pmem[i] = 0;
    pmem2[i] = 0;
    pcpu[i] = 0;
    pcpu2[i] = 0;
}

  // instead of “inputfile1” and “inputfile2”
  // i am doing “top.snapshot.3.c” and “top.snapshot.4.c”
  fptr = fopen("top.snapshot.3.c", "r");
  fptr2 = fopen("top.snapshot.4.c", "r");
  
  fscanf(fptr,"%s",mystring);
  for (i=1; i<=75; i++) fscanf(fptr,"%s",mystring); // line 1
  fscanf(fptr2,"%s",myotherstring);
  for (i=1; i<=75; i++) fscanf(fptr2,"%s",myotherstring); // line 1
  
  // going through “top.snapshot.3.c” line by line
  for (nl=1; nl<=300; nl++) {
    result = fscanf(fptr,"%s",mystring2); // this should be a 1
    if (result == EOF) break;
    seenpid[atoi(mystring2)] = 1;
    fscanf(fptr,"%s",mystring); // this should be the string root
    if (strcmp(mystring,"root")==rootonly) {
      for (j=1; j<=10; j++) {
        fscanf(fptr,"%s",mystring); // this should be the string root
        if (j==8) {
          // sets pmem[pid], which corresponds to “top.snapshot.3.c” to its %MEM
          pmem[atoi(mystring2)] = atof(mystring);
        } else if (j==9) {
          sscanf(mystring,"%d:%f",&mins,&secs);
          // sets pcpu[pid], which corresponds to “top.snapshot.3.c” to its TIME+
          pcpu[atoi(mystring2)] = 60*((float) mins)+secs;
        }
      }
    } else { // not a root line, but still need to grab 10 fields
      // this omission may be a bug in earlier versions!
      for (j=1; j<=10; j++) {
        fscanf(fptr,"%s",mystring); // this should be the string root
      }
    }
  }

  // restart times for going through next file
  mins=0;
  secs=0;

  // going through “top.snapshot.3.c” line by line
  for (nl=1; nl<=300; nl++) {
    result2 = fscanf(fptr2,"%s",mystring3);
    if (result2 == EOF) break;
    seenpid2[atoi(mystring3)] = 1;
    fscanf(fptr2,"%s",myotherstring); // this should be the string root
    if (strcmp(myotherstring,"root")==rootonly) {
      for (j=1; j<=10; j++) {
        fscanf(fptr2,"%s",myotherstring); // this should be the string root
        if (j==8) {
          // sets pmem2[pid], which corresponds to “top.snapshot.4.c” to its %MEM
          pmem2[atoi(mystring3)] = atof(myotherstring);
        } else if (j==9) {
          sscanf(myotherstring,"%d:%f",&mins,&secs);
          // sets pcpu2[pid], which corresponds to “top.snapshot.4.c” to its TIME+
          pcpu2[atoi(mystring3)] = 60*((float) mins)+secs;
        }
      }
    } else { // not a root line, but still need to grab 10 fields
      // this omission may be a bug in earlier versions!
      for (j=1; j<=10; j++) {
        fscanf(fptr2,"%s",myotherstring); // this should be the string root
      }
    }
  }

// now that we have all of the information about all of the root processes, 
// it’s time to find and report the differences
  for (i=1; i<=32767; i++) {
    if (seenpid[i] != seenpid2[i] && seenpid[i] == 1) printf("PID %d IS AN OLD PROCESS\n",i);
    else if (seenpid[i] != seenpid2[i] && seenpid2[i] == 1) printf("PID %d IS A NEW PROCESS\n",i);
    else if (pmem[i] != pmem2[i]) {
      printf("PID %d MEM HAS CHANGED FROM %f TO %f \n",i,pmem[i],pmem2[i]);
    }
    else if (pcpu[i] != pcpu2[i]) {
      printf("PID %d CPU TIME HAS CHANGED FROM %f TO %f \n",i,pcpu[i],pcpu2[i]);
    }
  }
}
