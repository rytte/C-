#include <iostream>
#include "controller.h"


int main(int argc, char* argv[])
{

	Model m;                        //创建模型
	View v;                           //创建视图

	Controller c(m, v);              //创建控制器，使其指针指向已有模型和视图对象，从而操作这俩对象。
						  //调用指向模型的方法传入this使模型的指针指向控制器对象，视图仅作输出。

	m.set_data("Hello world");
	return 0;

}


//View（视图层）完成前端的数据展示；
// Controller（控制层）是对数据的接收和触发事件的接收和传递；Controller越薄越好，多余业务代码应交由Model来实现。
// Model（模型层）则是对数据的储存和处理，再传递给视图层相应或者展示。
