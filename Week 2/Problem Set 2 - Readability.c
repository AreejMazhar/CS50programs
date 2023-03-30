#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int count_letters(string text);
int count_words(string text);
int count_sentences(string text);
int colemanLiau_index(int letters, int words, int sentences);

int main(void)
{
    //prompt user for text
    string content = get_string("Text: ");

    //call functions to count letters, words and sentences
    int Letters = count_letters(content);
    int Words = count_words(content);
    int Sentences = count_sentences(content);

    //call Coleman-Liau index
    int X = colemanLiau_index(Letters, Words, Sentences);

    //printing out grade (Before Grade 1, Grade 2 - 16, Grade 16+)
    if (X < 1)
    {
        printf("Before Grade 1\n");
    }

    if (X >= 1 && X <= 16)
    {
        printf("Grade %i\n", X);
    }

    if (X > 16)
    {
        printf("Grade 16+\n");
    }

}

//count letters (upper and lower case)
int count_letters(string text)
{
    int total = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i])) //checks if the character is an alphabet
        {
            total += 1 ;
        }
    }
    return total;
}

//count words (separated by spaces)
int count_words(string text)
{
    int total = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == ' ') //checks if the character is a whitespace
        {
            total += 1;
        }
    }

    total += 1; //to count in the last word

    return total;
}

//count sentences (separated by . or ! or ?)
int count_sentences(string text)
{
    int total = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.') //checks if the character is a period
        {
            total += 1;
        }

        if (text[i] == '?') //checks if the character is a question mark
        {
            total += 1;
        }

        if (text[i] == '!') //checks if the character is an exclamation mark
        {
            total += 1;
        }
    }
    return total;
}

//Coleman-Liau index
int colemanLiau_index(int letters, int words, int sentences)
{
    float L = ((float)letters / (float)words) * 100; //average number of letters per 100 words in the text
    float S = ((float)sentences / (float)words) * 100; //average number of sentences per 100 words in the text
    float result = 0.0588 * L - 0.296 * S - 15.8;
    int Index = round(result);

    return Index;
}
