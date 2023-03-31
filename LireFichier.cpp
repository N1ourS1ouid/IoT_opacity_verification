// LireFichier.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "json/json.h"
#include"Place.h"
#include"Transition.h"
#include"Edge.h"
#include"PetriNet.h"
#include"tinyxml.h"
#include"tinystr.h"
#include"tinyxml.cpp"
#include"tinystr.cpp"
#include"tinyxmlerror.cpp"
#include"tinyxmlparser.cpp"

using namespace std;
bool verifex(string n)
{
	for (int i = 0; i < n.length(); i++)
	{
		if (n[i]=='!')
		{
			return true;
		}
	}
	return false;
}

vector<string> Listsec(const char* f)
{
	std::ostringstream stream;
	std::string str;
	std::string text;
	std::ifstream fichier(f);
	while (std::getline(fichier, str)) //--edit.
		text = text + str;
	//std::cout << text; 
	Json::CharReaderBuilder builder;
	Json::CharReader* reader = builder.newCharReader();

	Json::Value root;
	string errors;

	bool parsingSuccessful = reader->parse(text.c_str(), text.c_str() + text.size(), &root, &errors);


	if (!parsingSuccessful)
	{
		cout << text << endl;
		cout << errors << endl;
	}
	vector<string> v;
	for (int i = 0; i < root.size()-1; i++)
	{
		string name = root[i]["name"].asCString();
		string id = root[i]["id"].asCString();
		string type = root[i]["type"].asCString();
		if (verifex(name))
		{
			if (type._Equal("link out"))
			{
				v.push_back("Pfin");
			}
			if (type._Equal("link in"))
			{
				v.push_back("P1"+to_string(i));
			}
			if (type._Equal("inject"))
			{
				v.push_back("P1" + to_string(i));
			}
			if (type._Equal("function"))
			{
				v.push_back("msg1" + to_string(i));
			}
		
		}
	}
	return v;
}
vector<string> Listeobs(const char* f)
{
	std::ostringstream stream;
	std::string str;
	std::string text;
	std::ifstream fichier(f);
	while (std::getline(fichier, str)) //--edit.
		text = text + str;
	//std::cout << text; 
	Json::CharReaderBuilder builder;
	Json::CharReader* reader = builder.newCharReader();

	Json::Value root;
	string errors;

	bool parsingSuccessful = reader->parse(text.c_str(), text.c_str() + text.size(), &root, &errors);


	if (!parsingSuccessful)
	{
		cout << text << endl;
		cout << errors << endl;
	}
	vector<string> v;
	for (int i = 0; i < root.size(); i++)
	{
		string type = root[i]["type"].asCString();
		string id = root[i]["id"].asCString();
		if ((type._Equal("link in"))|| (type._Equal("link out")))
		{
			v.push_back("T" + id);
		}
	}
	return v;
}
bool VerifAnd(string name)
{
	for (int i = 0; i < name.length(); i++)
	{
		if (name[i] == '&')
		{
			return true;
		}
	}
	return false;
}
vector<string> ElementAnd(string s)
{
	string cl;
	vector<string>ch;
	int j = 0;
	if (VerifAnd(s))
	{
		for (int i = 0; i < s.length(); i++)
		{
			if ( (s[i] != '&')&& (s[i] != '\n'))
			{
				cl = cl + s[i];
			}
			else
			{
				ch.push_back(cl);
				j = j + 1;
				cl = "";
			}
		}
		ch.push_back(cl);
		j = j + 1;
		cl = "";
		
     }
	return ch;
}
bool VerifType(string id,string type,const char* f)
{
	std::ostringstream stream;
	std::string str;
	std::string text;
	std::ifstream fichier(f);
	while (std::getline(fichier, str)) //--edit.
		text = text + str;
	//std::cout << text; 
	Json::CharReaderBuilder builder;
	Json::CharReader* reader = builder.newCharReader();

	Json::Value root;
	string errors;

	bool parsingSuccessful = reader->parse(text.c_str(), text.c_str() + text.size(), &root, &errors);


	if (!parsingSuccessful)
	{
		cout << text << endl;
		cout << errors << endl;
	}
	for (int i = 0; i < root.size(); i++)
	{
		if ((root[i]["id"]==id)&& (root[i]["type"]==type))
		{
			return true;
		}
	}
	return false;

}
string ReturnCode(string id)
{
	std::ostringstream stream;
	std::string str;
	std::string text;
	std::ifstream fichier("flux.txt");
	while (std::getline(fichier, str)) //--edit.
		text = text + str;
	//std::cout << text; 
	Json::CharReaderBuilder builder;
	Json::CharReader* reader = builder.newCharReader();

	Json::Value root;
	string errors;

	bool parsingSuccessful = reader->parse(text.c_str(), text.c_str() + text.size(), &root, &errors);


	if (!parsingSuccessful)
	{
		cout << text << endl;
		cout << errors << endl;
	}
	for (int i = 0; i < root.size(); i++)
	{
		string d = root[i]["id"].asCString();
		string t = root[i]["type"].asCString();
		if((d==id) && (t=="function"))
		{
			string s = root[i]["func"].asCString();
			return s;
		}
	}
	return "non";
	
}
vector<string> Positionif(string name)
{
	vector <string> v;
	int a = 0;
	string cl;
	vector<string>ch;
	int j = 0;
	for (int i = 0; i < name.length(); i++)
	{
		if ((name[i] != ' ' && (name[i] != '\0') && (name[i] != '\n')))
		{
			cl = cl + name[i];
		}
		else
		{
			ch.push_back(cl);
			j = j + 1;
			cl = "";
		}
	}
	ch.push_back(cl);
	j = j + 1;
	cl = "";
	int k = 0;
	for (int i = 1; i <ch.size(); i++)
	{
		if ((ch[i-1] == "if")|| (ch[i-1] == "elseif"))
		{
			v.push_back(ch[i]);
		}
	}
	return v;
}
int Nombrereturn(string name)
{
	int a = 0;
	string cl;
	vector<string>ch;
	int j = 0;
	for (int i = 0; i < name.length(); i++)
	{
		if ((name[i] != ' ' && (name[i] != '\0') && (name[i] != '\n')))
		{
			cl = cl + name[i];
		}
		else
		{
			ch.push_back(cl);
			j = j + 1;
			cl = "";
		}
	}
	ch.push_back(cl);
	j = j + 1;
	cl = "";
	for (int i = 0; i < ch.size(); i++)
	{
		if (ch[i] == "return")
		{
			a = a + 1;
		}
	}
	return a;
}
vector <string> listevoisin(string name)
{
	string cl;
	vector<string>ch;
	int j = 0;
	for (int i = 0; i < name.length(); i++)
	{
		if ((name[i] != ' ') && (name[i] != '\0') && (name[i] != '\n') && (name[i] != '[') && (name[i] != ']') && (name[i] != '\t') && (name[i] != '"'))
		{
			cl = cl + name[i];
		}
		else
		{
			ch.push_back(cl);
			j = j + 1;
			cl = "";
		}
	}
	ch.push_back(cl);
	j = j + 1;
	cl = "";
	vector<string> v;
	for (int i = 0; i < ch.size(); i++)
	{
		if ((!ch[i].empty())&&(ch[i]!="\t") && (ch[i] != ","))
		{
			v.push_back(ch[i]);

		}
	}
	return v;
}
vector<string> afficheResultat(string name)
{
	string cl;
	vector<string>ch;
	int j = 0;
	for (int i = 0; i < name.length(); i++)
	{
		if ((name[i] != ' ' && (name[i] != '\0') && (name[i] != '\n')))
		{
			cl = cl + name[i];
		}
		else
		{
			ch.push_back(cl);
			j = j + 1;
			cl = "";
		}
	}
	ch.push_back(cl);
	j = j + 1;
	cl = "";
	vector<string>result;
	for (int i = 1; i < ch.size(); i++)
	{
		if (ch[i-1] == "return")
		{
			result.push_back(ch[i]);
		}
	}
	return result;
}
vector<string> ChangerListe(string liste)
{
	string cl;
	vector<string>ch;
	int j = 0;
	for (int i = 0; i < liste.length(); i++)
	{
		if ((liste[i] != ' ' && (liste[i] != '\0') && (liste[i] != '\n')&& (liste[i] != '[')&& (liste[i] != ']')&& (liste[i] != ',')))
		{
			cl = cl + liste[i];
		}
		else
		{
			ch.push_back(cl);
			j = j + 1;
			cl = "";
		}
	}
	ch.push_back(cl);
	j = j + 1;
	cl = "";
	return ch;
}
void Relier(int i, PetriNet petrinet, vector <string> L,const char* f)
{
	std::ostringstream stream;
	std::string str;
	std::string text;
	std::ifstream fichier(f);
	while (std::getline(fichier, str)) //--edit.
		text = text + str;
	//std::cout << text; 
	Json::CharReaderBuilder builder;
	Json::CharReader* reader = builder.newCharReader();

	Json::Value root;
	string errors;

	bool parsingSuccessful = reader->parse(text.c_str(), text.c_str() + text.size(), &root, &errors);


	if (!parsingSuccessful)
	{
		cout << text << endl;
		cout << errors << endl;
	}

	string gf = root[i]["type"].asCString();
	if (gf._Equal("inject"))
	{
		petrinet.Places.push_back(Place("Pinject" + to_string(i), "Pinject" + to_string(i), 0));
		cout << "done relier inject" << endl;
		petrinet.Edges.push_back(Edge("Einject" + to_string(i), root[i]["id"].asCString(), "Pinject" + to_string(i), 1));
		cout << "done arc inject" << endl;
		for (int j = 0; j < L.size(); j++)
		{
			//cout << ReturnCode(L[j]) << endl;
			if ((VerifType(L[j], "function",f)) && ((Nombrereturn(ReturnCode(L[j])) > 1)))
			{
				string pay = root[i]["payload"].asCString();
				cout << pay << endl;
				string s = ReturnCode(L[j]);
				vector<string> Q = Positionif(s);
				for (int k = 0; k < Q.size(); k++)
				{
					if (Q[k] == "msg.payload==" + pay)
					{
						petrinet.Edges.push_back(Edge("Einject" + to_string(k) + to_string(j), "Pinject" + to_string(k), root[i]["id"].asCString() + to_string(j), 1));
					}
					else
					{
						cout << "hhhhhhhh" << endl;
					}
				}

			}
			else if ((VerifType(L[j], "function",f)) && ((Nombrereturn(ReturnCode(L[j])) == 1)))
			{
				petrinet.Edges.push_back(Edge("Einject" + to_string(i), "Pinject" + to_string(i), root[i]["id"].asCString(), 1));
				cout << "done edge inject fonction" << endl;
			}
			/*else if ((VerifType(L[i], "mysql") || (VerifType(L[i], "MySQLdatabase"))))
			{
				for (int v = 0; v < root.size(); v++)
				{
					if (root[v]["id"].asCString() == L[i])
					{
						string c = root[3]["wires"].toStyledString();
						vector <string> v;
						for (int i = 0; i < listevoisin(c).size(); i++)
						{
							v.push_back(listevoisin(c)[i]);
						}
						//Relier(k, petrinet, v);
					}

				}

			}
			else
			{
				petrinet.Edges.push_back(Edge("Einject" + to_string(k), "Pinject" + to_string(k), L[0], 1));
			}
		}

	}
	else if (root[k]["type"].asCString() == "function")
	{
		string ch = ReturnCode(root[k]["func"].asCString());
		if (Nombrereturn(ch) > 1)
		{
			for (int i = 0; i < L.size(); i++)
			{
				petrinet.Edges.push_back(Edge("Efonction" + to_string(i), "msg" + to_string(i), L[i], 1));
			}

		}
		else
		{
			petrinet.Edges.push_back(Edge("Efonction", root[k]["id"].asCString(), L[0], 1));
		}*/
		}
	}

}
vector<vector<string>> SupprimerMysql(const char * f)
{
	std::ostringstream stream;
	std::string str;
	std::string text;
	std::ifstream fichier(f);
	while (std::getline(fichier, str)) //--edit.
		text = text + str;
	//std::cout << text; 
	Json::CharReaderBuilder builder;
	Json::CharReader* reader = builder.newCharReader();

	Json::Value root;
	string errors;

	bool parsingSuccessful = reader->parse(text.c_str(), text.c_str() + text.size(), &root, &errors);


	if (!parsingSuccessful)
	{
		cout << text << endl;
		cout << errors << endl;
	}
	vector<vector<string>> v;
	for (int i = 0; i < root.size(); i++)
	{
		string c = root[i]["wires"].toStyledString();
		vector <string> L = listevoisin(c);
		for (int j = 0; j < L.size(); j++)
		{
			//cout << ReturnCode(L[j]) << endl;
			if (VerifType(L[j], "mysql",f))
			{
				string h = L[j];
				L.erase(L.begin() + j);
				for (int k = 0; k < root.size(); k++)
				{
					string id = root[k]["id"].asCString();
					if (id==h)
					{
						string ff = root[k]["wires"].toStyledString();
						vector <string> s = listevoisin(ff);
						for (int u = 0; u < s.size(); u++)
						{
							L.push_back(s[u]);
						}
					}
				}
				
			}
		}
		v.push_back(L);
	}
	return v;
}

int main(int argc, char** argv)
{
	std::ostringstream stream;
	std::string str;
	std::string text;
	std::ifstream fichier(argv[1]);
	while (std::getline(fichier, str)) //--edit.
		text=text+str;
	//std::cout << text; 
	Json::CharReaderBuilder builder;
	Json::CharReader* reader = builder.newCharReader();

	Json::Value root;
	string errors;

	bool parsingSuccessful = reader->parse(text.c_str(), text.c_str() + text.size(), &root, &errors);


	if (!parsingSuccessful)
	{
		cout << text << endl;
		cout << errors << endl;
	}
	int x = root.size();
	std::cout << x << endl;
	cout << Nombrereturn(ReturnCode(root[3]["id"].asCString()));
	/*string ff = root[5]["wires"].toStyledString();
	vector <string> ghe = listevoisin(ff);
	for (int j = 0; j < ghe.size(); j++)
	{
		//cout << ReturnCode(L[j]) << endl;
		cout<<"mysql"<<(VerifType(ghe[j], "mysql"))<<endl;
	}*/

	//cout << root[3]["id"].asCString()<<endl;
	//string fd = ReturnCode("f1d5051f.d2ed48");
	//cout << fd << endl;
	vector<vector<string>> sanssql = SupprimerMysql(argv[1]);
	//vector<string> cv = sanssql[5];
	//cout <<"el supprimer"<< cv.size() << endl;
	/*for (int i = 0; i < cv.size(); i++)
	{
		cout << cv[i] << endl;
	}
	string f = "rimez&&hattab";
	int nbo = 0;
	/*for (int i = 0; i <f.size(); i++)
	{
		cout << f[i] << endl;
	}*/
	//cout << nbo << endl;
	//cout << f[25] << endl;
	/*cout<<VerifAnd(f)<<endl;
	cout << ElementAnd(f).size() << endl;
	//cout << ElementAnd(f)[0] << endl;
	for (int i = 0; i < ElementAnd(f).size(); i++)
	{
		cout << ElementAnd(f)[i]<<endl;
	}
	//string c = afficheResultat(root[3]["func"].asCString())[1];
	/*vector<Json::Value> results;
	for (int i = 0; i < root[3]["wires"].size(); i++)
	{
		results.push_back(root[3]["wires"][i]);
	}
	for (int i = 0; i < results.size(); i++)
	{
		cout << results[i].asCString();
	}*/
	/*string cb = root[3]["id"].asCString();
	cout << VerifType(cb,"function")<<endl;
	string c = root[3]["wires"].toStyledString();
	vector <string> v = listevoisin(c);
	//cout << v << endl;
	for (int i = 0; i < v.size(); i++)
	{
		cout <<v[i] << endl;
	}
	//cout << c << endl;
	string cn = root[3]["func"].asCString();
	vector<string> result = Positionif(cn);
	cout << result[0] << endl;
	vector<string> w = ElementAnd(result[0]);
	for (int i = 0; i < w.size(); i++)
	{
		cout << w[i] << endl;
	}
	for (int i = 0; i < result.size(); i++)
	{
		cout << result[i] << endl;
	}*/
	PetriNet petrinet;
	Place Pint = Place("P0", "P0", 1);
	int markagefinale = 0;
	for (int i = 0; i < x; i++)
	{
		string strc = root[i]["type"].asCString();
		if ((strc._Equal("debug"))|| (strc._Equal("link out")))
		{
			markagefinale++;
		}

	}
	Place Pfin = Place("Pfin", "Pfin", markagefinale);
	Transition Tbig = Transition("Tbig", "Tbig");
	Edge edge =Edge("E1", Pint.getId(), Tbig.getId(), 1);
	petrinet.Places.push_back(Pint);
	petrinet.Places.push_back(Pfin);
	petrinet.Transitions.push_back(Tbig);
	petrinet.Edges.push_back(edge);

	for (int i = 0; i < x; i++)
	{
		string id = root[i]["id"].asCString();
		string strc = root[i]["type"].asCString();
		if (strc._Equal("inject"))
		{
			string id = root[i]["id"].asCString();
			string name = 'P' + to_string(i);
			Place place = Place("P"+id,name,0);
			petrinet.Places.push_back(place);
			string nametran = 'T' + to_string(i);
			Transition transition = Transition("T"+id, nametran);
			petrinet.Transitions.push_back(transition);
			petrinet.Edges.push_back(Edge('E' + to_string(i), Tbig.getId(), "P"+ id, 1));
			//cout << "done" << endl;
			petrinet.Edges.push_back(Edge("E2" + to_string(i), "P"+ id, "T"+ id, 1));
			//cout << "done" << endl;
        }

		else if (strc._Equal("debug"))
		{
			string id = root[i]["id"].asCString();
			petrinet.Transitions.push_back(Transition("T"+ id, "Tdeb" + to_string(i)));
			//cout << "done debug" << endl;
			petrinet.Edges.push_back(Edge("E" + to_string(i), "T"+ id, Pfin.getId(), 1));
			//cout << "done arc debug" << endl;

		}
		else if (strc._Equal("function"))
		{
			string id = root[i]["id"].asCString();
			string code = root[i]["func"].asCString();
			/*for (int i = 0; i < afficheResultat(code).size(); i++)
			{
				cout<< afficheResultat(code)[i];
			}*/
			
			int n=Nombrereturn(code);
			//cout << n << endl;
			for (int j = 0; j < n; j++)
			{
				petrinet.Transitions.push_back(Transition("T" +id+to_string(j), 'T'+ to_string(i)+ to_string(j)));
				//cout << "done fonction"<<endl;
			}
			int nbplace = root[i]["outputs"].asInt();
			for (int j = 0; j < nbplace; j++)
			{
				petrinet.Places.push_back(Place("msg" + to_string(j+1)+ to_string(i), "msg" + to_string(j+1), 0));
				//cout << "done place fonction";
			}
			for (int y = 0; y < afficheResultat(code).size(); y++)
			{
				string s= afficheResultat(code)[y];
				vector<string> h = ChangerListe(s);
				for (int g = 0; g < h.size(); g++)
				{
					if ((h[g] != "null") && (!h[g].empty()))
					{
						petrinet.Edges.push_back(Edge("ET" + to_string(i) + to_string(g), "T"+ id+ to_string(y), "msg"+to_string(g+1) + to_string(i), 1));
						cout << "ok" << endl;
					}
					
				}
				/*for (int k = 0; k < ChangerListe(s).size(); k++)
				{
					if ((ChangerListe(s)[y]!="null")&& (!ChangerListe(s)[y].empty()))
					{
						petrinet.Edges.push_back(Edge("ET"+to_string(i)+to_string(k),root[i]["id"].asCString() + to_string(i), ChangerListe(s)[i], 1));
						cout << "ok" << endl;
					}
				}*/

			}
		}
		else if (strc._Equal("link out"))
		{
			string id = root[i]["id"].asCString();
			petrinet.Transitions.push_back(Transition("T" + id, "T" + id+"!"));
			cout << "hay tzadit" << endl;
			petrinet.Edges.push_back(Edge("E1" + to_string(i), "T"+ id, Pfin.getId(), 1));
			cout << "rfbv" << endl;
		}
		else if (strc._Equal("link in"))
		{
			string id = root[i]["id"].asCString();
			petrinet.Transitions.push_back(Transition("T"+ id, "T" + id + "?"));
			cout << "hay tzadit in" << endl;
			petrinet.Places.push_back(Place("P"+ id, "P" + id, 0));
			cout << "hay tzadit place in" << endl;
			petrinet.Edges.push_back(Edge("E0" + to_string(i), Tbig.getId(), "P" + id, 1));
			petrinet.Edges.push_back(Edge("E1" + to_string(i), "P"+ id, "T"+ id, 1));
			cout << "rfbv in" << endl;
		}
		else if ((strc._Equal("decrypt"))|| (strc._Equal("encrypt"))|| (strc._Equal("encode"))|| (strc._Equal("decode")))
		{
			string id = root[i]["id"].asCString();
			petrinet.Transitions.push_back(Transition("T"+id, root[i]["id"].asCString()));
			cout << "hay tzadit decrypt" << endl;
			petrinet.Places.push_back(Place("P"+id, root[i]["id"].asCString(), 0));
			cout << "hay tzadit place decrypt" << endl;
			petrinet.Edges.push_back(Edge("EDecrypt" + to_string(i), "T"+ id, "P"+ id, 1));
			cout << "rfbv decrypt" << endl;
        }
		
	}
	//petrinet.Edges.push_back(Edge("E00", "Tbig", "Pdb210cbc.f534d", 1));//fog
	//petrinet.Edges.push_back(Edge("E14", "Tc5ad7c3b.9236f", "Pad80d547.bbff88", 1));//fog
	//petrinet.Edges.push_back(Edge("E01", "Td5837f92.ee80b", "Pfin", 1));//fog
	//petrinet.Edges.push_back(Edge("E00", "Tbig", "Pf0a861dc.79362", 1));//prive
	//petrinet.Edges.push_back(Edge("E14", "T15735ce2.0aa4e3", "P3e61b414.1bc77c", 1));
	//petrinet.Edges.push_back(Edge("E01", "Tbig", "Pc4d94dc.7d0b1b", 1));
	//petrinet.Edges.push_back(Edge("E15", "Tf25abac5.6c2eb8", "P6e5db271.2e242c", 1));
	//petrinet.Edges.push_back(Edge("E16", "Tf25abac5.6c2eb8", "P3b2afc4b.d4ce44", 1));
	//petrinet.Edges.push_back(Edge("E17", "Tf25abac5.6c2eb8", "Pef35fb1a.e55058", 1));
	//petrinet.Edges.push_back(Edge("E18", "Tf25abac5.6c2eb8", "Pa6cb34e6.01e7c8", 1));
	//petrinet.Edges.push_back(Edge("E19", "T821c70b7.f4c36", "Pfin", 1));//cprives7i7a
	//petrinet.Edges.push_back(Edge("E20", "Tlink out94af899f.a58a88", "Pfin", 1));
	//petrinet.Edges.push_back(Edge("E21", "Tlink out74cff39b.96c91c", "Pfin", 1));
	//petrinet.Edges.push_back(Edge("E22", "Tlink out2d552f9b.3cf63", "Pfin", 1));//prive
	//petrinet.Edges.push_back(Edge("E00", "Tbig", "Plink indbfe1b95.65dd68", 1));
	//petrinet.Edges.push_back(Edge("E14", "Tlink out66884040.5363e", "Plink in3ea7cc81.8882f4", 1));
	//petrinet.Edges.push_back(Edge("E00", "Tbig", "Plindb210cbc.f534d",1));//fog
	//petrinet.Edges.push_back(Edge("E14", "Toutc5ad7c3b.9236f", "Plinad80d547.bbff88", 1));//fog
	//petrinet.Edges.push_back(Edge("E17", "Toutd5837f92.ee80b", "Pfin", 1));//fog
	PetriNet pt;
	for (int i = 0; i < x; i++)
	{
		vector<string> v = sanssql[i];
		string gf = root[i]["type"].asCString();
		string ifd = root[i]["id"].asCString();
		if ((gf._Equal("inject")))
		{
			petrinet.Places.push_back(Place("P1"+ to_string(i), "P1" + to_string(i), 0));
			cout << "done relier inject" << endl;
			petrinet.Edges.push_back(Edge("E" + gf + to_string(i), "T" +ifd, "P1"+ to_string(i), 1));
			cout << "done arc inject" << endl;
			for (int j = 0; j < v.size(); j++)
			{
				//cout << ReturnCode(L[j]) << endl;
				if ((VerifType(v[j], "function", argv[1])) && ((Nombrereturn(ReturnCode(v[j])) > 1)))
				{
					cout << "hana lina" << endl;
					string pay = root[i]["payload"].asCString();
					string fdg= ReturnCode(v[j]);
					int ret = Nombrereturn(fdg);
					cout << pay << endl;
					string s = ReturnCode(v[j]);
					vector<string> Q = Positionif(s);
					for (int k = 0; k < ret; k++)
					{
						if (Q[k] == "msg.payload==" + pay)
						{
							petrinet.Edges.push_back(Edge("E" + gf + to_string(k) + to_string(j), "P"+ ifd, "T"+v[j]+ to_string(k), 1));
						}
						else
						{
							cout << "hhhhhhhh" << endl;
						}
					}

				}
				else if ((VerifType(v[j], "function", argv[1])) && ((Nombrereturn(ReturnCode(v[j])) == 1)))
				{
					petrinet.Edges.push_back(Edge("E"+gf + to_string(i) + to_string(j), "P"+ifd, "T"+v[j]+to_string(0), 1));
					cout << "done edge inject fonction" << endl;
				}
				else
				{
					petrinet.Edges.push_back(Edge("E"+gf + to_string(j), "P"+ifd, "T"+v[j], 1));
					cout << "inject cas 3" << endl;
				}


			}}
		else if (gf._Equal("link in"))
		{
			petrinet.Places.push_back(Place("P1" + to_string(i), "P1" + to_string(i), 0));
			cout << "done relier link in" << endl;
			petrinet.Edges.push_back(Edge("E" + gf + to_string(i), "T"+ ifd, "P1"+ to_string(i), 1));
			cout << "done arc lin" << endl;
			for (int j = 0; j < v.size(); j++)
			{
				//cout << ReturnCode(L[j]) << endl;
				if ((VerifType(v[j], "function", argv[1])) && ((Nombrereturn(ReturnCode(v[j])) > 1)))
				{
					cout << "hana lina" << endl;
					string fdg = ReturnCode(v[j]);
					int ret = Nombrereturn(fdg);
					//cout << pay << endl;
					string s = ReturnCode(v[j]);
					//vector<string> Q = Positionif(s);
					for (int k = 0; k < ret; k++)
					{
						petrinet.Edges.push_back(Edge("E" + gf + to_string(k) + to_string(j),"P1" + to_string(i), "T"+v[j]+ to_string(k), 1));
						/*if (Q[k] == "msg.payload==" + pay)
						{
							petrinet.Edges.push_back(Edge("E" + gf + to_string(k) + to_string(j), "P"+gf + to_string(i), "T"+v[j]+ to_string(k), 1));
						}
						else*/

						
					 cout << "hhhhhhhh" << endl;
						
					}

				}
				else if ((VerifType(v[j], "function", argv[1])) && ((Nombrereturn(ReturnCode(v[j])) == 1)))
				{
					petrinet.Edges.push_back(Edge("E" + gf + to_string(i) + to_string(j),"P1" + to_string(i), "T" + v[j]+to_string(0), 1));
					cout << "done edge inject fonction" << endl;
				}
				else
				{
					petrinet.Edges.push_back(Edge("E" + gf + to_string(j), "P1" + to_string(i), v[j], 1));
					cout << "inject cas 3" << endl;
				}


			}
		}
		else if (gf._Equal("function"))
		{
			string ch = ReturnCode(root[i]["id"].asCString());
			cout << v.size() << endl;
			for (int j = 0; j < v.size(); j++)
			{
				//cout << ReturnCode(L[j]) << endl;
				if (VerifType(v[j], "function", argv[1]))
				{
					cout << (Nombrereturn(ReturnCode(v[j]))) << endl;
					if (((Nombrereturn(ReturnCode(v[j])) == 1)) && ((Nombrereturn(ch)) > 1))
					{
						cout << Nombrereturn(ReturnCode(v[j])) << endl;
						petrinet.Edges.push_back(Edge("Efonction" + to_string(i), "msg" + to_string(j + 1)+ to_string(i), "T"+v[j] , 1));
						cout << "hamdoullah" << endl;

					}
					else if (((Nombrereturn(ReturnCode(v[j])) > 1)) && ((Nombrereturn(ch)) > 1))
					{
						for (int p = 0; p < Nombrereturn(ReturnCode(v[j])); p++)
						{
							petrinet.Edges.push_back(Edge("EFF" + to_string(i), "msg" + to_string(j + 1)+ to_string(i), "T" + v[j] + to_string(p), 1));
						}
						cout << "mala hena" << endl;
					}
					else if (((Nombrereturn(ReturnCode(v[j])) > 1)) && ((Nombrereturn(ch)) == 1))
					{
						
						for (int p = 0; p < Nombrereturn(ReturnCode(v[j])); p++)
						{
							petrinet.Edges.push_back(Edge("Efonc" + to_string(i), "msg1"+ to_string(i), "T" + v[j] + to_string(p), 1));
						}
						cout << "lina mouchkla" << endl;
					}
					else if (((Nombrereturn(ReturnCode(v[j])) == 1)) && ((Nombrereturn(ch)) == 1))
					{
						
							petrinet.Edges.push_back(Edge("Efonc" + to_string(i), "msg1"+ to_string(i), "T" + v[j] , 1));
						

					}
					
				}
				else
				{
					if (Nombrereturn(ch) > 1)
					{
							petrinet.Edges.push_back(Edge("Efonction" + to_string(j), "msg" + to_string(j + 1)+ to_string(i), "T" + v[j], 1));
							cout << "hamdoullah" << endl;

					}
					else if (Nombrereturn(ch) == 1)
					{
						petrinet.Edges.push_back(Edge("Efonction1", "msg1"+to_string(i), "T" + v[j], 1));
						cout << "haya hamdoullah" << endl;
					}

				}
				
				
					

			}



			/**/

		}

			/*string ch = ReturnCode(root[i]["id"].asCString());
			if (Nombrereturn(ch) > 1)
			{
				for (int i = 0; i < v.size(); i++)
				{
					petrinet.Edges.push_back(Edge("Efonction" + to_string(i), "msg" + to_string(i+1), "T" +v[i], 1));
					cout << "hamdoullah" << endl;
				}

			}
			else if (Nombrereturn(ch) == 1)
			{
				petrinet.Edges.push_back(Edge("Efonction1", "msg1", "T"+v[0], 1));
				cout << "haya hamdoullah" << endl;
			}*/
		//}
		else if ((gf._Equal("decrypt")) || (gf._Equal("encrypt")) || (gf._Equal("encode")) || (gf._Equal("decode")))
		{
			for (int j = 0; j < v.size(); j++)
			{
				petrinet.Edges.push_back(Edge("Ecode" + to_string(i), "P"+ ifd, "T" + v[j], 1));
				cout << "hamdoullah" << endl;
			}
		}
		
	}
	petrinet.AfficherPlaces();
	cout << petrinet.Edges[0].getId() << endl;
	//pt.AfficherTransition();
	TiXmlDocument doc1;
	TiXmlDeclaration* decl1 = new TiXmlDeclaration("1.0", "UTF-8", "");
	doc1.LinkEndChild(decl1);
	//TiXmlElement* el = new TiXmlElement("rimez");
	//doc1.LinkEndChild(el);
	TiXmlElement* element1 = new TiXmlElement("pnml");
	doc1.LinkEndChild(element1);
	element1->SetAttribute("xmlns", "http://www.pnml.org/version-2009/grammar/pnml");
	TiXmlElement* net = new TiXmlElement("net");
	element1->LinkEndChild(net);
	net->SetAttribute("id", "n-1D80-956C5-0");
	net->SetAttribute("type", "http://www.laas.fr/tina/tpn");
	TiXmlElement* page = new TiXmlElement("page");
	net->LinkEndChild(page);
	page->SetAttribute("id", "g-1808-86C77-1");
	TiXmlElement* placein = new TiXmlElement("place");
	page->LinkEndChild(placein);
	placein->SetAttribute("id", petrinet.Places[0].getId().c_str());
	TiXmlElement* markage = new TiXmlElement("initialMarking");
	placein->LinkEndChild(markage);
	TiXmlText* textm = new TiXmlText(" ");
	markage->LinkEndChild(textm);
	for (int i = 1; i < petrinet.Places.size(); i++)
	{
		TiXmlElement* place = new TiXmlElement("place");
		page->LinkEndChild(place);
		place->SetAttribute("id", petrinet.Places[i].getId().c_str());
		TiXmlText* textp = new TiXmlText(" ");
		place->LinkEndChild(textp);
		/*TiXmlElement* markage = new TiXmlElement("initialMarking");
		place->LinkEndChild(markage);
		TiXmlText* textm = new TiXmlText((to_string(petrinet.Places[i].getMarking())).c_str());
		markage->LinkEndChild(textm);*/
	}
	for (int i = 0; i < petrinet.Transitions.size(); i++)
	{
		TiXmlElement* tran = new TiXmlElement("transition");
		page->LinkEndChild(tran);
		tran->SetAttribute("id", petrinet.Transitions[i].getId().c_str());
		TiXmlText* textt = new TiXmlText(" ");
		tran->LinkEndChild(textt);
		//fich << "\t\t\t<transition id = \"" + petrinet.Transitions[i].getId() + "\" > " << endl;
		//fich << "\t\t\t\t<name><text>" + petrinet.Transitions[i].getName() + "< / text>< / name>" << endl;
		//fich << "\t\t\t< / transition>" << endl;
	}
	for (int i = 0; i < petrinet.Edges.size(); i++)
	{
		TiXmlElement* arc = new TiXmlElement("arc");
		page->LinkEndChild(arc);
		arc->SetAttribute("id", petrinet.Edges[i].getId().c_str());
		arc->SetAttribute("source", petrinet.Edges[i].getSource().c_str());
		arc->SetAttribute("target", petrinet.Edges[i].getTarget().c_str());
		TiXmlText* texta = new TiXmlText(" ");
		arc->LinkEndChild(texta);
		//fich << "\t\t\t<arc id = \"" + petrinet.Edges[i].getId() + "\" source = \"" + petrinet.Edges[i].getSource() + "\" target = \"" + petrinet.Edges[i].getTarget() + "\" > " << endl;
		//fich << "\t\t\t\t<inscription> < text>" + to_string(petrinet.Edges[i].getInscription()) + "< / text > < / inscription>" << endl;
		//fich << "\t\t\t< / arc>" << endl;
	}

	//TiXmlText* text1 = new TiXmlText("World");
	//element1->LinkEndChild(text1);
	doc1.SaveFile("C:/Users/Rimez Hattab/Desktop/rimez/3Info/PFE/Verificationopacite/test/petr.xml");
	std::ofstream fich("PetriNet1.txt");
	if (fich)
	{
		fich << "< ? xml version = \"1.0\" encoding = \"utf-8\" ? >" << endl;
		fich << "<pnml xmlns=\"http://www.pnml.org/version-2009/grammar/pnml\">" << endl;
		fich << "\t<net id=\"ERK - PT - 000001\" type=\"http://www.pnml.org/version-2009/grammar/ptnet\">" << endl;
		fich << "\t\t<page id = \"page0\">" << endl;
		fich << "\t\t\t<name><text>DefaultPage< / text>< / name>" << endl;
		for (int i = 0; i < petrinet.Places.size(); i++)
		{
			fich << "\t\t\t<place id =\"" + petrinet.Places[i].getId() + "\">" << endl;
			fich << "\t\t\t\t<name><text>" + petrinet.Places[i].getName() + "< / text>< / name>" << endl;
			fich << "\t\t\t\t<initialMarking> < text>" + to_string(petrinet.Places[i].getMarking()) + "</text></initialMarking>" << endl;
			fich << "\t\t\t< / place>" << endl;
		}
		for (int i = 0; i < petrinet.Transitions.size(); i++)
		{
			fich << "\t\t\t<transition id = \"" + petrinet.Transitions[i].getId() + "\" > " << endl;
			fich << "\t\t\t\t<name><text>" + petrinet.Transitions[i].getName() + "< / text>< / name>" << endl;
			fich << "\t\t\t< / transition>" << endl;
		}
		for (int i = 0; i < petrinet.Edges.size(); i++)
		{
			fich << "\t\t\t<arc id = \"" + petrinet.Edges[i].getId() + "\" source = \"" + petrinet.Edges[i].getSource() + "\" target = \"" + petrinet.Edges[i].getTarget() + "\" > " << endl;
			fich << "\t\t\t\t<inscription> < text>" + to_string(petrinet.Edges[i].getInscription()) + "< / text > < / inscription>" << endl;
			fich << "\t\t\t< / arc>" << endl;
		}
		fich << "\t\t< / page>" << endl;
		fich << "</net>" << endl;
		fich << "< / pnml>" << endl;
			
			
			

			
	}
	else
	{
		cout << "il y a un problème";
	}
	vector<string> ob=Listeobs(argv[1]);
	std::ofstream fichi("C:/Users/Rimez Hattab/Desktop/rimez/3Info/PFE/Verificationopacite/test/ob.txt");
	fichi << ob.size() << endl;
	for (int i = 0; i < ob.size()-1; i++)
	{
		fichi << ob[i]+" ";
	}
	fichi << ob[ob.size() - 1];
	cout << verifex("Rimez!!") << endl;
	vector <string>sec = Listsec(argv[1]);
	std::ofstream fichii("C:/Users/Rimez Hattab/Desktop/rimez/3Info/PFE/Verificationopacite/test/sec.txt");
	for (int i = 0; i < sec.size(); i++)
	{
		fichii << 1<<endl;
		fichii << sec[i] << endl;

	}
	std::ofstream fic("C:/Users/Rimez Hattab/Desktop/rimez/3Info/PFE/Verificationopacite/test/Choix.txt");
	fic << 0;
	delete reader;
	}
