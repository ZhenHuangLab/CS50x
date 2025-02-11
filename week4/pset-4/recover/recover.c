#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");

    // Handle error if memory card doesn't exist
    if (card == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    // Create a buffer for a block of data
    BYTE buffer[512];

    // Allocate 8 bytes for file name `###.jpg` (backslash zero!)
    char *filename = malloc(8 * sizeof(BYTE));

    // Check if memory is enough
    if (filename == NULL)
    {
        return 2;
    }

    // Initialize file name count and img pointer
    int filename_count = 0;
    FILE *img = NULL;

    // While there is still data remaining in memory card
    // Load 512 bytes into a buffer
    while (fread(buffer, 1, 512, card) == 512)
    {
        // If start of new JPG
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) &&
            ((buffer[3] & 0xf0) == 0xe0))
        {
            // If first JPG
            if (filename_count == 0)
            {
                // Generate a string for file name
                sprintf(filename, "%03i.jpg", filename_count);
            }
            else
            {
                // Close previous image file before opening new one
                fclose(img);

                // Set next new file name
                sprintf(filename, "%03i.jpg", filename_count);
            }
            // Open a new file
            img = fopen(filename, "w");

            // Write to the new file
            fwrite(buffer, 1, 512, img);

            // Update file name count
            filename_count++;
        }
        // If not the start of new JPG
        else
        {
            // Only write if we've found at least one JPEG
            if (filename_count > 0)
            {
                // Keep writing
                fwrite(buffer, 1, 512, img);
            }
        }
    }

    // fclose img
    if (img != NULL)
    {
        fclose(img);
    }

    // Free memory and fclose card
    free(filename);
    fclose(card);
    return 0;
}
