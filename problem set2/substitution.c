#include <stdio.h>
#include <cs50.h>
#include <string.h>

int cal_margin(char c, int i);
string get_text(void);
string cipher(string text, int key[]);

int main(int argc, string argv[])
{
    //This program has the following functions
    //1.takes in cipher key; 2.check if key is valid; 3.turns input text into ciphertext; 4.output ciphertext
    if (argc != 2) // - no argument
    {
        printf("Invalid argument\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26) // not 26 chars
    {
        printf("Invalid Key - not 26 characters\n");
        return 2;
    }
    else
    {
        int key_int[26];
        int check = 0;
        // "check = 0" is a very simple and undemanding test that whether the 26 chars in key appear only once
        for (int i = 0; i < 26; i++)
        {
            key_int[i] = cal_margin(argv[1][i], i);
            check += key_int[i];
        }
        if (check != 0)
        {
            printf("Invalid key - chararters should only appear once\n");
            printf("check%i\n", check);
            return 3;
        }
        else
        {
            string text = get_text();
            string ciphertext = cipher(text, key_int);
            printf("ciphertext: %s\n", ciphertext);
            return 0;
        }
    }
}

int cal_margin(char c, int i)
{
    // This function gets the margin between key and common alphabet.
    int margin = 0;
    if (c >= 'a' && c <= 'z')
    {
        margin = c - 'a' - i;
    }
    else if (c >= 'A' && c <= 'Z')
    {
        margin = c - 'A' - i;
    }
    return margin;
}

string get_text(void)
{
    int i = 0;
    string text; // have to statement string type here instead of in the do -while loop
    do
    {
        text = get_string("Plaintext:  ");
    }
    while (strlen(text) == 0);
    return text;
}

string cipher(string text, int key[])
{
    // ‘Cipher’ takes in plain text and key_int(which is the margin array) and cipher the plaintext.
    string ciphertext = text;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] >= 'a' && text[i] <= 'z')
        {
            ciphertext[i] = (char)(text[i] + key[text[i] - 'a']); // key[text[i] - 'a'] helps locate the right margin
        }
        else if (text[i] >= 'A' && text[i] <= 'Z')
        {
            ciphertext[i] = (char)(text[i] + key[text[i] - 'A']);
        }
        else
        {
            // does not change punctuations and numbers.
            ciphertext[i] = text[i];
        }
    }
    return ciphertext;
}
