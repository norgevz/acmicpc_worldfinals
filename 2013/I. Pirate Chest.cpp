#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 5e2+10;
const ll oo = -(1LL << 50);

ll st[MAXN];
ll lft[MAXN], rgt[MAXN];

void solve_linear(ll * s, int n)
{
	s[0] = oo;
	st[0] = 0;
	for(int i = 1, sp = 1; i <= n; i++ )
	{
		while(s[i] <= s[st[sp-1]])
			sp--;
		lft[i] = st[sp-1];
		st[sp++] = i;
	}
	
	s[n+1] = oo;
	st[0] = n+1;
	for(int i = n, sp = 1; i > 0; i-- )
	{
		while(s[i] <= s[st[sp-1]])
			sp--;
		rgt[i] = st[sp-1];
		st[sp++] = i;
	}
	
}

int MIN[MAXN][MAXN][MAXN];
int M[MAXN][MAXN];
ll arr[MAXN];

ll solve(ll a , ll b, int m , int n)
{
	ll sol = oo;

	for( int i = 0; i < m; i++ )
	{
		for( int k = i; k < m && (k-i+1 <= a); k++ )
		{
			
			for( int l = 1; l <= n; l++)			
				arr[l] = MIN[l-1][i][k];
						
			solve_linear(arr , n);			
			
			for( int l = 1; l <= n; l++ )
			{
				ll area = min(b , rgt[l] - lft[l] - 1)* (k - i +1);
				ll size =  area*(arr[l]) ;
				ll res = (n * m - area);
				ll add = size / res;	
				
				if(size % (res) == 0)
				add--;
				if(add < 0)add = 0;
							
				size += area * add;				
				sol = max(sol ,  size);		
			}			
		}
	}
	return sol;
}

ll a , b , m , n;


void build_MIN()
{
	for( int c = 0; c < n; c++ )
	{
		for( int i = 0; i < m; i++ )
		{
			MIN[c][i][i] = M[i][c];
			for( int k = i+1; k < m; k++ )
			{
				MIN[c][i][k] = min(MIN[c][i][k-1], M[k][c]);
			}
		} 
	}
}


int main()
{
	cin.sync_with_stdio( 0 );
	cin.tie( 0 );
	
	cin >> a >> b >> m >> n;
	bool flag = 0;
	for( int i = 0; i < m; i++ )
	for( int j = 0; j < n; j++ )
		cin >> M[i][j], flag |= (M[i][j] != 0);
		
	if(!flag )
	{
		cout << 0 << '\n';
		return 0;
	}
	
	build_MIN();

	ll sol = max(solve(a , b , m , n), solve(b , a , m , n));
	if(sol == oo)
		sol = 0;
	cout << sol << "\n";
}
