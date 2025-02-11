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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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

    // Create sobel Gx kernel
    int sobelGx[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    // Create sobel Gy kernel
    int sobelGy[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    // Process each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize
            int weighted_sum_Gx_red = 0;
            int weighted_sum_Gx_green = 0;
            int weighted_sum_Gx_blue = 0;
            int weighted_sum_Gy_red = 0;
            int weighted_sum_Gy_green = 0;
            int weighted_sum_Gy_blue = 0;

            // Calculate pixel weighted sums for all surrounding pixels
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int Gx_weight = sobelGx[di+1][dj+1];
                    int Gy_weight = sobelGy[di+1][dj+1];

                    int ni = i + di;
                    int nj = j + dj;

                    // Check if the pixel is within bounds
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        weighted_sum_Gx_red += Gx_weight * copy[ni][nj].rgbtRed;
                        weighted_sum_Gx_green += Gx_weight * copy[ni][nj].rgbtGreen;
                        weighted_sum_Gx_blue += Gx_weight * copy[ni][nj].rgbtBlue;
                        weighted_sum_Gy_red += Gy_weight * copy[ni][nj].rgbtRed;
                        weighted_sum_Gy_green += Gy_weight * copy[ni][nj].rgbtGreen;
                        weighted_sum_Gy_blue += Gy_weight * copy[ni][nj].rgbtBlue;
                    }
                }
            }

            int weighted_sum_red = (int) round(sqrt(pow(weighted_sum_Gx_red, 2) + pow(weighted_sum_Gy_red, 2)));
            int weighted_sum_green = (int) round(sqrt(pow(weighted_sum_Gx_green, 2) + pow(weighted_sum_Gy_green, 2)));
            int weighted_sum_blue = (int) round(sqrt(pow(weighted_sum_Gx_blue, 2) + pow(weighted_sum_Gy_blue, 2)));

            if (weighted_sum_red > 255)
            {
                weighted_sum_red = 255;
            }
            if (weighted_sum_green > 255)
            {
                weighted_sum_green = 255;
            }
            if (weighted_sum_blue > 255)
            {
                weighted_sum_blue = 255;
            }

            // Set the filtered pixel
            image[i][j].rgbtRed = weighted_sum_red;
            image[i][j].rgbtGreen = weighted_sum_green;
            image[i][j].rgbtBlue = weighted_sum_blue;
        }
    }

}
