#include <stdio.h>
#include <cs50.h>
#include <math.h>

float get_change(string prompt);
int main(void)
{
    int coins = 0;
    float change = get_change("Change: ");
    //Procedure for counting coins
    if (change > 0.25 || change == 0.25)
    {
        do
        {
            change = change - 0.25;
            coins++;
        }while (change > 0.24);
    }
    if (change > 0.10 || change == 0.10)
    {
        do
        {
            change = change - 0.10;
            coins++;
        }while (change > 0.09);
    }
    if (change > 0.05 || change == 0.05)
    {
        do
        {
            change = change - 0.05;
            coins++;
        }while (change > 0.04);
    }
    if (change > 0.01 || change == 0.01 )
    {
       do
       {

         change = change - 0.01;
         coins++;
       }while ( change > 0.00);
    }
    printf("%i\n", coins);
}

//Prompt user for input
float get_change(string prompt)
{
    float number;
    do
    {
        number = get_float("%s",prompt);
    }
    while(number < 0.00);
    return number;
}
