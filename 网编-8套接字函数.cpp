/********************/套接字/************************************************************/
基本套接字函数

//socket：生成一个套接字。
原型： int socket(int family, int type, int protocol)
参数
family：指明协议簇；<AF_INET>IPv4，<AF_INET6>IPv6
type：套接字类型；<SOCK_STREAM>流类型，<SOCK_DGRAM>数据报类型
protocol：指定协议。<IPPROTO_TCP>TCP协议，<PPTOTO_UDP>UDP协议
return ：socket句柄。
备注：实际上为一个socket数据结构分配存储空间，返回对应句柄。

//socketpair：生成一对连接好的套接字。
原型： int socketpair(int family,int type,int protocol,int fd_array[2])
参数
前三个参数同socket函数
fd_array[2]：用于存放两个套接字句柄。
return ：成功2，失败-1。
备注：仅用于UNIX，可以看作是双向管道。

//bind：将套接字与本机网络地址和端口号绑定在一起。
原型： int bind(int fd,struct sockaddr *addr,int addrlen)
参数
fd：套接字句柄；
addr：指向一个地址结构；
addrlen：地址结构字节数。
返回值：成功0，失败-1。
备注：一般用于服务器端绑定公认端口，客户端可以不执行此操作。
struct sockaddr {
	sa_family_t  sin_family;   //地址族（Address Family），也就是地址类型
	char         sa_data[14];	//IP地址和端口号
};
struct sockaddr_in6 {
	sa_family_t     sin6_family;   /* AF_INET6 */
	in_port_t       sin6_port;     /* port number */
	uint32_t        sin6_flowinfo; /* IPv6 flow information */
	struct in6_addr sin6_addr;     /* IPv6 address */
	uint32_t        sin6_scope_id; /* Scope ID (new in 2.4) */
};

//connect：连接服务器端套接字。
原型： int connect(int fd,struct sockaddr * addressp,int addrlen)
参数
与bind的参数含义相同，不同之处是这里的地址是服务器端的。
return ：成功0，失败-1。
备注：一般用于客户端向服务器发起连接，服务端可以不执行此操作。

//listen：监听客户请求并将其插入请求队列中排队。
原型： int listen(int fd,int qlen)
参数
fd：套接字句柄
qlen：请求队列长度。
return ：成功0，失败-1。
备注：服务器端使用。

//accept：从全连接队列中获取一个套接字。
原型： int accept(int fd,struct sockaddr * clientaddr,int *addrlen)
参数
fd：全连接队列中的套接字句柄
clientaddr：客户机的地址
addrlen：地址结构长度
return ：大于0是新建立的套接字句柄，执行成功。失败返回-1。
备注：适用于服务器端。返回的句柄是真正用于传输的套接字，在无连接请求时阻塞进程。

//read/write：在套接字缓冲区中接收或发送数据。
原型： int read/write(int fd,char *buf,int len)
参数
fd：套接字句柄
buf：套接字对应缓冲区地址
len：接收或发送数据的长度。
return ：大于0成功，为接收或发送数据的字节数。小于0则失败。
备注：无。

//close：关闭socket。
原型： int close(int sockfd)
参数
sockfd:套接字句柄。
return ：成功1，失败-1。
备注：只是本进程关闭对该套接字的一次引用，需要所有引用全部清除套接字才会消失。


/************************************************************/
高级套接字函数

//send/recv：通过信道发送或接收数据。
原型： int send/recv(int fd,char *buf,int len,int flags)
参数
fd：套接字句柄
buf：数据缓冲区
len：数据缓冲区字节数
flags：控制标记。
return ：大于零成功，失败-1。
备注：无连接协议可用函数sendto/recvfrom,此外还有一个更强大的sendmsgrecvmsg/函数,不再赘言。

//readv/writev：用于对多个不连续的缓冲区散布读和聚集写。
原型： ssize_t readv(int fd,const struct iovec iov[],int iovcnt)
参数
fd：套接字句柄
iov[]：存放缓冲区地址结构指针的数组
iovcnt：数组长度。
return ：成功返回读 / 写的总字节数，失败返回-1。
备注：多缓冲区的字节传送。

//shutdown：终止网络连接。
原型： int shutdown(int fd,int action)
参数
fd：套接字句柄
action：0停止读，1停止写，2停止读写。
return ：成功0，失败-1。
备注：关闭的是TCP连接，不考虑套接字引用计数。能够控制单向通道的开关。

//getpeername/getsockname：获得与指定套接字相连的对端/本地地址。
原型： int getpeername/getsockname(int fd,struct sockaddr* proaddr,int * addrlen)
参数
fd：指定套接字句柄
proaddr：地址缓冲区指针
addrlen：缓冲区字节数指针
return ：成功0，失败-1。
备注：无。

//getsockopt/setsockopt：获取/设置套接字选项。
原型： int getsockopt/setsockopt(int sockfd, int level, int optname, void *optval, sock_len_t *optlen)
参数
sockfd：套接字句柄
level：协议级别
optname：指定选项
optval：选项值缓冲区
optlen：缓冲区长度。
return ：成功0，失败-1。
备注：对套接字的自定义设置。

//fcntl：管理套接字属性。
原型： int fcntl(int fd,int cmd,int arg)
参数
fd：套接字句柄
cmd：要执行的操作
arg：与操作配套的参数
return ：成功返回值>=0，失败返回-1。
备注：和套接字进程、阻塞有关。

//ioctl：处理套接字各种设备选择项。
原型： int ioctl(int fd,int request,int * args)
参数
fd：套接字句柄
request：指定操作类型
args：与request配套使用，存储返回参数值。
return ：成功0，失败-1。
备注：可管理磁盘、文件、磁带、套接字、终端等设备或伪设备。



