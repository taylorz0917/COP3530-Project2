#include <iostream>
#include <cmath>
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
	int maxinc;
};

realm::realm(string charm, vector <int> magi):charm(charm),magi(magi){
	vector<int> temp(magi.size()),b;
	int s,d;

	if(magi.empty()) return;

	b.push_back(0);

	for(unsigned int i = 0; i< magi.size(); i++)
	{
		if(magi[b.back()] < magi[i])
		{
			temp[i] = b.back();
			b.push_back(i);
			continue;
		}
		for(s = 0, d = b.size()-1; s<d;)
		{
			int c = (s + d)/2;
			if(magi[b[c]] < magi[i])
				s=c++;
			else
				d = c;
		}
		if (magi[i] < magi[b[s]])
		{
			if(s > 0)
				temp[i] = b[s-1];
			b[s] = i;
		}
	}
	for(s = b.size(), d = b.back(); s--; d = temp[d])
			b[s] = d;
	for(unsigned int i = 0; i< b.size(); i++)
	{
		cout << b[i] << endl;
	}
		this->maxinc = b.size();
}

struct edge
{
	realm *from;
	realm *to;
	int weight;
};

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
	vector <realm*> realms;

	cin >> numrealms;

	for(int i = 0; i < numrealms; i++)
	{
		cin >> charm;
		cin >> nummagi;

		for(int j = 0; j < nummagi; j++)
		{
			cin >> power;
			vec.push_back(power);
		}
		realm *r = new realm(charm, vec);
		realms.push_back(r);
	}

	cin >> currcharm;
	cin >> destcharm;
}
