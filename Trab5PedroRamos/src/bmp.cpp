//*********************************************************
//
// classe para fazer o carregamento de arquivos no formato BMP
// Autor: Cesar Tadeu Pozzer
//        pozzer@inf.ufsm.br
//  Versao 09/2010
//
//**********************************************************

#include "Bmp.h"
#include <string.h>

Bmp::Bmp(const char *fileName)
{
  width = height = 0;
  data = NULL;
  if (fileName != NULL && strlen(fileName) > 0)
  {
    load(fileName);
  }
  else
  {
    printf("Error: Invalid BMP filename");
  }
}

uchar *Bmp::getImage()
{
  return data;
}

int Bmp::getWidth(void)
{
  return width;
}

int Bmp::getHeight(void)
{
  return height;
}

void Bmp::convertBGRtoRGB()
{
  unsigned char tmp;
  if (data != NULL)
  {
    for (int y = 0; y < height; y++)
      for (int x = 0; x < width * 3; x += 3)
      {
        int pos = y * width * 3 + x;
        tmp = data[pos];
        data[pos] = data[pos + 2];
        data[pos + 2] = tmp;
      }
  }
}

void Bmp::load(const char *fileName)
{
  FILE *fp = fopen(fileName, "rb");
  if (fp == NULL)
  {
    printf("\nErro ao abrir arquivo %s para leitura", fileName);
    return;
  }

  // le o HEADER componente a componente devido ao problema de alinhamento de bytes. Usando
  // o comando fread(header, sizeof(HEADER),1,fp) sao lidos 16 bytes ao inves de 14
  fread(&header.type, sizeof(unsigned short int), 1, fp);
  fread(&header.size, sizeof(unsigned int), 1, fp);
  fread(&header.reserved1, sizeof(unsigned short int), 1, fp);
  fread(&header.reserved2, sizeof(unsigned short int), 1, fp);
  fread(&header.offset, sizeof(unsigned int), 1, fp); // indica inicio do bloco de pixels

  // le o INFOHEADER componente a componente devido ao problema de alinhamento de bytes
  fread(&info.size, sizeof(unsigned int), 1, fp);
  fread(&info.width, sizeof(int), 1, fp);
  fread(&info.height, sizeof(int), 1, fp);
  fread(&info.planes, sizeof(unsigned short int), 1, fp);
  fread(&info.bits, sizeof(unsigned short int), 1, fp);
  fread(&info.compression, sizeof(unsigned int), 1, fp);
  fread(&info.imagesize, sizeof(unsigned int), 1, fp);
  fread(&info.xresolution, sizeof(int), 1, fp);
  fread(&info.yresolution, sizeof(int), 1, fp);
  fread(&info.ncolours, sizeof(unsigned int), 1, fp);
  fread(&info.impcolours, sizeof(unsigned int), 1, fp);

  width = info.width;
  height = info.height;
  bits = info.bits;
  bytesPerLine = (3 * (width + 1) / 4) * 4;
  imagesize = bytesPerLine * height;
  int delta = bytesPerLine - (3 * width);

  if (header.type != 19778)
  {
    printf("\nError: Arquivo BMP invalido");
    getchar();
    exit(0);
  }

  if (info.compression != 0)
  {
    printf("\nError: Formato BMP comprimido nao suportado");
    getchar();
    return;
  }
  if (bits != 24)
  {
    printf("\nError: Formato BMP com %d bits/pixel nao suportado", bits);
    getchar();
    return;
  }

  if (info.planes != 1)
  {
    printf("\nError: Numero de Planes nao suportado: %d", info.planes);
    getchar();
    return;
  }

  data = new unsigned char[3 * width * height];
  for (int l = 0; l < height; l++)
  {
    int pos = l * bytesPerLine;
    fseek(fp, header.offset + pos, SEEK_SET);
    fread(data + width * 3 * l, sizeof(unsigned char), 3 * width, fp);
  }

  fclose(fp);
}
