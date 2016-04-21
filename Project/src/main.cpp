#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;



class realm
{
public:
	realm(string charm, vector <int> magi);

private:
	string charm;
	vector <int> magi;
	vector <int> gems;
};

struct edge
{
	realm *from;
	realm *to;
	int weight;
};

realm::realm(string charm, vector <int> magi):charm(charm),magi(magi){
	//LIS to get gems
}



class graph
{
public:
	graph(int v, vector<realm> realms);
	void dist(realm u, realm v);
private:
	int vertices;
	list<edge> *adj;
	vector<realm> realms;
};

graph::graph(int v, vector<realm> realms):vertices(v),realms(realms){
	this->adj = NULL;
}

void graph::dist(realm u, realm v){

}


int main()
{
	int numrealms, nummagi, power;
	string charm, currcharm, destcharm;
	vector <int> vec;
	vector <realm> realms;

	cin >> numrealms;

	for(int i = 0; i < numrealms; i++)
	{
		realm r;
		cin >> charm;
		cin >> nummagi;

		for(int j = 0; j < nummagi; j++)
		{
			cin >> power;
			vec.push_back(power);
		}
		r.realm(charm,vec);
		realms.push_back(r);
	}

	cin >> currcharm;
	cin >> destcharm;
}
