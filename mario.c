#include <cs50.h>
#include <stdio.h>

int get_height(string prompt);
int main(void)
{
    int height = get_height("Height: ");

    for (int row = 0; row < height + 1; row++)
    {
       if (row > 0)
        {
        int sign = height - row;
        printf("%.*s", sign , "             ");
        }
        for(int colum = 0 ; colum < row ;colum++)
        {
            printf("#");
        }
        printf("\n");
    }
}



//Prompt user for input
int get_height(string prompt)
{
    int number;
    do
    {
        number = get_int("%s", prompt);
    }
    while (number < 1 || number > 8);
    return number;
}
