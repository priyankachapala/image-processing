/* The read program is invoked by: readimage inputfile outputfile */
#include <stdio.h> /* This header file defines the I/O functions */
#include <stdlib.h> /* include standard dfeinitions like exit() */
#define FALSE 0
#define TRUE 1
int main(int argc, char **argv)
{
FILE *fpIn;
FILE *fpOut;
char *string;
char c;
int highVal;
int doneReading = FALSE;
int numberOfRows, numberOfColumns, numberOfBands;
int totalPixels;
unsigned char *image;
float meanF;
int meanI;
int i;
if (argc < 3) {
fprintf(stderr,"Usage: readimage input-file-name output-file-name\n");
exit;
}
fpIn = fopen(argv[1],"rb"); /* argv[1] contains the filename */
if (fpIn == NULL) {
fprintf(stderr,"%s either cannot be read or does not exist\n", argv[1]);
exit;
}
string = (char *) calloc(256,1);
/* initialized dynamic memory allocation */
while (!doneReading && (c = (char) fgetc(fpIn)) != '\0')
switch(c) {
case 'P':
c = (char) getc(fpIn);
switch(c) {
case '2':
numberOfBands = 1;
/* ppmType = PPMASCII; */
break;
case '3':
numberOfBands = 3;
/* ppmType = PPMASCII; */
break;
case '5':
numberOfBands = 1;
/* ppmType = PPMGRAY; */
break;
case '6':
numberOfBands = 3;
/* ppmType = PPMRAW; */
break;
}
c = (char) getc(fpIn);
if (c != 0x0A) {
ungetc(c,fpIn);
}
else {
ungetc(c,fpIn);
fgets(string,256,fpIn);
}
break;
case '#':
fgets(string,256,fpIn);
break;
case '1':
case '2':
case '3':
case '4':
case '5':
case '6':
case '7':
case '8':
case '9':
ungetc(c,fpIn);
fscanf(fpIn,"%d %d %d", &numberOfColumns, &numberOfRows, &highVal);
doneReading = TRUE;
fgetc(fpIn);
break;
}
free(string);
totalPixels = numberOfRows*numberOfColumns*numberOfBands;
image = (unsigned char *) malloc(totalPixels);
fread(image,1,totalPixels,fpIn);
/* find image mean
*/
meanF = 0.0;
meanI = 0;
for (i = 0; i < totalPixels; i++) {
meanF += image[i];
meanI += image[i];
}
meanI /= totalPixels;
meanF /= (float) totalPixels;
fprintf(stdout,"meanI = %d meanF = %f\n", meanI, meanF);
fpOut = fopen(argv[2],"wb");
fprintf(fpOut,"P%d\n%d %d\n255\n",
(numberOfBands==3?6:5), numberOfColumns, numberOfRows);
fwrite(image,1,totalPixels,fpOut);
}

