#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

bool key_check(string s);
char rotate(char c, int k);

int main(int argc, string argv[])
{
    //key check
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //check that the key is numerical
    bool check = key_check(argv[1]);
    if (check == false)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    //convert argv[1] into int
    int key = atoi(argv[1]);

    //prompt user for plain text
    string plaintext = get_string("Plain text: ");
    printf("Ciphertext: ");

    //call rotate funcion
    for (int j = 0, length = strlen(plaintext); j < length; j++)
    {
        char letter = rotate(plaintext[j], key);
        printf("%c", letter);
    }
    printf("\n");
}

bool key_check(string s)
{
    bool flag = false;

    for (int i = 0, n = strlen(s); i < n; i++)
    {
        if (!isdigit(s[i]))
        {
            flag = false;
        }
        else
        {
            flag = true;
        }
    }

    if (flag == false)
    {
        return false;
    }
    else
    {
        return true;
    }
}

char rotate(char c, int k)
{
    char enc = '\0'; //encrypted character

    if (!isalpha(c)) //if character not an alphabet, returns as it is
    {
        enc = c;
    }

    else if (isupper(c)) //check if character is uppercase
    {
        enc = (c - 65 + k) % 26 + 65;
    }

    else if (islower(c)) //check if character is lowercase
    {
        enc = (c - 97 + k) % 26 + 97;
    }
    return enc;
}
