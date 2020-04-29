#include <cs50.h>
#include <stdio.h>

int get_height(string prompt);
int main(void)
{
    //Call get_height function to get value
    int height = get_height("Height: ");
    //Make pyramid with value entered
    for (int row = 0; row < height + 1; row++)
    {
        //iterate over each row
        if (row > 0)
        {
            int sign = height - row;
            printf("%.*s", sign, "             ");
        }
        //iterate over each colum
        for (int colum = 0 ; colum < row ; colum++)
        {
            printf("#");
        }
        //Move to next line
        printf("\n");
    }
}



//Prompt user for value
int get_height(string prompt)
{
    int number;
    do
    {
        number = get_int("%s", prompt);
    }
    //Run loop only if number is between 1 and 8 inclusive
    while (number < 1 || number > 8);
    return number;
}
