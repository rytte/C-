('''********************'''operator 模块'''************************************************************'''
 operator 模块提供了一套与 Python 的内置运算符对应的高效率函数。

import operator

# operator 方法
运算         语法                函数
                                 
加法         a + b               add(a, b)
字符串拼接   seq1 + seq2         concat(seq1, seq2)
包含测试     obj in seq          contains(seq, obj)
除法         a / b               truediv(a, b)
除法         a // b              floordiv(a, b)
按位与       a & b               and_(a, b)
按位异或     a ^ b               xor(a, b)
按位取反     ~ a                 invert(a)
按位或       a | b               or_(a, b)
取幂         a ** b              pow(a, b)
标识         a is b              is_(a, b)
标识         a is not b          is_not(a, b)
索引赋值     obj[k] = v          setitem(obj, k, v)
索引删除     del obj[k]          delitem(obj, k)
索引取值     obj[k]              getitem(obj, k)
左移         a << b              lshift(a, b)
取模         a % b               mod(a, b)
乘法         a * b               mul(a, b)
矩阵乘法     a @ b               matmul(a, b)
取反（算术） - a                 neg(a)
取反（逻辑） not a               not_(a)
正数         + a                 pos(a)
右移         a >> b              rshift(a, b)
切片赋值     seq[i:j] = values   setitem(seq, slice(i, j), values)
切片删除     del seq[i:j]        delitem(seq, slice(i, j))
切片取值     seq[i:j]            getitem(seq, slice(i, j))
字符串格式化 s % obj             mod(s, obj)
减法         a - b               sub(a, b)
真值测试     obj                 truth(obj)
比较         a < b               lt(a, b)
比较         a <= b              le(a, b)
相等         a == b              eq(a, b)
不等         a != b              ne(a, b)
比较         a >= b              ge(a, b)
比较         a > b               gt(a, b)



