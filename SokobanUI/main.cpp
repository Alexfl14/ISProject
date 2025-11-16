#include <iostream>
#include "include/GUI_View.h"
#include <Position.h>
using namespace std;
int main()
{
	Position pos (0, 0);
	cout << pos.getCol() << ", " << pos.getRow() << endl;
	return 0;
}