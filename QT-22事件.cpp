/********************/事件/************************************************************/
在Qt框架中，事件（Event）是对应用程序内部或外部产生的事情或动作的通称。
Qt使用对象来表示事件，这些事件都继承自QEvent类。
Qt的事件处理机制允许开发者响应这些事件，从而改变应用程序的行为或状态。

QT中，一个事件就是一个类对象。
只要有一个事件发生（如鼠标单击事件），此时就会有一个 QEvent 对象被创建出来，然后开始各种传送。
由于 Qt 事件系统是依托于元对象系统的，所以所有的 QObject 类都可以接收 / 处理 QEvent 事件。


//事件队列
我们创建一个 Qt 程序的时候，一般在 main 下面会看到 QCoreApplication a(argc, argv) 以及 return a.exec() 的字样。
这其实就是开启了 Qt 事件循环来维护一个事件队列，exec 的本质就是不停的调用 processEvent() 函数从队列中获取事件来处理。


//事件优先级
每个事件都有一个优先级，用于确定事件在事件队列中的处理顺序。
Qt使用整数值表示事件的优先级，数值越小表示优先级越高。
默认情况下，事件的优先级是0，可以通过设置QEvent::setPriority()方法来改变事件的优先级。


//常见的事件类型
鼠标事件(QMouseEvent) : 处理鼠标的移动、点击、释放等动作。
键盘事件(QKeyEvent) : 处理键盘按键的按下和释放。
定时事件(QTimerEvent) : 在定时器到期时触发，用于执行周期性任务。
绘图事件(QPaintEvent) : 当控件需要重新绘制时触发，用于自定义绘制。
焦点事件(QFocusEvent) : 处理键盘焦点的移动，如窗口控件获得或失去焦点。
进入和离开事件(QEnterEvent 和 QLeaveEvent) : 处理鼠标移入或移出窗口控件的事件。
移动事件(QMoveEvent) : 处理窗口控件的位置改变事件。
大小改变事件(QResizeEvent) : 处理窗口控件的大小改变事件。
显示和隐藏事件(QShowEvent 和 QHideEvent) : 处理窗口控件的显示和隐藏事件。
窗口事件(QWindowStateChangeEvent) : 处理窗口是否为当前窗口的状态变化事件。


//事件处理：通常通过两种方式实现
重载相关的事件处理函数：例如，通过重载paintEvent(), mousePressEvent()等函数，可以处理特定部件的特定事件。
使用事件过滤器：可以在对象上安装事件过滤器，这样可以在一个界面类中同时处理不同子部件的不同事件。

//事件循环
Qt的事件处理还涉及到事件循环（Event Loop）。
事件循环是Qt应用程序的核心部分，它负责接收和处理来自系统或其他线程的事件。
事件循环不断运行，直到应用程序退出。


//QEvent函数
accept标志：设置 accept标志(为 true)，表示接受参数指示事件接收器需要事件。若设为 false 则意味着事件接收器不需要该事件，不需要事件可能被传播给父级 Widget。

bool isAccepted() const                              //默认为 true。不能依赖于此，因为子类可能会在子类构造器中清除该标志。
void setAccepted(bool accepted)               //设置 accept 标志为 true 或 false。

void accept()                                           //设置事件对象的接受标志，等价于 setAccepted(true)。
void ignore()                                           //清除事件对象的 accept 标志，等价于 setAccepted(false)。
 
bool spontaneous() const                //若事件发源于应用程序外(如系统事件)则返回 true ，否则返回 false 。绘制事件的返回值是未定义的。
Type QEvent::type() const               //返回事件的类型

static int registerEventType(int hint = -1)     //注册并返回一个自定义事件类型。
如果 hint 是合法的，则会返回这个值；否则返回介于 QEvent::User 和 QEvent::MaxUser 之间的一个尚未被注册的值。
如果其值不在 QEvent::User 和 QEvent::MaxUser 之间，hint 值将被忽略。
如果可用的值被使用或程序关闭，将返回 - 1。该函数是线程安全的。


//type值
每一个事件类都有个唯一身份值：type值
这个 type 值的作用就是我们在处理事件时用于识别事件类的代号。请看下面实际中的例子：
bool FilterObject::eventFilter(QObject* object, QEvent* event)
{
        if (object == target && event->type() == QEvent::KeyPress)
        {
                QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
                if (keyEvent->key() == Qt::Key_Tab)
                        return true;
                else
                        return false;
        }
        return false;
}


//自定义事件类
class MyEvent : public QEvent
{
public:
        MyEvent();
        MyEvent(int x, int y, int z);

        static const Type type;         //自己定义的事件类也有个 type 值

        int x;
        int y;
        int z;
};
假如我程序中触发了某某槽函数，产生了一个三维坐标事件，要把坐标发送出去，那我上面写的这个事件类就派上用场了。
我创建一个事件对象，并把坐标参数传到这个事件对象里（MyEvent event(1, 2, 3)），
这样这个 event 对象就产生了，它承载着一个三维坐标。

QT中 enum QEvent::Type 取值范围为[0, 999]
因此自定义 type 的数值要大于 999。Qt 给我们规定了两个边界值：QEvent::User 和 QEvent::MaxUser，即 1000 - 65535。
可以使用 registerEventType() 函数获取一个合法的 type 值。


//发送一个事件
Qt 提供了三个 static 事件发送函数：sendEvent、postEvent、sendPostEvents。函数原型如下：

bool QCoreApplication::sendEvent(QObject* receiver, QEvent* event)
void QCoreApplication::postEvent(QObject* receiver, QEvent* event, int priority = Qt::NormalEventPriority)
void QCoreApplication::sendPostedEvents(QObject* receiver = Q_NULLPTR, int event_type = 0)

//直接发送：sendEvent
对于许多事件类，有一个名为 isAccepted() 来告诉你是否被处理。
因为事件被发送的时候，event 对象并不会被销毁，因此我们要在栈上创建 event 对象。
int main(int argc, char* argv[])
{
        QCoreApplication a(argc, argv);

        MainWindow w;
        w.show();

        MyEvent event(1, 2, 3);
        QCoreApplication::sendEvent(&w, &event);

        return a.exec();
};

//发到队列：postEvent
postEvent() 的作用：把事件发送到事件队列中去。这种方式不需要等待处理结果，所以返回值是 void 。
* 由于事件队列会持有发送的事件对象，在 post 的时候会将事件 delete 掉，所以我们必须在堆上创建 event 对象。

//在队列中立即处理：sendPostedEvents
看参数我们就可以知道，这个函数的作用就是立刻、马上将队列中的 event_type 类型的事件立马交给 receiver 进行处理。
需要注意的是，来自窗口系统的事件并不由这个函数进行处理，而是 processEvent()。


//发送的事件在哪里捕获？
我们发送的事件传给了 QObject 对象，更具体点是传给了 QObject 对象的 event() 函数。
所有的事件都会进到这个函数里面，因此我们处理事件就要重写这个 event() 函数。

//在 event() 中怎么处理事件？
event() 函数本身不会去处理事件，而是根据事件类型（type值）调用不同的事件处理器函数。
举个简单的例子：鼠标点击一下->产生鼠标点击事件->接收者的 event() 函数判断类型->发给 mousePressEvent() 函数处理。
代码如下：
void MyCheckBox::mousePressEvent(QMouseEvent* event)
{
        if (event->button() == Qt::LeftButton)
        {
                ....//点击左键后实现的功能
        }
        else
        {
                QCheckBox::mousePressEvent(event);                 //完成正常QCheckBox的功能
        }
}
需要注意的是，重写事件处理器函数时，如果不实现任何功能，最好调用基类的实现。
就像上面的那段代码，Qt 本身就已经写了一大堆的实现了，你要是不写上 QCheckBox::mousePressEvent(event) 这个代码，
那你写的这个继承于 QCheckBox 类的 MyCheckBox 就不会对鼠标点击产生任何反应。


event 函数的作用就在于 事件的分发，在 even filter 之后执行
bool myWidget::event(QEvent* e)
{
        if (e->type() == QEvent::KeyPress)
        {
                //将QEvent对象转换为真正的QKeyEvent对象
                QKeyEvent* keyEvent = static_cast<QKeyEvent*>(e);
                if (keyEvent->key() == Qt::Key_Tab)
                {
                        qDebug() << "You press tab.";
                        return true;
                }
        }
        //按照原来的流程来进行事件的分发
        return QWidget::event(e);
}
若返回 父类的 event，即 return QWidget::event(e); 则还会调用 父组件。
需要注意的是，重写event函数之后最好返回父类的event函数来处理其他的事件分发，不然就只能处理自己定义的事件。
bool myTextEdit::event(QEvent* e)
{
        if (e->type() == QEvent::KeyPress)
        {
                //将QEvent对象转换为真正的QKeyEvent对象
                QKeyEvent* keyEvent = static_cast<QKeyEvent*>(e);
                if (keyEvent->key() == Qt::Key_Tab)
                {
                        qDebug() << "You press tab.";
                        return true;
                }
        }
        //直接返回false
        return false;
}
在这个例子中，因为没有调用父类QTextEdit的event函数，所以只能处理Tab的情况，
你再按其他按键就啥反应都没有了。同样，事件也不能进行传播。



//技巧一：接收 / 忽略事件
所有的事件的祖先都是 QEvent 类，而该类里有个 isAccepted() 函数来判断这个事件是否被接受（处理）了。
当收到一个事件对象时，我先拿到这个事件。如果不去处理，就会层层向父控件对象传递。
事实上，我们很少会用到 accept()、ignore() 函数的，如果忽略事件（即自己不想去处理这个事件），只要调用父类的响应函数就可以了。

一个特殊的例子：QWidget
Qt 中大部分的事件处理函数都是默认 accept() 接收事件对象，而 QWidget 却是默认 ignore() 的。
这样的话如果某个 QWidget 子类想忽略某个事件，既可以调用 ignore() 函数，也可以调用基类 QWidget 的默认实现。

必须调用 accept()、ignore() 函数的场景
就是窗口关闭事件！对于 QCloseEvent 来说，接收意味着事件到此结束不再传播，窗口关闭；忽略意味着事件继续传播，窗口仍然开着。


//技巧二：过滤事件
为对象安装过滤器： void QObject::installEventFilter(QObject* filterObj);
过滤器处理函数：    bool QObject::eventFilter(QObject* watched, QEvent* event);

事件过滤器是一个对象，它接收发送到此对象的所有事件。
过滤器可以停止该事件，也可以将其转发给该对象。
事件过滤器filterObj通过其 eventFilter() 函数接收事件。
在重新实现 eventFilter() 函数时，如果应该过滤事件，即停止进一步处理事件，则该函数必须返回 true ，否则它必须返回 false 。
如果在单个对象上安装了多个事件过滤器，则首先激活最后安装的过滤器。

举例：
比如在主界面上有一个按钮叫“A“。
当 A->installEventFilter(MainWindow) 的时候，A 产生的事件就不会进入接收者的 event() 函数中了，
而是进入接收者的 eventFilter() 函数中。

注意：
1、如果你在事件过滤器中 delete 了某个接收组件，务必将函数返回值设为 true 。否则，Qt 还是会将事件分发给这个接收组件，从而导致程序崩溃。
2、事件过滤器和被安装过滤器的组件必须在同一线程，否则，过滤器将不起作用。
3、如果在安装过滤器之后，这两个组件到了不同的线程，那么，只有等到二者重新回到同一线程的时候过滤器才会有效。



/********************/事件处理方法归纳/************************************************************/
Qt的事件处理函数都是虚函数，在基类中声明，在子类中重新实现，这些相应的事件函数在.h文件中定义在.cpp文件中重新实现函数内容

事件执行流程：
事件产生(窗口)->事件过滤(过滤器)->事件分发(指定执行窗口)->事件执行(具体控件)


//1. 重新实现特定事件（修改事件处理）
重新实现如 mousePressEvent(), keyPressEvent() 和 paintEvent() 等这些Qt事先已定义的事件处理器是进行事件处理的最简单的方式

//2. 重新实现 event()函数（修改事件过滤）
bool QObject::event(QEvent * e)
通过重新实现event()函数, 可以在事件到达特定的事件处理器之前截获并处理它们.
这种方法可以用来覆盖已定义事件的默认处理方式, 也可以用来处理Qt中尚未定义特定事件处理器的事件.
当重新试下 event() 函数时, 如果不进行事件处理, 则需要调用基类的 event() 事件

//3. 在QObject中注册事件过滤器（修改事件过滤）   
如果对象使用installEventFilter()函数注册了事件过滤器, 目标对象中而所有事件将先发给这个监视对象的eventFilter()函数

//4. 在QApplication中注册事件过滤器（修改事件过滤）
如果一个事件过滤器被注册到程序中唯一的QApplication对象, 应用程序中的所有对象里的每一个事件都会在他们被送达其他事件过滤器前,
首先抵达这个eventFilter() 函数.它可以用来处理一些通常被QApplication忽略的事件, 如发送给失效窗口的鼠标事件等.

//5. 继承QApplication 并重新实现notify()函数（修改事件分发）
在QApplication类的基础上派生出自定义的工程类，实现自定义的事件循环队列。在这里重写notify的事件分发方法。
virtual bool notify(QObject * receiver, QEvent * e) override
main函数中的application类对象使用自定义的app类对象。



/********************/枚举QEvent::Type/************************************************************/
这个枚举类型定义了Qt中有效的事件类型。事件类型和每个类型的专门类如下：

常量	                                                                        值	描述
QEvent::None	                                                        0	不是一个事件
QEvent::ActionAdded	                                        114	一个新 action 被添加（QActionEvent）
QEvent::ActionChanged	                                        113	一个 action 被改变（QActionEvent）
QEvent::ActionRemoved	                                        115	一个 action 被移除（QActionEvent）
QEvent::ActivationChange	                                99	Widget 的顶层窗口激活状态发生了变化
QEvent::ApplicationActivate	                                121	这个枚举已被弃用，使用 ApplicationStateChange 代替
QEvent::ApplicationActivated	ApplicationActivate	（这个枚举已被弃用，使用 ApplicationStateChange 代替）
QEvent::ApplicationDeactivate	                        122	这个枚举已被弃用，使用 ApplicationStateChange 代替
QEvent::ApplicationFontChange	                        36	应用程序的默认字体发生了变化
QEvent::ApplicationLayoutDirectionChange	        37	应用程序的默认布局方向发生了变化
QEvent::ApplicationPaletteChange	                        38	应用程序的默认调色板发生了变化
QEvent::ApplicationStateChange	                        214	应用程序的状态发生了变化
QEvent::ApplicationWindowIconChange	        35	应用程序的图标发生了变化
QEvent::ChildAdded	                                        68	一个对象获得孩子（QChildEvent）
QEvent::ChildPolished	                                        69	一个部件的孩子被抛光（QChildEvent）
QEvent::ChildRemoved	                                        71	一个对象时区孩子（QChildEvent）
QEvent::Clipboard	                                                40	剪贴板的内容发生改变
QEvent::Close	                                                        19	Widget 被关闭（QCloseEvent）
QEvent::CloseSoftwareInputPanel	                        200	一个部件要关闭软件输入面板（SIP）
QEvent::ContentsRectChange	                                178	部件内容区域的外边距发生改变
QEvent::ContextMenu	                                        82	上下文弹出菜单（QContextMenuEvent）
QEvent::CursorChange	                                        183	部件的鼠标发生改变
QEvent::DeferredDelete	                                        52	对象被清除后将被删除（QDeferredDeleteEvent）
QEvent::DragEnter	                                                60	在拖放操作期间鼠标进入窗口部件（QDragEnterEvent）
QEvent::DragLeave	                                                62	在拖放操作期间鼠标离开窗口部件（QDragLeaveEvent）
QEvent::DragMove	                                                61	拖放操作正在进行（QDragMoveEvent）
QEvent::Drop	                                                        63	拖放操作完成（QDropEvent）
QEvent::DynamicPropertyChange	                        170	动态属性已添加、更改或从对象中删除
QEvent::EnabledChange	                                        98	部件的 enabled 状态已更改
QEvent::Enter	                                                        10	鼠标进入部件的边界（QEnterEvent）
QEvent::EnterEditFocus	                                        150	编辑部件获得焦点进行编辑，必须定义 QT_KEYPAD_NAVIGATION
QEvent::EnterWhatsThisMode                              	124	当应用程序进入“What’s This?”模式，发送到 toplevel 顶层部件
QEvent::Expose	                                                206	当其屏幕上的内容无效，发送到窗口，并需要从后台存储刷新
QEvent::FileOpen	                                                116	文件打开请求（QFileOpenEvent）
QEvent::FocusIn	                                                8	部件或窗口获得键盘焦点（QFocusEvent）
QEvent::FocusOut	                                                9	部件或窗口失去键盘焦点（QFocusEvent）
QEvent::FocusAboutToChange	                        23	部件或窗口焦点即将改变（QFocusEvent）
QEvent::FontChange	                                        97	部件的字体发生改变
QEvent::Gesture	                                                198	触发了一个手势（QGestureEvent）
QEvent::GestureOverride                                 	202	触发了手势覆盖（QGestureEvent）
QEvent::GrabKeyboard	                                        188	Item 获得键盘抓取（仅限 QGraphicsItem）
QEvent::GrabMouse	                                        186	项目获得鼠标抓取（仅限 QGraphicsItem）
QEvent::GraphicsSceneContextMenu	                159	在图形场景上的上下文弹出菜单（QGraphicsScene ContextMenuEvent）
QEvent::GraphicsSceneDragEnter	                        164	在拖放操作期间，鼠标进入图形场景（QGraphicsSceneDragDropEvent）
QEvent::GraphicsSceneDragLeave	                        166	在拖放操作期间鼠标离开图形场景（QGraphicsSceneDragDropEvent）
QEvent::GraphicsSceneDragMove	                        165	在场景上正在进行拖放操作（QGraphicsSceneDragDropEvent）
QEvent::GraphicsSceneDrop	                                167	在场景上完成拖放操作（QGraphicsSceneDragDropEvent）
QEvent::GraphicsSceneHelp	                                163	用户请求图形场景的帮助（QHelpEvent）
QEvent::GraphicsSceneHoverEnter	                        160	鼠标进入图形场景中的悬停项（QGraphicsSceneHoverEvent）
QEvent::GraphicsSceneHoverLeave                 	162	鼠标离开图形场景中一个悬停项（QGraphicsSceneHoverEvent）
QEvent::GraphicsSceneHoverMove                  	161	鼠标在图形场景中的悬停项内移动（QGraphicsSceneHoverEvent）
QEvent::GraphicsSceneMouseDoubleClick	        158	鼠标在图形场景中再次按下（双击）（QGraphicsSceneMouseEvent）
QEvent::GraphicsSceneMouseMove	                155	鼠标在图形场景中移动（QGraphicsSceneMouseEvent）
QEvent::GraphicsSceneMousePress	                156	鼠标在图形场景中按下（QGraphicsSceneMouseEvent）
QEvent::GraphicsSceneMouseRelease	                157	鼠标在图形场景中释放（QGraphicsSceneMouseEvent）
QEvent::GraphicsSceneMove	                                182	部件被移动（QGraphicsSceneMoveEvent）
QEvent::GraphicsSceneResize	                                181	部件已调整大小（QGraphicsSceneResizeEvent）
QEvent::GraphicsSceneWheel	                                168	鼠标滚轮在图形场景中滚动（QGraphicsSceneWheelEvent）
QEvent::Hide	                                                        18	部件被隐藏（QHideEvent）
QEvent::HideToParent	                                        27	子部件被隐藏（QHideEvent）
QEvent::HoverEnter	                                                127	鼠标进入悬停部件（QHoverEvent）
QEvent::HoverLeave	                                        128	鼠标留离开悬停部件（QHoverEvent）
QEvent::HoverMove	                                        129	鼠标在悬停部件内移动（QHoverEvent）
QEvent::IconDrag	                                                96	窗口的主图标被拖走（QIconDragEvent）
QEvent::IconTextChange	                                        101	部件的图标文本发生改变（已弃用）
QEvent::InputMethod	                                        83	正在使用输入法（QInputMethodEvent）
QEvent::InputMethodQuery	                                207	输入法查询事件（QInputMethodQueryEvent）
QEvent::KeyboardLayoutChange	                        169	键盘布局已更改
QEvent::KeyPress	                                                6	键盘按下（QKeyEvent）
QEvent::KeyRelease              	                                7	键盘释放（QKeyEvent）
QEvent::LanguageChange	                                89	应用程序翻译发生改变
QEvent::LayoutDirectionChange	                        90	布局的方向发生改变
QEvent::LayoutRequest	                                        76	部件的布局需要重做
QEvent::Leave	                                                        11	鼠标离开部件的边界
QEvent::LeaveEditFocus	                                        151	编辑部件失去编辑的焦点，必须定义 QT_KEYPAD_NAVIGATION
QEvent::LeaveWhatsThisMode	                        125	当应用程序离开“What’s This?”模式，发送到顶层部件
QEvent::LocaleChange	                                        88	系统区域设置发生改变
QEvent::NonClientAreaMouseButtonDblClick	176	鼠标双击发生在客户端区域外
QEvent::NonClientAreaMouseButtonPress	        174	鼠标按钮按下发生在客户端区域外
QEvent::NonClientAreaMouseButtonRelease	        175	鼠标按钮释放发生在客户端区域外
QEvent::NonClientAreaMouseMove	                173	鼠标移动发生在客户区域外
QEvent::MacSizeChange	                                        177	用户更改了部件的大小（仅限 OS X）
QEvent::MetaCall	                                                43	通过 QMetaObject::invokeMethod() 调用异步方法
QEvent::ModifiedChange	                                102	部件修改状态发生改变
QEvent::MouseButtonDblClick	                        4	鼠标再次按下（QMouseEvent）
QEvent::MouseButtonPress	                                2	鼠标按下（QMouseEvent）
QEvent::MouseButtonRelease	                                3	鼠标释放（QMouseEvent）
QEvent::MouseMove	                                        5	鼠标移动（QMouseEvent）
QEvent::MouseTrackingChange	                        109	鼠标跟踪状态发生改变
QEvent::Move	                                                        13	部件的位置发生改变（QMoveEvent）
QEvent::NativeGesture	                                        197	系统检测到手势（QNativeGestureEvent）
QEvent::OrientationChange	                                208	屏幕方向发生改变（QScreenOrientationChangeEvent）
QEvent::Paint	                                                        12	需要屏幕更新（QPaintEvent）
QEvent::PaletteChange	                                        39	部件的调色板发生改变
QEvent::ParentAboutToChange	                        131	部件的 parent 将要更改
QEvent::ParentChange	                                        21	部件的 parent 发生改变
QEvent::PlatformPanel	                                        212	请求一个特定于平台的面板
QEvent::PlatformSurface	                                        217	原生平台表面已创建或即将被销毁（QPlatformSurfaceEvent）
QEvent::Polish	                                                        75	部件被抛光
QEvent::PolishRequest	                                        74	部件应该被抛光
QEvent::QueryWhatsThis	                                        123	如果部件有“What’s This?”帮助，应该接受事件
QEvent::ReadOnlyChange	                                106	部件的 read-only 状态发生改变
QEvent::RequestSoftwareInputPanel	                199	部件想要打开软件输入面板（SIP）
QEvent::Resize	                                                        14	部件的大小发生改变（QResizeEvent）
QEvent::ScrollPrepare	                                        204	对象需要填充它的几何信息（QScrollPrepareEvent）
QEvent::Scroll	                                                        205	对象需要滚动到提供的位置（QScrollEvent）
QEvent::Shortcut	                                                117	快捷键处理（QShortcutEvent）
QEvent::ShortcutOverride	                                51	按下按键，用于覆盖快捷键（QKeyEvent）
QEvent::Show	                                                        17	部件显示在屏幕上（QShowEvent）
QEvent::ShowToParent	                                        26	子部件被显示
QEvent::SockAct	                                                50	Socket 激活，用于实现 QSocketNotifier
QEvent::StateMachineSignal	                                192	信号被传递到状态机（QStateMachine::SignalEvent）
QEvent::StateMachineWrapped	                        193	事件是一个包装器，用于包含另一个事件（QStateMachine::WrappedEvent）
QEvent::StatusTip	                                                112	状态提示请求（QStatusTipEvent）
QEvent::StyleChange	                                        100	部件的样式发生改变
QEvent::TabletMove	                                        87	Wacom 写字板移动（QTabletEvent）
QEvent::TabletPress	                                                92	Wacom 写字板按下（QTabletEvent）
QEvent::TabletRelease	                                        93	Wacom 写字板释放（QTabletEvent）
QEvent::OkRequest	                                                94	Ok 按钮在装饰前被按下，仅支持 Windows CE
QEvent::TabletEnterProximity	                                171	Wacom 写字板进入接近事件（QTabletEvent），发送到 QApplication
QEvent::TabletLeaveProximity	                                172	Wacom 写字板离开接近事件（QTabletEvent），发送到 QApplication
QEvent::ThreadChange	                                        22	对象被移动到另一个线程。这是发送到此对象的最后一个事件在上一个线程中，参见：QObject::moveToThread()
QEvent::Timer	                                                        1	定时器事件（QTimerEvent）
QEvent::ToolBarChange	                                        120	工具栏按钮在 OS X 上进行切换
QEvent::ToolTip	                                                110	一个 tooltip 请求（QHelpEvent）
QEvent::ToolTipChange	                                        184	部件的 tooltip 发生改变
QEvent::TouchBegin	                                        194	触摸屏或轨迹板事件序列的开始（QTouchEvent）
QEvent::TouchCancel	                                        209	取消触摸事件序列（QTouchEvent）
QEvent::TouchEnd	                                                196	触摸事件序列结束（QTouchEvent）
QEvent::TouchUpdate	                                        195	触摸屏事件（QTouchEvent）
QEvent::UngrabKeyboard	                                189	Item 失去键盘抓取（QGraphicsItem）
QEvent::UngrabMouse	                                        187	Item 失去鼠标抓取（QGraphicsItem、QQuickItem）
QEvent::UpdateLater	                                        78	部件应该排队在以后重新绘制
QEvent::UpdateRequest	                                        77	部件应该被重绘
QEvent::WhatsThis	                                                111	部件应该显示“What’s This”帮助（QHelpEvent）
QEvent::WhatsThisClicked	                                118	部件的“What’s This”帮助链接被点击
QEvent::Wheel	                                                        31	鼠标滚轮滚动（QWheelEvent）
QEvent::WinEventAct	                                        132	发生了 Windows 特定的激活事件
QEvent::WindowActivate	                                        24	窗口已激活
QEvent::WindowBlocked	                                        103	窗口被模态对话框阻塞
QEvent::WindowDeactivate	                                25	窗户被停用
QEvent::WindowIconChange	                                34	窗口的图标发生改变
QEvent::WindowStateChange	                                105	窗口的状态（最小化、最大化或全屏）发生改变（QWindowStateChangeEvent）
QEvent::WindowTitleChange	                                33	窗口的标题发生改变
QEvent::WindowUnblocked	                                104	一个模态对话框退出后，窗口将不被阻塞
QEvent::WinIdChange	                                        203	本地窗口的系统标识符发生改变
QEvent::ZOrderChange	                                        126	部件的 z 值发生了改变，该事件不会发送给顶层窗口

用户事件的值应该介于 User 和 MaxUser 之间。
常量	                        值	                描述
QEvent::User	        1000	                用户定义的事件
QEvent::MaxUser	65535	        最后的用户事件 ID



