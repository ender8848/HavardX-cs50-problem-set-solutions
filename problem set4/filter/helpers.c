#include "helpers.h"
#include <stdlib.h>
#include<math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j ++)
        {
            image[i][j].rgbtBlue = (int)(image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
            image[i][j].rgbtGreen = image[i][j].rgbtBlue;
            image[i][j].rgbtRed = image[i][j].rgbtBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (int)width / 2; j++ )
        {
            RGBTRIPLE tmp;
            tmp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // clloac another chunk of memory for blurred image
    RGBTRIPLE(*b_image)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    // generate blurred image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            int sumBlue = 0;
            int sumGreen = 0;
            int sumRed = 0;
            for (int i_change = -1; i_change <= 1; i_change++)
            {
                for (int j_change = -1; j_change <= 1; j_change++)
                {
                    // make sure the surroundings are in the scope and exclude the middle pixel
                    if ((i + i_change) >= 0 && (i + i_change) < height &&
                        (j + j_change) >= 0 && (j + j_change) < width
                        && i_change != 0 && j_change != 0)
                        {
                            count++;
                            sumBlue += image[i + i_change][j + j_change].rgbtBlue;
                            sumGreen += image[i + i_change][j + j_change].rgbtGreen;
                            sumRed += image[i + i_change][j + j_change].rgbtRed;
                        }
                }
            }
            b_image[i][j].rgbtBlue = (int)sumBlue / count;
            b_image[i][j].rgbtGreen = (int)sumGreen / count;
            b_image[i][j].rgbtRed = (int)sumRed / count;
        }
    }

    // copy blurred image to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = b_image[i][j];
        }
    }
    free(b_image);
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // define sobel operator Gx and Gy
    int Gx[3][3];
    Gx[0][0] = -1;
    Gx[0][1] = 0;
    Gx[0][2] = 1;
    Gx[1][0] = -2;
    Gx[1][1] = 0;
    Gx[1][2] = 2;
    Gx[2][0] = -1;
    Gx[2][1] = 0;
    Gx[2][2] = 1;

    int Gy[3][3];
    Gy[0][0] = -1;
    Gy[0][1] = -2;
    Gy[0][2] = -1;
    Gy[1][0] = 0;
    Gy[1][1] = 0;
    Gy[1][2] = 0;
    Gy[2][0] = 1;
    Gy[2][1] = 2;
    Gy[2][2] = 1;

    // clloac another chunk of memory for blurred image
    RGBTRIPLE(*e_image)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    // generate blurred image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sumBluex = 0;
            int sumGreenx = 0;
            int sumRedx = 0;
            int sumBluey = 0;
            int sumGreeny = 0;
            int sumRedy = 0;

            for (int i_change = -1; i_change <= 1; i_change++)
            {
                for (int j_change = -1; j_change <= 1; j_change++)
                {
                   if ((i + i_change) >= 0 && (j + j_change) >= 0 &&
                        (i + i_change) < height && (j + j_change) < width)
                    {
                        sumBluex += Gx[i_change + 1][j_change + 1] * image[i + i_change][j + j_change].rgbtBlue;
                        sumGreenx += Gx[i_change + 1][j_change + 1] * image[i + i_change][j + j_change].rgbtGreen;
                        sumRedx += Gx[i_change + 1][j_change + 1] * image[i + i_change][j + j_change].rgbtRed;
                        sumBluey += Gy[i_change + 1][j_change + 1] * image[i + i_change][j + j_change].rgbtBlue;
                        sumGreeny += Gy[i_change + 1][j_change + 1] * image[i + i_change][j + j_change].rgbtGreen;
                        sumRedy += Gy[i_change + 1][j_change + 1] * image[i + i_change][j + j_change].rgbtRed;
                    }
                }
            }
            e_image[i][j].rgbtBlue = (int)sqrt((sumBluex / 9) * (sumBluex / 9) + (sumBluey / 9) * (sumBluey / 9));
            e_image[i][j].rgbtGreen = (int)sqrt((sumGreenx / 9) * (sumGreenx / 9) + (sumGreeny / 9) * (sumGreeny / 9));
            e_image[i][j].rgbtRed = (int)sqrt((sumRedx / 9) * (sumRedx / 9) + (sumRedy / 9) * (sumRedy / 9));
        }
    }

    // copy blurred image to image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = e_image[i][j];
        }
    }
    free(e_image);
    return;
}
