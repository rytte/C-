/********************/UI范式基础语法/************************************************************/

//ArkTS的基本组成
装饰器、UI描述、自定义组件、系统组件、属性方法、事件方法


//装饰器
用于装饰类、结构、方法以及变量，并赋予其特殊的含义

@Builder			自定义构建函数
@LocalBuilder		维持组件父子关系
@BuilderParam		引用@Builder函数
wrapBuilder			封装全局@Builder
@Styles				定义组件重用样式
@Extend				定义扩展组件样式
stateStyles			多态样式
@AnimatableExtend	定义可动画属性
@Require			校验构造传参
@Reusable			组件复用


//创建组件（声明式UI描述）
{}中可添加子组件。Column、Row、Stack、Grid、List等组件都是容器组件，支持多级嵌套。

Column() {								//无参创建
	Button('click me')					//有参创建
		.fontSize(12)					//属性
		.fontColor(Color.Red)			//该参数为预定义的枚举类型
		.width(this.offset + 100)		//参数可以为表达式
		.onClick(() = > {				//事件配置
			this.myText = 'ArkUI';
		})
	Text('Hello')
}

//事件绑定
使用组件的成员函数配置组件的事件方法

1、箭头函数
fn = () = > {
	console.info(`counter: ${ this.counter }`)
		this.counter++
}
Button('add counter')
	.onClick(this.fn)

2、bind this（不推荐）
myClickHandler() : void {
	this.counter += 2;
}
Button('add counter')
	.onClick(this.myClickHandler.bind(this))



/********************/自定义组件/************************************************************/
@Entry		表示该自定义组件为入口组件。单个UI页面中，最多可以使用@Entry装饰一个自定义组件。
@Component	表示自定义组件，仅能装饰 struct 关键字声明的数据结构。具有组件化的能力，需要实现build方法描述UI
@State		表示组件中的状态变量，状态变量变化会触发UI刷新
@Reusable	装饰的自定义组件具备可复用能力
build()		用于定义自定义组件的声明式UI描述，自定义组件必须定义build()函数。
struct		自定义组件关键字。不能有继承关系。实例化可以省略 new 。

@Component
struct HelloComponent {
	@State message : string = 'Hello, World!';
	private color: Color = Color.Blue;

	build() {
		// HelloComponent自定义组件组合系统组件Row和Text
		Row() {
			Text(this.message)
				.onClick(() = > {
				// 状态变量message的改变驱动UI刷新，UI从'Hello, World!'刷新为'Hello, ArkUI!'
				this.message = 'Hello, ArkUI!';
			})
		}
	}
}

可使用export关键字导出，以在其它文件中import该组件并使用。

@Component	可接受一个bool参数(freezeWhenInactive)，表示是否开启组件冻结。	//v11+
@Component({ freezeWhenInactive: true })
struct MyComponent {
}

@Entry可选参数
名称					类型				说明
routeName			string			表示作为命名路由页面的名字。
storage				LocalStorage	页面级的UI状态存储。
useSharedStorage	boolean			是否使用LocalStorage.getShared()接口返回的LocalStorage实例对象，默认值false。


//成员函数/变量
约束：
1、自定义组件的成员函数/变量为私有的，且不建议声明成静态函数/变量。
2、自定义组件的成员变量本地初始化有些是可选的，有些是必选的。


//父子组件函数传递
下面的示例代码将父组件中的函数传递给子组件。

@Entry
@Component
struct Parent {
	@State cnt : number = 0
		submit : () = > void = () = > {
		this.cnt++;
	}

	build() {
		Son({ submitArrow: this.submit })
			.width(100)			//可以通过“.”链式调用的形式设置通用样式
	}
}
}

@Component
struct Son {
	submitArrow ? : () = > void		//?: 表示该属性为可选，因此使用前应if (this.submitArrow)判断是否存在
	//...
}


//build() 函数
所有声明在build()函数的语句，我们统称为UI描述
规则：
1、@Entry装饰的自定义组件，其build()函数下的根节点唯一且必要，且必须为容器组件，其中ForEach禁止作为根节点。
2、@Component装饰的自定义组件，其build()函数下的根节点唯一且必要，可以为非容器组件，其中ForEach禁止作为根节点。
@Entry
@Component
struct MyComponent {
	build() {
		// 根节点唯一且必要，必须为容器组件
		Row() {
			ChildComponent()
		}
	}
}
@Component
struct ChildComponent {
	build() {
		// 根节点唯一且必要，可为非容器组件
		Image('test.jpg')
	}
}

3、不允许声明本地变量。
4、不允许在UI描述里直接使用console.info，但允许在方法或者函数里使用。
5、不允许创建本地的作用域
build() {
	// 反例：不允许声明本地变量
	let num : number = 1;

	// 反例：不允许console.info
	console.info('print debug log');

	// 反例：不允许本地作用域
	{
		// ...
	}
}

6、不允许调用没有用@Builder装饰的方法，允许系统组件的参数是TS方法的返回值。
@Component
struct ParentComponent {
	calcTextValue() : string{
		return 'Hello World';
	}

	@Builder doSomeRender() {
		Text(`Hello World`)
	}

	build() {
		Column() {
			// 反例：不能调用没有用@Builder装饰的方法
			this.calcTextValue();
			// 正例：参数可以为调用TS方法的返回值
			Text(this.calcTextValue())
			// 正例：可以调用
			this.doSomeRender();
		}
	}
}

7、不允许使用switch语法，如果需要使用条件判断，请使用if。
8、不允许使用表达式，请使用if组件。
build() {
	Column() {
		// 反例：不允许使用表达式
		(this.aVar > 10) ? Text('...') : Image('...')

		// 正例：使用if判断
		if (this.aVar > 10) {
			Text('...')
		}
		else {
			Image('...')
		}
	}
}
9、不允许直接改变状态变量（以及@Builder方法内也不行），而应该在专门的方法内修改。
这可能会造成循环渲染的风险，如 Text('${this.count++}') 在全量更新或最小化更新会产生不同的影响

全量更新（API8及以前版本）：@State状态变量改变时会触发渲染，执行整个build构建函数，而渲染时又会改变状态变量的值。因此产生无限循环。
最小化更新（API9 - 至今版本）：目前UI以组件为单位进行更新，如果组件上某一个属性发生改变，会更新整体的组件。



//生命周期
页面生命周期，即被@Entry装饰的组件生命周期，提供以下生命周期接口：
1、onPageShow：页面每次显示时触发一次，包括路由过程、应用进入前台等场景。
2、onPageHide：页面每次隐藏时触发一次，包括路由过程、应用进入后台等场景。
3、onBackPress：当用户点击返回按钮时触发。

组件生命周期，即一般用@Component装饰的自定义组件的生命周期，提供以下生命周期接口：
1、aboutToAppear：组件的构造函数，在其build()函数之前执行。
2、onDidBuild：build()函数执行完成之后回调该接口。
3、aboutToDisappear：组件的析构函数，在自定义组件析构销毁之前执行。该函数中不允许改变状态变量，特别是@Link变量的修改可能会导致应用程序行为不稳定。


//自定义组件的创建和渲染流程
初始化成员变量 >> aboutToAppear方法 >> 执行build方法渲染系统组件, 首次渲染时，框架会记录状态变量和组件的映射关系 >> onDidBuild方法

//自定义组件的删除
1、在删除组件之前，将调用其aboutToDisappear生命周期函数，标记着该节点将要被销毁。
ArkUI的节点删除机制是：后端节点直接从组件树上摘下，后端节点被销毁，对前端节点解引用，前端节点已经没有引用时，将被JS虚拟机垃圾回收。
2、自定义组件和它的变量将被删除，如果其有同步的变量，比如@Link、@Prop、@StorageLink，将从同步源上取消注册。

//自定义组件布局接口
onMeasureSize：组件每次布局时触发，计算子组件的尺寸，其执行时间先于onPlaceChildren。
onPlaceChildren：组件每次布局时触发，设置子组件的起始位置。

//成员属性访问限定符
1、@State / @Prop / @Provide / @BuilderParam / 常规成员变量(不涉及更新的普通变量)的初始化规则为可以被外部初始化，也可以使用本地值进行初始化。当组件开发者不希望当前变量被外部初始化时，可以使用private进行修饰，此时会有编译告警日志提示。
2、@StorageLink / @StorageProp / @LocalStorageLink / @LocalStorageProp / @Consume变量的初始化规则为不可以被外部初始化，当组件开发者希望当前变量被外部初始化而使用public修饰时，这和装饰器本身的初始化规则是相违背的，会有编译告警日志提示。
3、@Link / @ObjectLink变量的初始化规则为必须被外部初始化，禁止本地初始化。当组件开发者使用private对变量进行修饰时，这和装饰器本身的初始化规则相矛盾，会有编译告警日志提示。
4、由于struct没有继承能力，上述所有的这些变量使用protected修饰时，会有编译告警日志提示。
5、@Require含义是当前被@Require装饰的变量必须被外部初始化，当@Require和private同时装饰@State / @Prop / @Provide / @BuilderParam / 常规成员变量(不涉及更新的普通变量)时，他们的含义是自相矛盾的，会有编译告警日志提示。






