#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Input card number
    long card;

    do
    {
        card = get_long("Number: ");
    }
    while (card < 0);

    //Checking length
    long creditnum = card;
    int length = 0;

    while (creditnum > 0)
    {
        creditnum = creditnum / 10;
        length++;
    }

    //checking if length is valid
    if ((length != 13) && (length != 15) && (length != 16))
    {
        printf("INVALID\n");
        return 0; //to end the program
    }

    //calculating checksum
    int sum1 = 0; //sum of digits that aren't multiplied by 2
    int sum2 = 0; //sum of digits that are multiplied by 2
    long num = card;
    int total = 0;
    int digit1, digit2; //the product's digits, max can be 2 digits
    int i, j; //modulus values

    do
    {
        //removing the last digit(in every iteration)
        i = num % 10;
        num = num / 10;
        sum1 = sum1 + i;

        //removing the second last digit(in every iteration)
        j = num % 10;
        num = num / 10;

        //calculating sum2 (doubling the second last digit)
        j = j * 2;
        digit1 = j % 10;
        digit2 = j / 10;
        sum2 = sum2 + digit1 + digit2;
    }
    while (num > 0);

    total = sum1 + sum2;

    //check Luhn Algorithm (last digit should be equal to 0)
    if (total % 10 != 0)
    {
        printf("INVALID\n");
        return 0; //end the program
    }

    //get the starting digits of the card
    long startd = card;

    do
    {
        startd = startd / 10;
    }
    while (startd > 100); //need first two digits, any number below 100 is double digit

    //check for Mastercard (51, 52, 53, 54, 55) and length=16
    if ((startd / 10 == 5) && (startd % 10 > 0 && startd % 10 < 6) && (length == 16))
    {
        printf("MASTERCARD\n");
    }

    //check for Amex (34 or 37) and length=15
    else if ((startd / 10 == 3) && (startd % 10 == 4 || startd % 10 == 7) && (length == 15))
    {
        printf("AMEX\n");
    }

    //check for VISA (4) and length=13,16
    else if ((startd / 10 == 4) && (length == 13 || length == 16))
    {
        printf("VISA\n");
    }

    //if none of the checks apply
    else
    {
        printf("INVALID\n");
    }

}
