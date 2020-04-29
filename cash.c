#include <stdio.h>
#include <cs50.h>
#include <math.h>

float get_change(string prompt);
int main(void)
{
    int coins = 0;
    //Convert the user input to cents
    int change = round(get_change("Change: ") * 100);
    //Check if user input is greater than or equal to 25 cents
    if (change > 25 || change == 25)
    {
        do
        {
            change = change - 25;
            coins++;
        }
        while (change > 24);
    }
    ////Check if user input is greater than or equal to 25 cents
    if (change > 10 || change == 10)
    {
        do
        {
            change = change - 10;
            coins++;
        }
        while (change > 9);
    }
    //Check if user input is greater than or equal to 5 cents
    if (change > 5 || change == 5)
    {
        do
        {
            change = change - 5;
            coins++;
        }
        while (change > 4);
    }
    //Check if user input is greater than or equal to 1 cents
    if (change > 1 || change == 1)
    {
        do
        {

            change = change - 1;
            coins++;
        }
        while (change > 0);
    }
    printf("%i\n", coins);
}

//Prompt user for input
float get_change(string prompt)
{
    float number;
    do
    {
        number = get_float("%s", prompt);
    }
    //Run loop as long as number is less than 0
    while (number < 0);
    return number;
}


