/********************/TCP Socket/************************************************************/
//服务器
1、创建套接字			int sfd = socket(AF_INET, SOCK_STREAM, 0);
2、绑定套接字			int ret = bind(sfd, (struct sockaddr*)&addr, sizeof(addr));			//结构体：服务器地址
3、监听套接字			listen(sfd, 1);
4、获取连接的套接字	int cfd = accept(sfd, (struct sockaddr*)&c_addr, &len);
5、读取数据			read(cfd, buf, sizeof(buf));

//客户端
1、创建套接字			int cfd = socket(AF_INET, SOCK_STREAM, 0);
2、连接服务器			int ret = connect(cfd, (struct sockaddr*)&addr, sizeof(addr));		//结构体：服务器地址
3、写入数据			write(cfd, buf, strlen(buf));



/********************/UDP Socket/************************************************************/
//接收端
1、创建套接字			int s_fd = socket(AF_INET, SOCK_DGRAM, 0);
2、绑定套接字			int ret = bind(s_fd, (struct sockaddr*)&addr, sizeof(struct sockaddr));	//结构体：自身地址
3、接收数据			recvfrom(s_fd, buf, sizeof(buf), 0, (struct sockaddr*)&src, &srclen);	//结构体：消息源地址

//发送端
1、创建套接字			int c_fd = socket(AF_INET, SOCK_DGRAM, 0);
2、发送数据			sendto(c_fd, buf, sizeof(buf), 0, (struct sockaddr*)&dst, sizeof(dst));	//结构体：目的地址


//发送广播
1、创建套接字			int c_fd = socket(AF_INET, SOCK_DGRAM, 0);
2、获取广播属性		getsockopt(c_fd, SOL_SOCKET, SO_BROADCAST, &val, &len);
3、设置广播属性		setsockopt(c_fd, SOL_SOCKET, SO_BROADCAST, &on, sizeof(on));
4、发送广播消息		sendto(c_fd, buf, sizeof(buf), 0, (struct sockaddr*)&dst, sizeof(dst));	//结构体：广播地址


//接收组播
1、创建套接字			int s_fd = socket(AF_INET, SOCK_DGRAM, 0);
2、设置组播属性		setsockopt(s_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mult, sizeof(mult));	//结构体：组播地址
3、绑定套接字			int ret = bind(s_fd, (struct sockaddr*)&addr, sizeof(struct sockaddr));		//结构体：自身地址
4、接收数据			recvfrom(s_fd, buf, sizeof(buf), 0, (struct sockaddr*)&src, &srclen);		//结构体：消息源地址



