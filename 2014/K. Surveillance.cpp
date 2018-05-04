#include <bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef pair<int, int> pii;


const int LEN = 2e6 + 10;

int n , k;
vector<pii> c;
int t[4 * LEN];

void build( int v , int b , int e ){
    if(b == e){
        t[v] = -1;
        return;
    }
    int m = (b + e) >> 1;
    build(2 * v , b , m);
    build(2 * v + 1 , m + 1 , e);
    t[v] = -1;
}

void pull( int v ){
    if(t[2 * v] == -1)
        t[v] = t[2 * v + 1];
    else
    if(t[2 * v + 1] == -1)
        t[v] = t[2 * v];
    else
        t[v] = c[t[2 * v]].second < c[t[2 * v + 1]].second ?
                t[2 * v + 1] : t[2 * v];

}

void update( int v , int b , int e , int pos, int idx){
    if(b == e)
    {
        if(t[v] == -1 || c[t[v]].second < c[idx].second)
            t[v] = idx;
        return;
    }
    int m = (b + e) >> 1;
    if(m >= pos)
        update(2 * v , b , m , pos , idx);
    else update(2 * v  + 1 , m + 1 , e , pos , idx);

    pull( v );
}

int query( int v , int b , int e , int l , int r ){
    if(b > r || e < l)return -1;
    if(b >= l && e <= r){
        return t[v];
    }

    int m = (b + e) >> 1;
    int q1 = query(2 * v , b , m , l , r);
    int q2 = query(2 * v + 1, m + 1 , e , l , r);

    if(q1 == -1)
        return q2;
    if(q2 == -1)
        return q1;

    return c[q1].second < c[q2].second ? q2 : q1;
}

const int LOG = 19;

int p[LEN];
int st[LOG][LEN];

int kth( int u , int k ){
    for( int i = LOG - 1; i >= 0; i-- ){
        if(k >= (1 << i)){
            u = st[i][u];
            k -= (1 << i);
        }
    }
    return u;
}

int main() {

    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> k;

    rep(i , k){
        int a , b;
        cin >> a >> b;
        if(a <= b){
            c.push_back(pii(a , b));
            c.push_back(pii(a + n , b + n));
        }else{
            c.push_back(pii(a , n + b));
        }
    }
    k = c.size();

    sort(c.begin(), c.end());

    build(1 , 1 , LEN);

    for( int i = k - 1; i >= 0; i-- ){
        update(1 , 1 , LEN, c[i].first, i);
        p[i] = query(1 , 1 , LEN , c[i].first, c[i].second + 1);

    }

    for( int i = 0; i < k; i++ ){
        st[0][i] = p[i];
    }

    for( int i = 1; (1 << i) <= k; i++ )
        for( int j = 0; j < k; j++ )
            st[i][j] = st[i-1][st[i-1][j]];

    int res = 1e9;


    for(int i = 0; i < k; i++ ){
        int b = c[i].first;

        int kp = kth(i , k);
        int e = c[kp].second;
        if(e - b + 1 < n)continue;

        int lo = 0, hi = k;

        while( lo < hi ){
            int m = (lo + hi) >> 1;
            kp = kth(i , m);
            e = c[kp].second;
            if(e - b + 1 >= n)
                hi = m;
            else lo = m + 1;
        }

        res = min(res , lo + 1);

    }

    if(res == 1e9){
        cout << "impossible" << endl;
    }
    else cout << res << endl;
    
    return 0;
}
