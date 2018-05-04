#include <bits/stdc++.h>

using namespace std;
 
typedef long long ll;
typedef pair<ll, ll> pii;    
 
 
const ll MAXN = 200000;
const ll MAXE = 1000000;
const ll ll_MAX = 1LL << 50;
 
ll E, nodes;
ll last[MAXN], head[MAXE], pprev[MAXE];
ll flow[MAXE], cap[MAXE], cost[MAXE];
ll prio[MAXN], curflow[MAXN], edge[MAXN], st[MAXN], q[MAXN];
 
void graphClear(ll _nodes) {
    fill(last, last + MAXN, -1);
    E = 0;
    nodes = _nodes;
}
 
void addEdge1(ll u, ll v, ll _cap, ll _cost) {
    head[E] = v;
    cap[E] = _cap;
    cost[E] = _cost;
    flow[E] = 0;
    pprev[E] = last[u];
    last[u] = E++;
}
 
void addEdge(ll u, ll v, ll cap, ll cost) {     
    addEdge1(u, v, cap, cost);
    addEdge1(v, u, 0, -cost);
}
 
pii maxFlowOfMinCost(ll s, ll t) {
    ll f = 0;
    ll flowCost = 0;
    while (true) {
        curflow[s] = ll_MAX;
        fill(st, st + nodes, 2);
        fill(prio, prio + nodes, ll_MAX);
        prio[s] = 0;
        ll qh = 0;
        ll qt = 0;
        q[qt++] = s;
        if (qt == nodes)
            qt = 0;
        while (qh != qt) {
            ll u = q[qh++];
            if (qh == nodes)
                qh = 0;
            st[u] = 0;
            for (ll e = last[u]; e >= 0; e = pprev[e]) {
                ll v = head[e];
                ll nprio = prio[u] + cost[e];
                if (cap[e] > flow[e] && prio[v] > nprio) {
                    prio[v] = nprio;
                    edge[v] = e;
                    curflow[v] = min(curflow[u], cap[e] - flow[e]);
 
                    if (st[v] == 2) {
                        q[qt++] = v;
                        if (qt == nodes)
                            qt = 0;
                    } else if (st[v] == 0) {
                        if (--qh == -1)
                            qh = nodes - 1;
                        q[qh] = v;
                    }
                    st[v] = 1;
                }
            }
        }
        if (prio[t] == ll_MAX)
            break;
        ll df = curflow[t];
        f += df;
        flowCost += df * prio[t];
        for (ll v = t; v != s; v = head[edge[v] ^ 1]) {
            flow[edge[v]] += df;
            flow[edge[v] ^ 1] -= df;
        }
    }
    return make_pair(f, flowCost);
}
 
 
 
const ll LEN = 200;
const ll inf = 1LL << 30;
 
ll cc[LEN][LEN];
ll n , k;
 
inline ll in( ll x )
{
        return x;
}
 
 
inline ll out( ll x )
{
        return x + n;
}
 
 
int main()
{
        ios::sync_with_stdio( 0 );
        cin.tie( 0 );
        
        
        cin >> n >> k;
        n++;
        
        for( ll i = 1; i <= n; i++ )
                for( ll j = i + 1; j<= n; j++)
                        cin >> cc[i][j];
        
        ll source = 0;
        ll sink = 2 * n + 1;
        
        graphClear(2 * n + 2);  
        
        addEdge(source , in(1), k , 0); 
        addEdge(in(1) , out(1), inf , -inf);
        
        for( ll i = 2; i <= n; i++ )
                addEdge(in(i) , out(i), 1 , -inf);
        
        for( ll i = 1; i <= n; i++ )
                for( ll j = i + 1; j <= n; j++ )
                        addEdge(out(i) , in(j), 1 , cc[i][j]);  
        
        addEdge(out(1) , sink , k , 0);  
        
        for( ll i = 2; i <= n; i++ )
                addEdge(out(i) , sink , 1 , 0);
        
        pii res = maxFlowOfMinCost(source , sink);              
        ll sol = res.second;
        
        while(sol < 0)sol += inf;       
        
        cout << sol << endl;
        
                
        return 0;
}
 