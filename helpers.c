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
            image[i][j].rgbtRed = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen)/3);
            image[i][j].rgbtBlue = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen)/3);
            image[i][j].rgbtGreen = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen)/3);
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
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
