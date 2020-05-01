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
                 image[i][j].rgbtBlue = sepiaBlue;
            }
            if (sepiaGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                 image[i][j].rgbtGreen = sepiaGreen;
            }
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Create a duplicate image
    RGBTRIPLE duplicate_image[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            duplicate_image[i][j] = image[i][j];
        }
    }
    //Correct width
    int length = width - 1;
    //iterate over each row of the image
    for(int i = 0; i < height; i++)
    {
        //iterate over each colum of the image
        for(int j = 0; j < width; j++)
        {
            image[i][j] = duplicate_image[i][length - j];
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Create a og image
    RGBTRIPLE duplicate[height][width];
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            duplicate[i][j] = image[i][j];
        }
    }
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
          //Unique Case first
          //Case (0,0)
          if (i == 0 && j == 0)
            {
                image[i][j].rgbtRed = round((duplicate[i][j].rgbtRed + duplicate[i+1][j].rgbtRed
                + duplicate[i][j+1].rgbtRed + duplicate[i+1][j+1].rgbtRed) / 4.0);

                image[i][j].rgbtGreen = round((duplicate[i][j].rgbtGreen + duplicate[i+1][j].rgbtGreen
                + duplicate[i][j+1].rgbtGreen + duplicate[i+1][j+1].rgbtGreen) / 4.0);

                image[i][j].rgbtBlue = round((duplicate[i][j].rgbtBlue + duplicate[i+1][j].rgbtBlue
                + duplicate[i][j+1].rgbtBlue + duplicate[i+1][j+1].rgbtBlue) / 4.0);
            }
            //Case (0,lastcolum)
            else if (i == 0 && j == width - 1)
            {
                image[i][j].rgbtRed = round((duplicate[i][j].rgbtRed + duplicate[i+1][j].rgbtRed
                + duplicate[i][j-1].rgbtRed + duplicate[i+1][j-1].rgbtRed) / 4.0);

                image[i][j].rgbtGreen = round((duplicate[i][j].rgbtGreen + duplicate[i+1][j].rgbtGreen
                + duplicate[i][j-1].rgbtGreen + duplicate[i+1][j-1].rgbtGreen) / 4.0);

                image[i][j].rgbtBlue = round((duplicate[i][j].rgbtBlue + duplicate[i+1][j].rgbtBlue
                + duplicate[i][j-1].rgbtBlue + duplicate[i+1][j-1].rgbtBlue) / 4.0);
            }
            //Case for First row
            else if (i == 0)
            {
                image[i][j].rgbtRed = round((duplicate[i][j].rgbtRed + duplicate[i][j-1].rgbtRed + duplicate[i][j+1].rgbtRed
                + duplicate[i+1][j].rgbtRed + duplicate[i+1][j-1].rgbtRed + duplicate[i+1][j+1].rgbtRed) / 6.0);

                image[i][j].rgbtGreen = round((duplicate[i][j].rgbtGreen + duplicate[i][j-1].rgbtGreen + duplicate[i][j+1].rgbtGreen
                + duplicate[i+1][j].rgbtGreen + duplicate[i+1][j-1].rgbtGreen + duplicate[i+1][j+1].rgbtGreen) / 6.0);

                image[i][j].rgbtBlue = round((duplicate[i][j].rgbtBlue + duplicate[i][j-1].rgbtBlue + duplicate[i][j+1].rgbtBlue
                + duplicate[i+1][j].rgbtBlue + duplicate[i+1][j-1].rgbtBlue + duplicate[i+1][j+1].rgbtBlue) / 6.0);
            }
            //Case for (last row,first colum)
            else if (i == height - 1 && j == 0)
            {
                image[i][j].rgbtRed = round((duplicate[i][j].rgbtRed + duplicate[i-1][j].rgbtRed
                + duplicate[i][j+1].rgbtRed + duplicate[i-1][j+1].rgbtRed) / 4.0);

                image[i][j].rgbtGreen = round((duplicate[i][j].rgbtGreen + duplicate[i-1][j].rgbtGreen
                + duplicate[i][j+1].rgbtGreen + duplicate[i-1][j+1].rgbtGreen) / 4.0);

                image[i][j].rgbtBlue = round((duplicate[i][j].rgbtBlue + duplicate[i-1][j].rgbtBlue
                + duplicate[i][j+1].rgbtBlue + duplicate[i-1][j+1].rgbtBlue) / 4.0);
            }
            //Case for last colum
            else if (j == 0)
            {
                image[i][j].rgbtRed = round((duplicate[i][j].rgbtRed + duplicate[i-1][j].rgbtRed + duplicate[i+1][j].rgbtRed
                + duplicate[i][j+1].rgbtRed + duplicate[i-1][j+1].rgbtRed + duplicate[i+1][j+1].rgbtRed) / 6.0);

                image[i][j].rgbtGreen = round((duplicate[i][j].rgbtGreen + duplicate[i-1][j].rgbtGreen + duplicate[i+1][j].rgbtGreen
                + duplicate[i][j+1].rgbtGreen + duplicate[i-1][j+1].rgbtGreen + duplicate[i+1][j+1].rgbtGreen) / 6.0);

                image[i][j].rgbtBlue = round((duplicate[i][j].rgbtBlue + duplicate[i-1][j].rgbtBlue + duplicate[i+1][j].rgbtBlue
                + duplicate[i][j+1].rgbtBlue + duplicate[i-1][j+1].rgbtBlue + duplicate[i+1][j+1].rgbtBlue) / 6.0);
            }
            //Case for (last row, last colum)
            else if (i == height - 1 && j == width - 1)
            {
                image[i][j].rgbtRed = round((duplicate[i][j].rgbtRed + duplicate[i-1][j].rgbtRed
                + duplicate[i][j-1].rgbtRed + duplicate[i-1][j-1].rgbtRed) / 4.0);

                image[i][j].rgbtGreen = round((duplicate[i][j].rgbtGreen + duplicate[i-1][j].rgbtGreen
                + duplicate[i][j-1].rgbtGreen + duplicate[i-1][j-1].rgbtGreen) / 4.0);

                image[i][j].rgbtBlue = round((duplicate[i][j].rgbtBlue + duplicate[i-1][j].rgbtBlue
                + duplicate[i][j-1].rgbtBlue + duplicate[i-1][j-1].rgbtBlue) / 4.0);
            }
            //Case for last row
            else if (i == height - 1)
            {
                image[i][j].rgbtRed = round((duplicate[i][j].rgbtRed + duplicate[i][j-1].rgbtRed + duplicate[i][j+1].rgbtRed
                + duplicate[i-1][j].rgbtRed + duplicate[i-1][j-1].rgbtRed + duplicate[i-1][j+1].rgbtRed) / 6.0);

                image[i][j].rgbtGreen = round((duplicate[i][j].rgbtGreen + duplicate[i][j-1].rgbtGreen + duplicate[i][j+1].rgbtGreen
                + duplicate[i-1][j].rgbtGreen + duplicate[i-1][j-1].rgbtGreen + duplicate[i-1][j+1].rgbtGreen) / 6.0);

                image[i][j].rgbtBlue = round((duplicate[i][j].rgbtBlue + duplicate[i][j-1].rgbtBlue + duplicate[i][j+1].rgbtBlue
                + duplicate[i-1][j].rgbtBlue + duplicate[i-1][j-1].rgbtBlue + duplicate[i-1][j+1].rgbtBlue) / 6.0);
            }
            //Case for last colum
            else if (j == width - 1)
            {
                image[i][j].rgbtRed = round((duplicate[i][j].rgbtRed + duplicate[i-1][j].rgbtRed + duplicate[i+1][j].rgbtRed
                + duplicate[i][j-1].rgbtRed + duplicate[i-1][j-1].rgbtRed + duplicate[i+1][j-1].rgbtRed) / 6.0);

                image[i][j].rgbtGreen = round((duplicate[i][j].rgbtGreen + duplicate[i-1][j].rgbtGreen + duplicate[i+1][j].rgbtGreen
                + duplicate[i][j-1].rgbtGreen + duplicate[i-1][j-1].rgbtGreen + duplicate[i+1][j-1].rgbtGreen) / 6.0);

                image[i][j].rgbtBlue = round((duplicate[i][j].rgbtBlue + duplicate[i-1][j].rgbtBlue + duplicate[i+1][j].rgbtBlue
                + duplicate[i][j-1].rgbtBlue + duplicate[i-1][j-1].rgbtBlue + duplicate[i+1][j-1].rgbtBlue) / 6.0);
            }
            //All other between elements
            else
            {
                image[i][j].rgbtRed = round((duplicate[i][j].rgbtRed + duplicate[i][j-1].rgbtRed + duplicate[i][j+1].rgbtRed
                + duplicate[i-1][j].rgbtRed + duplicate[i-1][j-1].rgbtRed + duplicate[i-1][j+1].rgbtRed
                + duplicate[i+1][j].rgbtRed + duplicate[i+1][j-1].rgbtRed + duplicate[i+1][j+1].rgbtRed) / 9.0);

                image[i][j].rgbtGreen = round((duplicate[i][j].rgbtGreen + duplicate[i][j-1].rgbtGreen + duplicate[i][j+1].rgbtGreen
                + duplicate[i-1][j].rgbtGreen + duplicate[i-1][j-1].rgbtGreen + duplicate[i-1][j+1].rgbtGreen
                + duplicate[i+1][j].rgbtGreen + duplicate[i+1][j-1].rgbtGreen + duplicate[i+1][j+1].rgbtGreen) / 9.0);

                image[i][j].rgbtBlue = round((duplicate[i][j].rgbtBlue + duplicate[i][j-1].rgbtBlue + duplicate[i][j+1].rgbtBlue
                + duplicate[i-1][j].rgbtBlue + duplicate[i-1][j-1].rgbtBlue + duplicate[i-1][j+1].rgbtBlue
                + duplicate[i+1][j].rgbtBlue + duplicate[i+1][j-1].rgbtBlue + duplicate[i+1][j+1].rgbtBlue) / 9.0);
            }
        }
    }
    return;
}
