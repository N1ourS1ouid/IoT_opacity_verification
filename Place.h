#pragma once
#include<string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;
class Place
{
private:
	string id;
	string name;
	int marking;
public:
	Place();
	~Place();
	Place(string, string,int);
	string getId();
	string getName();
	int getMarking();
	void setId(string);
	void setName(string);
	void setMarking(int);
};

