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

// ��value�[��stacks[tower]������(�̫�)
void stackPush(int tower, int value)
{
	// Fill in the code

}

// �Nstacks[tower]������(�̫�)���Ȩ��X
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

// �Nmovement�̧�Enqueue�ܰ}�Cmovements��
void genHanoiMovements(int layer, int from = 0, int to = 2, int tmp = 1)
{
	// Fill in the code

}

hanoi::Stacks hanoi::getStacks()
{
	return stacks;
}

// �N�}�Cmovements Dequeue�@���A�N���o����ƹ�@��stacks���A�æ^�ǧ�s�᪺stacks
// ��main function�C��I�s�@��
hanoi::Stacks hanoi::nextStacks()
{
	// Fill in the code


	return stacks;
}

// ��l�ƪ��A�ò���movements
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
