#include "Transition.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;
Transition::Transition()
{
	id = "";
	name = "";
}
Transition::Transition(string idi, string namee)
{
	id = idi;
	name = namee;
}
Transition::~Transition(){}
string Transition::getId()
{
	return id;
}
string Transition::getName()
{
	return name;
}
void Transition::setId(string id)
{
	id = id;
}
void Transition::setName(string name)
{
	name = name;
}