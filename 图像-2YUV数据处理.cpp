#include <iostream>

using namespace std;

//本文中像素的采样位数一律为8bit。由于1Byte=8bit，所以一个像素的一个分量的采样值占用1Byte
/**
 * Split Y, U, V planes in YUV420P file.
 * @param url  Location of Input YUV file.
 * @param w    Width of Input YUV file.
 * @param h    Height of Input YUV file.
 * @param num  Number of frames to process.
 *
 */
 //(1) 分离YUV420P像素数据中的Y、U、V分量
void simplest_yuv420_split(const char* url, int w, int h, int num)
{
        FILE* fp = fopen(url, "rb+");
        FILE* fp1 = fopen("output_420_y.y", "wb+");
        FILE* fp2 = fopen("output_420_u.y", "wb+");
        FILE* fp3 = fopen("output_420_v.y", "wb+");
        unsigned char* pic = (unsigned char*)malloc(w * h * 3 / 2);

        for (int i = 0; i < num; i++)
        {
                fread(pic, 1, w * h * 3 / 2, fp);
                fwrite(pic, 1, w * h, fp1);                              //Y
                fwrite(pic + w * h, 1, w * h / 4, fp2);            //U
                fwrite(pic + w * h * 5 / 4, 1, w * h / 4, fp3); //V
        }

        free(pic);
        fclose(fp);
        fclose(fp1);
        fclose(fp2);
        fclose(fp3);
}


//(2)分离YUV444P像素数据中的Y、U、V分量
void simplest_yuv444_split(char* url, int w, int h, int num)
{
        FILE* fp = fopen(url, "rb+");
        FILE* fp1 = fopen("output_444_y.y", "wb+");
        FILE* fp2 = fopen("output_444_u.y", "wb+");
        FILE* fp3 = fopen("output_444_v.y", "wb+");
        unsigned char* pic = (unsigned char*)malloc(w * h * 3);

        for (int i = 0; i < num; i++)
        {
                fread(pic, 1, w * h * 3, fp);
                fwrite(pic, 1, w * h, fp1);      //Y
                fwrite(pic + w * h, 1, w * h, fp2);  //U
                fwrite(pic + w * h * 2, 1, w * h, fp3);//V
        }

        free(pic);
        fclose(fp);
        fclose(fp1);
        fclose(fp2);
        fclose(fp3);
}

//(3) 将YUV420P像素数据去掉颜色（变成灰度图）
//如果想把YUV格式像素数据变成灰度图像，只需要将U、V分量设置成128即可。
//这是因为U、V是图像中的经过偏置处理的色度分量。
//色度分量在偏置处理前的取值范围是-128至127，这时候的无色对应的是“0”值。
//经过偏置后色度分量取值变成了0至255，因而此时的无色对应的就是128了。
void simplest_yuv420_gray(char* url, int w, int h, int num)
{
        FILE* fp = fopen(url, "rb+");
        FILE* fp1 = fopen("output_gray.yuv", "wb+");
        unsigned char* pic = (unsigned char*)malloc(w * h * 3 / 2);

        for (int i = 0; i < num; i++)
        {
                fread(pic, 1, w * h * 3 / 2, fp);
                memset(pic + w * h, 128, w * h / 2);  //Gray
                fwrite(pic, 1, w * h * 3 / 2, fp1);
        }

        free(pic);
        fclose(fp);
        fclose(fp1);
}

//(4)将YUV420P像素数据的亮度减半
void simplest_yuv420_halfy(char* url, int w, int h, int num)
{
        FILE* fp = fopen(url, "rb+");
        FILE* fp1 = fopen("output_half.yuv", "wb+");
        unsigned char* pic = (unsigned char*)malloc(w * h * 3 / 2);

        for (int i = 0; i < num; i++)
        {
                fread(pic, 1, w * h * 3 / 2, fp);
                for (int j = 0; j < w * h; j++)        //(Half)将图像的每个像素的Y值取出来分别进行除以2
                {
                        unsigned char temp = pic[j] / 2;
                        //printf("%d,\n",temp);
                        pic[j] = temp;
                }
                fwrite(pic, 1, w * h * 3 / 2, fp1);
        }

        free(pic);
        fclose(fp);
        fclose(fp1);
}

//(5)将YUV420P像素数据的周围加上边框
//从代码可以看出，图像的边框的宽度为border，本程序将距离图像边缘border范围内的像素的亮度分量Y的取值设置成了亮度最大值255。
/**
 * @param border  Width of Border.
 */
void simplest_yuv420_border(char* url, int w, int h, int border, int num)
{
        FILE* fp = fopen(url, "rb+");
        FILE* fp1 = fopen("output_border.yuv", "wb+");
        unsigned char* pic = (unsigned char*)malloc(w * h * 3 / 2);

        for (int i = 0; i < num; i++)
        {
                fread(pic, 1, w * h * 3 / 2, fp);
                //Y
                for (int j = 0; j < h; j++)
                {
                        for (int k = 0; k < w; k++)
                        {
                                if (k<border || k>(w - border) || j<border || j>(h - border)) {
                                        pic[j * w + k] = 255;
                                        //pic[j*w+k]=0;
                                }
                        }
                }
                fwrite(pic, 1, w * h * 3 / 2, fp1);
        }

        free(pic);
        fclose(fp);
        fclose(fp1);
}

//(6) 生成YUV420P格式的灰阶测试图
//从源代码可以看出，本程序一方面通过灰阶测试图的亮度最小值ymin，亮度最大值ymax，
//灰阶数量barnum确定每一个灰度条中像素的亮度分量Y的取值。
//另一方面还要根据图像的宽度width和图像的高度height以及灰阶数量barnum确定每一个灰度条的宽度。
//有了这两方面信息之后，就可以生成相应的图片了。
/**
 * Generate YUV420P gray scale bar.
 * @param width    Width of Output YUV file.
 * @param height   Height of Output YUV file.
 * @param ymin     Max value of Y
 * @param ymax     Min value of Y
 * @param barnum   Number of bars
 * @param url_out  Location of Output YUV file.
 * 调用：simplest_yuv420_graybar(640, 360,0,255,10,"graybar_640x360.yuv");
 */
int simplest_yuv420_graybar(int width, int height, int ymin, int ymax, int barnum, char* url_out)
{
        int barwidth;
        float lum_inc;
        unsigned char lum_temp;
        int uv_width, uv_height;
        FILE* fp = NULL;
        unsigned char* data_y = NULL;
        unsigned char* data_u = NULL;
        unsigned char* data_v = NULL;
        int t = 0, i = 0, j = 0;

        barwidth = width / barnum;
        lum_inc = ((float)(ymax - ymin)) / ((float)(barnum - 1));
        uv_width = width / 2;
        uv_height = height / 2;

        data_y = (unsigned char*)malloc(width * height);
        data_u = (unsigned char*)malloc(uv_width * uv_height);
        data_v = (unsigned char*)malloc(uv_width * uv_height);

        if ((fp = fopen(url_out, "wb+")) == NULL)
        {
                printf("Error: Cannot create file!");
                return -1;
        }

        //Output Info
        printf("Y, U, V value from picture's left to right:\n");
        for (t = 0; t < (width / barwidth); t++)
        {
                lum_temp = ymin + (char)(t * lum_inc);
                printf("%3d, 128, 128\n", lum_temp);
        }
        //Gen Data
        for (j = 0; j < height; j++)
        {
                for (i = 0; i < width; i++)
                {
                        t = i / barwidth;
                        lum_temp = ymin + (char)(t * lum_inc);
                        data_y[j * width + i] = lum_temp;
                }
        }
        for (j = 0; j < uv_height; j++)
        {
                for (i = 0; i < uv_width; i++)
                {
                        data_u[j * uv_width + i] = 128;
                }
        }
        for (j = 0; j < uv_height; j++)
        {
                for (i = 0; i < uv_width; i++)
                {
                        data_v[j * uv_width + i] = 128;
                }
        }
        fwrite(data_y, width * height, 1, fp);
        fwrite(data_u, uv_width * uv_height, 1, fp);
        fwrite(data_v, uv_width * uv_height, 1, fp);
        fclose(fp);
        free(data_y);
        free(data_u);
        free(data_v);
        return 0;
}

//(7)计算两个YUV420P像素数据的PSNR
/**
 * Calculate PSNR between 2 YUV420P file
 * @param url1     Location of first Input YUV file.
 * @param url2     Location of another Input YUV file.
 * @param w        Width of Input YUV file.
 * @param h        Height of Input YUV file.
 * @param num      Number of frames to process.
 * 调用：simplest_yuv420_psnr("lena_256x256_yuv420p.yuv","lena_distort_256x256_yuv420p.yuv",256,256,1);
 */
void simplest_yuv420_psnr(char* url1, char* url2, int w, int h, int num)
{
        FILE* fp1 = fopen(url1, "rb+");
        FILE* fp2 = fopen(url2, "rb+");
        unsigned char* pic1 = (unsigned char*)malloc(w * h);
        unsigned char* pic2 = (unsigned char*)malloc(w * h);

        for (int i = 0; i < num; i++)
        {
                fread(pic1, 1, w * h, fp1);
                fread(pic2, 1, w * h, fp2);

                double mse_sum = 0, mse = 0, psnr = 0;
                for (int j = 0; j < w * h; j++)
                {
                        mse_sum += pow((double)(pic1[j] - pic2[j]), 2);
                }
                mse = mse_sum / (w * h);
                psnr = 10 * log10(255.0 * 255.0 / mse);
                printf("%5.3f\n", psnr);

                fseek(fp1, w * h / 2, SEEK_CUR);
                fseek(fp2, w * h / 2, SEEK_CUR);

        }

        free(pic1);
        free(pic2);
        fclose(fp1);
        fclose(fp2);
}

int main()
{
        simplest_yuv420_split("bow.yuv", 352, 288, 300);

        return 0;
}
