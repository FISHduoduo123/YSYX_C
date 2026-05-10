#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

//a struct type label is person
struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

// return pointer of type:struct Person * 
struct Person *Person_create(char *name, int age, int height, int weight)
{
    // allocate mem-equal with struct Person data and save the struct pointer in who pointer
    struct Person *who = malloc(sizeof(struct Person));
    // check if who is NULL
    assert(who != NULL);

    // allocate a mem-equal with string array data and save the pointer to the string array in name pointer   
    who->name = strdup(name);
    // save age 
    who->age = age;
    // save height
    who->height = height;
    // save weight
    who->weight = weight;

    // return a pointer to the struct person in the mem 
    return who;
}

void Person_destroy(struct Person *who)
{
    // check if who is NULL
    assert(who != NULL);
    // free data string array from mem-equal
    free(who->name);
    // free struct who from mem-equal
    free(who);
}

// print the person's information from struct person 
void Person_print(struct Person *who)
{
    printf("Name: %s\n", who->name);
    printf("\tAge: %d\n", who->age);
    printf("\tHeight: %d\n", who->height);
    printf("\tWeight: %d\n", who->weight);
}

int main(int argc, char *argv[])
{
    // make two people structures
    struct Person *joe = Person_create(
            "Joe Alex", 32, 64, 140);

    struct Person *frank = Person_create(
            "Frank Blank", 20, 72, 180);

    // print them out and where they are in memory
    printf("Joe is at memory location %p:\n", joe);
    Person_print(joe);

    printf("Frank is at memory location %p:\n", frank);
    Person_print(frank);

    // make everyone age 20 years and print them again
    joe->age += 20;
    joe->height -= 2;
    joe->weight += 40;
    Person_print(joe);

    frank->age += 20;
    frank->weight += 20;
    Person_print(frank);

    // destroy them both so we clean up
    Person_destroy(joe);
    Person_destroy(frank);

    return 0;
}