#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg = 0;
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0; j < width ; j++ )
        {
            avg = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen)/3);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height ; i++)
    {
         for (int j = 0; j < width; j++)
        {
          // finding sepia values
          int   sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
          int   sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
          int   sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
          //assigning sepia values to pixels if they are correct
          if  (sepiaRed <=255)
          {
           image[i][j].rgbtRed = sepiaRed;
          }
          else
          {
              image[i][j].rgbtRed = 255;
          }
          if (sepiaGreen <=255)
          {
              image[i][j].rgbtGreen = sepiaGreen;
          }
          else
          {
             image[i][j].rgbtGreen = 255;
          }
          if (sepiaBlue)
          {
              image[i][j].rgbtBlue = sepiaBlue;
          }
          else
          {
            image[i][j].rgbtBlue = 255;
          }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //initializing temporary values
    int Red = 0;
    int Blue = 0;
    int Green = 0;
    int w = width;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Placing image pixels to temporary storage
             Red = image[i][j].rgbtRed;
             Blue = image[i][j].rgbtBlue;
             Green = image[i][j].rgbtGreen;
            //Swapping
            image[i][j].rgbtRed = image[i][w].rgbtRed;
            image[i][j].rgbtBlue = image[i][w].rgbtBlue;                            
            image[i][j].rgbtGreen = image[i][w].rgbtGreen;
            //More Swapping
            image[i][w].rgbtRed = Red;
            image[i][w].rgbtBlue = Blue;
            image[i][w].rgbtGreen = Green;
            //Correcting width values
            w--;
            if ( w < 0)
            {
                w = width;
                break;
            }
        }
    }
    return;
}
void blur(int height, int width, RGBTRIPLE image[height][width])
{
 //initializing temporary values
    RGBTRIPLE original[height][width];
    int Counter = 0;
    int Red_Sum = 0;
    int Blue_Sum = 0;
    int Green_Sum = 0;
for (int i = 0; i < height; i++)
{
    for (int j = 0; j < width; j ++)
    {
        original[i][j] = image[i][j];
    }
}
for (int i = 0; i < height; i++)
{
    for (int j = 0; j < width; j ++)
    {
        if (i - 1 >= 0 && j - 1 >= 0)
        {
            Red_Sum += original[i- 1][j - 1].rgbtRed;
            Blue_Sum += original[i- 1][j - 1].rgbtBlue;
            Green_Sum += original[i- 1][j - 1].rgbtGreen;
            Counter++;
        }
        if (i - 1 >= 0)
        {
            Red_Sum += original[i- 1][j].rgbtRed;
            Blue_Sum += original[i- 1][j].rgbtBlue;
            Green_Sum += original[i- 1][j].rgbtGreen;
            Counter++;
        }
        if (i - 1 >= 0 && j + 1 <= width - 1)
        {
            Red_Sum += original[i- 1][j + 1].rgbtRed;
            Blue_Sum += original[i- 1][j + 1].rgbtBlue;
            Green_Sum += original[i- 1][j + 1].rgbtGreen;
            Counter++;
        }
        if ( j + 1 <= width - 1)
        {
            Red_Sum += original[i][j + 1].rgbtRed;
            Blue_Sum += original[i][j + 1].rgbtBlue;
            Green_Sum += original[i][j + 1].rgbtGreen;
            Counter++;
        }
        if (i + 1 <= height - 1 && j + 1 <= width - 1)
        {
            Red_Sum += original[i + 1][j + 1].rgbtRed;
            Blue_Sum += original[i + 1][j + 1].rgbtBlue;
            Green_Sum += original[i + 1][j + 1].rgbtGreen;
            Counter++;
        }
        if (i + 1 <= height - 1)
        {
            Red_Sum += original[i + 1][j].rgbtRed;
            Blue_Sum += original[i + 1][j].rgbtBlue;
            Green_Sum += original[i + 1][j].rgbtGreen;
            Counter++;
        }
        if ( i + 1 <= height - 1 && j - 1 >= 0)
        {
            Red_Sum += original[i + 1][j - 1].rgbtRed;
            Blue_Sum += original[i + 1][j - 1].rgbtBlue;
            Green_Sum += original[i + 1][j - 1].rgbtGreen;
            Counter++;
        }
        if (j - 1 >= 0)
        {
            Red_Sum += original[i][j - 1].rgbtRed;
            Blue_Sum += original[i][j - 1].rgbtBlue;
            Green_Sum += original[i][j - 1].rgbtGreen;
            Counter++;
        }
         Red_Sum += original[i + 1][j + 1].rgbtRed;
         Blue_Sum += original[i + 1][j + 1].rgbtBlue;
         Green_Sum += original[i + 1][j + 1].rgbtGreen;
         Counter++;

         //Final blurred pixel values assign
         image[i][j].rgbtRed = round(Red_Sum / Counter);
         image[i][j].rgbtBlue = round(Blue_Sum / Counter);
         image[i][j].rgbtGreen = round(Green_Sum / Counter);

    }
}
}