#include <stdio.h>
#include <ctype.h>
#include "dbg.h"


int print_a_message(const char *msg, int str_len)
{
    printf("A STRING: %s\n", msg);

    return 0;
}


int uppercase(const char *msg, int str_len)
{

    check(msg != NULL, "NULL was passed instead of a string.");
    int i = 0;

    // BUG: \0 termination problems
    for(i = 0; i < str_len; i++) {
        printf("%c", toupper(msg[i]));
    }

    printf("\n");

    return 0;

    error:
        return -1;
}

int lowercase(const char *msg, int str_len)
{
    check(msg != NULL, "NULL was passed instead of a string.");
    int i = 0;

    // BUG: \0 termination problems
    for(i = 0; i < str_len; i++) {
        printf("%c", tolower(msg[i]));
    }

    printf("\n");

    return 0;

    error:
        return -1;
}

int fail_on_purpose(const char *msg, int str_len)
{
    return 1;
}
