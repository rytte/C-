

//KMP
由于部分字符已经匹配过，因此在主串下一个字符开始时，搜索串不需从头开始进行匹配。
可以直接偏移（搜索串）开始部分到与匹配失败位置的前部相同字符的个数的位置。
如搜索串ABCCABD在D处匹配失败时，主串指针位置不变，搜索串由于失败处D前的AB与其头部AB相同，因此重置指针时可以从C处开始。


//next数组确定
搜索串在每一位置（下标）匹配失败时，其前缀与后缀（排除匹配的那位）相同字母的个数（值）
匹配成功时或搜索串指针为0，两串指针都后移一位。当匹配失败时，搜索串指针置为数组相应值。

//next数组优化（nextval）
nextval[1] = 0;
for (int j = 2; j < T.length; j++)
{
	if (T.ch[next[j]] == T.ch[j])
		nextval[j] = nextval[next[j]];
	else
		nextval[j] = next[j];
}

//算法（S源串，T搜索串）
int Index_KMP(string S, string T, int next[])
{
	int i = 1; j = 1;
	while (i < S.length && j <= T.length)
	{
		if (j == 0 || S.ch[i] == T.ch[j])
		{
			++i;
			++j;
		}
		else
			j = next[j];
	}
	if (j > T.length)
		return i - T.length;
	else
		return 0;
}

KMP算法，最坏时间复杂度 O(m+n)
其中，求next数组时间复杂度O(m)，匹配过程最坏时间复杂度O(n)。
普通匹配算法最坏时间复杂度为O(mn)。


//我的：next下标从0开始
char* source[] = "abccacceee"
char* temp[] = "abccabd"
int next[] = {}
next[0]  a：i++ (j = 0)
next[1]  b：i++; j = 0;
next[2]  c：i++; j = 0;
next[3]  c：i++; j = 0;
next[4]  a：i++; j = 0;
next[5]  b：j = 1;	（next数组优化：与跳转位置相同，改为i++，j = 0）
next[6]  d：j = 2;

int Index_KMP(string S, string T, int next[])
{
	int i = 1; j = 1;
	while (i < S.length && j <= T.length)
	{
		if (S[i] == T[j])		//相同则匹配下一位
		{
			i++;
			j++;
		}
		else if (j == 0)			//搜索串清空时，主串从下一位开始
			i++;
		else
			j = next[j];		//不同则偏移搜索串指针
	}
	if (j > T.length)
		return i - T.length;
	else
		return 0;
}

