#include "quickdemo.h"

QuickDemo::QuickDemo()
{
        image = imread("D:/Code/opencv_test2/600395.jpg", 1);
}

//图片拼接
void QuickDemo::imageSplicing()
{
        Mat image1 = imread("D:/Code/opencv_test2/600395.jpg", 1);
        Mat image2 = imread("D:/Code/opencv_test2/240236.jpg", 1);
        if (!image1.data) return;

        Mat imageROI = image1(Rect(50, 80, image2.cols, image2.rows));            //横坐标，纵坐标，列数，行数
        image2.copyTo(imageROI);

        namedWindow("ROI图像叠加", WINDOW_GUI_NORMAL);
        imshow("ROI图像叠加", image1);
}

//色彩空间转换
void QuickDemo::colorSpace()
{
        Mat gray;
        Mat hsv;
        cvtColor(image, hsv, COLOR_BGR2HSV);
        cvtColor(image, gray, COLOR_BGR2GRAY);

        //    imwrite("C:/Users/13055/Desktop/hsv.jpg", hsv);           //保存hsv图片
        //    imwrite("C:/Users/13055/Desktop/gray.jpg", gray);         //保存gray图片

        imshow("HSV", hsv);
        imshow("灰度", gray);
}

//mat创建
void QuickDemo::mat_creation()
{
        Mat m3 = Mat::zeros(Size(400, 400), CV_8UC3);
        m3 = Scalar(0, 0, 255);
        imshow("图像", m3);

        Mat m4 = m3;
        m4 = Scalar(0, 255, 255);
        imshow("图像", m3);               //m3随浅拷贝的m4改变而改变

        Mat m5;
        //m5 = m3.clone();              //克隆，深拷贝
        m3.copyTo(m5);                  //复制，深拷贝
        m5 = Scalar(255, 255, 0);
        imshow("图像", m3);              //m3不随m5改变而改变
}

//像素访问
void QuickDemo::pixel_visit()
{
        int w = image.cols;
        int h = image.rows;
        int dims = image.channels();

        for (int row = 0; row < h; row++)
        {
                for (int col = 0; col < w; col++)
                {
                        if (dims == 1)                                   //灰度图像
                        {
                                int px = image.at<uchar>(row, col);         //获取像素值
                                image.at<uchar>(row, col) = 255 - px;           //修改像素值，取反
                        }
                        if (dims == 3)                                   //彩色图像
                        {
                                Vec3b bgr = image.at<Vec3b>(row, col);      //获取像素值
                                image.at<Vec3b>(row, col)[0] = 255 - bgr[0]; //修改像素值，取反
                                image.at<Vec3b>(row, col)[1] = 255 - bgr[1];
                                image.at<Vec3b>(row, col)[2] = 255 - bgr[2];
                        }
                }
        }
        imshow("像素读写", image);
}

//操作符运算
void QuickDemo::operators_demo()
{
        imshow("原图", image);

        Mat dst;
        dst = image + Scalar(40, 40, 40);               //add(image, m, dst);
        imshow("加法操作", dst);
        dst = image - Scalar(40, 40, 40);               //subtract(image, m, dst);
        imshow("减法操作", dst);
        dst = image / Scalar(2, 2, 2);                  //divide(image, m, dst);
        imshow("除法操作", dst);
        //直接乘法操作会造成内存溢出
        Mat m = Mat::zeros(image.size(), image.type());
        m = Scalar(2, 2, 2);
        multiply(image, m, dst);
        imshow("乘法操作", dst);
}

//滚动条调节
static void on_track(int b, void* userdata)
{
        Mat image = *((Mat*)userdata);
        Mat dst = Mat::zeros(image.size(), image.type());
        Mat m = Mat::zeros(image.size(), image.type());
        m = Scalar(b, b, b);
        add(image, m, dst);
        imshow("亮度调整", dst);
}

void QuickDemo::tracking_bar()
{
        namedWindow("亮度调整", WINDOW_AUTOSIZE);
        int lightness = 50;
        int max_value = 100;
        createTrackbar("Value Bar:", "亮度调整", &lightness, max_value, on_track, (void*)(&image));
        on_track(50, &image);
}

//伪彩色
void QuickDemo::color_style()
{
        Mat dst;
        int index = 0;
        while (true)
        {
                int c = waitKey(1500);
                if (c == 27)
                        break;

                applyColorMap(image, dst, index++ % 19);
                imshow("颜色风格", dst);
        }
}

//图像位操作
void QuickDemo::bitwise()
{
        Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
        Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);
        rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);
        rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);
        //    imshow("m1", m1);
        //    imshow("m2", m2);
        Mat dst;
        bitwise_and(m1, m2, dst);
        imshow("像素与操作", dst);
        bitwise_or(m1, m2, dst);
        imshow("像素或操作", dst);
        bitwise_xor(m1, m2, dst);
        imshow("像素异或操作", dst);
        bitwise_not(m1, dst);
        imshow("像素非操作", dst);
}

//通道分离与合并
void QuickDemo::channels()
{
        vector<Mat> mv;
        split(image, mv);
        imshow("蓝色通道", mv[0]);
        imshow("绿色通道", mv[1]);
        imshow("红色通道", mv[2]);

        Mat dst;
        mv[1] = 0;
        mv[2] = 0;
        merge(mv, dst);
        imshow("蓝色", dst);

        int from_to[] = { 0, 2, 1, 1, 2, 0 };
        mixChannels(&image, 1, &dst, 1, from_to, 3);
        imshow("通道混合", dst);
}

//抠图
void QuickDemo::inrange()
{
        Mat hsv;
        cvtColor(image, hsv, COLOR_BGR2HSV);
        Mat mask;
        inRange(hsv, Scalar(35, 43, 46), Scalar(77, 255, 255), mask);

        Mat redback = Mat::zeros(image.size(), image.type());
        redback = Scalar(40, 40, 200);
        bitwise_not(mask, mask);
        imshow("mask", mask);
        image.copyTo(redback, mask);
        imshow("ROI区域提取", redback);
}

//像素统计计算
void QuickDemo::pixel_statistic()
{
        double minv, maxv;
        Point minLoc, maxLoc;
        vector<Mat> mv;
        split(image, mv);
        for (int i = 0; i < mv.size(); i++)
        {
                minMaxLoc(mv[i], &minv, &maxv, &minLoc, &maxLoc, Mat());        //获取区域最大值最小值
                cout << "No.channel:" << i << "    ";
                cout << "min value:" << minv << "    ";
                cout << "max value:" << maxv << endl;
        }

        Mat mean, stddev;
        meanStdDev(image, mean, stddev);                                    //计算均值与方差
        cout << "mean:" << mean << endl;                                    //分别输出三个通道均值
        cout << "stddev:" << stddev << endl;                                //分别输出三个通道方差
}

//图形绘制
void QuickDemo::geometry_drawing()
{
        Rect rect;
        rect.x = 200;
        rect.y = 100;
        rect.width = 80;
        rect.height = 80;
        rectangle(image, rect, Scalar(0, 0, 255), 2, 8, 0);                       //绘制矩形
        circle(image, Point(200, 200), 20, Scalar(255, 0, 0), 2, LINE_AA, 0);     //绘制圆           LINE_AA:反锯齿
        line(image, Point(100, 100), Point(300, 300), Scalar(0, 255, 0), 4, 8, 0);  //绘制直线

        RotatedRect rrt;
        rrt.center = Point(200, 200);
        rrt.size = Size(100, 200);
        rrt.angle = 90.0;
        ellipse(image, rrt, Scalar(0, 255, 255), 2, LINE_AA);                     //绘制椭圆

        imshow("绘制演示", image);
}

//随机数与随机颜色
void QuickDemo::random_drawing()
{
        Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
        RNG rng(12345);
        while (1)
        {
                int c = waitKey(20);
                if (c == 27)
                        break;

                int x1 = rng.uniform(0, canvas.cols);
                int y1 = rng.uniform(0, canvas.rows);
                int x2 = rng.uniform(0, canvas.cols);
                int y2 = rng.uniform(0, canvas.rows);
                line(canvas, Point(x1, y1), Point(x2, y2), Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255)), 1, 8, 0);  //绘制随机直线
                imshow("随机绘制", canvas);
        }
}

//绘制多边形和填充
void QuickDemo::polyline_drawing()
{
        Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
        Point p1(100, 100);
        Point p2(350, 100);
        Point p3(450, 280);
        Point p4(320, 450);
        Point p5(80, 400);
        vector<Point> pts;
        pts.push_back(p1);
        pts.push_back(p2);
        pts.push_back(p3);
        pts.push_back(p4);
        pts.push_back(p5);
        //    polylines(canvas, pts, true, Scalar(0,0,255), 2, 8, 0);                     //绘制多边形
        //    fillPoly(canvas, pts, Scalar(255,255,0), 8, 0);                             //填充多边形

        vector<vector<Point>> contours;
        contours.push_back(pts);
        drawContours(canvas, contours, -1, Scalar(255, 0, 0), -1);                      //绘制多个多边形及填充

        imshow("多边形绘制", canvas);
}

//鼠标绘图操作
Point sp(-1, -1);
Point ep(-1, -1);
Mat temp;

static void on_draw(int event, int x, int y, int flag, void* userdata)
{
        Mat image = *((Mat*)userdata);
        if (event == EVENT_LBUTTONDOWN)                  //鼠标按下获取起始点
        {
                sp.x = x;
                sp.y = y;
                cout << "start point:" << sp << endl;
        }
        else if (event == EVENT_LBUTTONUP)               //鼠标松开获取终点
        {
                ep.x = x;
                ep.y = y;
                int dx = ep.x - sp.x;
                int dy = ep.y - sp.y;
                if (dx > 0 && dy > 0)
                {
                        Rect box(sp.x, sp.y, dx, dy);
                        rectangle(image, box, Scalar(0, 0, 255), 2, 8, 0);
                        imshow("鼠标绘制", image);
                        imshow("ROI区域", temp(box));
                        sp.x = -1;
                        sp.y = -1;
                }
        }
        else if (event == EVENT_MOUSEMOVE)
        {
                if (sp.x > 0 && sp.y > 0)
                {
                        ep.x = x;
                        ep.y = y;
                        int dx = ep.x - sp.x;
                        int dy = ep.y - sp.y;
                        if (dx > 0 && dy > 0)
                        {
                                Rect box(sp.x, sp.y, dx, dy);
                                temp.copyTo(image);
                                rectangle(image, box, Scalar(0, 0, 255), 2, 8, 0);
                                imshow("鼠标绘制", image);
                        }
                }
        }
}

void QuickDemo::mouse_drawing()
{
        namedWindow("鼠标绘制", WINDOW_AUTOSIZE);
        setMouseCallback("鼠标绘制", on_draw, (void*)(&image));
        imshow("鼠标绘制", image);
        temp = image.clone();
}

//归一化
void QuickDemo::norm_demo()
{
        Mat dst;
        cout << image.type() << endl;
        image.convertTo(dst, CV_32F);                   //像素类型转换
        cout << dst.type() << endl;
        normalize(image, dst, 1.0, 0, NORM_MINMAX);     //归一化：将所有像素数据按比例变为0-1之间的数
        cout << dst.type() << endl;
        imshow("图像数据归一化", dst);
}

//图像缩放
void QuickDemo::resize_demo()
{
        Mat zoomin, zoomout;
        int w = image.cols;
        int h = image.rows;
        resize(image, zoomin, Size(w / 2, h / 2), 0, 0, INTER_LINEAR);
        imshow("zoomin", zoomin);
        resize(image, zoomout, Size(w / 1.5, h / 1.5), 0, 0, INTER_LINEAR);
        imshow("zoomout", zoomout);
}

//图像翻转
void QuickDemo::flip_demo()
{
        Mat dst;
        flip(image, dst, 0);                     //上下翻转
        imshow("上下翻转", dst);
        flip(image, dst, 1);                     //左右翻转
        imshow("左右翻转", dst);
        flip(image, dst, -1);                    //对角翻转
        imshow("对角翻转", dst);
}

//图像旋转
void QuickDemo::rotate_demo()
{
        Mat dst, M;
        int w = image.cols;
        int h = image.rows;
        M = getRotationMatrix2D(Point(w / 2, h / 2), 45, 1.0);                                       //计算二维旋转的仿射矩阵
        double cos = abs(M.at<double>(0, 0));
        double sin = abs(M.at<double>(0, 1));
        int new_w = cos * w + sin * h;
        int new_h = sin * w + cos * h;
        M.at<double>(0, 2) += (new_w / 2 - w / 2);
        M.at<double>(1, 2) += (new_h / 2 - h / 2);
        warpAffine(image, dst, M, Size(new_w, new_h), INTER_LINEAR, 0, Scalar(150, 180, 150));     //对图像应用仿射变换
        imshow("旋转演示", dst);
}

//视频操作
void QuickDemo::video_demo()
{
        VideoCapture capture("C:/Users/13055/Desktop/秋.mp4");              //参数为0则播放摄像头数据
        Mat frame;

        int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);                //获取帧宽度属性
        int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);              //获取帧宽度属性
        int frame_count = capture.get(CAP_PROP_FRAME_COUNT);                //获取视频帧数
        double fps = capture.get(CAP_PROP_FPS);                             //获取视频帧率
        cout << "width:" << frame_width << endl;
        cout << "height:" << frame_height << endl;
        cout << "count:" << frame_count << endl;
        cout << "fps:" << fps << endl;

        VideoWriter writer("C:/Users/13055/Desktop/out.mp4", capture.get(CAP_PROP_FOURCC), fps, Size(frame_width, frame_height), true);

        while (1)
        {
                int c = waitKey(40);
                if (c == 27)
                        break;

                capture.read(frame);                                            //一帧一帧读取
                if (frame.empty())
                        break;
                flip(frame, frame, 1);
                imshow("frame", frame);
                writer.write(frame);                                            //图像写入文件
        }

        capture.release();
        writer.release();
}

//图像直方图
void QuickDemo::histogram_demo()
{
        //三通道分离
        vector<Mat> bgr_plane;
        split(image, bgr_plane);
        //定义参数变量
        const int channels[1] = { 0 };
        const int bins[1] = { 256 };
        float hranges[2] = { 0,255 };
        const float* ranges[1] = { hranges };
        Mat b_hist;
        Mat g_hist;
        Mat r_hist;
        //计算Blue,Rgeen,Red通道的直方图
        calcHist(&bgr_plane[0], 1, 0, Mat(), b_hist, 1, bins, ranges);
        calcHist(&bgr_plane[1], 1, 0, Mat(), g_hist, 1, bins, ranges);
        calcHist(&bgr_plane[2], 1, 0, Mat(), r_hist, 1, bins, ranges);
        //显示直方图
        int hist_w = 512;
        int hist_h = 400;
        int bin_w = cvRound((double)hist_w / bins[0]);
        Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);
        //归一化直方图数据
        normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
        normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
        normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
        //绘制直方图曲线
        for (int i = 1; i < bins[0]; i++)
        {
                line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
                        Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
                line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
                        Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
                line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(b_hist.at<float>(i - 1))),
                        Point(bin_w * (i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
        }
        //显示直方图
        namedWindow("Histogram Demo", WINDOW_AUTOSIZE);
        imshow("Histogram Demo", histImage);
}

//2D直方图
void QuickDemo::histogram_2d_demo()
{
        Mat hsv, hs_hist;
        cvtColor(image, hsv, COLOR_BGR2HSV);
        int hbins = 30, sbins = 32;
        int hist_bins[] = { hbins, sbins };
        float h_range[] = { 0, 180 };
        float s_range[] = { 0, 256 };
        const float* hs_ranges[] = { h_range, s_range };
        int hs_channels[] = { 0,1 };
        calcHist(&hsv, 1, hs_channels, Mat(), hs_hist, 2, hist_bins, hs_ranges, true, false);
        double maxVal = 0;
        minMaxLoc(hs_hist, 0, &maxVal, 0, 0);
        int scale = 10;
        Mat hist2d_image = Mat::zeros(sbins * scale, hbins * scale, CV_8UC3);
        for (int h = 0; h < hbins; h++)
        {
                for (int s = 0; s < sbins; s++)
                {
                        float binVal = hs_hist.at<float>(h, s);
                        int intensity = cvRound(binVal * 255 / maxVal);
                        rectangle(hist2d_image, Point(h * scale, s * scale),
                                Point((h + 1) * scale - 1, (s + 1) * scale - 1),
                                Scalar::all(intensity),
                                -1);
                }
        }
        applyColorMap(hist2d_image, hist2d_image, COLORMAP_JET);                            //伪彩色
        imshow("H-s Histogram", hist2d_image);
        //imwrite("C:/Users/13055/Desktop/Histogram2d.png", hist2d_image);                  //保存图片
}

//直方图均衡化（量化取值）
void QuickDemo::histogram_eq_demo()
{
        Mat gray;
        cvtColor(image, gray, COLOR_BGR2GRAY);
        imshow("灰度图像", gray);
        Mat dst;
        equalizeHist(gray, dst);                        //均衡化函数只支持单通道
        imshow("直方图均衡化", dst);
}

//卷积操作
void QuickDemo::blur_demo()
{
        Mat dst;
        blur(image, dst, Size(11, 11), Point(-1, -1));
        imshow("原图", image);
        imshow("图像模糊", dst);
}

//高斯模糊
void QuickDemo::gaussian_blur_demo()
{
        Mat dst;
        GaussianBlur(image, dst, Size(5, 5), 15);
        imshow("原图", image);
        imshow("高斯模糊", dst);
}

void QuickDemo::bifilter_demo()
{
        Mat dst;
        bilateralFilter(image, dst, 0, 100, 10);
        imshow("原图", image);
        imshow("高斯双边模糊", dst);
}






