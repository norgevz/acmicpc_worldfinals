#include<bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

const int MAXN = 100;
int N = 26, n;
int GetOp(int x) {return x > N ? x-N : x + N;}

vector<int> G[MAXN];
bool marks[MAXN];
string S;
int getid(char a , char b)
{
	if(a == '0' && b=='0')return 0;

	int u = a - ('A'-1);
	if(b == '-')return u+N;
	return u;
}

int init = -1;
bool solve(int u , int p)
{
	if(u == 0)return false;
	marks[u] = true;

	int size = G[u].size();
	bool sol = 0;
	for( int i = 0; i < size; i ++ )
	{
		int v = G[u][i];
		if(!v)continue;

		if(v == p || G[GetOp(v)].size()== 0)continue;
		v = GetOp(v);

		if(v == init)return true;

		if(!marks[v] )
			sol |= solve(v, u);
	}
	return sol;
}

void add(int i , int j)
{
	int u = getid(S[2*i], S[2*i+1]);
	int v = getid(S[2*j], S[2*j+1]);
	G[u].PB(v);
	G[v].PB(u);
}

int main()
{
	cin.sync_with_stdio(0);
	cin.tie(0);

	cin >> n;
	for( int i = 0; i < n; i++ )
	{
		cin >> S;
		for( int i = 0; i < 4; i++)
			for(int j = i+1; j < 4; j++)
				add(i,j);
	}
	
	bool flag = false;
	
	for( int i = 1; i < MAXN; i++)
	{
		memset(marks , 0 , sizeof marks);
		init = i;

		if(solve(i, -1))
		{
			flag = true;
			break;
		}
	}

	cout << (flag ? "unbounded" : "bounded") << "\n";

	return 0;
}

