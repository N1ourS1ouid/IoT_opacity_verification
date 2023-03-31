#pragma once
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include<string>
using namespace std;
class Edge
{
private:
	string id;
	string source;
	string target;
	int inscription;
public:
	Edge();
	Edge(string, string, string, int);
	~Edge();
	string getId();
	string getSource();
	string getTarget();
	int getInscription();
	void setId(string);
	void setSource(string);
	void setTarget(string);
	void setInscription(int);
	
	
};

