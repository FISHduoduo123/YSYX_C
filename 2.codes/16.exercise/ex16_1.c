#include <stdio.h>
#include <assert.h>
#include <string.h>

//a struct type label is person
struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

// create a stack person and stack pointer
struct Person person[20];
char sp_person = 0;

// return pointer of type:struct Person * 
char Person_create(char *name, int age, int height, int weight)
{
    // save the string array name   
    person[sp_person].name = name;
    // save age 
    person[sp_person].age = age;
    // save height
    person[sp_person].height = height;
    // save weight
    person[sp_person].weight = weight;
    // push sp+1 
    return sp_person++;
}

void Person_destroy()
{
    // pop sp-1 
    sp_person--;
}

// print the person's information from statck
void Person_print(char sp)
{
    if (sp == sp_person ) 
    {
        printf("This id an invalid address !!!!");
        return;
    }
    printf("Name: %s\n", person[sp].name);
    printf("\tAge: %d\n", person[sp].age);
    printf("\tHeight: %d\n", person[sp].height);
    printf("\tWeight: %d\n", person[sp].weight);
}

int main(int argc, char *argv[])
{
    // make two people structures
    char joe = Person_create(
            "Joe Alex", 32, 64, 140);

    char frank = Person_create(
            "Frank Blank", 20, 72, 180);

    // print them out and where they are in memory
    printf("Joe is at memory location %d:\n", joe);
    Person_print(joe);

    printf("Frank is at memory location %d:\n", frank);
    Person_print(frank);

    // make everyone age 20 years and print them again
    person[joe].age += 20;
    person[joe].height -= 2;
    person[joe].weight += 40;
    Person_print(joe);

    person[frank].age += 20;
    person[frank].weight += 20;
    Person_print(frank);

    // pop them form stack 
    Person_destroy();
    Person_destroy();

    return 0;
}