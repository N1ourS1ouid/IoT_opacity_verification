#include "Place.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;
Place::Place()
{
	id = "";
	name = "";
	marking = 0;
}
Place::Place(string a, string b,int c) 
{
	id = a;
	name = b;
	marking = c;
}
string Place::getId()
{
	return id;
}
string Place::getName()
{
	return name;
}
int Place::getMarking()
{
	return marking;
}
void Place::setId(string id)
{
	id = id;
}
void Place::setName(string name)
{
	name = name;
}
void Place::setMarking(int m)
{
	marking = m;
}
Place::~Place()
{}