#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    if (argc > 2)
    {
        printf("Invalid input\n");
        return 1;
    }

    char *infile = argv[1];

    //Read address of raw file, and give feedback if fails to read.
    FILE *inptr = fopen(infile, "r");

    if (inptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    // Give space to buffer and initialize it.
    uint8_t buffer[512];

    char *filename = malloc(8); //give 8B to filename

    // count the num of JPEGs that have been found yet
    int count = 0;
    int flag = 0; // use flag to see if we meet the start of data chunks

    sprintf(filename, "%03i.jpg", count);
    FILE *outptr = fopen(filename, "w");

    while(fread(buffer, 512, 1, inptr) > 0)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (count == 0)
            {
                fwrite(buffer, 512, 1, outptr);
                flag = 1;
                count++;
            }
            else
            {
                fclose(outptr);
                sprintf(filename, "%03i.jpg", count);
                outptr = fopen(filename, "w");
                fwrite(buffer, 512, 1, outptr);
                count++;
            }
        }
        else
        {
            if (flag == 1)
            {
                fwrite(buffer, 512, 1, outptr);
            }
        }
    }
    fclose(outptr);
    fclose(inptr);
    free(filename);
}
