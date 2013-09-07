#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define STRSIZE 100
#define NFIELDS 9
#define FILENAME "stateoutflow0708.txt"

int main(void)
    {
    char line[STRSIZE*NFIELDS];
    char s1[STRSIZE];
    char s2[STRSIZE];
    char s3[STRSIZE];
    char s4[STRSIZE];
    char s5[STRSIZE];
    char state[STRSIZE];
    int i1;
    int i2;
    int value;
    int total;
    
    FILE *fp=NULL;
    fp=fopen(FILENAME,"r");
    fgets(line, STRSIZE*NFIELDS, fp); //read 1st line and drop
    while (fgets(line, STRSIZE*NFIELDS, fp))
        {
        sscanf(line, "%s %s %s %s %s %s %i %i %i",
                s1, s2, s3, s4, s5, state, &i1, &i2, &value);
        total += value;
        printf("\t%-25s\t%10i\n", state, value);
        }
        puts("---------------");
        printf("\t%-25s\t%10i\n", "TOTAL", total);
        fclose(fp);
    }
