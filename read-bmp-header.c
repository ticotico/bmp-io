#include <stdio.h>
#include <stdlib.h>

typedef struct{
  unsigned short int type;
  unsigned int size;
  unsigned short int reserved[2];
  unsigned int offset;

} FileHeader;

void fileHeaderRead(FILE *fp, FileHeader *fh){
  fread(&fh->type, sizeof(unsigned short int), 1, fp);
  fread(&fh->size, sizeof(unsigned int), 1, fp);
  fread(&fh->reserved, 2 * sizeof(unsigned short int), 1, fp);
  fread(&fh->offset, sizeof(unsigned int), 1, fp);
}

void fileHeaderPrint(FileHeader fh) {
	printf("type = %x\n", fh.type);
	printf("size = %d\n", fh.size);
	printf("reversed[0] = %d\n", fh.reserved[0]);
	printf("reversed[1] = %d\n", fh.reserved[1]);
	printf("offset = %d\n", fh.offset);
}

typedef struct{
  unsigned int infosize;
  int width, height;
  unsigned short int planes;
  unsigned short int bits;
  unsigned int compression;
  unsigned int imagesize;
  int xresolution, yresolution;
  unsigned int ncolours;
  unsigned int importantcolours;

} InfoHeader;

void infoHeaderRead(FILE *fp, InfoHeader *ih){
  fread(&ih->infosize, sizeof(unsigned int), 1, fp);
  fread(&ih->width, sizeof(int), 1, fp);
  fread(&ih->height, sizeof(int), 1, fp);
  fread(&ih->planes, sizeof(unsigned short int), 1, fp);
  fread(&ih->bits, sizeof(unsigned short int), 1, fp);
  fread(&ih->compression, sizeof(unsigned int), 1, fp);
  fread(&ih->imagesize, sizeof(unsigned int), 1, fp);
  fread(&ih->xresolution, sizeof(int), 1, fp);
  fread(&ih->yresolution, sizeof(int), 1, fp);
  fread(&ih->ncolours, sizeof(unsigned int), 1, fp);
  fread(&ih->importantcolours, sizeof(unsigned int), 1, fp);
}

void infoHeaderPrint(InfoHeader ih){
 	printf("infosize = %d\n", ih.infosize);
 	printf("width = %d\n", ih.width);
 	printf("height = %d\n", ih.height);
 	printf("planes = %d\n", ih.planes);
 	printf("bits = %d\n", ih.bits);
 	printf("compression = %d\n", ih.compression);
 	printf("imagesize = %d\n", ih.imagesize);
 	printf("xresolution = %d\n", ih.xresolution);
 	printf("yresolution = %d\n", ih.yresolution);
 	printf("ncolours = %d\n", ih.ncolours);
 	printf("importantcolours = %d\n", ih.importantcolours);
 }
int main(void)
{
  char filename[256] = "filename.bmp\0";
  FILE *fp;
  FileHeader fh;
  InfoHeader ih;
  fp = fopen(filename, "rb");
  if (fp == NULL) {
  	printf("Error: cannot open %s\n", filename);
  	return -1;
  }
  
  fileHeaderRead(fp, &fh);
  infoHeaderRead(fp, &ih);
  
  fileHeaderPrint(fh);
  infoHeaderPrint(ih);
  
  fclose(fp);
  return 0;
}
