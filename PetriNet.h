#pragma once
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
class PetriNet
{
public:
	vector<Place> Places;
	vector<Transition> Transitions;
	vector<Edge> Edges;
public:
	PetriNet();
	~PetriNet();
	vector<Place>getPlaces();
	vector<Transition>getTransition();
	vector<Edge>getEdge();
	void AfficherPlaces();
	void AfficherTransition();
};

