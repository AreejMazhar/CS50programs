#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    //commands check
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //check that key is 26 letters long
    string key = argv[1];

    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }


    for (int i = 0, n = strlen(key); i < n; i++) //iterates through every character of the key
    {
        if (!isalpha(key[i])) //check that key is alphabetical
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }

        for (int j = i + 1, length = strlen(key); j < length; j++) //checks the next character of the key
        {
            if (toupper(key[j]) == toupper(key[i])) //checks for repeated elements
            {
                printf("Usage: ./substitution key\n");
                return 1;
            }
        }
    }

    //ask for plain text
    string plaintext = get_string("plaintext: ");

    //covert all letters in key into uppercase
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (islower(key[i]))
        {
            key[i] = key[i] - 32;
        }
    }

    //print cipher text
    printf("ciphertext: ");

    //substitute the letters
    for (int j = 0, n = strlen(plaintext); j < n; j++)
    {
        if (!isalpha(plaintext[j]))
        {
            printf("%c", plaintext[j]);
        }

        else if (isupper(plaintext[j]))
        {
            int position = plaintext[j] - 65;
            printf("%c", key[position]);
        }

        else if (islower(plaintext[j]))
        {
            int position = plaintext[j] - 97; //65 + 32 = 97
            printf("%c", key[position] + 32);
        }
    }
    printf("\n");

}

