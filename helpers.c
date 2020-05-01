#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //iterate over the height of the image
    for (int i = 0; i < height; i++)
    {
        //iterate over the width of the image
        for (int j = 0; j < width; j++)
        {
            //Calculate average of all three colours
            int avg = round(((float)image[i][j].rgbtBlue + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtRed)/3);

            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE original[height][width];
    //Create a duplicate image
    for (int i =  0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            original[i][j] = image[i][j];
        }
    }
    //Assign sepia values
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * (float)original[i][j].rgbtRed + .769 * (float)original[i][j].rgbtGreen + .189 * (float)original[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * (float)original[i][j].rgbtRed + .686 *(float)original[i][j].rgbtGreen + .168 * (float)original[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * (float)original[i][j].rgbtRed + .534 * (float)original[i][j].rgbtGreen + .131 * (float)original[i][j].rgbtBlue);
            //check if sepia values between 0 and 255
            if (sepiaRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                 image[i][j].rgbtRed = sepiaRed;
            }
            if (sepiaBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                 image[i][j].rgbtRed = sepiaBlue;
            }
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                 image[i][j].rgbtRed = sepiaGreen;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
