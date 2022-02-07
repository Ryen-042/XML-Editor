#include "Graph.hpp"

Graph::Graph(int maxV,vector<User> users):users(users)
{
    numVertices = 0;
    maxVertices = maxV;
    vertices = new int[maxV];
    edges = new int* [maxV];
    for(int i = 0; i < maxV; i++)
        edges[i] = new int[maxV];
		
	//initialize arrays 
	for(int i=0;i<maxV;i++)
		vertices[i] = 0;
	for(int i=0;i<maxV;i++){
		for(int j=0;j<maxV;j++)
			edges[i][j] = NULL_EDGE;
    }
}

bool Graph::isEmpty() const{
	return numVertices == 0;
}
bool Graph::isFull() const{
	return numVertices == maxVertices - 1;
}

vector<string> Graph::build_graph(){
    for(const auto &user:users){
		addVertex(user.id);
		for(auto follower:user.followers){
			addEdge(user.id,follower);
		}
    }
    vector<string> res;
    string temp;
    for(int i=1;i<=numVertices;i++){
        temp ="";
        for(int j=1;j<=numVertices;j++)
            temp += to_string(edges[i][j]);
        res.push_back(temp);
    }
    return res;
}


void Graph::addVertex(int vertex)
{
    vertices[vertex] = 1;
    numVertices++;
}
void Graph::addEdge(int fromVertex,int toVertex)
{
    edges[fromVertex][toVertex] = 1;
}

User Graph::most_influencer_user()
{
    int cout = 0;
    int max_cout = 0;
    int user_id = 0;
    for(int i=1;i<=numVertices;i++){
        cout = 0;
        for(int j=1;j<=numVertices;j++){
           cout += edges[j][i];
        }
        if(max_cout < cout){
            max_cout = cout;
            user_id = i;
        }
    }
    return user_from_id(user_id);
}

User Graph::most_active_user()
{
    int cout = 0;
    int max_cout = 0;
    int user_id = 0;
    for(int i=1;i<=numVertices;i++){
        cout = 0;
        for(int j=1;j<=numVertices;j++){
           cout += edges[i][j];
        }
        if(max_cout < cout){
            max_cout = cout;
            user_id = i;
        }
    }
    return user_from_id(user_id);
}


User Graph::user_from_id(int id)
{
    for(const auto &user:users){
        if(user.id == id)
            return user;
    }
    return User();
}


void Graph::print(){
	for(int i=1;i<=numVertices;i++){
		for(int j=1;j<=numVertices;j++)
            qDebug()<<edges[i][j]<<" ";
        qDebug()<<endl;
	}
}

Graph::~Graph()
{
    for(int i = 0; i < maxVertices; i++)
        delete[] edges[i];

    delete[] vertices;
    delete[] edges;
}
