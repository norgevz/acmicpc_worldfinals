#include<bits/stdc++.h>

using namespace std;

#define ALL(c) c.begin(), c.end()
#define SZ(x) ((int)(x).size())
#define PB push_back
#define MP make_pair
#define FOR( i , n ) for( int i = 0; i < (n); i++ )
#define FORR( i , n ) for( int i = ( n - 1 ); i >= 0 ; i-- )
#define DB( x ) cout << #x << " = " << x << endl;
#define OUT( a , n ) for( int J = 0; J < (n); J++ )cout<< (a)[J] << " \n"[J == (n) - 1 ]
#define WAIT cout << flush , system("PAUSE");

typedef  long long ll;

const int MAXN = 502, oo = 1e9;

int MEN[MAXN][MAXN][MAXN] , ens[MAXN][MAXN], MIN[MAXN][MAXN], S[MAXN][MAXN], dp[MAXN][MAXN];
int MAX, n, s[MAXN];
int cumul[MAXN];
bool good[MAXN][MAXN];

int main()

{
	cin.sync_with_stdio( 0 );
	cin.tie( 0 );

	cin >> n;
	for( int i = 0; i < n; i++ )
		cin >> s[i];

	for( int i = 0; i < n; i++ )
	{
		int m = s[i];
		MIN[i][i] = m;
		for( int j = i+1; j < n; j++)
			MIN[i][j] = min(MIN[i][j-1], s[j]);
	}

	for( int i = 0 ; i < n; i++ )
	{
		memset(cumul, 0 , sizeof cumul);
		for( int j = i; j < n; j++ )
		{
			cumul[s[j]]++;
			bool flag = true;
			int len = j - i + 1;
			for( int k = 1; k < MAXN; k++ )
				{
					MEN[i][j][k] = MEN[i][j][k-1] + cumul[k];
					if(k <= len && cumul[k] != 1)
						flag = false;
				}
			good[i][j] = flag;
		}
	}

	memset(S , 30, sizeof S);
	for( int i = 0; i < n; i++)
		S[i][i+1] = 0;

	for(int l = 2; l <=n; l++ )
	{
		for( int i = 0; i < n - l + 1; i++ )
		{
			int j = i + l;
			for( int k = i+1; k < j; k++){
				int diff = 0;
				if(MIN[i][k-1] < MIN[k][j-1])
					diff = MEN[i][k-1][MIN[k][j-1]];
				else
					diff = MEN[k][j-1][MIN[i][k-1]];
				diff = l - diff;
				S[i][j] = min(S[i][j], S[i][k] + S[k][j] + diff);
			}
		}
	}

	memset(dp , 30, sizeof dp);
	for( int i = n-1; i >=0; i--)
		if(good[i][n-1])
			dp[i][1] = S[i][n];
	for( int i = n-1; i >=0 ; i--)
	{
		for( int j = i; j < n; j++)
			for( int k = 2; k <= n; k++)
			{
				if(good[i][j])
					dp[i][k] = min(dp[i][k] , S[i][j+1] + dp[j+1][k-1]);
			}
	}

	int sol = oo;
	for( int i = 1; i <=n; i++)
		sol = min(sol , dp[0][i]);
	
	if(sol == oo)
		cout << "Impossible" << "\n";
	else cout << sol << "\n";
	return 0;
}

