#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int main( int argc,string argv[])
{
   bool Answer = false;
   if (argc == 2)
   //Validating the key
   {
       int key = atoi(argv[1]);
       //iterate over each object in argv[1]
       for (int i = 0; i < strlen(argv[1]); i++)
       {
           if (isdigit(argv[1][i]))
           {
               Answer = true;
           }
           // Errpr message incase argv[1][i] not a digit
           else
           {
                printf("Usage: ./caesar key\n");
                return 1;
           }
       }
       //Encryption
       if (Answer == true)
           {
               string plain = get_string("plaintext: ");
               int len = strlen(plain);
               for (int i = 0 ; i < len; i++)
               {
                             if (isupper(plain[i]))
                             {
                                 printf("%c",(((plain[i] - 65) + key) % 26) + 65);
                             }
                            else if (islower(plain[i]))
                             {
                                 printf("%c",asc[i] = (((plain[i] - 97) + key) % 26) + 97);
                             }
                            else
                            {
                             printf("ciphertext: %c\n ",plain[i]);
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


