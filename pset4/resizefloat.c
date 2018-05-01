// Copies a BMP file
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: float copy infile outfile\n");
        return 1;
    }
	//assign each variable one by one
	char *size=argv[1];
	char *infile=argv[2];
	char *outfile=argv[3];
	
	//alternative implementation
	//char *size=NULL;
	//char *infile=NULL;
	//char *outfile=NULL;
	//sscanf(*argv, "%s %s %s", size, infile, outfile);
	
	// To check if the value is correct for each of the var
	printf("%s, %s, %s", size, infile, outfile);
	
	//change the type
	int rratio = atoi(size);
	
	//check for float value
	if (rratio < 0 || rratio > 100 )
	{
		fprintf(stderr, "f must be floating-point value in (0.0, 100.0]\n");
		return 2;
	}
	

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

	// width and height in px of infile
	LONG oldbiWidth = bi.biWidth;
	LONG oldbiHeigth = abs(bi.biHeight);
    int oldpadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
	
	//calculate the new size
	bi.biWidth *= f;
	bi.biHeight *= f;

	LONG newbiWidth = bi.biWidth;
	LONG newbiHeight = abs(bi.biHeight);

	//padding of newfile
    int padding = (4 - (newbiWidth * sizeof(RGBTRIPLE)) % 4) % 4;

	//change image size according
	bi.biSizeImage = ((sizeof(RGBTRIPLE) * newbiWidth) + padding) * newbiHeight; 
	bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);


    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

	for ( i = 0; i < newbiHeight; i++)
	{
		
    // determine padding for scanlines
	if ( enlarge == 1 )
	{
		// iterate over infile's scanlines
		for (int i = 0, biHeight = abs(oldbiHeigth); i < biHeight; i++)
		{
			for (int row = 0; row < rratio; row++)
			{
				// iterate over pixels in scanline
				for (int j = 0; j < oldbiWidth; j++)
				{
					for(int col = 0; col < rratio; col++)
					{
						
						// temporary storage
						RGBTRIPLE triple;

						// read RGB triple from infile
						fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
						fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
						
						if (col !=(rratio-1))
						{
							fseek(inptr, -sizeof(RGBTRIPLE), SEEK_CUR);
						}
					}
				}

				// skip over padding, if any
				fseek(inptr, oldpadding, SEEK_CUR);
		
				// then add it back (to demonstrate how)
				for (int k = 0; k < padding; k++)
				{
					fputc(0x00, outptr);
				}
				if (row !=(rratio-1))
				{
					fseek(inptr, -(oldbiWidth * sizeof(RGBTRIPLE)) - oldpadding, SEEK_CUR);
				}
			}
		}
	}
	else if ( enlarge == 0)
	{
		for (int i = 0, biHeight = abs(oldbiHeigth); i < biHeight; i++)
		{
			//fseek appropriate row
			for (int j = 0; j < oldbiWidth; j++)
			{
				// temporary storage
				RGBTRIPLE triple;

				// read RGB triple from infile
				fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
				fseek(inptr, shift - 1, SEEK_CUR); 
				fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
				

				// skip over padding, if any
				fseek(inptr, oldpadding, SEEK_CUR);
		
				// then add it back (to demonstrate how)
				for (int k = 0; k < padding; k++)
				{
					fputc(0x00, outptr);
				}
				
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
