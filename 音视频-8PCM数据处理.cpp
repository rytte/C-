#include <iostream>

using namespace std;

//本文中声音样值的采样频率一律是44100Hz，采样格式一律为16LE。
//“16”代表采样位数是16bit。由于1Byte=8bit，所以一个声道的一个采样值占用2Byte。
//“LE”代表Little Endian，代表2 Byte采样值的存储方式为高位存在高地址中。


//（1）分离PCM16LE双声道音频采样数据的左声道和右声道
//PCM16LE双声道数据中左声道和右声道的采样值是间隔存储的。每个采样值占用2Byte空间
/**
 * Split Left and Right channel of 16LE PCM file.
 * @param url  Location of PCM file.
 *
 */
void simplest_pcm16le_split(const char* url)
{
        FILE* fp = fopen(url, "rb+");
        FILE* fp1 = fopen("output_l.pcm", "wb+");
        FILE* fp2 = fopen("output_r.pcm", "wb+");
        unsigned char* sample = (unsigned char*)malloc(4);

        while (!feof(fp))
        {
                fread(sample, 1, 4, fp);
                fwrite(sample, 1, 2, fp1);        //L
                fwrite(sample + 2, 1, 2, fp2);      //R
        }

        free(sample);
        fclose(fp);
        fclose(fp1);
        fclose(fp2);
}

//（2）将PCM16LE双声道音频采样数据中左声道的音量降一半
void simplest_pcm16le_halfvolumeleft(char* url)
{
        FILE* fp = fopen(url, "rb+");
        FILE* fp1 = fopen("output_halfleft.pcm", "wb+");

        int cnt = 0;
        unsigned char* sample = (unsigned char*)malloc(4);

        while (!feof(fp))
        {
                short* samplenum = NULL;
                fread(sample, 1, 4, fp);

                samplenum = (short*)sample;
                *samplenum = *samplenum / 2;

                fwrite(sample, 1, 2, fp1);        //L
                fwrite(sample + 2, 1, 2, fp1);      //R

                cnt++;
        }
        printf("Sample Cnt:%d\n", cnt);

        free(sample);
        fclose(fp);
        fclose(fp1);
}

//（3）将PCM16LE双声道音频采样数据的声音速度提高一倍
void simplest_pcm16le_doublespeed(char* url)
{
        FILE* fp = fopen(url, "rb+");
        FILE* fp1 = fopen("output_doublespeed.pcm", "wb+");

        int cnt = 0;
        unsigned char* sample = (unsigned char*)malloc(4);

        while (!feof(fp))
        {
                fread(sample, 1, 4, fp);

                if (cnt % 2 != 0)        //只采样了每个声道奇数点的样值
                {
                        fwrite(sample, 1, 2, fp1);            //L
                        fwrite(sample + 2, 1, 2, fp1);          //R
                }
                cnt++;
        }
        printf("Sample Cnt:%d\n", cnt);

        free(sample);
        fclose(fp);
        fclose(fp1);
}

//（4）将PCM16LE双声道音频采样数据转换为PCM8音频采样数据
//PCM16LE格式的采样数据的取值范围是-32768到32767，而PCM8格式的采样数据的取值范围是0到255。
//所以PCM16LE转换到PCM8需要经过两个步骤：
//第一步是将-32768到32767的16bit有符号数值转换为-128到127的8bit有符号数值，
//第二步是将-128到127的8bit有符号数值转换为0到255的8bit无符号数值。
//在本程序中，16bit采样数据是通过short类型变量存储的，而8bit采样数据是通过unsigned char类型存储的。
void simplest_pcm16le_to_pcm8(char* url)
{
        FILE* fp = fopen(url, "rb+");
        FILE* fp1 = fopen("output_8.pcm", "wb+");

        int cnt = 0;
        unsigned char* sample = (unsigned char*)malloc(4);

        while (!feof(fp))
        {
                short* samplenum16 = NULL;
                char samplenum8 = 0;
                unsigned char samplenum8_u = 0;
                fread(sample, 1, 4, fp);
                //(-32768-32767)
                samplenum16 = (short*)sample;
                samplenum8 = (*samplenum16) >> 8;
                //(0-255)
                samplenum8_u = samplenum8 + 128;
                //L
                fwrite(&samplenum8_u, 1, 1, fp1);

                samplenum16 = (short*)(sample + 2);
                samplenum8 = (*samplenum16) >> 8;
                samplenum8_u = samplenum8 + 128;
                //R
                fwrite(&samplenum8_u, 1, 1, fp1);
                cnt++;
        }
        printf("Sample Cnt:%d\n", cnt);

        free(sample);
        fclose(fp);
        fclose(fp1);
}

//（5）将从PCM16LE单声道音频采样数据中截取一部分数据
//本程序可以从PCM数据中选取一段采样值保存下来，并且输出这些采样值的数值。
//上述代码运行后，会把单声道PCM16LE格式的“drum.pcm”中从2360点开始的120点的数据保存成output_cut.pcm文件。
/**
 * Cut a 16LE PCM single channel file.
 * @param url        Location of PCM file.
 * @param start_num  start point
 * @param dur_num    how much point to cut
 * 调用：simplest_pcm16le_cut_singlechannel("drum.pcm",2360,120);
 */
void simplest_pcm16le_cut_singlechannel(char* url, int start_num, int dur_num)
{
        FILE* fp = fopen(url, "rb+");
        FILE* fp1 = fopen("output_cut.pcm", "wb+");
        FILE* fp_stat = fopen("output_cut.txt", "wb+");

        unsigned char* sample = (unsigned char*)malloc(2);

        int cnt = 0;
        while (!feof(fp))
        {
                fread(sample, 1, 2, fp);
                if (cnt > start_num && cnt <= (start_num + dur_num))
                {
                        fwrite(sample, 1, 2, fp1);

                        short samplenum = sample[1];
                        samplenum = samplenum * 256;
                        samplenum = samplenum + sample[0];

                        fprintf(fp_stat, "%6d,", samplenum);
                        if (cnt % 10 == 0)
                                fprintf(fp_stat, "\n", samplenum);
                }
                cnt++;
        }

        free(sample);
        fclose(fp);
        fclose(fp1);
        fclose(fp_stat);
}


int main()
{
        simplest_pcm16le_split("aki.pcm");

        return 0;
}
