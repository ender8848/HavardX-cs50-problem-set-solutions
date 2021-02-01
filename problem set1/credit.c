#include <stdio.h>
#include <cs50.h>
#include <math.h>

bool checksum(long cn);
long get_cn(void);
void type(long cn);


int main(void)
{
    // Take in card number(cn) and do checksum to see if cn is valid(stored in bool legit)
    long cn = get_cn();
    bool legit = checksum(cn);

    // If valid, check which kind of card it is
    if (legit)
    {
        // printf("CHECKSUM VALID\n");
        type(cn);
    }
    else
    {
        printf("INVALID\n");
    }
}

long get_cn(void)
{
    // Get card number from user, reprompt if not between 13 and 16 digits.
    long cn = 0;
    do
    {
        cn = get_long("Input your card number:\n");
    }
    while (cn < pow(10,13) || cn > pow(10,17));
    return cn;
}


bool checksum(long cn)
{
    // Check digits sum (based on the mathematical rule that each card follows)
    int sum = 0;
    int digit = 0; // digit stores the digits used here.
    long lts = cn; // comtemporarily store cn
    lts /= 10; // now the last digit of lts == last-to-second digit of cn

    // Double last-to-second to first digits every other digits and calculate their digits' sum
    for (int i = 0; i < 8; i++) // repeat 8 times (would be pretty enough)
    {
        digit = lts % 10 * 2; // %10 always gets the last digit from a number
        lts /= 100;
        sum += digit % 10; // add the last digit
        sum += digit / 10; // add 1 if the doubled number is more than 10
    }

    // Add other digits.
    for (int i = 0; i < 8; i++) // repeat 8 times
    {
        sum += cn % 10;
        cn /= 100;
    }

    if ((float)sum/10 == sum/10)
    {
        return true;
    }
    else
    {
        return false;
    }
}


void type(long cn)
{
    // if passed checksum, check the card type
    if (cn/(long)pow(10,14) < 10 && (cn/(long)pow(10,13) == 34 || cn/(long)pow(10,13) == 37))
    {
        printf("AMEX\n");
    }
    else if (cn/(long)pow(10,15) < 10 && cn/(long)pow(10,14) >= 51 && cn/(long)pow(10,14) <= 55)
    {
        printf("MASTERCARD\n");
    }
    else if (cn/(long)pow(10,15) == 4 || cn/(long)pow(10,12) == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("VALID BUT UNKNOWN CARD TYPE\n");
    }
}