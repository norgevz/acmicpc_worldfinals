#include<bits/stdc++.h>

using namespace std;
#define endl '\n'
#define rep(i , n) for( int i = 0; i < n; i++ )
#define DB(x) cout << #x << " --> " << x << endl;
#define OUT(a , n) rep(I , n) cout << (a)[I] << " \n"[I == (n) - 1]

const int MAX = 20, oo = 1e9 + 100;
int C[MAX][MAX];
int beg[1 << MAX][MAX];
int en[1 << MAX][MAX];
int n , m;
int bc[1 << MAX];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);     
    
    for( int i = 1; i < (1 << MAX); i++ )   {
        bc[i] = bc[i - (i & -i)] + 1;
    }
    
    int tc = 0; 
    while(cin >> n >> m){
    
        rep(i, n)rep(j, n)C[i][j] = oo;
        rep(i, n)C[i][i] = 0;
        
        rep(i, m){
            int u , v , w;
            cin >> u >> v >> w;
            C[u][v] = C[v][u] = min(C[u][v] , w);
        }
            
        rep(k, n)rep(i, n)rep(j, n)C[i][j] = min(C[i][j] , C[i][k] + C[k][j]);
        
        for( int mask = 0; mask < (1 << n); mask++ ){
            for( int j = 0; j < n; j++ )
                beg[mask][j] = oo;
        }
        for( int mask = 0; mask < (1 << n); mask++ ){
            for( int j = 0; j < n; j++ )
                en[mask][j] = oo;
        }       
        
        beg[1 << 0][0] = 0;
        en[1 << (n - 1)][n - 1] = 0;
        
        for( int mask = 1; mask < (1 << n); mask++ )
        {
            for( int i = 0; i < n; i++ )
            {
                if(!i || i == n - 1)continue;
                
                if(mask & (1 << i)){
                    int newmask = mask ^ (1 << i);  
                    for( int j = 0; j < n; j++ ){
                        if(newmask & (1 << j)){
                            beg[mask][i] = min(beg[mask][i], beg[newmask][j] + C[j][i]);
                            en[mask][i] = min(en[mask][i], en[newmask][j] + C[j][i]);
                        }
                    }
                }           
            }
        }
        
        int best = oo;
        for( int lft = 1; lft < (1 << n); lft++ ){
            int c = bc[lft];        
            if(!(lft & 1) || c - 1 != (n-2) / 2)continue;
            
            int rgt = ((1 << (n)) - 1) ^ lft;       
                    
            int to = oo;
            for( int i = 0; i < n; i++ )
                for( int j = 0; j < n; j++ ){
                    if((lft & (1 << i)) && (rgt & (1 << j)))
                        to = min(to , beg[lft][i] + C[i][j] + en[rgt][j]);
                }
            int from = oo;
            
            int lftcopy = lft ^ (1) ^ (1 << (n - 1));
            int rgtcopy = rgt ^ (1) ^ (1 << (n - 1));
            
            for( int i = 0; i < n; i++ )
                for( int j = 0; j < n; j++ ){
                    if((lftcopy & (1 << i)) && (rgtcopy & (1 << j)))
                        from = min(from , en[lftcopy][i] + C[i][j] + beg[rgtcopy][j]);
                }
            best = min(best , from + to);
        }   
        
        cout << "Case " << ++tc << ": " << best << endl;
    }
    
} 