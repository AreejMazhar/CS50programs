#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //user input for positive integer between 1 to 8 inclusive

    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //making left side of the pyramid
    //need rows and columns

    int row;
    int column;
    int space;

    for (row = 0; row < height; row++)
    {
        for (space = 0; space < height - row - 1; space++)
        {
            printf(" ");
        }

        for (column = 0; column <= row; column++)
        {
            printf("#");
        }

        //2 space in between the pyramids
        printf("  ");

        //print right side of pyramid
        for (column = 0; column <= row; column++)
        {
            printf("#");
        }
        
        printf("\n");
    }
}
