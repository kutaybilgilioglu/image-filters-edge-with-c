#include "helpers.h"
#include <math.h>
#include <stdlib.h>


void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }
    return;
}


void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE reflectedImage[height][width];


    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            reflectedImage[i][j] = image[i][width - 1 - j];
        }
    }


    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            image[i][j] = reflectedImage[i][j];
        }
    }
    return;
}


void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE blurredImage[height][width];


    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            int redSum = 0, greenSum = 0, blueSum = 0, squareSum = 0;

            for (int row = (i - 1) ; row <= (i + 1) ; row++)
            {
                for (int col = (j - 1) ; col <= (j + 1) ; col++)
                {

                    if (row == -1 || row == height || col == -1 || col == width)
                    {
                        continue;
                    }
                    redSum += image[row][col].rgbtRed;
                    greenSum += image[row][col].rgbtGreen;
                    blueSum += image[row][col].rgbtBlue;

                    squareSum++;
                }
            }

            blurredImage[i][j].rgbtRed = round(redSum / (float)squareSum);
            blurredImage[i][j].rgbtGreen = round(greenSum / (float)squareSum);
            blurredImage[i][j].rgbtBlue = round(blueSum / (float)squareSum);
        }
    }


    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            image[i][j] = blurredImage[i][j];
        }
    }
    return;
}


void edges(int height, int width, RGBTRIPLE image[height][width])
{

    int gxArray[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gyArray[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    RGBTRIPLE edgeImage[height][width];

    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            float gxRed = 0, gxGreen = 0, gxBlue = 0;
            float gyRed = 0, gyGreen = 0, gyBlue = 0;


            for (int row = i - 1 ; row <= i + 1 ; row++)
            {
                for (int col = j - 1 ; col <= j + 1 ; col++)
                {

                    if (row == -1 || row == height || col == -1 || col == width)
                    {
                        continue;
                    }


                    gxRed += image[row][col].rgbtRed * gxArray[row - (i - 1)][col - (j - 1)];
                    gxGreen += image[row][col].rgbtGreen * gxArray[row - (i - 1)][col - (j - 1)];
                    gxBlue += image[row][col].rgbtBlue * gxArray[row - (i - 1)][col - (j - 1)];

                    gyRed += image[row][col].rgbtRed * gyArray[row - (i - 1)][col - (j - 1)];
                    gyGreen += image[row][col].rgbtGreen * gyArray[row - (i - 1)][col - (j - 1)];
                    gyBlue += image[row][col].rgbtBlue * gyArray[row - (i - 1)][col - (j - 1)];

                }
            }


            int red = round(sqrt(gxRed * gxRed + gyRed * gyRed));
            int green = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int blue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));


            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            edgeImage[i][j].rgbtRed = red;
            edgeImage[i][j].rgbtGreen = green;
            edgeImage[i][j].rgbtBlue = blue;
        }
    }


    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            image[i][j] = edgeImage[i][j];
        }
    }
    return;
}
void edge_pixel(int height, int width, RGBTRIPLE image[height][width]){
    RGBTRIPLE customImage[height][width];
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            int average = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);
            customImage[i][j].rgbtBlue = average;
            customImage[i][j].rgbtGreen = average;
            customImage[i][j].rgbtRed = average;
        }
    }


    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width-1 ; j++)
        {
            if(abs(customImage[i][j].rgbtBlue-customImage[i][j+1].rgbtBlue)>35){

                customImage[i][j].rgbtBlue=255;
                customImage[i][j].rgbtRed=255;
                customImage[i][j].rgbtGreen=0;

            }
        }
    }
    for (int i = 0 ; i < width ; i++)
    {
        for (int j = 0 ; j < height-1 ; j++)
        {
            if(abs(customImage[j][i].rgbtBlue-customImage[j+1][i].rgbtBlue)>35){

                customImage[j][i].rgbtBlue=255;
                customImage[j][i].rgbtRed=255;
                customImage[j][i].rgbtGreen=0;

            }
        }
    }
    for (int i = 0 ; i < height ; i++)
    {
        for (int j = 0 ; j < width ; j++)
        {
            image[i][j] = customImage[i][j];
        }
    }

}
