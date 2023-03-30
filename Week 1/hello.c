#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //input for user's name
    string name = get_string("What's your name?");
    //outputs user's name with hello
    printf("hello, %s\n", name);
}
