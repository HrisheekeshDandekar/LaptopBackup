//Code to extract all bytes of an image file into a text file to be added to an arary
#include <stdio.h>
#include <stdlib.h>

FILE* output_file_create();
void generate_img_array(FILE* image, FILE* output_file, char* key);
void close_buffers(FILE* image, FILE* output_file);
void encrypt_shift_3(char current_val);

int main(int argc, char** argv)
{
    FILE* image = fopen(argv[1], "r");

    if (!image)
    {
        printf("[File Not Opened]\n");
        return 1;
    }

    FILE* output_file = output_file_create();
    


    generate_img_array(image, output_file, "ctf_logo.png");

    close_buffers(image, output_file);

    return 0;
}

FILE* output_file_create()
{
    FILE* fp = fopen("output_file.txt", "w");
    if (!fp)
    {
        printf("[Output File was not created]\n");
    }

    return fp;
}

void generate_img_array(FILE* image, FILE* output_file, char* key)
{

    fseek(image, 0, SEEK_END);
    long int size = ftell(image);
    fseek(image, 0, SEEK_SET);

    unsigned char* image_buffer = (unsigned char*)malloc(size);

    int bytes_read = fread(image_buffer, sizeof(unsigned char), size, image);


    int newline_till = 40;
    int mulby = 1;
    for (int i = 0; i < size; i++)
    {
            //encrypt
        unsigned char read_write_byte;
        read_write_byte = image_buffer[i] ^ (key[i % sizeof(key)] * mulby);
        mulby++;
        mulby % 4;
        if (mulby == 0)
        {
            mulby = 1;
        }

        fprintf(output_file, "%d ,", read_write_byte);
        
        newline_till--;
        if (!newline_till)
        {
            newline_till = 40;
            fprintf(output_file, "\n\t");
        }

    }
}

void close_buffers(FILE* image, FILE* output_file)
{
    fclose(image);
    fclose(output_file);
}