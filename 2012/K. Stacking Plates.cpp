#include<bits/stdc++.h>

using namespace std;

const int MAX = 55;

set<int> G[MAX * MAX];

int isIn( int len , int idx )
{
    return G[len].find(idx) != G[len].end();
}

int changes( int x ){
    return x - 1;
}

int dp[ MAX * MAX][MAX];

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int stacks;
    int tc = 0;
    while(cin >> stacks){

        int minlen = 1e9, maxlen = 0;

        for (int i = 0; i < MAX * MAX; ++i)
            G[i].clear();
        
        for( int i = 1; i <= stacks; i++ )
        {
            int k;
            cin >> k;
            for( int j = 0; j < k; j++ ){
                int x;
                cin >> x;

                minlen = min(minlen , x);
                maxlen = max(maxlen , x);

                G[x].insert(i);
            }
        }

        memset(dp , 31 , sizeof dp);

        
        for( auto v : G[minlen] ){
            dp[minlen][v] = changes(G[minlen].size());      
        }

        int mprev = minlen;
        for (int i = minlen + 1; i <= maxlen; ++i)
        {
            if(!G[i].size()){
                for (int j = 0; j < MAX; ++j)
                    dp[i][j] = dp[i-1][j];
                continue;
            }

            for( auto v : G[i] ){

                for( auto z : G[mprev] ){
                    if(isIn(i , z)){
                        dp[i][v] = min(dp[i][v] , dp[mprev][z] + changes(G[i].size()));
                    }
                    else dp[i][v] = min(dp[i][v] , dp[mprev][z] + changes(G[i].size()) + 1);
                }
            }

            mprev = i;
        }

        int res = 1e9;

        for( auto v : G[maxlen]){
            res = min(res , dp[maxlen][v]);     
        }

        cout << "Case " << ++tc << ": " << 2 * res + 1 - stacks << endl;
    }
    return 0;
}