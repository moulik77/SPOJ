#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <utility>
using namespace std;

set <pair<int, int>> shortestPathEdges;

int dijkstraShortestPath(vector <pair<int, int>> graph[], int N, int src, int dest){
	int i, j, u, v, w;
	vector <int> dist(N, -1), visited(N, 0), prev[N];
	priority_queue <pair <int, int>, vector <pair<int, int>>, greater <pair<int, int>>> pq;
	dist[src]=0;
	pq.push(make_pair(dist[src], src));
	while(!pq.empty()){
		u=pq.top().second;
		pq.pop();
		visited[u]=1;
		for(i=0; i<graph[u].size(); i++){
			v=graph[u][i].first;
			w=graph[u][i].second;
			if((dist[v]==-1 || dist[v]>dist[u]+w) && !visited[v]){
				dist[v]=dist[u]+w;
				pq.push(make_pair(dist[v], v));
				prev[v].clear();
				prev[v].push_back(u);
			}
			else if(dist[v]==dist[u]+w)
				prev[v].push_back(u);
		}
	}
	if(dist[dest]==-1)
		return -1;
	visited.assign(N, 0);
	visited[dest]=1;
	queue <int> q;
	q.push(dest);
	while(!q.empty()){
		u=q.front();
		for(i=0; i<prev[u].size(); i++){
			if(!visited[prev[u][i]]){
				visited[prev[u][i]]=1;
				q.push(prev[u][i]);
			}
			shortestPathEdges.insert(make_pair(prev[u][i], u));
		}
		q.pop();
	}
	return dist[dest];
}

int dijkstraAlmostShortestPath(vector <pair<int, int>> graph[], int N, int src, int dest){
	int i, u, v, w;
	vector <int> dist(N, -1), visited(N, 0);
	priority_queue <pair<int, int>, vector <pair<int, int>>, greater <pair<int, int>>> q;
	dist[src]=0;
	q.push(make_pair(dist[src], src));
	while(!q.empty()){
		u=q.top().second;
		q.pop();
		visited[u]=1;
		for(i=0; i<graph[u].size(); i++){
			v=graph[u][i].first;
			w=graph[u][i].second;
			if(shortestPathEdges.find(make_pair(u, v))==shortestPathEdges.end()){
				if((dist[v]==-1 || dist[v]>dist[u]+w) && !visited[v]){
					dist[v]=dist[u]+w;
					q.push(make_pair(dist[v], v));
				}
			}
		}
	}
	shortestPathEdges.clear();
	return dist[dest];
}

int main() {
	int N, M, S, D, U, V, P, i, dist;
	while(cin>>N>>M && N+M!=0){
		cin>>S>>D;
		vector <pair<int, int>> graph[N];
		for(i=0; i<M; i++){
			cin>>U>>V>>P;
			graph[U].push_back(make_pair(V, P));
		}
		dist=dijkstraShortestPath(graph, N, S, D);
		if(dist==-1)
			cout<<"-1\n";
		else{
			dist=dijkstraAlmostShortestPath(graph, N, S, D);
			cout<<dist<<"\n";
		}
	}
	return 0;
}