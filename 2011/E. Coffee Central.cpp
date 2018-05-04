#include<bits/stdc++.h>

#define OUT(a , n) for( int I = 0; I < (n); I++ ) cout << (a)[I] << " \n"[I == (n)-1]
#define DB(x) cout << #x << " " << x << endl;
#define endl '\n'

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 5000;

int R , C , n , q;
int dp[MAXN][MAXN];

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie();
	
	int tc = 0;
	while( cin >> R >> C >> n >> q )
	{
		if(R + C + n + q == 0)return 0;
		
		int MAX =  (R + C) + 1;
		for( int i = 1; i <= MAX; i++ )
		for( int j = 1; j <= MAX; j++ )dp[i][j] = 0;
		
		for( int i = 0; i < n; i++ )
		{
			int x , y;
			cin >> x >> y;
			int newx = x+y-1;
			int newy = R-x+y;
			dp[newx][newy]++;
		}
		
		for( int i = 1; i <= MAX; i++ )
		for( int j = 1; j <= MAX; j++ )
			dp[i][j] = dp[i][j] + dp[i-1][j] + dp[i][j-1] - dp[i-1][j-1];
			
		int m;
		cout << "Case " << ++tc << ":\n";
		for(; q ; q-- )
		{
			int bestx =-1, besty = -1, cost = -1;
			
			cin >> m;
			
			for( int i = 1; i <= R; i++ )
			for( int j = 1; j <= C; j++ )
			{
				int x = i+j-1;
				int y = R-i+j;
				
				int u = max(1 , x - m);
				int d = min(MAX , x + m);
				
				int l = max(1 , y - m);
				int r = min(MAX , y + m);
				
				int cnt = dp[d][r] - dp[d][l-1] - dp[u-1][r] + dp[u-1][l-1];
				
				if(cnt > cost || (cnt == cost && (j < besty || (j == besty && i < bestx))))
				{
					cost = cnt;
					besty = j;
					bestx = i;
				}
			}
			
			cout << cost << " (" << bestx << "," << besty << ")" << endl;
		}
	}
}