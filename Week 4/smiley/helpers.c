#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing

    //loop through each row
    for (int i = 0; i < height; i++)
    {
        //loop through each column
        for (int j = 0; j < width; j++)
        {
            //check if image pixels are black
            if (image[i][j].rgbtRed == 0x00 && image[i][j].rgbtGreen == 0x00 && image[i][j].rgbtBlue == 0x00)
            {
                //change black pixels to purple(my fav :D)
                image[i][j].rgbtRed = 128;
                image[i][j].rgbtGreen = 0;
                image[i][j].rgbtBlue = 128;
            }
        }
    }

}
