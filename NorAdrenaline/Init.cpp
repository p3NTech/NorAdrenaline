#include "Init.h"

std::stack<void(*)()> &init_stack()
{
	static std::stack<void(*)()> stack;
	return stack;
}

InitRoutine::InitRoutine(void(*func)())
{
	init_stack().push(func);
}