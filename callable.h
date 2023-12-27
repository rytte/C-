#ifndef CALLABLE_H
#define CALLABLE_H


#include <string>
class Callable
{
public:
	virtual ~Callable() {}
	virtual void notify() = 0;
};


#endif // CALLABLE_H
