##TODO
#Resize
#parse float input
-sscanf, atof
-check cs50 own get float function

#update headerfile
-change
file size
image size

width
-in pixels? not including padding
-scale by f

height
-in pixels
scale by f

biSizeImage in bytes
size of triple * bi.biwidth + padding * abs (bibiheightj)

bfSize
-total size, including pixels, padding and headers.
-bi.biSizeimage + header + infoheader

#resize horizontaly
for each i in row, write i f times
define a int var r = i/f, so that if f > 1, r will be the same for several i which r is will be search for the line to read and if f < 1, r will be skipping. 
#re padding

#resize vertically

##Recover

#background
-the first three bytes of JPEGS is specified ff, d8, ff
-the fourth is 1110 xxxx in hex
-FAT system save stuff in 512B, even the photo is 511B, and this is called "slacked space"
-each time find the signature, clone the file to a buffer of 512B
-but it can also span contiguous blocks
- the slack space in this case will be 0s

#TODO
- [ ] Open memory file
  -fopen
- [ ] find the beginging of JPEG
  -buffer3 & 0xf0 == 0xe0 to find the last byte
- [ ] make a new jpeg
  - filenames: ###.jpg, in roder starting at 000
  - sprintf(filename, "%03i.jpg", 2);
    -filename: char array to store the resultant string
  - FILe \*img = fopen(filename, "w")
- write 512B in the new file until new JPEG is found 
  - fread returns how many items of size size were read and return numbers
  - can use it directly in a condition i.e size = 512, number = 0 or 1 ?

#pseudocode
  -open card
  -repeat until the end of card
    - read 512B into buffer(malloc?)
	- check start of a new JPEG?
	  - yes ...
	  - no ...
	- alfready found a JPEG?
	  - no ... start the first jpeg
	  - yes ... need to close the previous file and open a new one
  - close any remaing files
