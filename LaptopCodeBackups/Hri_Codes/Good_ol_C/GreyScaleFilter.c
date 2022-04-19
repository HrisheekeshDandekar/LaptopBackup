//Copying header to new file created
/*
 *    Code to take in a BMP name in the same directory as a command line argument to main
 *
 *    PSUDO CODE:
 *      >  Open file
 *      >  Open another file wtih _bw as a suffix
 *      >  Make sure it is an BMP file
 *      >  Locate bitmap starting pos
 *      >  Apply formula to each pixal and rewrite pixals till the end
 *      >  Flash error / success msg
 *      >  Close both files
 *      >  exit
 *
 *      TODO:
 *			> Account for different identifiers for BMP file header start bytes
 *				{ BM, BA, CI, CP, IC, PT }
 *			> Account for varaible size DIB header
 *				{ current size is static }
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

void temp_func_header_display(Bitmap_file_header* BMP_header, DIB_header* DIB_Header);
bool arguments_to_main_validation (int argc, char** argv);
bool open_files (FILE* original, FILE* to_create, char* original_name);
char* new_file_name (char* original_name);
bool file_is_bmp (FILE* fp);
long bitmap_start (FILE* fp);
long bitmap_end (FILE* fp);
bool read_headers (FILE* fp, Bitmap_file_header* BMP_header, DIB_header* DIB_Header);
bool apply_greyscale (FILE* fp);
void status_printed ();

typedef struct Errors {
	int fopen_original;
	int fopen_final;
	int filter_application_failure;
	int fclose_original;
	int fclose_final;
	int arguments_err;
	int arg_name_err;
	int fopen_new;
	int not_bmp;
	int headers_err;
	int file_header;
	int DIB_header;
	
	char msgs[12][100];
} Error_msgs;

Error_msgs code_errors = {
		.fopen_original = 0,
		.fopen_final = 0,
		.filter_application_failure = 0,
		.fclose_original = 0,
		.fclose_final = 0,
		.arguments_err = 0,
		.arg_name_err = 0,
		.not_bmp = 0;
		.headers_err = 0;
		.file_header = 0;
		.DIB_header = 0;
			
		.msgs[0] = "---[ Error Opening original image ]---\n",		
		.msgs[1] = "---[ Error createing file with suffix _bw ]---\n(make sure file does not exist)\n",		
		.msgs[2] = "---[ Failed to apply Fileter ]---\n",		
		.msgs[3] = "---[ Error closing original file ]---\n",		
		.msgs[4] = "---[ Error closing created file ]---\n"
		.msgs[5] = "---[ Wrong arguments passed ]---\nUsage: ./program_name image_name.bmp\n"
		.msgs[6] = "---[ Bad name passed ]---\nUsage: ./program_name image_name.bmp\n"
		.msgs[7] = "---[ Could not create new output file ]---\n"
		.msgs[8] = "---[ File is not a BMP ]---\n"
		.msgs[9] = "---[ Error Reading Header/s ]---\n"
		.msgs[10] = "---[ File Header Reading Failed ]---\n"
		.msgs[11] = "---[ DIB header reading failed ]---\n"
	};

#pragma pack(push, 0)	//making sure padding is disabled for reading headers
typedef struct Bitmap_file_header {
	char identifier[2];
	int32_t bmp_size;
	char reserved1[2];
	char reserved2[2];
	int32_t pixal_arr_start;
} Bitmap_file_header;
 
typedef struct DIB_header {
	int32_t header_size;    // Should be 12 bytes
	int16_t bitmap_width;
	int16_t bitmap_height;
	int16_t color_planes;
	int16_t bits_per_pixal;
} DIB_header;
#pragma pack(pop)	//Re-enable padding for performance

int main(int argc, char** argv)
{
	//Print the correct error/success msg whenever program exits
	atexit(status_printed);

	//Correct arguments passed to the program
	if (!arguments_to_main_validation(argc, argv))		{ return 1; }

	FILE* original;
	FILE* to_create;

	if (!open_files(original, to_create, argv[1]))		{ return 1; }
		
	if (!file_is_bmp(original))				{ return 1; } 

	if (!apply_greyscale(original))				{ return 1; }

	return 0;
}

void temp_func_header_display(Bitmap_file_header* BMP_header, DIB_header* DIB_Header)
{
	//		--- FILE HEADER PRINT ---
	printf(
			"\n --- FILE HEADER ---\n",
		    "Identifier: %c%c\n",
		    "Size of BMP file: %d\n",
		    "Reserved Bytes 1: %c%c\n",
		    "Reserved Bytes 2: %c%c\n",
		    "Bitmap start offset: %d\n",
		    BMP_header->identifier[0],
		    BMP_header->identifier[1],
		    BMP_header->bmp_size,
		    BMP_header->reserved1[0],
		    BMP_header->reserved1[1],
		    BMP_header->reserved2[0],
		    BMP_header->reserved2[1],
		    BMP_header->pixal_arr_start);

	//		--- BMP HEADER PRINT ---
	printf(
			"\n --- BMP HEADER ---\n",
		    "Size of header file: %d\n",
		    "BMP width: %d\n",
		    "BMP height: %d\n",
		    "Color Planes: %d\n",
		    "Bits per pixal: %d\n",
		    DIB_header->header_size,
		    DIB_header->bitmap_width,
		    DIB_header->bitmap_height,
		    DIB_header->color_planes,
		    DIB_header->bits_per_pixal
		 );

}

bool arguments_to_main_validation(int argc, char** argv)
{
	//Argc needs to be 2, first argv is the exe name, 2nd is the img name
	if (argc != 2) 
	{
		code_errors.arguments_err = 1;
		return false;
	}
		
	//If wrong arguments passed, set correct flags
	if (!strcmp(argv[strlen(argv[1]) - 4], ".bmp"))
	{
		code_errors.arg_name_err = 1;
		return false;
	}

	return true;
}

bool open_files(FILE* original, FILE* to_create, char* original_name)
{
	//Check if file exists
	original = fopen(original_name, "rb");
	if (!original)
	{
		code_errors.fopen_original = 1;
		return false;
	}

	//Check and open open to_create file with added suffix
	char* output_file_name = new_file_name(original_name);
	to_create = fopen(output_file_name, "rb");
	if (!to_create)
	{
		code_errors.fopen_final = 1;
		return false;
	}
	fclose(to_create);

	//Create a blank file for output
	to_create = fopen(output_file_name, "wb")
	if (!to_create)
	{
		code_errors.fopen_new = 1;
		return false;
	}

}

char* new_file_name (char* original_name)
{
    //Add suffix _bx by creating new char array with original size +2 len
    char* new_name;
    new_name = (char*)malloc((strlen(original_name) + 3) * sizeof(char));

    //Copying as it is
    strcpy(new_name, original_name);

    //Adding suffix
    strcpy(&new_name[strlen(new_name) - 4], "_bm.bmp");

    return new_name;
}

bool file_is_bmp (FILE* fp)
{
	//check if the file is actually an bmp file
	//Approach: Check first 2 bytes are BM in ascii
	char expected_bytes[2];
	
	//If not , set the correct error codes and return false
	if (fread(expected_bytes, sizeof(char), 2, fp) != 2)
	{
		code_errors.not_bmp = 1;	
		return false;
	}
	if (strcmp(expected_bytes, "BM"))
	{
		code_errors.not_bmp = 1;
		return false;
	}

	//Setting file cursor back to start
	fseek(fp, 0, SEEKSET);

	//Checkes passed
	return true;	
}

bool apply_greyscale (FILE* fp)
{
	//Reading headers
	Bitmap_file_header BMP_header;
	DIB_header DIB_Header;
	if (!read_headers(fp, &BMP_header, &DIB_Header))
	{
		code_errors.headers_err = 1;
		return false;
	}
	
	//Copying header to new file created
	//Apply the greyscale filter to the whole bitmap
	//Formula : Grayscale = 0.299R + 0.587G + 0.114B.
	
	//Find bitmap size 
	//Find start position
	//Find end position
	//Itterate through the bitmap and convert every pixal
}

bool read_headers (FILE* fp, Bitmap_file_header* BMP_header, DIB_header* DIB_Header)
{
	//Setting cursor to start 
	fseek(fp, 0, SEEKSET);	

	//Reading Bitmap File Header
	if (fread(BMP_header, sizeof(*BMP_header), 1, fp) != 1)
	{
		code_errors.headers_err = 1;
		code_errors.file_header = 1;
		return false;
	}

	//Setting cursor to DIB header start
	fseek(fp, 14, SEEKSET);

	//Reading [ WINDOWS ] DIB header
	if (fread(DIB_Header, sizeof(*DIB_Header), 1, fp) != 1)
	{
		code_errors.headers_err = 1;
		code_errors.DIB_header = 1;
		return false;
	}
	
	return true;
}

long bitmap_start (FILE* fp)
{
	//Return address of the bitmap start position as a long
}

long bitmap_end (FILE* fp)
{
	//Return the end address of the bitmap position as a long
}


void status_printed()
{
	//Check for all the encountered errors in the error structure and print the corresponding 
	//message 
}

