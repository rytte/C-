from matplotlib import hatch


('''********************'''YOLO'''************************************************************'''
 https://blog.csdn.net/qq_67105081/article/details/137519207

YOLO：主要用于对象检测、分割、姿态估计、跟踪和分类。基于深度学习和计算机视觉领域的尖端技术，在速度和准确性方面具有无与伦比的性能。
https://docs.ultralytics.com/zh


('''********************'''环境安装'''************************************************************'''
1、安装conda
2、安装Pycharm
3、安装cuda
4、安装cudnn
5、执行"conda create -n yolo python=3.10.11"
6、执行"conda activate yolo"
7、执行"pip install torch==2.0.0+cu118 torchvision==0.15.1+cu118 --extra-index-url https://download.pytorch.org/whl/cu118"
8、执行"pip install ultralytics"
9、下载.pt模型文件(yolov8n.pt): https://docs.ultralytics.com/zh/models/yolov8/#supported-tasks-and-modes
10、准备一张猫猫图片"cat.jpg"，将.pt文件和"cat.jpg"放在同一目录下，进入目录
11、cli运行：执行"yolo predict model=yolov8n.pt source='cat.jpg'"
12、code运行: 新建一个yolov8_predict.py，执行"python yolov8_predict.py"。
from ultralytics import YOLO
model = YOLO('yolov8n.pt')          # 加载预训练的 YOLOv8n 模型
source = 'cat.jpg'                  # 定义图像文件的路径
model.predict(source, save=True)    # 运行推理，并附加参数

#PyCharm使用
1、下载yolo环境源码: https://github.com/ultralytics/ultralytics/
2、解压后右键使用Pycharm打开
3、配置虚拟环境：设置 >> 项目:ultralytics >> python解释器 >> 添加解释器 >> 添加本地解释器...
>> 环境:选择现有 >> 类型:python >> "C:\Users\13055\miniconda3\envs\yolov8\python.exe" >> 应用 >> 确定



('''********************'''CLI语法功能'''************************************************************'''
 yolo TASK MODE ARGS
TASK (可选) ：detect, segment, classify, pose, obb
MODE (必填) ：train, val, predict, export, track, benchmark
ARGS (可选) 为 arg=value 如 imgsz=640 覆盖默认值。



图片检测：yolo predict model=yolov11n.pt source='cat.jpg'
视频检测：yolo track model=yolov11n.pt source='../media/animation.mp4'


('''********************'''训练'''************************************************************'''
1、获取数据集
https://www.kaggle.com/ 搜索 >> 筛选Datasets >> 含"annotations"和"JPEGImages"文件夹的为可用数据 >> DownLoad
2、数据集转换
附注文件若为VOC(.xml)格式，需要转换成YOLO(.txt)格式，代码见 voc_to_yolo.py
3、数据集划分
数据集需要划分为训练集、验证集和测试集，这里提供一个参考代码，划分比例为8：1：1，代码见 separate.py
4、配置数据集训练的 YAML 文件
源码目录下，新建文件 data.yaml，代码见 data.yaml，注意替换路径和类别
5、准备模型
将yolo11n.pt，放在源码目录下（模型大小 n < s < m < l < x ，训练时长成倍增加）
6、创建训练代码
源码目录下，新建 yolo11_train.py，代码见 yolo11_train.py 
参数说明：
epochs：训练轮数
workers：使用线程数，最好为2的n次方。
batch：批处理数量，即同时处理的数量，数值越大占用显存越大，最好为2的n次方。
device：0为GPU，若无GPU则"device='cpu'"
imgsz：图片大小，640即640*640，数值越大显存占用越大。
amp：自动混合精度，开启后将由32位浮点(FP32)降低为16位浮点(FP16)，可以加快训练和减少显存占用。
optimizer：优化器，即参数优化算法，'SGD'为随机梯度下降

也可以使用命令行执行训练
"yolo task=detect mode=train model=yolo11n.yaml pretrained=yolo11n.pt data=data.yaml epochs=300 imgsz=640 device=0 workers=8 batch=64 amp=False optimizer='SGD'"
7、训练结果
训练结果在【runs\detect\train】目录下，"weights"目录中 best.pt 为训练的最好的一组权重模型，可以使用。
详细图表分析见笔记:yolo训练结果.py


【voc_to_yolo.py】
import os
import xml.etree.ElementTree as ET

# 定义类别顺序
categories = ['helmet', 'head']  # 填写对象名
category_to_index = {category: index for index, category in enumerate(categories)}

# 定义输入文件夹和输出文件夹
input_folder = r'C:\Users\13055\Desktop\archive\annotations'  # 替换为实际的XML文件夹路径
output_folder = r'C:\Users\13055\Desktop\archive\labels'  # 替换为实际的输出TXT文件夹路径

# 确保输出文件夹存在
os.makedirs(output_folder, exist_ok=True)

# 遍历输入文件夹中的所有XML文件
for filename in os.listdir(input_folder):
    if filename.endswith('.xml'):
        xml_path = os.path.join(input_folder, filename)
        # 解析XML文件
        tree = ET.parse(xml_path)
        root = tree.getroot()
        # 提取图像的尺寸
        size = root.find('size')
        width = int(size.find('width').text)
        height = int(size.find('height').text)
        # 存储name和对应的归一化坐标
        objects = []

        # 遍历XML中的object标签
        for obj in root.findall('object'):
            name = obj.find('name').text
            if name in category_to_index:
                category_index = category_to_index[name]
            else:
                continue  # 如果name不在指定类别中，跳过该object

            bndbox = obj.find('bndbox')
            xmin = int(bndbox.find('xmin').text)
            ymin = int(bndbox.find('ymin').text)
            xmax = int(bndbox.find('xmax').text)
            ymax = int(bndbox.find('ymax').text)

            # 转换为中心点坐标和宽高
            x_center = (xmin + xmax) / 2.0
            y_center = (ymin + ymax) / 2.0
            w = xmax - xmin
            h = ymax - ymin

            # 归一化
            x = x_center / width
            y = y_center / height
            w = w / width
            h = h / height

            objects.append(f"{category_index} {x} {y} {w} {h}")

        # 输出结果到对应的TXT文件
        txt_filename = os.path.splitext(filename)[0] + '.txt'
        txt_path = os.path.join(output_folder, txt_filename)
        with open(txt_path, 'w') as f:
            for obj in objects:
                f.write(obj + '\n')


【separate.py】
import os
import shutil
import random
 
# random.seed(0)  #随机种子，可自选开启
def split_data(file_path, label_path, new_file_path, train_rate, val_rate, test_rate):
	images = os.listdir(file_path)
	labels = os.listdir(label_path)
	images_no_ext = {os.path.splitext(image)[0]: image for image in images}
	labels_no_ext = {os.path.splitext(label)[0]: label for label in labels}
	matched_data = [(img, images_no_ext[img], labels_no_ext[img]) for img in images_no_ext if img in labels_no_ext]
 
	unmatched_images = [img for img in images_no_ext if img not in labels_no_ext]
	unmatched_labels = [label for label in labels_no_ext if label not in images_no_ext]
	if unmatched_images:
		print("未匹配的图片文件:")
		for img in unmatched_images:
			print(images_no_ext[img])
	if unmatched_labels:
		print("未匹配的标签文件:")
		for label in unmatched_labels:
			print(labels_no_ext[label])
 
	random.shuffle(matched_data)
	total = len(matched_data)
	train_data = matched_data[:int(train_rate * total)]
	val_data = matched_data[int(train_rate * total):int((train_rate + val_rate) * total)]
	test_data = matched_data[int((train_rate + val_rate) * total):]
 
	# 处理训练集
	for img_name, img_file, label_file in train_data:
		old_img_path = os.path.join(file_path, img_file)
		old_label_path = os.path.join(label_path, label_file)
		new_img_dir = os.path.join(new_file_path, 'train', 'images')
		new_label_dir = os.path.join(new_file_path, 'train', 'labels')
		os.makedirs(new_img_dir, exist_ok=True)
		os.makedirs(new_label_dir, exist_ok=True)
		shutil.copy(old_img_path, os.path.join(new_img_dir, img_file))
		shutil.copy(old_label_path, os.path.join(new_label_dir, label_file))
	# 处理验证集
	for img_name, img_file, label_file in val_data:
		old_img_path = os.path.join(file_path, img_file)
		old_label_path = os.path.join(label_path, label_file)
		new_img_dir = os.path.join(new_file_path, 'val', 'images')
		new_label_dir = os.path.join(new_file_path, 'val', 'labels')
		os.makedirs(new_img_dir, exist_ok=True)
		os.makedirs(new_label_dir, exist_ok=True)
		shutil.copy(old_img_path, os.path.join(new_img_dir, img_file))
		shutil.copy(old_label_path, os.path.join(new_label_dir, label_file))
	# 处理测试集
	for img_name, img_file, label_file in test_data:
		old_img_path = os.path.join(file_path, img_file)
		old_label_path = os.path.join(label_path, label_file)
		new_img_dir = os.path.join(new_file_path, 'test', 'images')
		new_label_dir = os.path.join(new_file_path, 'test', 'labels')
		os.makedirs(new_img_dir, exist_ok=True)
		os.makedirs(new_label_dir, exist_ok=True)
		shutil.copy(old_img_path, os.path.join(new_img_dir, img_file))
		shutil.copy(old_label_path, os.path.join(new_label_dir, label_file))
	print("数据集已划分完成")
 
if __name__ == '__main__':
	file_path = r"C:\Users\13055\Desktop\archive\images"  # 图片文件夹
	label_path = r'C:\Users\13055\Desktop\archive\labels'  # 标签文件夹
	new_file_path = r"C:\Users\13055\Desktop\archive\VOCdevkit"  # 新数据存放位置
	split_data(file_path, label_path, new_file_path, train_rate=0.8, val_rate=0.1, test_rate=0.1)


【data.yaml】
path: C:/Users/13055/Desktop/archive/VOCdevkit  #数据集根路径，指定后下面配置可使用相对路径
train: train/images  # train images (relative to 'path') 128 images
val: val/images  # val images (relative to 'path') 128 images
test: images

#类别数量
nc: 2
 
# Classes
names: ['helmet','head']


【yolo11_train.py】
from ultralytics import YOLO
#多线程添加代码
if __name__ == '__main__': 
    model = YOLO('ultralytics/cfg/models/11/yolo11.yaml')  # 从YAML建立一个新模型
    model.load('yolo11n.pt')
 
    # # 训练模型
    results = model.train(data='data.yaml',
                      epochs=50, imgsz=320, device=0, workers=8, batch=128, optimizer='SGD', amp=True)



('''********************'''自制数据集'''************************************************************'''
自制数据集需要先获取一定数量的目标图片，图片足够之后使用标注工具Labelimg进行标注

1、python3.10以上版本使用labelimg会异常闪退，因此使用 conda 创建 python=3.8 版本环境继续。
1、安装"pip install labelimg"
2、创建文件夹datasets，里面存放以下目录或文件
annotations     #xml文件夹
images          #图片文件夹
labels          #txt文件夹
classes.txt     #类别文件，里面存放所有的类别，每个类别占一行，可以自己起名，需要是英文，如果有空格最好用下划线比如no_hat

【classes.txt】
hat
nohat

3、打开labelimg: "labelimg images classes.txt"
4、点击"change save dir"选择annotations文件夹，点击"save"下面的图标切换到"pascal voc"或"yolo"格式
5、点击工具栏的 view，将 Auto Save mode（切换到下一张图会自动保存标签）和 Display Labels（显示标注框和标签）保持打开状态。
6、按下w调出标注十字架，标注完成之后选择对应的类别，这张图全部标注完后按d下一张，所有图像标注完成后数据集即制作完成。
常用快捷键：
A：切换到上一张图片
D：切换到下一张图片
W：调出标注十字架
del ：删除标注框



('''********************'''摄像头实时检测'''************************************************************'''
from ultralytics import YOLO
import cv2
from cv2 import getTickCount, getTickFrequency
yolo=YOLO('./yolo11n.pt')
 
 
#摄像头实时检测
 
cap = cv2.VideoCapture(0)
while cap.isOpened():
    loop_start = getTickCount()  #记录循环开始的时间，用于计算每一帧的处理时间
    success, frame = cap.read()  # 读取摄像头的一帧图像
 
    if success:
        results = yolo.predict(source=frame)  # 对当前帧进行目标检测并显示结果
    annotated_frame = results[0].plot()   #将检测结果绘制在图像上，得到带有目标框的图像。
 
    # 显示程序
    loop_time = getTickCount() - loop_start #计算处理一帧图像所花费的时间。
    total_time = loop_time / (getTickFrequency())  #将处理时间转换为秒数。
    FPS = int(1 / total_time) #FPS计算
    # 在图像左上角添加FPS文本
    fps_text = f"FPS: {FPS:.2f}"#构造显示帧率的文本字符串
    font = cv2.FONT_HERSHEY_SIMPLEX#选择字体类型
    font_scale = 1  #设置字体的缩放比例
    font_thickness = 2 #设置字体的粗细
    text_color = (0, 0, 255)  # 红色
    text_position = (10, 30)  # 左上角位置
 
    cv2.putText(annotated_frame, fps_text, text_position, font, font_scale, text_color, font_thickness)
    cv2.imshow('Real-time detection', annotated_frame)
    # 通过按下 'q' 键退出循环
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
 
cap.release()  # 释放摄像头资源
cv2.destroyAllWindows()  # 关闭OpenCV窗口

