#include <stdio.h>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
int main(int argc, char *argv[])
{
if(argc !=3)
{
    fprintf(stderr,"Uso: %s <ruta_imagen_color.jpg> <ruta_imagen_gris.jpg\n",argv[0]);
    return 1;
}

    const char *fotopluto1=argv[1];
    const char *fotopluto2=argv[2];
    int width,height,channels;
    unsigned char *img_data;

    img_data=stbi_load(fotopluto1,&width,&height,&channels,STBI_rgb);
    if(img_data==NULL)
    {
        fprintf(stderr,"Error:no se pudo cargar la imagen '%s'.\n",fotopluto1);
        return 1;
    }
    printf("Imagen cargada:%s (Ancho %d,Alto %d,Canales originales %d)\n",fotopluto1,width,height,channels);

    unsigned char *gray_img_data= (unsigned char *)malloc (width* height* sizeof(unsigned char));
    if(gray_img_data==NULL)
    {

    fprintf(stderr,"Error: No se pudo asignar memoria a la imagen.\n");
    stbi_image_free(img_data);
    return 1;
    }
long i,j;
for(i=0;i<height;i++)
{
    for(j=0;j<width;j++)
    {
        long pixel_index_rgb=(i * width+j)*3;
        unsigned char r=img_data[pixel_index_rgb];
        unsigned char g=img_data[pixel_index_rgb +1];
        unsigned char b=img_data[pixel_index_rgb +2];

        unsigned char gray=(unsigned char)(0.299*r+0.587*g+0.114*b);
        long pixel_index_gray=(i*width+j);
        gray_img_data[pixel_index_gray]=gray;
    }
}

int success =stbi_write_jpg(fotopluto2,width,height,1,gray_img_data,90);
if(success)
{
    printf("Imagen convertida y guardada como '%s'.\n",fotopluto2);
}
else
{
    fprintf(stderr,"Error:No se puedo guardar la imagen '%s'.\n",fotopluto2);
}
stbi_image_free(img_data);
free(gray_img_data);

return 0;
}

