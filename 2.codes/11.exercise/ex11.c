#include <stdio.h>

int main(int argc, char *argv[])
{
    // go through each string in argv
    argc--;
    while(argc >= 0) {
        printf("arg %d: %s\n", argc, argv[argc]);
        argc--;
    }

    // let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };

    int i = 3;  // watch for this
    while(i >= 0) {
        printf("state %d: %s\n", i, states[i]);
        i--;
    }

    return 0;
}