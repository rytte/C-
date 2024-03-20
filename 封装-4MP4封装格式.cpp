/*************************/MP4封装格式/***************************************************************************/

//MP4封装结构
MP4文件由多个box组成，每个box存储不同的信息，且box之间是树状结构

3个顶层box：
ftyp：File Type Box，描述文件遵从的MP4规范与版本；
moov：Movie Box，媒体的metadata信息，有且仅有一个。
mdat：Media Data Box，存放实际的媒体数据，一般有多个；

box由两部分组成：box header、box body。

box header：box 的元数据，如：box type、box size。
box body：box 的数据部分，实际存储的内容跟 box 类型有关，比如 mdat 中 body 部分存储的媒体数据。

box header中，只有type、size是必选字段。当size == 0时，存在largesize字段。
在部分box中，还存在version、flags字段，这样的box叫做Full Box。当box body中嵌套其他box时，这样的box叫做container box。


//Box Header
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



//【一】ftyp（File Type Box）
major_brand：比如常见的 isom、mp41、mp42、avc1、qt等。它表示优先基于哪种格式来解析当前的文件。
minor_version：提供 major_brand 的说明信息，比如版本号，不得用来判断媒体文件是否符合某个标准 / 规范；
compatible_brands：文件兼容的brand列表。比如 mp41 的兼容 brand 为 isom。通过兼容列表里的 brand 规范，可以将文件部分（或全部）解码出来；


//【一】moov（Movie Box）
Movie Box，存储 mp4 的 metadata，一般位于mp4文件的开头。

* mvhd：Movie Header Box，mp4文件的整体信息，比如创建时间、文件时长等；
* trak：Track Box，存放音频、视频轨道相关信息。一个mp4可以包含一个或多个轨道。

mvhd（Movie Header）描述整个影片
tkhd（Track Header）描述单个track
mdhd（Media Header）描述媒体
vmhd（Video Movie Header）描述视频
smhd（Sound Movie Header）描述音频


//【二】mvhd（Movie Header Box）
MP4文件的整体信息，跟具体的视频流、音频流无关，比如创建时间、文件时长等。字段如下：

* creation_time：文件创建时间；
* modification_time：文件修改时间；
* timescale：一秒包含的时间单位（整数）。举个例子，如果timescale等于1000，那么，一秒包含1000个时间单位（后面track等的时间，都要用这个来换算，比如track的duration为10, 000，那么，track的实际时长为10, 000 / 1000 = 10s）；
* duration：影片时长（整数），根据文件中的track的信息推导出来，等于时间最长的track的duration；
* rate：推荐的播放速率，32位整数，高16位、低16位分别代表整数部分、小数部分（[16.16]），举例 0x0001 0000 代表1.0，正常播放速度；
* volume：播放音量，16位整数，高8位、低8位分别代表整数部分、小数部分（[8.8]），举例 0x01 00 表示 1.0，即最大音量；
* matrix：视频的转换矩阵，一般可以忽略不计；
* next_track_ID：32位整数，非0，一般可以忽略不计。当要添加一个新的track到这个影片时，可以使用的track id，必须比当前已经使用的track id要大。也就是说，添加新的track时，需要遍历所有track，确认可用的track id；

//【二】udta

//【三】meta

//【四】hdlr

//【四】ilst

//【二】trak（Track Box）
trak是container box，至少包含两个box：tkhd、mdia；


//【三】tkhd（Track Header Box）
* version：tkhd box的版本；
* flags：按位或操作获得，默认值是7（0x000001 | 0x000002 | 0x000004），表示这个track是启用的、用于播放的 且 用于预览的。
* Track_enabled：值为0x000001，表示这个track是启用的，当值为0x000000，表示这个track没有启用；
* Track_in_movie：值为0x000002，表示当前track在播放时会用到；
* Track_in_preview：值为0x000004，表示当前track用于预览模式；
* creation_time：当前track的创建时间；
* modification_time：当前track的最近修改时间；
* track_ID：当前track的唯一标识，不能为0，不能重复；
* duration：当前track的完整时长（需要除以timescale得到具体秒数）；
* layer：视频轨道的叠加顺序，数字越小越靠近观看者，比如1比2靠上，0比1靠上；
* alternate_group：当前track的分组ID，alternate_group值相同的track在同一个分组里面。同个分组里的track，同一时间只能有一个track处于播放状态。当alternate_group为0时，表示当前track没有跟其他track处于同个分组。一个分组里面，也可以只有一个track；
* volume：audio track的音量，介于0.0~1.0之间；
* matrix：视频的变换矩阵；
* width、height：视频的宽高；


//【三】edts（Edit Decision List）
edts是一个可选的原子（atom），用于存储编辑决策列表。
这个列表主要记录了视频和音频流的编辑信息，比如哪些部分被剪切掉了，哪些部分被重新排列了等。
这些信息对于播放器在播放视频时正确呈现编辑后的内容非常重要。


//【三】mdia
mdia是一个container box（容器盒），它定义了track媒体类型以及sample数据，并描述sample信息。
通常，一个mdia包含一个mdhd（媒体头）、一个hdlr（处理器引用）和一个minf（媒体信息）。


//【四】mdhd（Media Header Box）


//【四】hdlr（Handler Reference Box）
声明当前track的类型，以及对应的处理器（handler）。

* vide（0x76 69 64 65），video track；
* soun（0x73 6f 75 6e），audio track；
* hint（0x68 69 6e 74），hint track；

//【四】minf（Media Information Box）

//【五】vmhd（Video Movie Header Box）

//【五】dinf

//【六】dref
url

//【五】stbl（Sample Table Box）
MP4文件的媒体数据部分在mdat box里，而stbl则包含了这些媒体数据的索引以及时间信息，了解stbl对解码、渲染MP4文件很关键。

在MP4文件中，媒体数据被分成多个chunk，每个chunk可包含多个sample，而sample则由帧组成（通常1个sample对应1个帧）

stbl中比较关键的box包含stsd、stco、stsc、stsz、stts、stss、ctts。下面先来个概要的介绍，然后再逐个讲解细节。

//【六】stsd（Sample Description Box）
stsd：给出视频、音频的编码、宽高、音量等信息，以及每个sample中包含多少个frame；

//【七】avc1
avcC

//【六】stco / stsc / stsz / stts / stss / ctts 概述
stts（time to sample box）：每个sample解码时间的压缩表。
ctts（composition time to sample box）：每个sample的CTS与DTS的时间差的压缩表。
stss（sync sample box）：针对视频，关键帧的序号。
stsz / stz2（sample size box）：每个sample的字节大小；
stsc（sample to chunk box）：sample - chunk映射表。每个chunk中包含几个sample；
stco / co64：chunk offset box，chunk在文件中的偏移。

sgpd
sbgp


//【一】mdat
存放实际的媒体数据，一般有多个。

























0 ~3 字节是 box 的 size （大小）
4 ~7 字节是 box 的类型。












