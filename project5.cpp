/*
Student Name: Begun Unal
Student Number: 2013400021
Project Numner: 5
Operating System: Virtual Machine
Compile Status: {Compiling/Not Compiling}
Program Status: {Working/Not Working}
Notes: Anything you want to say about your code that will be helpful in the grading process.
*/
#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
using namespace std;

unsigned int N,M,s,t;
struct Node;
struct Edge{
	int length;
	Node* to;
	Edge(Node* to, int length){
		this->to = to;
		this->length = length;
	}
};
struct Node{
	int indegree = 0;
	int distfromsource = -1;
	vector<Edge*> adj;
};
vector<Node> cities;
queue<Node*> topologic1;
queue<Node*> topologic2;

void importData(char *infilename){
	ifstream reader(infilename);
	reader>>N;
	unsigned int i;
	for(i=0; i<N; i++){
		Node n;
		cities.push_back(n);
	}
	reader>>M;
	reader>>s;
	reader>>t;
	for(i=0; i<M; i++){
		int firstVer, secondVer,length;
		reader>>firstVer;
		reader>>secondVer;
		reader>>length;
		Edge *e = new Edge(&cities[secondVer-1],length);
		e->to->indegree++;
		cities[firstVer-1].adj.push_back(e);
	}
}

int main(int argc, char *argv[]){
	if(argc!=3){
			printf("Usage: ./project1 infile outfile\n");
			return 0;
	}
	importData(argv[1]);
	unsigned int i;
	for(i=0; i<cities.size(); i++){
		if(cities[i].indegree == 0){
			topologic1.push(&cities[i]);
		}
	}
	while(!topologic1.empty()){
		Node* n = topologic1.front();
		topologic2.push(n);
		for(i=0; i<n->adj.size(); i++){
			n->adj[i]->to->indegree--;
			if(n->adj[i]->to->indegree == 0){
				topologic1.push(n->adj[i]->to);
			}
		}
		topologic1.pop();
	}
	while(!topologic2.empty()){
		Node* n = topologic2.front();
		cities[s-1].distfromsource = 0;
		if(&cities[s-1] == n || n->distfromsource != -1){
			for(i=0; i<n->adj.size(); i++){
				n->adj[i]->to->distfromsource = max(n->adj[i]->to->distfromsource, n->adj[i]->length+n->distfromsource);
			}
		}
		topologic2.pop();
	}
	ofstream writer(argv[2]);
	writer<<cities[t-1].distfromsource<<endl;
}
