#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    //Ensuring program only accepts one command line argument
    if ( argc != 2 )
    {
       return 1;
    }
    // Open the file entered
    FILE *f = fopen( argv[1], "r" );
    // incase the file does not exist
    if ( argv[1] == NULL )
    {
        return 1;
    }
    //Making a new file for output
    FILE *img == NULL
    //Creating new data type to store byte of data
    typedef uint8_t BYTE;
    //Creating storage array
    BYTE buffer[512];
    //Creating index of JPEG file found
    int index = 0;
    // creating an array to store filenames of JPEG images
    char filename[8];
    //Reading the file
    while(fread(buffer,512,1,argv[1]) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0 == 0xe0)
        {
            if (index == 0)
            {
                //give name to file
                sprintf(filename, "%03i.jpg", index);
                //open file for writing
                FILE *img = fopen(filename, "w");
                index++;
                //write to file
                fwrite(buffer,512,1,img);
            }
            else if (index > 0 )
            {
                //close current file to write in a new file
                fclose(img);
                 //give name to file
                sprintf(filename, "%03i.jpg", index);
                //open file for writing
                FILE *img = fopen(filename, "w");
                index++;
                //write to file
                fwrite(buffer,512,1,img);

            }

        }else if (index > 0)
        {
            fwrite(buffer,512,1,img);
        }
    }
    //close remaining files
    fclose(f);
    fclose(img);

    return 0;
}
