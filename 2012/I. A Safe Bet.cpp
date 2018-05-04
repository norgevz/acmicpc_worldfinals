#include<bits/stdc++.h>

#define endl '\n'
#define PB push_back
#define sqr(x) ((x)*(x))
#define SZ(c) ((int)(c).size())
#define REP(i, c) for(int i=0; i<c; i++)
#define DB(x) cerr << #x << " --> " << x << endl;

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;


const int MAX = 1e6+100;
const int oo = 1e9;


set<pii> R[MAX];
set<pii> C[MAX];

bool exist(int x , int y){
    auto it = R[x].lower_bound({y , -1});
    if(it == R[x].end())return false;
    return it->first == y;
}

struct event{
    bool vert;
    int val , lo , hi;
    int b;

    bool operator < (const event &o)const{
        if(val != o.val)
            return val < o.val;
        if(b != o.b)
            return b > o.b;

        return vert > o.vert;
    }
};

int bestx = oo;
int besty = oo;

struct seg{

    int xlo , ylo;
    int xhi , yhi;

    void print(){
        cout << xlo << " " << ylo << " " << xhi << " " << yhi << endl;
    }
};

int n , m , r , c;
bool COOL;
void get_rays(vector<seg> &hor, vector<seg> &vert, int px , int py, int dir){
    int nx , ny;
    bool end = false;
    while(true){
        if(dir == 0){
            auto it = C[py].lower_bound({px , -1});
            if(it == C[py].begin()){
                nx = 0;
                ny = py;
                end = true;
            }
            else{
                it--;
                nx = it->first;
                ny = py;

                if(it->second)
                    dir = 3;
                else
                    dir = 1;
            }
        }
        else if(dir == 2){
            auto it = C[py].upper_bound({px , oo});
            if(it == C[py].end()){
                nx = r + 1;
                ny = py;
                end = true;
            }
            else{
                nx = it->first;
                ny = py;

                if(it->second)
                    dir = 1;
                else
                    dir = 3;
            }
        }
        else if(dir == 3){
            auto it = R[px].lower_bound({py , -1});
            if(it == R[px].begin()){
                nx = px;
                ny = 0;
                end = true;
            }
            else{
                it--;
                nx = px;
                ny = it->first;

                if(it->second)
                    dir = 0;
                else
                    dir = 2;
            }
        }
        else if(dir == 1){
            auto it = R[px].upper_bound({py , oo});
            if(it == R[px].end()){
                nx = px;
                ny = c+1;
                end = true;
            }
            else{
                nx = px;
                ny = it->first;
                if(it->second)
                    dir = 2;
                else
                    dir = 0;

            }
        }       
        
        if(nx == px){
            hor.push_back((seg){nx , min(py , ny) + 1, nx , max(py , ny) - 1});
        }
        else if (ny == py){
            vert.push_back((seg){min(px , nx) + 1, ny , max(px , nx) - 1, ny});
        }

        if(end)break;
        px = nx; py = ny;
    }
    
    if(nx == r && ny == c + 1)COOL = true;
}

int t[MAX];

void add(int i, int val){    
    if(i <= 0)return;
    for(; i < MAX; i += (i & -i) )
        t[i] += val;        
}

ll get(int i){
  ll res = 0;  
  if(i <= 0)return 0;
  for(; i > 0; i -= (i & -i))
    res += t[i];
    return res;
}

ll sum(int l , int r){
    if(l > r)return 0;
    return get(r) - get(l - 1);
}

ll inter(vector<seg> hor, vector<seg> vert){
    memset(t , 0 , sizeof t);
    
    vector<event> e;
    
    for(auto h : hor){
        e.push_back((event){false , h.ylo , h.xlo , h.xlo, 1});
        e.push_back((event){false , h.yhi , h.xlo , h.xlo, -1});
    }
    
    for(auto h : vert){
        e.push_back((event){true , h.ylo, h.xlo , h.xhi , -1});        
    }
    sort(e.begin() , e.end());
    
    ll res = 0;
    for(auto ev : e ){
        if(ev.vert){
            int lo = ev.lo , hi = ev.hi;
            ll s = sum(lo , hi);            
            if(s <= 0)continue;
            
            while( lo < hi ){
                int m = (lo + hi) / 2;
                if(sum(ev.lo , m) >= 1)
                    hi = m;
                else lo = m + 1;
            }
                      
            if(lo == bestx){
                if(besty > ev.val)
                    besty = ev.val;
            }
            else
            if(lo < bestx){
                bestx = lo;
                besty = ev.val;
            }
            
            res += s;
        }
        else{
            add(ev.lo , ev.b);                    
        }
    }
    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int tc = 0;
    while(cin >> r >> c >> m >> n){
        
        cout << "Case " << ++tc << ": ";
        for( int i = 0; i <= r + 1; i++ )R[i].clear();
        for( int i = 0; i <= c + 1; i++ )C[i].clear();
        
        bestx = oo;
        besty = oo;

        for( int i = 0; i < m; i++ ){
            int x , y;
            cin >> x >> y;
            R[x].insert({y , 0});
            C[y].insert({x , 0});
        }
    
        for( int i = 0; i < n; i++ ){
            int x , y;
            cin >> x >> y;
            R[x].insert({y , 1});
            C[y].insert({x , 1});
        }
    
        vector<seg> horA;
        vector<seg> vertA;
        COOL = false;        
        get_rays(horA , vertA , 1 , 0, 1);
        
        if(COOL){       
           cout << 0 << endl;
           continue;
        }

        vector<seg> horB;
        vector<seg> vertB;
        get_rays(horB , vertB , r, c + 1, 3);
    
        ll res = 0;
        res += inter(horA , vertB);
        res += inter(horB , vertA);
    
        if(res == 0)
            cout << "impossible" << endl;
        else cout << res << " " << bestx << " " << besty << endl; 
    }   

}