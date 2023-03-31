#include "PetriNet.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include"Place.h"
#include"Transition.h"
#include"Edge.h"
using namespace std;
PetriNet::PetriNet(){}
PetriNet::~PetriNet(){}
vector<Place> PetriNet::getPlaces()
{
	return Places;
}
vector<Transition> PetriNet::getTransition()
{
	return Transitions;
}
vector<Edge> PetriNet::getEdge()
{
	return Edges;
}
void PetriNet::AfficherPlaces()
{
	int length = Places.size();
	for (int i = 0; i < length; i++)
	{
		cout << Places[i].getId() << endl;
	}
}
void PetriNet::AfficherTransition()
{
	int length = Transitions.size();
	for (int i = 0; i < length; i++)
	{
		cout << Transitions[i].getName() << endl;
	}
}