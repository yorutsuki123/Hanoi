#include "RunHanoi.h"
#include <cmath>

/* definition of hanoi::Stacks

typedef struct StacksTag
{
	int stack[3][MAX_LAYER];
	int length[3];
	bool isDone;
}Stacks;
*/

typedef struct MovementTag
{
	int from, to;
}Movement;

hanoi::Stacks stacks;

Movement *movements; // An array, as a queue
int movementHead;
int movementBottom;

// ----------------stacks handle----------------

// 把value加到stacks[tower]的頂端(最後)
void stackPush(int tower, int value)
{
	// Fill in the code

}

// 將stacks[tower]的頂端(最後)的值取出
int stackPop(int tower)
{
	// Fill in the code

	return 0;
}

// ----------------movement handle----------------

int movementLenth()
{
	return movementBottom - movementHead;
}

void movementEnqueue(Movement m)
{
	// Fill in the code

}

Movement movementDequeue()
{
	// Fill in the code

	return Movement{};
}

// ----------------hanoi handle----------------

// 將movement依序Enqueue至陣列movements中
void genHanoiMovements(int layer, int from = 0, int to = 2, int tmp = 1)
{
	// Fill in the code

}

hanoi::Stacks hanoi::getStacks()
{
	return stacks;
}

// 將陣列movements Dequeue一次，將取得的資料實作至stacks中，並回傳更新後的stacks
// 由main function每秒呼叫一次
hanoi::Stacks hanoi::nextStacks()
{
	// Fill in the code


	return stacks;
}

// 初始化狀態並產生movements
bool hanoi::initHanoi(int layer)
{
	if (layer > MAX_LAYER)
		return false;
	// init stacks
	stacks = hanoi::Stacks{ 0 };
	for (int i = layer; i >= 1; i--)
		stackPush(0, i);
	// init movement
	movements = new Movement[(int)pow(2, layer)]{ 0 };
	movementBottom = movementHead = -1;
	// generate movement
	genHanoiMovements(layer);
	// success
	return true;
}
