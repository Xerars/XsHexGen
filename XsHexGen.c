#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
  if(argc<2)
  {
    printf("Usage:\n\t XsHexGen <filename>\n");
    return 1;
  }

  const char *fname=argv[1];

  FILE *fp=fopen(fname,"rb");
  if(!fp)
  {
    fprintf(stderr,"Error Opening Files: %s.\n",fname);
    return 1;
  }

  //Get File Size
  fseek(fp,0,SEEK_END);       //Shift to End
  const int fsize=ftell(fp);  //Get File Size
  fseek(fp,0,SEEK_SET);       //Shift to First

  unsigned char *b=malloc(fsize);

  fread(b,fsize,1,fp);    //Read File
  fclose(fp);             //Close File

  printf("/* Embedded Image File : %s */\n",fname);
  printf("const int fsize  = %d;        /* File Size */\n",fsize);
  printf("const unsigned char *file =\n");
  printf("{\n");
  int i;
  for(i=0;i<fsize;++i)
    printf("0x%02x%s",b[i],i==fsize-1?"":((i+1)%16==0?",\n":","));

  printf("\n};\n");
  return 0;
}