#pragma once

#pragma once

#include <stack>

std::stack<void(*)()> &init_stack();

class InitRoutine
{
public:
	InitRoutine(void(*func)());
};