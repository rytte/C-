/********************/代理模式（Proxy Pattern）/************************************************************/
代理模式：为其他对象提供一种代理以控制对这个对象的访问。
在某些情况下，一个对象不适合或者不能直接引用另一个对象，而代理对象可以在客户端和目标对象之间起到中介的作用。

//实现方法
写一个抽象类，含有一些纯虚方法（业务方法）。
写一个委托类，继承抽象类，并实现这些方法，供代理类调用。
写多个代理类，继承抽象类，将委托类作为子类，并实现这些方法，需要体现出不同的访问权限。


//实例
// 抽象类（抽象角色）
class VideoSite
{
public:
	virtual void freemovie() = 0;
	virtual void vipmovie() = 0;
	virtual void ticketmovie() = 0;
};
// 委托类（真实角色）
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
// 免费游客对应代理类（代理角色）
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

// VIP会员对应代理类（代理角色）
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


可以看到，我们代码里面的委托类YangVideoSite就是上面提到的真实角色。它拥有了该网站所有视频的观看权限。
每一个代理类都有一个委托类的数据成员。代理类通过委托类来访问视频网站。
并且，可以根据当前代理的用户的身份（普通游客、VIP会员），来限制其访问的内容。

为了模拟在视频网站上浏览视频的全部情景，我们可以设计一个函数，专门用来观看电影（免费电影、VIP电影、用券观看的电影）：


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

	watchMovie(p1);			//免费用户观看
	cout << "-----------------------------------------" << endl;
	watchMovie(p2);			//VIP用户观看

	return 0;
}




