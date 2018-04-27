# Questions

## What's `stdint.h`?
'stdint.h' is a header file in the C-standard library to allow more portable code byproviding a set of typedefs that specify exact-width integer types, togeter with the defined minimum and max allowable values for each type, using macros.


## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

so that diff variable can use diff int type so as to save space ?


## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

#BYTE
8 bits, one byte
#DWORD
32-bits, 4 bytes
#LONG
32-bits signed, 4 bytes
#WORD
16-bits unsigned, 2 bytes

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

bftype

## What's the difference between `bfSize` and `biSize`?

bfSize: the size of the bitmap file in bytes and is located in headerfile
biSize: the number of bytes required by the infofile struct

## What does it mean if `biHeight` is negative?

If biHeight is negative, indicating a top-down DIB, biCompression must be either BI_RGB or BI_BITFIELDS. Top-down DIBs cannot be compressed.
Topdown DIB and starts at top upper left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

maybe the file pointer could not local the file 

## Why is the third argument to `fread` always `1` in our code?

because we going to read one byte at a time

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

since RGBTriple is 3 bytes, so 3

## What does `fseek` do?

change the file pointer by a offset which can be positive and negative number which means point the either directions

## What is `SEEK_CUR`?

change the pointer from the current location, some other options would be SEEK_END, or from the start SEEK_SET

