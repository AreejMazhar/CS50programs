#include <cs50.h>
#include <stdio.h>
#include <string.h>

const int BITS_IN_BYTE = 8;

void print_bulb(int bit);

int main(void)
{
    //TODO
    //ask user for input
    string text = get_string("Message: ");

    //Convert message to ASCII(decimal)
    for (int i = 0, n = strlen(text); i < n; i++) //this loops through every letter in the text
    {
        int ascii = text[i];

        //Convert ASCII to binary
        int byte[] = {0, 0, 0, 0, 0, 0, 0, 0};
        int j = 0;

        while (ascii > 0)
        {
            byte[j] = ascii % 2; //modulus divides by 2 and shows remainder
            ascii = ascii / 2; //divides decimal value by 2 to repeat the process until 0
            j++;
        }

        //print the bulbs
        for (int k = BITS_IN_BYTE - 1; k >= 0; k--) //prints the array in reverse
        {
            print_bulb(byte[k]);
        }
        printf("\n");
    }

}

void print_bulb(int bit)
{
    if (bit == 0)
    {
        // Dark emoji
        printf("\U000026AB");
    }
    else if (bit == 1)
    {
        // Light emoji
        printf("\U0001F7E1");
    }
}
