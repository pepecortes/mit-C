#include <stdio.h>

int strspn(const char* str, const char* delims)
    {
    printf("%s\n", *str);
    int output = 100;
    if (output == 100)
        output = -1;
    return output;
    }
    
int main()
    {
    puts("hola");
    int out = strspn("hola karakola", "ak");
    printf("OUTPUT = %i\n", out);
    return 0;
    }
