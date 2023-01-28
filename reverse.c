#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include "wav.h"

int check_format(WAVHEADER header);
int get_block_size(WAVHEADER header);

int main(int argc, char *argv[])
{
    // Ensure proper usage
    // TODO #1
    if (argc != 3)
    {
        printf("Usage: ./reverse input.wav output.wav\n");
        return 1;
    }

    // Open input file for reading
    // TODO #2
    char *infile = argv[1];
    FILE *input = fopen(infile, "r");
    if (input == NULL)
    {
        printf("%s is not found\n", infile);
        fclose(input);
        return 3;
    }
    // Read header into an array
    // TODO #3
    const int HEADER_SIZE = sizeof(WAVHEADER);
    WAVHEADER header;
    fread(&header, HEADER_SIZE, 1, input);

    // Use check_format to ensure WAV format
    // TODO #4
    if (check_format(header) == 1)
    {
        printf("Input is not a WAV file\n");
        fclose(input);
        return 4;
    }
    // Open output file for writing
    // TODO #5
    char *outfile = argv[2];
    FILE *output = fopen(outfile, "w");
    if (output == NULL)
    {
        printf("Could not create %s.\n", outfile);
        fclose(output);
        fclose(input);
        return 5;
    }

    // Write header to file
    // TODO #6
    fwrite(&header, HEADER_SIZE, 1, output);

    // Use get_block_size to calculate size of block
    // TODO #7
    int block_size = get_block_size(header);

    // Write reversed audio to file
    BYTE buffer[block_size];
    fseek(input, 0, SEEK_END);
    while(ftell(input) >= HEADER_SIZE)
    {
        fseek(input, -1 * block_size, SEEK_CUR);
        fread(buffer, sizeof(buffer), 1, input);
        fwrite(buffer, sizeof(buffer), 1, output);
        fseek(input, -1 * block_size, SEEK_CUR);
    }
    // TODO #8
    fclose(output);
    fclose(input);
}


int check_format(WAVHEADER header)
{
    // TODO #4
    char *wav = "WAVE";
    for (int i = 0; i < 4; i++)
    {
        if (header.format[i] != wav[i])
        {
            return 1;
            break;
        }
    }
    return 0;
}

int get_block_size(WAVHEADER header)
{
    // TODO #7
    int block_size = header.numChannels * header.bitsPerSample / 8;
    return block_size;
}
//dsafdf
