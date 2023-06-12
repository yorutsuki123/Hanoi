#pragma once
#ifndef RUNHANOI
#define RUNHANOI

#define MAX_LAYER 8

namespace hanoi
{
	typedef struct StacksTag
	{
		int stack[3][MAX_LAYER];
		int length[3];
		bool isDone;
	}Stacks;

	bool initHanoi(int layer);
	Stacks getStacks();
	Stacks nextStacks();
}
#endif // !RUNHANOI
