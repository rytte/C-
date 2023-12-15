/******************************/OpenCV/******************************************************************************************/
OpenCL是用于编写在异构平台上运行程序的框架，所谓异构平台，一般情况我们指GPU和CPU两种处理器混合的平台。
OpenCL由一门用于编写kernels （在OpenCL设备上运行的函数）的语言（基于C99）和一组用于定义并控制平台的API组成。
OpenCL可以实现GPGPU（General - purpose computing on graphics processing units, 通用图形处理器）运算，
是一种利用处理图形任务的GPU来计算原本由CPU处理的通用计算任务。

//OpenCL由在OpenCL设备上运行的kernel函数语言和控制平台的API组成
OpenCL包含两个主要部分：device和host。在CPU和GPU组成的异构平台中，我们一般把运行核函数的GPU处理器部分称为device，把控制平台API的CPU称为host。
相应的，把host上的内存（就是内存）称为host memory；而把device上的内存（GPU显存）称为device memory或者device buffer。
在OpenCV里，我们把这两种内存封装为 cv::Mat 和 cv::ocl::oclMat 结构。

//数据调度和传输
OpenCV的OCL模块中，在GPU上进行运算之前我们必须把内存转成GPU可以直接调用的显存。
而在GPU上的运算结束后，我们还需要将在GPU显存上的数据转移到CPU可用的内存上。
这两个操作在oclMat中定义为两个成员函数，分别为 oclMat::download 和 oclMat::upload。
由于这两个数据传输操作受PCI总线宽带的限制，在实际应用中应尽量减少数据传输，把尽可能多的运算在gpu device上计算完成后，
再把数据传回cpu host，以达到最大的数据吞吐量。



/******************************/Mat的创建、复制、释放/******************************************************************************************/
枚举类型 type ： enum { CV_8U = 0, CV_8S = 1, CV_16U = 2, CV_16S = 3, CV_32S = 4, CV_32F = 5, CV_64F = 6 };
分别对应，8位无符号(uchar)、8位有符号(char)、16位无符号(ushort)、16位有符号(short)、32位有符号(int)、32位浮点(float)和64位双精度(double)；
其次 CV_8UC1、CV_16FC2、..CV_64FC4等是多通道的类型，可以用CV_(深度)(类型)(通道数)描述， 例如本例中CV_8UC3，是指8位无符号3通道，其他类推。

Scalar类型，它的源头实际是一个4行1列的Mat，这里的Scalar(0, 0, 255)，直接可以理解成M矩阵的每一个元素都是（0，0，255）,
当M看成图像，就是一个2x2的红色方块，
Scalar有3个值，可以对应RGB色彩, 通道顺序为（B, G, R）。
CV_8UC2, 可以用Scalar(1, 2)赋值，
CV_64UC4可以用Scalar(0, 0.1, 0.08, 100.1)赋值，其他类推。


Mat(int rows, int cols, int type, const Scalar& s)		//构造函数：其中rows和cols是需要创建的矩阵的行数和列数，type是Mat的数据类型，s是Scalar类型的矩阵初值。
Mat clone() const CV_NODISCARD;							//克隆
void copyTo(OutputArray m) const;							//拷贝
void copyTo(OutputArray m, InputArray mask) const;				//拷贝
void release();												//释放
static MatExpr ones(int rows, int cols, int type);					//返回指定大小和类型的所有 1 的数组
static MatExpr zeros(int rows, int cols, int type);					//返回指定大小和类型的所有 0 的数组
static MatExpr eye(int rows, int cols, int type);					//对角阵

Mat A = (Mat_<uchar>(5, 2) << 1, 2, 3, 4, 5, 6, 7, 8, 9, 10); //A为5x2的uchar类型矩阵，并被赋初值1-10
Mat C = B.row(3);   // 同样是引用，C指向B的4行
B.row(4).copyTo(C); // B、C都是引用A，这里相当于是把A的第4行“7，8”两个数换成了第5行“9，10”

"="赋值号得到的Mat是进行浅拷贝，不开辟新内存，数据指针指向原先的数据域。
Mat类的两个拷贝函数，copyTo() 和 clone() ，都是进行深复制，也就是会另外开辟一个内存存储被复制的数据区域，
对复制得到的新矩阵进行释放release()不会影响原矩阵的数据（有其他方式会影响，后面遇到再讲）。
这里的copyTo()和clone()区别在于，copyTo()可选一个参数掩膜mask，根据mask的值选择复制区域。

对于Mat的引用（也就是浅复制，只分配信息头，数据区共享）情况下的释放，只会清除本身的信息头和置零数据区指针，不会影响被赋值的矩阵。
Mat有一个引用机制，有一个成员变量refcount，会自己根据被引用和释放的次数，自动管理内存，所以一般不需要用户自己去释放。
对于创建类型的构造函数（深复制），那么会有属于自己的数据区，完全和被赋值的矩阵可以独立开。

用一个矩阵的一行复制到另外一行，不能通过直接复制，必须通过运算才行（运算的结果会返回一个实际的矩阵）。
如矩阵mat的第1行复制到第2行，代码为 mat.row(1) = mat.row(0) 无效，但是 mat.row(1) = mat.row(0) + 0; 或者 mat.row(1) = mat.row(0) + mat.row(2); 都是有效的。



/******************************/Mat图像显示/******************************************************************************************/
Mat imread(const String& filename, int flags = IMREAD_COLOR);				//从文件中加载一副图像
void namedWindow(const string& winname, int flags = WINDOW_AUTOSIZE)		//设置窗口属性
void destroyWindow(const string& winname)								//销毁指定窗口
void destroyAllWindows()												//销毁所有窗口
void moveWindow(const string& winname, int x, int y)							//移动窗口到指定坐标
void imshow(const string& winname, InputArray mat)							//将图像数据显示在指定窗口

Point_、Point3_、Size_、Rect_、Matx、Vec、Scalar_等，分别为二维点、三维点、尺寸、矩形、小矩阵、小向量、标量等模板类。


//Mat构造函数
Mat()
Mat(int rows, int cols, int type)
Mat(Size size, int type)
Mat(int rows, int cols, int type, const Scalar& s)
Mat(Size size, int type, const Scalar& s)
Mat(const Mat& m)
Mat(int rows, int cols, int type, void* data, size_t step = AUTO_STEP)
Mat(Size size, int type, void* data, size_t step = AUTO_STEP)
Mat(const Mat& m, const Range& rowRange, const Range& colRange = Range::all())
Mat(const Mat& m, const Rect& roi)
Mat(const CvMat* m, bool copyData = false)
Mat(const IplImage* img, bool copyData = false)
template<typename T, int n> explicit Mat::Mat(const Vec<T, n>& vec, bool copyData = true)
template<typename T, int m, int n> explicit Mat::Mat(const Matx<T, m, n>& vec, bool copyData = true)
template<typename T> explicit Mat::Mat(const vector<T>& vec, bool copyData = false)
Mat(int ndims, const int* sizes, int type)
Mat(int ndims, const int* sizes, int type, const Scalar& s)
Mat(int ndims, const int* sizes, int type, void* data, const size_t* steps = 0)
Mat(const Mat& m, const Range* ranges)

部分参数：
ndims 		矩阵维数
rows，cols 	矩阵的行数和列数
size 			二维矩阵的尺寸 size : Size(cols, rows)，通常描述矩阵尺寸为行、列，构造反过来。
sizes 		描述n维矩阵尺寸的整形数组指针，int a = [100, 100, 100], sizes = a;
type 		用CV_8UC1, ..., CV_64FC4 创建1~4维的矩阵，或者CV_8UC(n), ..., CV_64FC(n)的n维矩阵。
s 			可选参数，用Scalar给矩阵每个元素赋初值。也可以在构造后 用“ = ”赋初值。
data 		用户数据指针，可以用自定义的数组给矩阵赋值。
step 			矩阵一行占用的字节数，由step = cols * elemSize()得到，elemSize()是一个元素占用字节数。
m 			被引用的矩阵，以获取m的子矩阵。如 Mat a = Mat(m, Range(1, 10), Range(5, 8));
vec 			元素为列向量的容器，以将vec转化为矩阵，vec行数为矩阵的行数，vec列数为矩阵的维数。
copyData 	bool变量，true时深复制，false时引用即浅复制

成员函数：
Mat & Mat::operator =
Mat Mat::row(int y) const								返回基于0的某一行为新的矩阵, 深复制
Mat::col(int x) const										返回基于0的某一列为新的矩阵, 深复制
Mat Mat::rowRange(int startrow, int endrow) const			子矩阵，连续某些行连续某些列构成的矩阵， 深复制。（类似还有colRange()方法）
Mat Mat::rowRange(const Range& r) const
Mat Mat::diag(int d = 0) const							取矩阵对角线元素为列向量
Mat::clone											克隆。深复制
Mat::copyTo											拷贝，第二个参数可选mask。深复制
void Mat::convertTo(OutputArray m, int rtype, double alpha = 1, double beta = 0) const			两种方式, (1) 改变数据类型(2)数据类型和数值两个变换
void Mat::resize(size_t sz)，								改变矩阵行数，当新的行数小于原矩阵行数，那么会释放新的行数后面的元素；大于时，可以指定后面新增的行数的元素初值为s
void Mat::resize(size_t sz, const Scalar& s)
Mat& Mat::setTo(InputArray value, InputArray mask = noArray())矩阵（可选mask区域）赋值
Mat Mat::reshape(int cn, int rows = 0) const					改变二维矩阵的size或 / 和通道数，浅复制（但是返回值不是引用）。变换后，必须保证 rows*cols*channels()保持相等。
Mat::t, Mat::inv, Mat::mul, Mat::cross, Mat::dot
//分别为：转置，矩阵的逆（LU、CHOLESKY、SVD三种解法），数乘（2个矩阵对应位置元素相乘或一个矩阵和一个标量相乘），叉乘（含有三个元素的2个向量运算），点乘（内积，2个向量（一维矩阵）运算）。
Mat::zeros，Mat::ones，Mat::eye       0						矩阵，1矩阵， 单位（主对角线为1）矩阵
Mat::create
Mat::addref, Mat::release
//前者用于给矩阵的内部成员变量refcount计数，后者用于释放矩阵。
//在Mat里面通常不用关心矩阵的内存分配和释放，矩阵会在有需要的时候自行分配，同样由于矩阵的引用计数机制使得在refcount为0时会自动释放矩阵内存。
void Mat::locateROI(Size& wholeSize, Point& ofs) const		确定子矩阵在被引用矩阵的顶点位置和被引用矩阵的size。
size_t Mat::total() const									矩阵元素个数 total = cols * rows
bool Mat::isContinuous() const							确定矩阵元素在内存中是否为连续存储。
size_t Mat::elemSize() const, size_t Mat::elemSize1()			elemSize() 矩阵一个元素占用字节数，elemSize1() 矩阵元素的一个通道占用的字节数。
int Mat::channels() const									矩阵通道数。如类型CV16SC2，通道数2（即类型中字母C后的数值）。
int Mat::depth() const									矩阵数据的类型，宏定义，其取值范围为0~7
int Mat::type() const									矩阵的类型，描述矩阵的数据类型和通道数目。
size_t Mat::step1(int i = 0) const，Size Mat::size() const
对于二维矩阵，size()返回Size(cols, rows)，step1(0)为一行元素的字节数，step1(1)为一个元素的字节数elemSize()。
对于多维，还有一个step的成员变量，是一个MStep结构体，step[i]是第i维占用的字节数。对于二维矩阵，step[0]是一行占用的字节数，step[1]是一个元素占用的字节数。
Mat::ptr, Mat::data, Mat::empty							两个数据区指针，data和ptr<_Tp>(0)都指向数据区的首地址，默认都是uchar *类型。
Mat::push_back， Mat::pop_back							这两个方法使得Mat有了STL容器的功能，可以在矩阵最后一行压入或者弹出一行元素。
Mat::at												返回指定元素的一个引用





void cvtColor(InputArray src, OutputArray dst, int code, int dstCn = 0);										颜色空间转换
bool imwrite(const String& filename, InputArray img, const std::vector<int>& params = std::vector<int>());			保存图像为文件
Mat Scalar(int, int, ...);																				矩阵赋值，参数对应每个通道
int createTrackbar(const String& trackbarname, const String& winname,										创建滚动条
		int* value, int count,
		TrackbarCallback onChange = 0,
		void* userdata = 0);
void applyColorMap(InputArray src, OutputArray dst, InputArray userColor);											伪彩色
void rectangle(CV_IN_OUT Mat& img, Rect rec, const Scalar& color,  int thickness = 1, int lineType = LINE_8, int shift = 0);		绘制矩形
void split(const Mat& src, Mat* mvbegin);																		颜色通道分离
void merge(InputArrayOfArrays mv, OutputArray dst);																颜色通道合并
void mixChannels(const Mat* src, size_t nsrcs, Mat* dst, size_t ndsts, const int* fromTo, size_t npairs);						通道混合
void inRange(InputArray src, InputArray lowerb, InputArray upperb, OutputArray dst);									选取颜色范围
void minMaxLoc(InputArray src, CV_OUT double* minVal,															获取区域最大值最小值
		double* maxVal = 0, CV_OUT Point* minLoc = 0,
		Point* maxLoc = 0, InputArray mask = noArray());
void meanStdDev(InputArray src, OutputArray mean, OutputArray stddev, InputArray mask = noArray());					计算均值与方差




HSV色彩空间
H（0 - 180）	色调
S（0 - 255）	饱和度
V（0 - 255）	明度