#if !defined (GRADES_H)
#define GRADES_H

#include "ScaleInfo.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <numeric>
#include <iomanip>
using namespace std;

class Grades
{
	private:
	
		ScaleInfo* si;
		vector<double>* w;
		vector<double>* p;
		vector<double>* catG;
		vector<double>* temp;
		vector<double>* gradeNeeded;
		vector<int>* scaleVals;
		vector<char>* scale;
		double currPer;
		double possible;
		double finalW;
	
	public:
	
		Grades();
		~Grades();
		//void catAmt();
		int getCatAmount();
		void getCatInfo();
		double getPer(string c);
		double sumW();
		int numSub(string c);
		double subGrade(int idx, string c);
		void copySN();
		void calcThat();
	
};

Grades::Grades()
{
	si = new ScaleInfo();
	gradeNeeded = new vector<double>();
	w = new vector<double>();
	p = new vector<double>();
	catG = new vector<double>();
	temp = new vector<double>();
	scaleVals = new vector<int>();
	scale = new vector<char>();
	
	scale->push_back('A');
	scale->push_back('B');
	scale->push_back('C');
	scale->push_back('D');
	scale->push_back('F');
	currPer = 0.0;
	possible = 0.0;
	finalW = 0.0;
	si->addScaleNums();
}
Grades::~Grades()
{
	delete si;
	

	w->clear();
	delete w;
	
	p->clear();
	delete p;
	
	catG->clear();
	delete catG;
	
	temp->clear();
	delete temp;
	gradeNeeded->clear();
	delete gradeNeeded;
	scaleVals->clear();
	delete scaleVals;
	scale->clear();
	delete scale;
}

int Grades::getCatAmount()
{
	string c = "";
	cout << "\n\r * How many grading categories do you have(Do not include the final exam)? : ";
	cin >> c;
	int cats = atoi(c.c_str());
	while(cats < 0)
	{
		cout << "\n**Invalid input!\n";
		cout << "\n	* How many grading categories do you have(Do not include the final exam)? : ";
		cin >> c;
		cats = atoi(c.c_str());
	}
	return cats;
}

void Grades::getCatInfo()
{
	int amt = getCatAmount();
	string s = "";
	for(int i = 0; i < amt; i++)
	{
		cout << "\n	~~ What is the name of category No." << i + 1 << "? : ";
		cin >> s;
		currPer = getPer(s);
		int sub = numSub(s);
		for(int j = 1; j <= sub; j++)
		{
			catG->push_back(subGrade(j, s));
		}
		int sum = accumulate(catG->begin(),catG->end() ,0.0);
		catG->clear();
		double wt = w->at(i) * sum;
		p->push_back(wt);
	}
	double t = sumW();
	finalW = 1 - t;
	possible = t * 100;
	copySN();
	calcThat();
}

double Grades::getPer(string c)
{
	string s = "";
	cout << "	~~ What is the weight of your " << c << "(s)? : ";
	cin >> s;
	double f = atof(s.c_str());
	while(f >= 100 || f <= 0)
	{
		cout << "\n**Invalid Input\n";
		cout << "	~~ What is the weight of your " << c << "(s)? : ";
		cin >> s;		
		f = atof(s.c_str());
	}
	double z = f / 100;
	w->push_back(z);
	return z;
}

double Grades::sumW()
{
	return accumulate(w->begin(), w->end(), 0.0);
}

int Grades::numSub(string c)
{
	string s = "";
	cout << "\n	* How many " << c << "(s) did you have? : ";
	cin >> s;
	int i = atoi(s.c_str());
	while(i <= 0)
	{
		cout << "\n**Invalid Input\n";
		cout << "	* How many " << c << "(s) did you have? : ";
		cin >> s;
		i = atoi(s.c_str());
	}
	return i;
}

double Grades::subGrade(int idx, string c)
{
	string s = "";
	cout << "	** What grade did you recieve for " << c << " No." << idx << "? : ";
	cin >> s;
	double f = atof(s.c_str());
	while(f < 0)
	{
		cout << "\n**Invalid Input\n";
		cout << "	** What grade did you recieve for " << c << " No." << idx << "? : ";
		cin >> s;
		f = atof(s.c_str());
	}
	return f;
}

void Grades::copySN()
{
	int* s = si->getScaleNums();
	for(int i = 0; i < 4; i++)
	{
		scaleVals->push_back(s[i]);
	}
	delete s;
}

void Grades::calcThat()
{
	double points = accumulate(p->begin(), p->end(), 0.0);
	cout << "***************************************************************\n";
	for(int i = 0; i < 5; i++)
	{
		if(i == 4)
		{
			cout << "**  ~ Final exam score needed for a(n) '" << scale->at(i) << "' : less than " << setprecision(2)<< fixed <<gradeNeeded->at(i-1) << "%"<<endl;
				cout << "***************************************************************\n";
			return;
		}
		gradeNeeded->push_back((scaleVals->at(i) - points)/finalW);
		cout << "**  ~ Final exam score needed for a(n) '" << scale->at(i) << "' : " << setprecision(2) <<fixed <<gradeNeeded->at(i) << "%"<<endl;

	}

}


#endif