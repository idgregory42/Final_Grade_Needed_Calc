#include "Grades.h"

#include <iostream>
using namespace std;
int main()
{
	Grades* si = new Grades();
	si->getCatInfo();
	cout << endl;
	system("pause");
	delete si;
	return 0;
}