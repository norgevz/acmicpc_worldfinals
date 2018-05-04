#include<bits/stdc++.h>

#define OUT(a , ppp) for(int I = 0; I < (ppp); I++ ) cout << (a)[(ppp)] << " \n"[(ppp)-1 == I]

using namespace std;

const int MAXN = 60, oo = 1e9;
typedef pair< int , int > pii;
typedef pair< int , pii > piii;

int u[MAXN][MAXN], d[MAXN][MAXN] , l[MAXN][MAXN], r[MAXN][MAXN];
int n , m;
char s[MAXN][MAXN];

char to[200000];

pii cells[MAXN * MAXN];
int tot;

vector<pii> all[0x100];
int dp[MAXN][MAXN];
bool mk[MAXN][MAXN];

void fill_mk()
{
    memset(mk , 0 , sizeof mk);
    for( int i = 0; i < tot; i++ )
        mk[cells[i].first][cells[i].second] = true;     
}

void update()
{
    fill_mk();
    
    for( int i = 1; i <= n; i++ )   
    for( int j = 1; j <= m; j++ )   
        if(!mk[i][j])
            dp[i][j] = oo;
}

bool mem[MAXN][MAXN];

bool isIn( int x , int y )
{
    return x >= 1 && x <= n && y >= 1 && y <= m;
}

void dijkstra()
{
    memset(mem, 0 , sizeof mem);
    priority_queue<piii , vector<piii> , greater<piii> > Q;
    
    
    for(int i = 0; i < tot; i++ )
    {
        int x = cells[i].first;
        int y = cells[i].second;
        Q.push(piii( dp[x][y], pii(x , y) ));
        mem[x][y] = true;
    }
    
    while(!Q.empty())
    {
        piii top = Q.top();
        Q.pop();
        
        pii cell = top.second;
        int x = cell.first;
        int y = cell.second;
        
        int xu = u[x][y];
        if( isIn(xu , y) && !mem[xu][y] && dp[xu][y] > dp[x][y] + 1)
        {
            dp[xu][y] = dp[x][y] + 1;
            Q.push(piii(dp[xu][y] ,pii(xu , y)));
        }
        
        int xd = d[x][y];
        if( isIn(xd , y) && !mem[xd][y] && dp[xd][y] > dp[x][y] + 1)
        {
            dp[xd][y] = dp[x][y] + 1;
            Q.push(piii(dp[xd][y] ,pii(xd , y)));
        }
        
        int yl = l[x][y];
        if(isIn(x , yl) && !mem[x][yl] && dp[x][yl] > dp[x][y] + 1)
        {
            dp[x][yl] = dp[x][y] + 1;
            Q.push(piii(dp[x][yl] , pii(x , yl)) );
        }
        
        int yr = r[x][y];
        if(isIn(x , yr) && !mem[x][yr] && dp[x][yr] > dp[x][y] + 1)
        {
            dp[x][yr] = dp[x][y] + 1;
            Q.push(piii(dp[x][yr] , pii(x , yr)) );
        }
    }
    
}


int main()
{
    ios_base::sync_with_stdio(0);
    
    cin >> n >> m;
    for( int i = 1; i <= n; i++ )
        cin >> (s[i]+1);
        
    cin >> to;
    strcat(to , "*");   
    
    int len = strlen(to);
    
    for( int i = 1; i <= n; i++ )   
        for( int j = 1; j <= m; j++ )   
        {
            char c = s[i][j];
            all[c].push_back(pii(i , j));
        }
    
    
    for( int i = 1; i <= n; i++ )
        for( int j = 1; j <= m; j++ )   
        {   
            u[i][j] = s[i][j] != s[i-1][j] ? i-1 : u[i-1][j];
            l[i][j] = s[i][j] != s[i][j-1] ? j-1 : l[i][j-1];       
        }
    
    for( int i = n; i >= 1; i-- )
        for( int j = m; j >= 1; j-- )
        {
            r[i][j] = s[i][j] != s[i][j + 1] ? j + 1 : r[i][j + 1];
            d[i][j] = s[i][j] != s[i + 1][j] ? i + 1 : d[i + 1][j];
        }

    
    // init 
    cells[0] =pii(1 , 1);
    tot = 1;        
    
    for( int i = 0; i < len; i++ )
    {       
        update();       
        dijkstra(); 
        int c = to[i];
        
        tot = 0;
        int sz = all[c].size();
        for( int j = 0; j < sz; j++ )
            cells[tot++] = all[c][j];
        
    }
    
    
    int res = oo;
    for( int i = 1; i <= n; i++ )   
        for( int j = 1; j <= m; j++ )   
            if(s[i][j] == '*')
                res = min(res, dp[i][j]);
                
    cout << res + strlen(to) << endl;
    
}