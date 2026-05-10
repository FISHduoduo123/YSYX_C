
#include <stdio.h>
#include <string.h>
#include "dbg.h"

#define MAX_DATA 100

typedef enum EyeColor {
    BLUE_EYES, GREEN_EYES, BROWN_EYES,
    BLACK_EYES, OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
    "Blue", "Green", "Brown", "Black", "Other"
};

typedef struct Person {
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;
    float income;
} Person;

/*
    使用scanf编写函数，按照文件名读取文件内容，每次读取单个字符，
    但是不要越过（文件和缓冲区的）末尾。
    使这个函数接受字符串大小来更加通用，
    并且确保无论什么情况下字符串都以'\0'结尾
*/
char *file_read(char *filename, int len)
{
    char *buffer[len+1];
    FILE *file = fopen(filename, "r");
    check(file, "Failed to open file: %s", filename);
    
    for(int i = 0; i < len; i++) {
        buffer[i] = fscanf(file, "%c", &buffer[i]);
        i++;
    }
    buffer[len] = '\0';
    fclose(file);
    return buffer;

    error:
        fclose(file);
        return NULL;
    
}

int main(int argc, char *argv[])
{
    Person you = {.age = 0};
    int i = 0;
    char *in = NULL;
    // 修改程序，是输入的名字不包含任何换行符和空白字符。
    printf("What's your First Name? ");
    in = fgets(you.first_name, MAX_DATA-1, stdin);
    check(in != NULL, "Failed to read first name.");
    // 去除换行符和空白字符
    you.first_name[strcspn(you.first_name, "\n")] = '\0';

    printf("What's your Last Name? ");
    in = fgets(you.last_name, MAX_DATA-1, stdin);
    check(in != NULL, "Failed to read last name.");
    you.last_name[strcspn(you.last_name, "\n")] = '\0';

    // 1. 将这个程序重写为不需要fscanf的版本。
    // 你需要使用类似于atoi的函数来将输入的字符串转换为数值。

    // 2. 修改这个程序，使用scanf来代替fscanf

    printf("How old are you? ");
    // int rc = fscanf(stdin, "%d", &you.age);
    // int rc = atoi(fgets(&you.age, MAX_DATA-1, stdin));
    int rc = scanf("%d", &you.age);
    check(rc > 0, "You have to enter a number.");

    printf("What color are your eyes:\n");
    for(i = 0; i <= OTHER_EYES; i++) {
        printf("%d) %s\n", i+1, EYE_COLOR_NAMES[i]);
    }
    printf("> ");

    int eyes = -1;
    //rc = fscanf(stdin, "%d", &eyes);
    // rc = atoi(fgets(&eyes, MAX_DATA-1, stdin));
    rc = scanf("%d", &eyes);
    check(rc > 0, "You have to enter a number.");

    you.eyes = eyes - 1;
    check(you.eyes <= OTHER_EYES && you.eyes >= 0, "Do it right, that's not an option.");

    printf("How much do you make an hour? ");
    // rc = fscanf(stdin, "%f", &you.income);
    // rc = atof(fgets(&you.income, MAX_DATA-1, stdin));
    rc = scanf("%f", &you.income);
    check(rc > 0, "Enter a floating point number.");

    printf("----- RESULTS -----\n");

    printf("First Name: %s ", you.first_name);
    printf("Last Name: %s ", you.last_name);
    printf("Age: %d\n", you.age);
    printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
    printf("Income: %f\n", you.income);

    return 0;
error:
    return -1;
}