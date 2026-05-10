#include <stdio.h>
#include <string.h>



void print_letters(char arg[])
{
    for (int i=0; arg[i]!='\0'; i++)
    {
        printf("%c",arg[i]);
    }
    printf(" == %ld\n",strlen(arg));
}

void print_arguments(int argc, char *argv[])
{
    for(int i = 0; i < argc; i++) {
        print_letters(argv[i]);
    }
}

int main(int argc, char *argv[])
{
    print_arguments(argc, argv);
    return 0;
}
