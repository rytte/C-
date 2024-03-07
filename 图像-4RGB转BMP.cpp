/*************************/RGB数据转BMP图像/***************************************************************************/
将RGB24格式像素数据封装为BMP图像
BMP图像内部实际上存储的就是RGB数据。本程序实现了对RGB像素数据的封装处理。


//BMP格式结构
BMP文件是由BITMAPFILEHEADER、BITMAPINFOHEADER、RGB像素数据共3个部分构成。
其中前两部分的结构如下所示。在写入BMP文件头的时候给其中的每个字段赋上合适的值就可以了。

typedef  struct  tagBITMAPFILEHEADER
{
	unsigned short int  bfType;		//位图文件的类型，必须为BM 
	unsigned long       bfSize;		//文件大小，以字节为单位
	unsigned short int  bfReserverd1;  //位图文件保留字，必须为0 
	unsigned short int  bfReserverd2; //位图文件保留字，必须为0 
	unsigned long       bfbfOffBits;      //位图文件头到数据的偏移量，以字节为单位
}BITMAPFILEHEADER;
typedef  struct  tagBITMAPINFOHEADER
{
	long biSize;                        //该结构大小，字节为单位
	long  biWidth;                     //图形宽度以象素为单位
	long  biHeight;                     //图形高度以象素为单位
	short int  biPlanes;               //目标设备的级别，必须为1 
	short int  biBitcount;             //颜色深度，每个象素所需要的位数
	short int  biCompression;       //位图的压缩类型
	long  biSizeImage;              //位图的大小，以字节为单位
	long  biXPelsPermeter;       //位图水平分辨率，每米像素数
	long  biYPelsPermeter;       //位图垂直分辨率，每米像素数
	long  biClrUsed;		//位图实际使用的颜色表中的颜色数
	long  biClrImportant;       //位图显示过程中重要的颜色数
}BITMAPINFOHEADER;

//BMP存储方式
BMP采用的是小端（Little Endian）存储方式。
这种存储方式中“RGB24”格式的像素的分量存储的先后顺序为B、G、R。
由于RGB24格式存储的顺序是R、G、B，所以需要将“R”和“B”顺序作一个调换再进行存储。


//实例
以下程序完成了主要完成两个工作：
 1)将RGB数据前面加上文件头。
 2)将RGB数据中每个像素的“B”和“R”的位置互换。

 /**
  * Convert RGB24 file to BMP file
  * @param rgb24path    Location of input RGB file.
  * @param width        Width of input RGB file.
  * @param height       Height of input RGB file.
  * @param url_out      Location of Output BMP file.
  * 调用：simplest_rgb24_to_bmp("lena_256x256_rgb24.rgb",256,256,"output_lena.bmp");
  */
int simplest_rgb24_to_bmp(const char* rgb24path, int width, int height, const char* bmppath)
{
        typedef struct
        {
                long imageSize;
                long blank;
                long startPosition;
        }BmpHead;

        typedef struct
        {
                long  Length;
                long  width;
                long  height;
                unsigned short  colorPlane;
                unsigned short  bitColor;
                long  zipFormat;
                long  realSize;
                long  xPels;
                long  yPels;
                long  colorUse;
                long  colorImportant;
        }InfoHead;

        int i = 0, j = 0;
        BmpHead m_BMPHeader = { 0 };
        InfoHead  m_BMPInfoHeader = { 0 };
        char bfType[2] = { 'B','M' };
        int header_size = sizeof(bfType) + sizeof(BmpHead) + sizeof(InfoHead);
        unsigned char* rgb24_buffer = NULL;
        FILE* fp_rgb24 = NULL, * fp_bmp = NULL;

        if ((fp_rgb24 = fopen(rgb24path, "rb")) == NULL)
        {
                printf("Error: Cannot open input RGB24 file.\n");
                return -1;
        }
        if ((fp_bmp = fopen(bmppath, "wb")) == NULL)
        {
                printf("Error: Cannot open output BMP file.\n");
                return -1;
        }

        rgb24_buffer = (unsigned char*)malloc(width * height * 3);
        fread(rgb24_buffer, 1, width * height * 3, fp_rgb24);

        m_BMPHeader.imageSize = 3 * width * height + header_size;
        m_BMPHeader.startPosition = header_size;

        m_BMPInfoHeader.Length = sizeof(InfoHead);
        m_BMPInfoHeader.width = width;
        //BMP storage pixel data in opposite direction of Y-axis (from bottom to top).
        m_BMPInfoHeader.height = -height;
        m_BMPInfoHeader.colorPlane = 1;
        m_BMPInfoHeader.bitColor = 24;
        m_BMPInfoHeader.realSize = 3 * width * height;

        fwrite(bfType, 1, sizeof(bfType), fp_bmp);
        fwrite(&m_BMPHeader, 1, sizeof(m_BMPHeader), fp_bmp);
        fwrite(&m_BMPInfoHeader, 1, sizeof(m_BMPInfoHeader), fp_bmp);

        //BMP save R1|G1|B1,R2|G2|B2 as B1|G1|R1,B2|G2|R2
        //It saves pixel data in Little Endian
        //So we change 'R' and 'B'
        for (j = 0; j < height; j++)
        {
                for (i = 0; i < width; i++)
                {
                        char temp = rgb24_buffer[(j * width + i) * 3 + 2];
                        rgb24_buffer[(j * width + i) * 3 + 2] = rgb24_buffer[(j * width + i) * 3 + 0];
                        rgb24_buffer[(j * width + i) * 3 + 0] = temp;
                }
        }
        fwrite(rgb24_buffer, 3 * width * height, 1, fp_bmp);
        fclose(fp_rgb24);
        fclose(fp_bmp);
        free(rgb24_buffer);
        printf("Finish generate %s!\n", bmppath);
        return 0;
}
