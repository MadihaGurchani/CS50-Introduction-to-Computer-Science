#include <stdio.h>
#include <cs50.h>
#include <math.h>

float get_change(string prompt);
int main(void)
{
    int coins = 0;
    int change = round(get_change("Change: ")*100);
    //Procedure for counting coins
    if (change > 25 || change == 25)
    {
        do
        {
            change = change - 25;
            coins++;
        }while (change > 24);
    }
    if (change > 10 || change == 10)
    {
        do
        {
            change = change - 10;
            coins++;
        }while (change > 9);
    }
    if (change > 5 || change == 5)
    {
        do
        {
            change = change - 5;
            coins++;
        }while (change > 4);
    }
    if (change > 1 || change == 1 )
    {
       do
       {

         change = change - 1;
         coins++;
       }while ( change > 0);
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
    while(number < 0);
    return number;
}
