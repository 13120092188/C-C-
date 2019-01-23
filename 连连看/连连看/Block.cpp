#include "Block.h"



Block::Block()
{
}

Block::Block(int num, int type, string photo_name)
{
	this->num = num;
	this->type = type;
	this->photo_name = photo_name;
}


Block::~Block()
{
}

void Block::set_choose()
{
	if (choose) choose = false;
	else choose = true;
}

void Block::disappear()
{
	if (appear1) appear1 = false;
	else appear1 = true;
}
