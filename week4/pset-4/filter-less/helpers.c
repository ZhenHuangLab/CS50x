#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels in image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate the average pixel value
            int average_grayscale = (int) round(
                (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            // Set each color value to the average value
            image[i][j].rgbtRed = average_grayscale;
            image[i][j].rgbtGreen = average_grayscale;
            image[i][j].rgbtBlue = average_grayscale;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over all pixels in image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Calculate each new color value using the Sepia formula
            int sepiaRed = (int) round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen +
                                       .189 * image[i][j].rgbtBlue);
            int sepiaGreen = (int) round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen +
                                         .168 * image[i][j].rgbtBlue);
            int sepiaBlue = (int) round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen +
                                        .131 * image[i][j].rgbtBlue);

            // Ensure the result is between 0 and 255
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            // Set the filtered pixel
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop over half pixels in image
    int halfnum = width / 2;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < halfnum; j++)
        {
            // Swap red values
            int tmp = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - 1 - j].rgbtRed;
            image[i][width - 1 - j].rgbtRed = tmp;

            // Swap green values
            tmp = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - 1 - j].rgbtGreen;
            image[i][width - 1 - j].rgbtGreen = tmp;

            // Swap blue values
            tmp = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - 1 - j].rgbtBlue;
            image[i][width - 1 - j].rgbtBlue = tmp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a copy of image
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // Process each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize
            int sum_red = 0;
            int sum_green = 0;
            int sum_blue = 0;
            float counter = 0.0;

            // Calculate pixel sums for all surrounding pixels
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;

                    // Check if the pixel is within bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        sum_red += copy[ni][nj].rgbtRed;
                        sum_green += copy[ni][nj].rgbtGreen;
                        sum_blue += copy[ni][nj].rgbtBlue;
                        counter++;
                    }
                }
            }

            // Calculate and set averages
            image[i][j].rgbtRed = (int) round(sum_red / counter);
            image[i][j].rgbtGreen = (int) round(sum_green / counter);
            image[i][j].rgbtBlue = (int) round(sum_blue / counter);
        }
    }
}
