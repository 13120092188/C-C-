#pragma once
#include <iostream>
#include <string>

using namespace std;

class Block
{
public:
	Block();
	Block(int num, int type, string photo_name);
	~Block();
	bool get_appear() { return appear1; }
	bool get_choose() { return choose; }
	int get_x() { return x; }
	int get_y() { return y; }
	int get_num() { return num; }
	int get_type() { return type; }
	string get_photo_name() { return photo_name; }
	void set_photo_name(string name) { photo_name = name; }
	void set_choose();
	void set_appear(bool b) { appear1 = b; }
	void set_type(int t) { type = t; }
	void disappear();
	
	void set_x(int x) { this->x = x; }
	void set_y(int y) { this->y = y; }

private:
	int num;
	bool appear1 = 0;
	bool choose = 0;
	int x;
	int y;
	int type;
	string photo_name;
};

