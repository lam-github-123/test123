#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>
#include <string.h>

#define BLOCK_SIZE 512
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // open memory card
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        printf("Could not open flie\n");
        return 2;
    }
    BYTE buffer[BLOCK_SIZE];
    int file_number = -1; // file hasn't exited yet
    char filename[strlen("000.jpg") + 1];
    FILE *img;
    // read 512 bytes into buffer
    while(fread(buffer,sizeof(BYTE), BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        //start of new jpeg
        if (
            buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0
            )
        {
            file_number ++;
            sprintf(filename, "%03i.jpg", file_number);
            img = fopen(filename, "w");
            if (file_number >= 1)
            {
                fclose(img);
                img = fopen(filename, "w");
            }
            if (img == NULL)
            {
                fclose(img);
                printf("can't creat img\n");
                return 3;
            }
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
        }
        else if (file_number >= 0)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
        }
    }
    fclose(img);
    fclose(raw_file);
    return 0;
}
