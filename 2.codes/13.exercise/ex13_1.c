#include <stdio.h>

int main(int argc, char *argv[]) 
{
    if(argc < 2) {
        printf("ERROR: You need at least one arguments.\n");
        // this is how you abort a program
        return 1;
    }

    // read all input argument 
    for (int j = 1;j < argc;j++)
    {
        for(int i = 0; argv[j][i] != '\0'; i++) 
        {

            if (argv[j][i] >= 'A' && argv[j][i] <= 'Z')
            {
                argv[j][i] += 32; 
            }

            switch(argv[j][i]) {
                case 'a':
                    printf("%d: 'A'\n", i);
                    break;
                case 'e':
                    printf("%d: 'E'\n", i);
                    break;
                case 'i':
                    printf("%d: 'I'\n", i);
                    break;
                case 'o':
                    printf("%d: 'O'\n", i);
                    break;
                case 'u':
                    printf("%d: 'U'\n", i);
                    break;
                case 'y':
                    printf("%d: 'Y'\n", i);
                    break;
                default:
                    printf("%d: %c is not a vowel\n", i, argv[j][i]);
            }
        }
    }
    return 0;
}