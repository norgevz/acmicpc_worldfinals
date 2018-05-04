#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long ll;
typedef pair<int, int> pii;

int n;
vector<pii> gain, lose;

bool solve(ll cnt){
    for(auto p : gain){
        if(cnt < p.first)return false;
        cnt += p.second - p.first;
    }
    
    for(auto p : lose){
        if(cnt < p.first)return false;
        cnt += p.second - p.first;
    }
    return true;
}
int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;

    vector<pii> arr(n);
    
    int x , y;
    for( int i = 0; i < n; i++ ){
        cin >> x >> y;
        if(x <= y)
          gain.push_back({x , y});
        else lose.push_back({x , y});
    }
    

    sort(gain.begin(), gain.end(), [](pii a , pii b){ return a.first < b.first; });
    sort(lose.begin(), lose.end(), [](pii a , pii b){ return a.second > b.second; });
    
    ll lo = 1, hi = 1LL << 60;
    
    while(lo < hi){
        ll m = (lo + hi) >> 1;
        if(solve(m))
            hi = m;
        else lo = m + 1;        
    }
    
    cout << lo << endl;
}
