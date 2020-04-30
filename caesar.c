#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int main(int argc, string argv[])
{
    bool Answer = false;
    // check if two arguements given
    if (argc == 2)
    {
        //Converting input to int type
        int key = atoi(argv[1]);
        //iterate over each object in argv[1] to check if input is digit
        for (int i = 0; i < strlen(argv[1]); i++)
        {
            if (isdigit(argv[1][i]))
            {
                Answer = true;
            }
            // Errpr message if argv[1][i] not a digit
            else
            {
                printf("Usage: ./caesar key\n");
                return 1;
            }
        }
        //if correct input then proceed
        if (Answer == true)
        {
            string plain = get_string("plaintext: ")
                           int len = strlen(plain);
            char asc[len];
            printf("ciphertext: ");
            //iterate over length of plaintext and encrypt
            for (int i = 0 ; i < len; i++)
            {
                //Check if upper case alphabet
                if (isupper(plain[i]))
                {
                    asc[i] = (((plain[i] - 65) + key) % 26) + 65;
                    printf("%c", asc[i]);
                }
                //Check if lower case alphabet
                else if (islower(plain[i]))
                {
                    asc[i] = (((plain[i] - 97) + key) % 26) + 97;
                    printf("%c", asc[i]);
                }
                //do this if plain[i] not alphabet
                else
                {
                    printf("%c", plain[i]);
                }
            }
            printf("\n");
        }
    }
    // Error message incase argc != 2
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    return 0;
}