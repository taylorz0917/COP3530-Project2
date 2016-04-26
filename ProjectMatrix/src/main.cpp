#include <iostream>
#include <cmath>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <limits.h>

using namespace std;

class realm
{
public:
	realm(string charm, vector <int> magi);
	string charm;
	int maxinc;
	vector <int> magi;
	vector <int> gems;
	int gemsum=0;

};

realm::realm(string charm, vector <int> magi) :charm(charm), magi(magi) {

	vector<int> b, temp(this->magi.size());
	int s = 0, d = 0;
	if (this->magi.empty()) return;

	b.push_back(0);
	for (unsigned int i = 0; i< this->magi.size(); i++)
	{
		if (this->magi[b.back()] < this->magi[i])
		{
			temp[i] = b.back();
			b.push_back(i);
			continue;
		}
		//cout<<b.size()<<" ";
		for (s = 0, d = b.size() - 1; s<d;)
		{
			int c = (s + d) / 2;
			if (this->magi[b[c]] < this->magi[i])
				s = 1 + c;
			else
				d = c;
		}
		//cout<<b.size()<<" ";
		if (this->magi[i] < this->magi[b[s]])
		{
			if (s > 0)
				temp[i] = b[s - 1];
			b[s] = i;
		}
		//cout<<b.size()<<" ";
	}
	for (s = b.size(), d = b.back(); s--; d = temp[d])
		b[s] = d;

	for (unsigned int i = 0; i< b.size(); i++)
	{
		gems.push_back(this->magi[b[i]]);
		//cout << this->magi[b[i]] << endl;
		gemsum=gemsum+magi[b[i]];
	}
	maxinc = b.size();
	//cout<<charm<<" "<<maxinc;
	b.clear();
	temp.clear();

}

struct edge
{
	realm *to;
	int weight;
	int index;
	edge(realm *to, int weight, int index) :  to(to), weight(weight), index(index){}
};

class graph
{
public:
	graph(vector<realm*> realms, string source, string destination);
	void addEdge(int dist, realm *d, int index);
	int dist(realm* u, realm* v);
	void shortDji(int idxS, int idxD);
	void addEdge(int dist, realm s, realm d);
	vector<edge> adj;
	vector<realm*> realms;
	vector<vector<edge> > lor;
};

graph::graph(vector<realm*> realms, string source, string destination) :realms(realms) {
	//cout<<endl;
	int matrix[realms.size()][realms.size()];
	int idxSource, idxDest;
	for(int i = 0; i<realms.size(); i++){
		if(realms[i]->charm == source)
		{
			idxSource = i;
			//cout<<i;
		}
		if(realms[i]->charm == destination)
		{
			idxDest = i;
			//cout<<i;
		}
		//cout<<realms[i]->charm<<" "<<realms[i]->maxinc;
		for(int j = 0; j<realms.size(); j++){
			matrix[i][j]=0;
			int distance = dist(realms[i],realms[j]);
			if(distance<=realms[i]->maxinc&& distance!=0){
				//addEdge(distance,realms[j],j);
				matrix[i][j]=distance;
			}
		}
		//lor.push_back(adj);
		//adj.clear();
	}

	/*for(int i = 0 ; i<realms.size(); i++){
		for(int j = 0; j<realms.size();j++){
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}*/

	int n = realms.size();
	int distance[n];
	bool visited[n];
	int previous[n];

	for(int i = 0; i<n; i++){
		distance[i] = INT_MAX;
		visited[i] = false;
		previous[i]=-1;
	}

	distance[idxSource]=0;

	for(int i = 0; i < n-1; i++){
		int min = INT_MAX;
		int minindex;
		for(int j = 0; j<n;j++){
			if(visited[j]==false && distance[j]<=min){
				min=distance[j], minindex=j;
			}

		}
		int u=minindex;
		visited[u]=true;
		for(int j = 0; j<n;j++){
				if(!visited[j]&&matrix[u][j]>0 && distance[u]!=INT_MAX && distance[u]+matrix[u][j]<distance[j]){
					distance[j]= distance[u]+matrix[u][j];
					previous[j]= u;
				}
		}
	}

	int x = 0;
	int i = idxDest;
	if(distance[i]==INT_MAX){
		cout<<"IMPOSSIBLE"<<endl;
	}
	else{
		cout<<distance[i]<<" ";
		while(i!=idxSource){
			i=previous[i];
			x=x+realms[i]->gemsum;
		}
		cout<<x<<endl;
	}



	/*for(int i = 0; i<n; i++){
		cout<<distance[i]<<" ";
	}
	cout<<endl;
	for(int i = 0; i<n; i++){
		cout<<previous[i]<<" ";
	}*/

	//-------------------------
	n = realms.size();

	for(int i = 0; i<n; i++){
		distance[i] = INT_MAX;
		visited[i] = false;
		previous[i]=-1;
	}

	distance[idxDest]=0;

	for(int i = 0; i < n-1; i++){
		int min = INT_MAX;
		int minindex;
		for(int j = 0; j<n;j++){
			if(visited[j]==false && distance[j]<=min){
				min=distance[j], minindex=j;
			}

		}
		int u=minindex;
		visited[u]=true;
		for(int j = 0; j<n;j++){
				if(!visited[j]&&matrix[u][j] && distance[u]!=INT_MAX && distance[u]+matrix[u][j]<distance[j]){
					distance[j]= distance[u]+matrix[u][j];
					previous[j]=u;
				}
		}
	}
	int y = 0;
	int j = idxSource;
	if(distance[j]==INT_MAX){
		cout<<"IMPOSSIBLE"<<endl;
	}
	else{
		cout<<distance[j]<<" ";
		while(j!=idxDest){
			j=previous[j];
			y=y+realms[j]->gemsum;
		}
		cout<<y<<endl;
	}



	/*for(int i = 0; i<realms.size();i++){
		for(int j = 0; j<realms.size(); j++){
			cout<<matrix[i][j]<<" ";
		}
		cout<<endl;
	}
	//shortDji(idxSource, idxDest);
	/*for(int i = 0; i<realms.size();i++){
		int x=lor[i].size();
		cout<<realms[i]->charm<<endl;
		for(int j = 0; j<x; j++){
			cout<<lor[i][j].to->charm<<" "<<lor[i][j].weight;
		}
		cout<<endl;
	}*/
}

void graph::shortDji(int idxS, int idxD){

	/*swap(realms[idxS], realms[0]);
	swap(lor[idxS], lor[0]);


	int distance[realms.size()];
	int previous[realms.size()];

	for(int i = 0; i < realms.size(); i++){
		distance[i] = INFINITY;
		previous[i] = NULL;
	}

	distance[idxS] = 0;

	for(int i = 1; i < realms.size()-1; i++)
	{
		for(int j = 0; j < lor[i].size(); j++)
		{
			if(distance[i]+lor[i][j].weight<distance[j]){
				distance[j] = distance[i] + lor[i][j].weight;
				cout<< distance[j]<<" ";
				previous[j] = i;
			}
		}
	}*/


}

void graph::addEdge(int dist, realm *d, int index)
{
	edge *e = new edge(d, dist, index);
	adj.push_back(*e);
	//cout << e->from << " " << e->to << " " << e->weight << endl;
}

int graph::dist(realm* u, realm* v)
{
	string x = u->charm;
	string y = v->charm;

	int n = x.length();
	int m = y.length();

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
			else if( x[i-1] == y[j-1])
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

	//cout << dist("florida", "flower") << endl;
	cin >> numrealms;

	for (int i = 0; i < numrealms; i++)
	{
		cin >> charm;
		cin >> nummagi;

		for (int j = 0; j < nummagi; j++)
		{
			cin >> power;
			vec.push_back(power);
		}
		realm *r = new realm(charm, vec);
		realms.push_back(r);
		vec.clear();
	}


	cin >> currcharm;
	cin >> destcharm;
	graph *x = new graph(realms,currcharm,destcharm);
	return 0;
}
