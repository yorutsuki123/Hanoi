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
	stacks.stack[tower][stacks.length[tower]++] = value;

}

// 將stacks[tower]的頂端(最後)的值取出
int stackPop(int tower)
{

	return stacks.stack[tower][--stacks.length[tower]];
}

// ----------------movement handle----------------

int movementLenth()
{
	return movementBottom - movementHead;
}

void movementEnqueue(Movement m)
{
	movements[++movementHead] = m;

}

Movement movementDequeue()
{

	return movements[++movementBottom];
}

// ----------------hanoi handle----------------

// 將movement依序Enqueue至陣列movements中
void genHanoiMovements(int layer, int from = 0, int to = 2, int tmp = 1)
{
	if (layer == 0) return;
	genHanoiMovements(layer - 1, from, tmp, to);
	movementEnqueue(Movement{ from, to });
	genHanoiMovements(layer - 1, tmp, to, from);
}

hanoi::Stacks hanoi::getStacks()
{
	return stacks;
}

// 將陣列movements Dequeue一次，將取得的資料實作至stacks中，並回傳更新後的stacks
// 由main function每秒呼叫一次
hanoi::Stacks hanoi::nextStacks()
{
	Movement move = movementDequeue();
	int mm = stackPop(move.from);
	stackPush(move.to, mm);
	stacks.isDone = (movementLenth() == 0);
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
