#if !defined (SCALEINFO_H)
#define SCALEINFO_H

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class ScaleInfo
{
	private:
	
		char* scaleLetters;
		string* scaleNums;
		string getVal(int idx);
		bool compVal(string s1, string s2);
		int* _nums;
		int size;
		
	public:
	
		ScaleInfo();
		~ScaleInfo();
		void addScaleNums();

		char* getScaleLetters();
		int* getScaleNums();
	
};

ScaleInfo::ScaleInfo()
{
	size = 5;
	scaleLetters = new char[size];
	scaleNums = new string[size - 1];
	_nums = new int[size - 1];
	
	scaleLetters[0] = 'A';
	scaleLetters[1] = 'B';
	scaleLetters[2] = 'C';
	scaleLetters[3] = 'D';
	scaleLetters[4] = 'F';
}

ScaleInfo::~ScaleInfo()
{
	delete[] scaleLetters;
	delete[] scaleNums;
	delete[] _nums;
}

void ScaleInfo::addScaleNums()
{
	string val = getVal(0);
	scaleNums[0] = val;
	
	for(int i = 1; i < 4; i++)
	{
		val = getVal(i);
		bool comp = compVal(scaleNums[i-1],val);
		while(comp)
		{
			cout << "\n	**Invalid input!\n\n";
			val = getVal(i);
			comp = compVal(scaleNums[i-1],val);
		}
		scaleNums[i] = val;
	}
	
}

string ScaleInfo::getVal(int idx)
{
	string val = "";
	cout << "\n\r What's the lowest grade to get a(n) '" << scaleLetters[idx] << "'? : ";
	cin >> val;
	return val;
}

bool ScaleInfo::compVal(string s1, string s2)
{
	if(atoi(s1.c_str()) <= atoi(s2.c_str())) 
		return true;
	else
		return false;
}

int* ScaleInfo::getScaleNums()
{
	int* sn = new int[size-1];
	for(int i = 0; i < size - 1; i++)
	{
		_nums[i] = atoi(scaleNums[i].c_str());
		sn[i] = _nums[i];
	}
	return sn;
}

char* ScaleInfo::getScaleLetters()
{
	char* si = new char[size];
	for(int i = 0; i < size; i++)
	{
		si[i] = scaleLetters[i];
	}
	return si;
}


#endif