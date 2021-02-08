#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>

string get_text(void);
// program would work more efficiently if below 3 functions can be assembled to 1.
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //calculate readability according to The Coleman-Liau index
    string text = get_text();
    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);
    int index = round(5.88 * letters / words - 29.6 * sentences / words - 15.8);

    if (index <= 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index <= 15)
    {
        printf("Grade %i\n", index);
    }
    else
    {
        printf("Grade 16+\n");
    }

    return 0;
}

string get_text(void)
{
    // Get string from user
    string text;
    do
    {
        text = get_string("Text: ");
    }
    while (strlen(text) == 0);
    return text;
}

int count_letters(string text)
{
    // count letters from 'a' to 'z', 'A' to 'Z'.
    int letters = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if ((text[i] <= 'Z' && text[i] >= 'A') || (text[i] <= 'z' && text[i] >= 'a'))
        {
            letters ++;
        }
    }
    return letters;
}

int count_words(string text)
{
    // count words (num of ' ' + 1).
    int words = 1;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == ' ')
        {
            words++;
        }
    }
    return words;
}

int count_sentences(string text)
{
    // count sentences (num of '.' + '1' + '?')
    int sentences = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return sentences;
}
