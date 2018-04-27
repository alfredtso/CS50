#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		fprintf(stderr, "Usage: whodunit infile outfile\n");
		return 1;
	}
	
	//remember filenames
	char *infile = argv[1];
	char *outfile = argv[2];

	//open the input file
	FILE *inptr = fopen(infile, "r");
	if (inptr == NULL)
	{
		fprintf(stderr, "Couldnt open file\n");
		return 2;
	}

	FILE *outptr = fopen(outfile, "w");
	if (outptr == NULL)
	{
		fprintf(stderr, "Couldnt create file\n");
		return 3;
	}
	
	//read infiles's BITMAPFILEHEADER
	BITMAPFILEHEADER br;
	fread(&br, sizeof(BITMAPFILEHEADER), 1, inptr);

	//read infiles's BITMAPINFOHEADER
	BITMAPINFOHEADER bc;
	fread(&bc, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (br.bfType != 0x4d42 || br.bfOffBits != 54 || bc.biSize != 40 ||
        bc.biBitCount != 24 || bc.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
	
	//write outfiles's BITMAPFILEHEADER
	fwrite(&br, sizeof(BITMAPFILEHEADER), 1, outptr);

	//read outfiles's BITMAPINFOHEADER
	fwrite(&bc, sizeof(BITMAPINFOHEADER), 1, outptr);

	//determine padding for scanlines
	int padding = (4 -(bc.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
	
	//iterate over infile's scanline
	for (int i = 0, biHeight = abs(bc.biHeight); i < biHeight; i++)
	{
		for (int j = 0; j < bc.biWidth; j++)
		{
			RGBTRIPLE tri;

			fread(&tri, sizeof(RGBTRIPLE), 1, inptr);
			if (tri.rgbtGreen == 0x00 && tri.rgbtBlue == 0x00)
			{
				tri.rgbtGreen = 0xFF;
				tri.rgbtBlue = 0xFF;
			}
			else if (tri.rgbtRed ==0x00 && tri.rgbtGreen != 0x00 && tri.rgbtBlue != 0x00)
			{
				tri.rgbtRed = 0x00;
				tri.rgbtGreen = 0x00;
				tri.rgbtBlue = 0x00;
			}
			
			fwrite(&tri, sizeof(RGBTRIPLE),1 , outptr);

		}

		//skip padding, if any
		fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
	}
	fclose(inptr);

	fclose(outptr);

	return 0;

}
