#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if(argc != 2)
	{
		fprintf(stderr, "Usage: recover infile \n");
		return 1;
	}
	
	//remember filenames
	char *infile = argv[1];

	//open the input file
	FILE *inptr = fopen(infile, "r");
	if (inptr == NULL)
	{
		fprintf(stderr, "Couldnt open file\n");
		return 2;
	}
	FILE *img;

	//buffer for reading each block in
	char filename[30]; 
	unsigned char buffer[512];
	int filenumber = 0;
	int c =0;

	//repeat until the end of card
	while (fread(buffer, 512, 1, inptr) == 1)
	{
		//find the begining of a JPEG by checking conditions
		if (buffer[0] ==  0xff && buffer[1] ==  0xd8 && buffer[2] ==  0xff
				&& (buffer[3] & 0xf0) ==  0xe0)
		{
			//close if the previous one is open
			if (img)
			{
				fclose(img);
			}

			filenumber++;
			sprintf(filename, "%03d.jpg", filenumber);
			img = fopen(filename, "w");
			
			//open newfile
			if (!img)
			{
				fprintf(stderr, "Error opening outputfile. \n");
				return 3;
			}

			//write 512B into new file
			fwrite(buffer, 512, 1, img);
		}
		else if (img)
		{
			fwrite(buffer, 512, 1, img);
		}
	}

	//close all files
	fclose(inptr);
	if (img)
	{
		fclose(img);
	}

	printf("OK\n");

	return 0;
}
