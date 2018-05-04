#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int , int> pii;

const int MAXV = 25005, MAXE = 110005, oo = 0x3f3f3f3f;
int E, N, M, C, u, v, c, last[MAXV], next[MAXE], adj[MAXE], level[MAXV], now[MAXV], Q[MAXV], source, sink;
int cap[MAXE], flow[MAXE];


void add_edge (int u, int v, int c){
	cap[E] = c, flow[E] = 0, adj[E] = v, next[E] = last[u], last[u] = E++;
}

#define RES(e)  (cap[e] - flow[e])

bool bfs (int s, int t)
{
	memset(level, -1, sizeof level);
	level[s] = 0;
	Q[0] = s;

	for (int ql = 0, qr = 1; ql < qr && level[t] == - 1; ++ql)
	{
		int u = Q[ql];

		for (int e = last[u]; e != -1; e = next[e])
		{
			int v = adj[e];

			if (level[v] == -1 && RES(e) > 0)
			{
				level[v] = level[u] + 1;
				Q[qr++] = v;
			}
		}
	}

	return level[t] != -1;
}

int dfs (int u, int curr)
{
	if (u == sink)
	    return curr;

	for (int e = now[u]; e != -1; now[u] = e = next[e])
	{
		int v = adj[e];

		if (level[v] == level[u] + 1 && RES(e) > 0)
		{
			int ans = dfs(v, min(curr, RES(e)));

			if (ans > 0)
			{
				flow[e] += ans;
				flow[e ^ 1] -= ans;
				return ans;
			}
		}
	}

	return 0;
}

int max_flow ()
{
	ll ans = 0, res;

	while (bfs(source, sink))
	{
		memcpy(now, last, sizeof now);

		while ((res = dfs(source, oo)) > 0)
		    ans += res;
	}

	return ans;
}

pii edges[MAXE];
int cnt, ids[MAXV];
int dist[MAXV];
bool marks[MAXV];
int MEM[MAXV];
vector<pii> G[MAXV];

int solve (int a , int b)
{
	
	sink = 1;
	source = N+1;
	memset(last, -1, sizeof last);
	for(int i = 0; i < E; i++ )
		flow[i] = 0;
	E = 0;
	for (int i = 0; i < cnt; ++i)
	{		
		add_edge(edges[i].first, edges[i].second, 1);
		add_edge(edges[i].second, edges[i].first, 0);
	}
	
	for( int i = a; i <= b; i++ )
	{
		add_edge(source , ids[i], MEM[ids[i]]);
		add_edge(ids[i] , source , 0);
	}
	
	return max_flow();
}


void dijkstra()
{
	priority_queue<pii , vector<pii>, greater<pii> > Q;
	for(int i = 1; i <= N; i++)
		dist[i] = oo;
	dist[1] = 0;
	for( Q.push(pii(0 , 1)); !Q.empty(); Q.pop() )
	{
		pii top = Q.top();		
		u = top.second;
		int size = G[u].size();
		
		if(marks[u])continue;
		
		for( int i = 0; i < size; i++ )
		{
			int v = G[u][i].first;
			int w = G[u][i].second;
			if(!marks[v] && dist[v] > dist[u] + w)
			{
				dist[v] = dist[u] + w;
				Q.push(pii(dist[v] , v));
			}
		}
	}	
}

bool cmp( int i , int j ){
	return dist[i] < dist[j];
}

int main()
{
	cin.sync_with_stdio( 0 );
	cin.tie( 0 );

	cin >> N >> M >> C;
	for( int i = 0; i < M; i++ )
	{
		cin >> u >> v >> c;
		G[u].PB(pii(v , c));
		G[v].PB(pii(u , c));
	}
	for( int i = 1; i <= C; i++ )
	{
		int x;
		cin >> x;
		MEM[x]++;
	}
	dijkstra();
	
	for( int i = 1; i <= N; i++ )
	{
		ids[i] = i;
		for( int j = 0; j < G[i].size(); j++ )
		{
			pii x = G[i][j];
			u = i;
			v = x.first;
			if(dist[v] == dist[u] + x.second)
			edges[cnt++] = pii(v ,u);
		}
	}

	sort(ids+1 , ids + N+1, cmp);
	
	int sol = 0;
	int l = 1;
	
	for( int i = 2; i <= N; i++ )
	{
		if(dist[ids[i]] != dist[ids[i-1]])
		{
			sol += solve(l , i-1);
			l = i;
		}
	}
	sol += solve(l , N);
	cout << (sol)<< "\n";
}
