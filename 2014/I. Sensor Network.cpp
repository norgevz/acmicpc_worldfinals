#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long ll;
typedef pair<int, int> pii;

const int MAX = 200, ITERATIONS = 500;
int n;
double d;
double x[MAX], y[MAX];

int sqr( int val )
{
	return val * val;
}

int dist2( int i , int j )
{
	return sqr(x[i] - x[j]) + sqr(y[i] - y[j]);
}

int p[MAX];
int sel[MAX], tot;
bool mk[MAX];

int solve( int ini )
{
	ini = p[ini];
	tot = 0;
	sel[tot++] = ini;
	for( int i = 0; i < n; i++ )
	{
		int idx = p[i];
		bool works = true;
		if(idx == ini)continue;
		
		for( int j = 0; j < tot; j++ )
		{
			if(dist2(idx , sel[j]) > sqr(d))
			{
				works = false;
				break;
			}
		}
		if(works)
			sel[tot++] = idx;
	}
	return tot;
}

int res[MAX];
int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie();
	

	cin >> n >> d;
	for( int i = 0; i < n; i++ )
		cin >> x[i] >> y[i];
		
	for( int i = 0; i < n; i++ )p[i] = i;
	
	int maxi = 0;
	for( int it = 0; it < ITERATIONS; it++ )
	{
		random_shuffle(p , p + n);
		for( int i = 0; i < n; i++ )
		{
			int tot = solve(i);
			if(tot > maxi)
			{
				maxi = tot;
				for( int k = 0; k < tot; k++ )res[k] = sel[k];
			}
		}
	}
	
	cout << maxi << endl;
	for( int i = 0; i < maxi; i++ )
		cout << res[i] + 1 << " \n"[i == maxi-1];
}
