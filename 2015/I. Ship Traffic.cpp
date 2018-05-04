#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
#define y1 hasihvdhvdfhbfgbhdfgn

typedef long long ll;
typedef pair<double, ll> pdi;

double inf = 1LL << 60;

double w , u , v;
int n, k;
double t1 , t2;
double l , p;

int main()
{
    ios::sync_with_stdio( 0 );
    cin.tie( 0 );
    
    cout <<setprecision(10) << fixed;   
    
    cin >> n >> w >> u >> v >> t1 >> t2;
    
    char type;  
    
    vector<pdi> e;
    
    e.push_back(pdi(-inf,1));
    e.push_back(pdi(t1,-1));
    
    e.push_back(pdi(t2,1));
    e.push_back(pdi(inf,-1));
    
    
    for( int i = 0; i < n; i++ )
    {
        cin >> type >> k;       
        double f1 = w * i / v;      
        double f2 = w * (i + 1) / v;        

        for( int j = 0; j < k; j++ )
        {
            cin >> l >> p;
            
            if( type == 'E' && p > 0)
            {
                if(p - l >= 0.0)continue;               
                l -= p;
                p = 0;              
            }
            
            if( type == 'W' && p < 0)  
            {
                if((p + l) <= 0.0)continue;             
                l -= (-p);
                p = 0;
            }
            
            double ini = fabs(p);           
            double end = ini + l;
            
            double tt1 = ini/(double)u;
            double tt2 = end/(double)u;     

            e.push_back(pdi(tt1 - f2,1));
            e.push_back(pdi(tt2 - f1,-1));
        }
    }   
    
    sort(e.begin() , e.end());  
    
    int b = 0;
    
    double res = 0;
    for( int i = 0; i < e.size(); i++ )
    {
        b += e[i].second;
        if(!b && i + 1 < e.size() )
        {
            res = max(res , e[i+1].first - e[i].first);
        }
    }
        
    cout <<  res << endl;
    return 0;
}