#pragma once
#include<string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;
class Transition
{	private:
		string id;
		string name;
	public:
		Transition();
		Transition(string, string);
		~Transition();
		string getId();
		string getName();
		void setId(string);
		void setName(string);
};

