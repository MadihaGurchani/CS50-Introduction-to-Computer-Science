#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

string Grade_Level(int number);
int main(void)
{
    //Initialization
    int letters = 0;
    int words = 1;
    int sentences = 0;
    //Get User Input
    string Text = get_string("Text: ");
    //length of User Input
    int len = strlen(Text);
    //Counting letters, words and sentences.
    for (int i = 0; i < len ; i++)
    {
        //Count letters
        if (isalpha(Text[i]))
        {
            letters++;
        }
        else if (isspace(Text[i]))
        {
            words++;
        }
        else if (Text[i] == '.' || Text[i] == '?' || Text[i] == '!')
        {
            sentences++;
        }
    }
    //Average Letters per 100 words
    float L =  100 * ((float) letters / (float) words) ;
    //Average Sentences per 100 words
    float S = 100 * ((float) sentences / (float) words);
    //Using Coleman-Liau index
    float index =  0.0588 * L - 0.296 * S - 15.8;
    //Print appropriate Grade Level
    int Count = round(index);
    if (Count < 1 || Count >= 16)
    {
         string Grade = Grade_Level(Count);
         printf("%s\n", Grade);
    }
    else
    {
        printf("Grade %i\n", Count);
    }
}

string Grade_Level(int number)
{
    string Outputs = "";
    if (number < 1)
    {
        Outputs = "Before Grade 1";
    }
    else if (number >= 16)
    {
        Outputs = "Grade 16+";
    }
    return Outputs;
}
