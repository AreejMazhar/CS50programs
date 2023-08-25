#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    //loop through every row
    for (int i = 0; i < height; i++)
    {
        //loop through every column
        for (int j = 0; j < width; j++)
        {
            //find avg of rgb and replace the pixel values
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;

            int avg = round((red + green + blue) / 3);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //loop through every row
    for (int i = 0; i < height; i++)
    {
        //loop through every column just halfway
        for (int j = 0; j < (width / 2.0); j++)
        {
            RGBTRIPLE temppixel, temppixel2;
            //pixel on left side
            temppixel = image[i][j];
            //pixel on right side
            temppixel2 = image[i][width - 1 - j];

            //switch
            image[i][j] = temppixel2;
            image[i][width - 1 - j] = temppixel;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //temp value
    RGBTRIPLE tempcopy[height][width];

    //make a copy of the image
    //loop through every row
    for (int i = 0; i < height; i++)
    {
        //loop through every column
        for (int j = 0; j < width; j++)
        {
            tempcopy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int totalred, totalblue, totalgreen;
            totalred = totalblue = totalgreen = 0;
            float avgcount = 0.00;

            //get neighboring pixels
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int currentx = i + x;
                    int currenty = j + y;

                    //check if neighboring pixels are valid
                    if (currentx < 0 || currentx > (height - 1) || currenty < 0 || currenty > (width - 1))
                    {
                        continue;
                    }

                    //get image value
                    totalred = totalred + image[currentx][currenty].rgbtRed;
                    totalgreen = totalgreen + image[currentx][currenty].rgbtGreen;
                    totalblue = totalblue + image[currentx][currenty].rgbtBlue;
                    avgcount++;
                }
            }

            //calculate the average of the pixels
            tempcopy[i][j].rgbtRed = round(totalred / avgcount);
            tempcopy[i][j].rgbtGreen = round(totalgreen / avgcount);
            tempcopy[i][j].rgbtBlue = round(totalblue / avgcount);

        }
    }

    //copy new pixels onto original image
    for (int i = 0; i < height; i++)
    {
        //loop through every column
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tempcopy[i][j].rgbtRed;
            image[i][j].rgbtGreen = tempcopy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tempcopy[i][j].rgbtBlue;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //temp value
    RGBTRIPLE tempcopy[height][width];

    //make a copy of the image
    //loop through every row
    for (int i = 0; i < height; i++)
    {
        //loop through every column
        for (int j = 0; j < width; j++)
        {
            tempcopy[i][j] = image[i][j];
        }
    }

    //initialize Gx and Gy arrays
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    //loop through each row
    for (int i = 0; i < height; i++)
    {
        //loop through every column
        for (int j = 0; j < width; j++)
        {
            float redX, greenX, blueX, redY, greenY, blueY;
            redX = greenX = blueX = redY = greenY = blueY = 0;

            //loop through neighbouring pixels
            for (int x = 0; x < 3; x++)
            {
                for (int y = 0; y < 3; y++)
                {

                    int currentX = i - 1 + x;
                    int currentY = j - 1 + y;
                    //check for valid pixels
                    if (currentX < 0 || currentX > (height - 1) || currentY < 0 || currentY > (width - 1))
                    {
                        continue;
                    }

                    //Calculate Gx
                    redX = redX + (image[currentX][currentY].rgbtRed * Gx[x][y]);
                    greenX = greenX + (image[currentX][currentY].rgbtGreen * Gx[x][y]);
                    blueX = blueX + (image[currentX][currentY].rgbtBlue * Gx[x][y]);

                    //Calculate Gy
                    redY = redY + (image[currentX][currentY].rgbtRed * Gy[x][y]);
                    greenY = greenY + (image[currentX][currentY].rgbtGreen * Gy[x][y]);
                    blueY = blueY + (image[currentX][currentY].rgbtBlue * Gy[x][y]);
                }
            }

            //calculate the square root of Gx^2 and Gy^2
            int red = round(sqrt((redX * redX) + (redY * redY)));
            int green = round(sqrt((greenX * greenX) + (greenY * greenY)));
            int blue = round(sqrt((blueX * blueX) + (blueY * blueY)));

            //cap value at 255
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

            //copy pixel values in tempcopy
            tempcopy[i][j].rgbtRed = red;
            tempcopy[i][j].rgbtGreen = green;
            tempcopy[i][j].rgbtBlue = blue;
        }
    }

    //copy new pixels into original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tempcopy[i][j].rgbtRed;
            image[i][j].rgbtGreen = tempcopy[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tempcopy[i][j].rgbtBlue;
        }
    }

    return;
}
