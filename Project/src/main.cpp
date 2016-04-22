#include <iostream>
#include <cmath>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;



class realm
{
public:
	realm(string charm, vector <int> magi);
	string charm;

private:
	vector <int> magi;
	vector <int> gems;
	int maxinc;
};

realm::realm(string charm, vector <int> magi):charm(charm),magi(magi){
	
	vector<int> b, temp(magi.size());
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
				s=1+c;
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
		cout << magi[b[i]] << endl;
	}
		this->maxinc = b.size();
}

struct edge
{
	realm *from;
	realm *to;
	int weight;
	
	edge(from, to, weight): from(from), to(to), weight(weight){}
};

class graph
{
public:
	graph(int v, vector<realm> realms);
	int dist(string u, string v);
	void edge(int dist, realm s, realm d);
private:
	int vertices;
	list<edge> *adj;
	vector<realm> realms;
};

graph::graph(int v, vector<realm> realms):vertices(v),realms(realms){
	this->adj = NULL;
}

void graph:edge(int dist, realm s, realm d)
{
	edge e = new edge(s, d, dist);
	//cout << e->from << " " << e->to << " " << e->weight << endl; 
}

int graph::dist(string u, string v)
{
	int n = u.length();
	int m = v.length();
	
	int matrix[n+1][m+1];
	
	for(int i = 0; i<= n; i++){
		for(int j = 0; j<=m; j++){
					
			if(i == 0)
			{
				matrix[i][j] = j;
			}
			else if(j ==0)
			{
				matrix[i][j] = i;
			}
			else if( u[i-1] == v[j-1])
			{
				matrix[i][j] = matrix[i-1][j-1];
			}
			else
			{
				int min1 = min(matrix[i][j-1],matrix[i-1][j]);
				int min2 = min(matrix[i-1][j-1],matrix[i-1][j]);
				min1 = min(min1,min2);
				matrix[i][j] = 1+ min1;	
			}
		}
	}
		return matrix[n][m];
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
