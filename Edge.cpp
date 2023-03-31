#include "Edge.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include<string>
using namespace std;
Edge::Edge()
{
	id = "";
	source = "";
	target = "";
	inscription = 0;
}
Edge::Edge(string a, string b, string c, int d)
{
	id = a;
	source = b;
	target = c;
	inscription = d;
}
Edge::~Edge(){}
string Edge::getId()
{
	return id;
}
string Edge::getSource()
{
	return source;
}
string Edge::getTarget()
{
	return target;
}
int Edge::getInscription()
{
	return inscription;
}
void Edge::setId(string id)
{
	id = id;
}
void Edge::setSource(string source)
{
	source = source;
}
void Edge::setTarget(string target)
{
	target = target;
}
void Edge::setInscription(int i)
{
	inscription = i;
}