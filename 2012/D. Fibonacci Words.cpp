#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define DB(x) cerr << #x << " --> " << x << endl;
#define endl '\n'

const int N = 301;
const int MAX = 1e5+10;
const int TOT = 25;

string pre[N];
ll dp[N];

string s;
int beg[N];
int en[N];
int fail[MAX];
void build_fail(){
    int k = 0;
    for( int i = 1; i < s.size(); i++ ){
        while( k > 0 && s[i] != s[k]){
            k = fail[k - 1];
        }
        if(s[i] == s[k])k++;
        fail[i]=k;
    }
}

ll kmp(int pos){
    ll res = 0;
    int k = 0;
    string &patt = pre[pos];
    for( int i = 0; i < patt.size(); i++ ){
        while(k && patt[i] != s[k]){
            k = fail[k - 1];
        }
        if(patt[i] == s[k])k++;
        if(k == s.size()){
            res++;
            k = fail[k - 1];
        }
    }
    return res;
}

char aux[1100100];

ll solve(int n){

    if(dp[n] != -1)return dp[n];

    if(n <= TOT){
        return dp[n] = kmp(n);
    }
    dp[n] = solve(n - 1) + solve(n - 2);

    int it = 0;
    for(int i = 0; i < pre[en[n - 1]].size(); i++ ){        
        aux[it++] = pre[en[n - 1]][i];
    }   
    int sz = it;
    for(int i = 0; i < pre[beg[n - 2]].size(); i++ ){       
        aux[it++] = pre[beg[n- 2]][i];
    }
    
    aux[it] = 0;
    
    int k = 0;
    for( int i = 0; i < it; i++ ){
        while(k && aux[i] != s[k]){
            k = fail[k - 1];
        }
        if(aux[i] == s[k])k++;
        if(k == s.size()){
        
            if(i - s.size() + 1 < sz && i >= sz)
            dp[n]++;
            k = fail[k - 1];
        }
    }

    return dp[n];
}


int main() {

   ios_base::sync_with_stdio(false);
   cin.tie(0);

   double ttime = clock();
   pre[0] = "0";
   pre[1] = "1";
   beg[1] = en[1] = 1;
   for( int i = 2; ; i++ ){
       pre[i] = pre[i - 1] + pre[i - 2];
       beg[i] = i;
       en[i] = i;
       if(pre[i].size() > MAX )break;
   }

   for( int i = TOT + 1; i <= 100; i++ ){
       beg[i] = beg[i - 1];
       en[i] = en[i - 2];
   }
   
   int n;
   int tc = 0;
   while(cin >> n){
       cin >> s;
       memset(fail , 0 , sizeof fail);
       build_fail();
       memset(dp, -1 , sizeof dp);
       cout << "Case " << ++tc << ": " << solve(n) << endl;

   }
   cerr << (clock() - ttime) / CLOCKS_PER_SEC << endl;
}