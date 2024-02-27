/********************/代理模式（Proxy Pattern）/************************************************************/
模式思想
简介
代理模式：为其他对象提供一种代理以控制对这个对象的访问。
在某些情况下，一个对象不适合或者不能直接引用另一个对象，而代理对象可以在客户端和目标对象之间起到中介的作用。

代理模式 属于 结构型模式。

组成
抽象角色：通过接口或抽象类声明真实角色实现的业务方法；
真实角色：实现抽象角色，定义真实角色所要实现的业务逻辑，供代理角色调用；
代理角色：实现抽象角色，是真实角色的代理，通过真实角色的业务逻辑方法来实现抽象方法，并可以附加自己的操作。（访问权限）
优点
职责清晰：真实的角色就是实现实际的业务逻辑，不用关心其他非本职的事务，通过后期的代理来完成事务，附带的结果就是编程简洁清晰；
代理对象可以在客户端和目标对象之间起到中介的作用，保护了目标对象；
高扩展性。


//实例
// 抽象类
class VideoSite
{
public:
	virtual void freemovie() = 0;
	virtual void vipmovie() = 0;
	virtual void ticketmovie() = 0;
};
// 委托类
class YangVideoSite :public VideoSite
{
public:
	void freemovie()
	{
		cout << "观看免费电影" << endl;
	}
	void vipmovie()
	{
		cout << "观看vip电影" << endl;
	}
	void ticketmovie()
	{
		cout << "用券观看电影" << endl;
	}
};
// 免费游客对应代理类
class FreeVideoSiteProxy :public VideoSite
{
public:
	void freemovie()
	{
		video.freemovie();
	}
	void vipmovie()
	{
		cout << "您只是普通游客，需要升级成VIP，才能观看VIP电影" << endl;
	}
	void ticketmovie()
	{
		cout << "您目前没有电影券，需要购买券才能观看电影" << endl;
	}
private:
	YangVideoSite video;
};

// VIP会员对应代理类
class VipVideoSiteProxy :public VideoSite
{
public:
	VipVideoSiteProxy() { pvideo = new YangVideoSite(); }
	~VipVideoSiteProxy() { delete pvideo; }
	void freemovie()
	{
		pvideo->freemovie();
	}
	void vipmovie()
	{
		pvideo->vipmovie();
	}
	void ticketmovie()
	{
		cout << "您目前没有电影券，需要购买券才能观看电影" << endl;
	}
private:
	YangVideoSite* pvideo;
};


void watchMovie(unique_ptr<VideoSite>& ptr)
{
	ptr->freemovie();
	ptr->vipmovie();
	ptr->ticketmovie();
}


int main()
{
	unique_ptr<VideoSite> p1(new FreeVideoSiteProxy());
	unique_ptr<VideoSite> p2(new VipVideoSiteProxy());

	watchMovie(p1);
	cout << "-----------------------------------------" << endl;
	watchMovie(p2);

	return 0;
}




