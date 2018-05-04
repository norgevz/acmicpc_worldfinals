#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
#define rep(i , n) for( int i = 0; i < (n); i++ )

const int MAX = 77;

bitset<MAX> G[MAX];

char s[MAX];
int n;

long long C[MAX][MAX];
int tc;

bool one(){
    for( int i = 0; i < n; i++ ){
            if(G[i].count() == n){
                cout << "Case " << ++tc << ": " << 1 << " " << i + 1 << endl;
                return true;
            }
        }

    return false;   
}

bool two(){
    for( int i = 0; i < n; i++ ){
        for( int j = i + 1; j < n; j++ ){
            bitset<MAX> res = G[i] | G[j];

            if(res.count() == n){
                cout << "Case " << ++tc << ": " << 2 << " " << i + 1 << " " << j + 1 << endl;
                return true;
            }
        }
    }

    return false;   
}


bool three(){
    for( int i = 0; i < n; i++ ){
        for( int j = i + 1; j < n; j++ ){
            for( int k = j + 1; k < n; k++ ){

            bitset<MAX> res = G[i] | G[j]| G[k];

            if(res.count() == n){
                    cout << "Case " << ++tc << ": " << 3 << " " << i + 1 << " " << j + 1  << " " << k + 1<< endl;
                    return true;
                }
            }
        }
    }

    return false;   
}

bool four(){
    for( int i = 0; i < n; i++ ){
        for( int j = i + 1; j < n; j++ ){
            for( int k = j + 1; k < n; k++ ){
                for( int p = k + 1; p < n; p++ ){

                    bitset<MAX> res = G[i] | G[j]| G[k]| G[p];

                    if(res.count() == n){
                            cout << "Case " << ++tc << ": " << 4 << " " << i + 1 << " " << j + 1  << " " << k + 1<< " " << p + 1<< endl;
                            return true;
                        }
                }
            }
        }
    }

    return false;   
}


bool five(){
    for( int i = 0; i < n; i++ ){
        for( int j = i + 1; j < n; j++ ){
            for( int k = j + 1; k < n; k++ ){
                for( int p = k + 1; p < n; p++ ){
                    for( int q = p + 1; q < n; q++ ){

                    bitset<MAX> res = G[i] | G[j]| G[k]| G[p]| G[q];

                    if(res.count() == n){
                            cout << "Case " << ++tc << ": " << 5 << " " << i + 1 << " " << j + 1  << " " << k + 1<< " " << p + 1<< " " << q + 1<<endl;
                            return true;
                        }
                    }
                }
            }
        }
    }

    return false;   
}

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    rep(i , MAX)C[i][i] = C[i][0] = 1;

    for (int i = 1; i < MAX; ++i)
    {
        for( int j = 1; j < i; j ++ )
            C[i][j] = C[i-1][j-1] + C[i-1][j];
    }
    
    
    while(cin >> n){

        rep(i , MAX){
            G[i].reset();
        }   

        rep(i , n){
            cin >> s;
            for( int j = 0; s[j]; j++ ){
                int c = s[j] - '0';
                if(c)
                    G[i][j] = 1;
            }
        }

        rep(i , n){
            G[i][i] = 1;
        }

        if(one())continue;
        if(two())continue;
        if(three())continue;
        if(four())continue;
        if(five())continue;

        
    }

    return 0;
}