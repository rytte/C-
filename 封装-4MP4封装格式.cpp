/*************************/MP4封装格式/***************************************************************************/

MP4文件的格式主要由 MPEG - 4 Part 12、MPEG - 4 Part 14 两部分进行定义。
其中：
MPEG - 4 Part 12 定义了ISO基础媒体文件格式，用来存储基于时间的媒体内容。
MPEG - 4 Part 14 实际定义了MP4文件格式，在MPEG - 4 Part 12的基础上进行扩展。


//MP4封装结构
MP4文件由多个box组成，每个box存储不同的信息，且box之间是树状结构

3个比较重要的顶层box：
ftyp：File Type Box，描述文件遵从的MP4规范与版本；
moov：Movie Box，媒体的metadata信息，有且仅有一个。
mdat：Media Data Box，存放实际的媒体数据，一般有多个；

box由两部分组成：box header、box body。

box header：box 的元数据，如：box type、box size。
box body：box 的数据部分，实际存储的内容跟 box 类型有关，比如 mdat 中 body 部分存储的媒体数据。

box header中，只有type、size是必选字段。当size == 0时，存在largesize字段。
在部分box中，还存在version、flags字段，这样的box叫做Full Box。当box body中嵌套其他box时，这样的box叫做container box。


//box header
type：box类型，包括 “预定义类型”、“自定义扩展类型”，占4个字节；
——预定义类型：比如ftyp、moov、mdat等预定义好的类型；
——自定义扩展类型：如果type == uuid，则表示是自定义扩展类型。size（或largesize）随后的16字节，为自定义类型的值（extended_type）
size：包含box header在内的整个box的大小，单位是字节。当size为0或1时，需要特殊处理：
——size等于0：box的大小由后续的largesize确定（一般只有装载媒体数据的mdat box会用到largesize）；
——size等于1：当前box为文件的最后一个box，通常包含在mdat box中；
largesize：box的大小，占8个字节；
extended_type：自定义扩展类型，占16个字节；


//Box Body
box数据体，不同box包含的内容不同，需要参考具体box的定义。
有的 box body 很简单，比如 ftyp。有的 box 比较复杂，可能嵌套了其他box，比如moov。


//Box vs FullBox
在Box的基础上，扩展出了FullBox类型。相比Box，FullBox 多了 version、flags 字段。

version：当前box的版本，为扩展做准备，占1个字节；
flags：标志位，占24位，含义由具体的box自己定义；





0 ~3 字节是 box 的 size （大小）
4 ~7 字节是 box 的类型。












