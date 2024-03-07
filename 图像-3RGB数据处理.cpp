#include <iostream>

using namespace std;

/**
 * Split R, G, B planes in RGB24 file.
 * @param url  Location of Input RGB file.
 * @param w    Width of Input RGB file.
 * @param h    Height of Input RGB file.
 * @param num  Number of frames to process.
 *
 */
 //(1)分离RGB24像素数据中的R、G、B分量
void simplest_rgb24_split(char* url, int w, int h, int num)
{
        FILE* fp = fopen(url, "rb+");
        FILE* fp1 = fopen("output_r.y", "wb+");
        FILE* fp2 = fopen("output_g.y", "wb+");
        FILE* fp3 = fopen("output_b.y", "wb+");
        unsigned char* pic = (unsigned char*)malloc(w * h * 3);

        for (int i = 0; i < num; i++)
        {
                fread(pic, 1, w * h * 3, fp);
                for (int j = 0; j < w * h * 3; j = j + 3)
                {
                        fwrite(pic + j, 1, 1, fp1);      //R
                        fwrite(pic + j + 1, 1, 1, fp2);    //G
                        fwrite(pic + j + 2, 1, 1, fp3);    //B
                }
        }

        free(pic);
        fclose(fp);
        fclose(fp1);
        fclose(fp2);
        fclose(fp3);
}

//(2)生成RGB24格式的彩条测试图
//本程序循环输出“白黄青绿品红蓝黑”8种颜色的彩条。
/**
 * Generate RGB24 colorbar.
 * @param width    Width of Output RGB file.
 * @param height   Height of Output RGB file.
 * @param url_out  Location of Output RGB file.
 * 调用：simplest_rgb24_colorbar(640, 360,"colorbar_640x360.rgb");
 */
int simplest_rgb24_colorbar(int width, int height, char* url_out)
{
        unsigned char* data = NULL;
        int barwidth;
        char filename[100] = { 0 };
        FILE* fp = NULL;
        int i = 0, j = 0;

        data = (unsigned char*)malloc(width * height * 3);
        barwidth = width / 8;

        if ((fp = fopen(url_out, "wb+")) == NULL)
        {
                printf("Error: Cannot create file!");
                return -1;
        }

        for (j = 0; j < height; j++)
        {
                for (i = 0; i < width; i++)
                {
                        int barnum = i / barwidth;
                        switch (barnum)
                        {
                        case 0: {
                                data[(j * width + i) * 3 + 0] = 255;
                                data[(j * width + i) * 3 + 1] = 255;
                                data[(j * width + i) * 3 + 2] = 255;
                                break;
                        }
                        case 1: {
                                data[(j * width + i) * 3 + 0] = 255;
                                data[(j * width + i) * 3 + 1] = 255;
                                data[(j * width + i) * 3 + 2] = 0;
                                break;
                        }
                        case 2: {
                                data[(j * width + i) * 3 + 0] = 0;
                                data[(j * width + i) * 3 + 1] = 255;
                                data[(j * width + i) * 3 + 2] = 255;
                                break;
                        }
                        case 3: {
                                data[(j * width + i) * 3 + 0] = 0;
                                data[(j * width + i) * 3 + 1] = 255;
                                data[(j * width + i) * 3 + 2] = 0;
                                break;
                        }
                        case 4: {
                                data[(j * width + i) * 3 + 0] = 255;
                                data[(j * width + i) * 3 + 1] = 0;
                                data[(j * width + i) * 3 + 2] = 255;
                                break;
                        }
                        case 5: {
                                data[(j * width + i) * 3 + 0] = 255;
                                data[(j * width + i) * 3 + 1] = 0;
                                data[(j * width + i) * 3 + 2] = 0;
                                break;
                        }
                        case 6: {
                                data[(j * width + i) * 3 + 0] = 0;
                                data[(j * width + i) * 3 + 1] = 0;
                                data[(j * width + i) * 3 + 2] = 255;

                                break;
                        }
                        case 7: {
                                data[(j * width + i) * 3 + 0] = 0;
                                data[(j * width + i) * 3 + 1] = 0;
                                data[(j * width + i) * 3 + 2] = 0;
                                break;
                        }
                        }

                }
        }
        fwrite(data, width * height * 3, 1, fp);
        fclose(fp);
        free(data);
}


int main()
{
        simplest_rgb24_split("cie1931_500x500.rgb", 500, 500, 1);
        return 0;
}
