/********************/Arduino IDE/************************************************************/

// 内置函数
1、pinMode(pin, mode)：用于配置数字引脚的输入或输出模式。pin 是数字引脚的编号，mode 是要设置的模式（输入或输出）。
2、digitalWrite(pin, value)：用于在数字引脚上写入数字值（HIGH 或 LOW）。pin 是数字引脚的编号，value 是要写入的值。
3、digitalRead(pin)：用于读取数字引脚上的数字值（HIGH 或 LOW）。pin 是数字引脚的编号。
4、analogRead(pin)：用于读取模拟引脚上的模拟值（0 - 1023）。pin 是模拟引脚的编号。
5、analogWrite(pin, value)：用于在支持 PWM 输出的数字引脚上输出模拟值（0 - 255）。pin 是数字引脚的编号，value 是要输出的值。
6、delay(ms)：用于在程序中创建暂停（延迟）时间。ms 是要延迟的毫秒数。
7、Serial.begin(baud)：用于初始化串口通信，其中 baud 是波特率。
8、Serial.println(data)：用于将数据打印到串口监视器。data 可以是数字、字符串或其他数据类型。

// 引脚
引脚类型				引脚编号										说明
数字引脚				0 - 13										用于数字输入和输出（0和1用于串口通信）
模拟输入引脚			A0 - A5										用于读取模拟信号
PWM 输出引脚			3, 5, 6, 9, 10, 11							支持模拟输出（PWM）
电源引脚				Vin, 5V, 3.3V, GND							Vin：输入电压，5V / 3.3V：电源输出，GND：地线
串口通信引脚			RX(0), TX(1)								用于串口数据接收和发送（RX为接收，TX为发送）
I2C 引脚				A4(SDA), A5(SCL)							A4：数据线，A5：时钟线
SPI 引脚				10 (SS), 11 (MOSI), 12 (MISO), 13 (SCK)		10：片选，11：主输出从输入，12：主输入从输出，13：时钟
其他引脚				AREF, Reset									AREF：参考电压输入，Reset：重置引脚


// 宏定义（电平）
#define HIGH 1
#define LOW 0

