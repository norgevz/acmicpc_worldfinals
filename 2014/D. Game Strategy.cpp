#include<bits/stdc++.h>

using namespace std;

#define OUT( a , n ) for( int J = 0; J < (n); J++ )cout<< (a)[J] << " \n"[J == (n) - 1 ]

typedef pair<int, int> pii;
typedef long long ll;
typedef complex<double> point;

const int MAXN = 25, LEN = 1e6+10;

int dp[MAXN][LEN], n, C[MAXN], L;

char s[30];

int dis[MAXN][MAXN];
bool mk[MAXN][MAXN];
bool marks[MAXN];

bool check( int mask , int pos)
{
    for( int i = C[pos] - 1; i >= 0; i--)
    {
        if((dp[pos][i] & mask) == dp[pos][i])
            return true;
    }
    return false;
}

void bfs(int target)
{
    mk[target][target] = 1;
    memset(marks , 0 , sizeof marks);

    int mask = 1 << target;

    for( int it = 1; it <= n; it++ )
    {
        bool found = 0;
        int newmask = mask;
        for( int i = 0; i < n; i++ )
        {
            if((mask & (1 << i)) == 0)
            {
                if(check(mask , i))
                {
                    dis[i][target] = it;
                    mk[i][target] = 1;
                    newmask |= (1 << i);
                    found = true;
                }
            }
        }
        if(!found)break;
        mask = newmask;
    }
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> n;

    for( int i = 0; i < n; i++ )
    {
        cin >> C[i];
        for( int j = C[i] - 1; j >= 0; j-- )
        {
            cin >> s;
            int mask = 0;
            for( int k = 0; s[k]; k++ )
            {
                int c = s[k] - 'a';
                mask |= (1 << c);
            }
            dp[i][C[i] - j - 1] = mask;
        }
    }

    for( int i = 0; i < n; i++ )
        bfs(i);

    for( int i = 0; i < n; i++ )
        for( int j = 0; j < n; j++ )
            if(!mk[i][j])
                dis[i][j] = -1;

    for( int i = 0; i < n; i++ )
        OUT(dis[i] , n);

    return 0;
}

