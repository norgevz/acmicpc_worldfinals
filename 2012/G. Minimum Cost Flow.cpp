#include<bits/stdc++.h>

#define endl '\n'

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<double, int> pdi;


const int N = 410;
const int oo = 1e9;

vector<int> G[N];
int x[N], y[N], z[N];
int holes[N];
int n , m;
bool flood[N];

int H[N];
vector<int> comp[N];
bool mk[N];
int cc;
int C[N];

void dfs(int u){
    comp[cc].push_back(u);
    H[cc] += holes[u];
    mk[u] = true;   
    C[u] = cc;
    for(auto v : G[u]){
        if(!mk[v] && flood[v]){
            dfs(v);
        }
    }
}

double add[N];

double msqr(double x){
    return x * x;
}

double mdist(double x , double y , double z, double xx , double yy, double zz){
    return sqrt(msqr(x - xx) + msqr(y - yy) + msqr(z - zz));
}

double dp[N];

double len(int u , int v){
    return mdist(x[u] , y[u] , z[u] , x[v] , y[v] , z[v] );
}

bool valid[N];

double solve(double MAX_Z){
    
    memset(flood,  0 , sizeof flood);
    memset(mk,  0 , sizeof mk);
    memset(H,  0 , sizeof H);
    memset(C,  0 , sizeof C);
    memset(dp,  0 , sizeof dp);
    memset(valid,  0 , sizeof valid);

    for( int i = 1; i <= n; i++ ){
        comp[i].clear();
    }
    cc = 0;
    for( int i = 1; i <= n; i++ ){
        if(z[i] <= MAX_Z){
            flood[i] = true;                    
        }
    }
    if(!flood[1] || !flood[n])return oo;

    for(int i = 1; i <= n; i++ ){
        if(flood[i] && !mk[i])
            ++cc , dfs(i);
    }


    if(C[1] == C[n]){
        return 0.5 * H[C[1]];
    }


    for( int i = 1; i <= cc; i++ ){
        if(i == C[1] || i == C[n]){
            if(!H[i])return oo;
            valid[i] = H[i] >= 1;
            add[i] = 0.5 * (H[i] - 1);
        }
        else {
            add[i] = 0.5 * (H[i] - 2);
            valid[i] = H[i] >= 2;
        }
    }

    
    for( int i = 1; i <= n; i++ ){
        dp[i] = oo;
    }

    dp[1] = add[C[1]];
    memset(mk , 0 , sizeof mk);

    priority_queue<pdi , vector<pdi>, greater<pdi> > Q;
    Q.push({ add[C[1]] , 1});
    while(!Q.empty()){
        auto top = Q.top();
        Q.pop();

        int u = top.second;
        if(mk[u])continue;
        mk[u] = true;
        for( int v = 1; v <= n; v ++ ){
            if(C[v] == C[u] && !mk[v] && dp[v] > dp[u]){
                dp[v] = dp[u];
                Q.push({dp[v] , v});
            }
            else if(C[v] != C[u] && !mk[v] && dp[v] > dp[u] + len(u , v) + add[C[v]] && holes[v] && holes[u] && valid[C[v]]){
                dp[v] = dp[u] + len(u , v) + add[C[v]];
                Q.push({dp[v] , v});        
            }
        }
    }

    return dp[n];
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cout << setprecision(4) << fixed;

    int tc = 0;
    while(cin >> n >> m){
        cout << "Case " << ++tc << ": ";
        vector<int> zs;
        for( int i = 1; i <= n; i++ ){
            cin >> x[i] >> y[i] >> z[i] >> holes[i];
            zs.push_back(z[i]);
        }
        for( int i = 1; i <= n; i++ ){
            G[i].clear();
        }
        sort(zs.begin(), zs.end());
        
        for( int i = 0; i < m; i++ ){
            int u , v;
            cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }

        double res = oo;
        for(auto zz : zs){
            double aux = solve(zz);         
            res = min(res , aux);
        }
        if(res == oo)
            cout << "impossible" << endl;
        else cout << res << endl;       
    }
}