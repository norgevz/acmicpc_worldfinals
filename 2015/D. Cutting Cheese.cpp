#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef long long ll;
typedef pair<ll, ll> pii;

const int MAXN = 1e4+100;
const double pi = 2 * acos(0.0);

inline double sqr( double x )
{
    return x * x;   
}

inline double cub( double x )
{
    return x * x * x;
}

int n , s;
double r[MAXN], x[MAXN], y[MAXN], z[MAXN], v[MAXN];
double tot_vol;

double calc( double _z )
{   
    double res = 0;
    for( int i = 0; i < n; i++ )    
    {
        if(z[i] - r[i] >= _z)
            continue;
        
        if(z[i] + r[i] <= _z)
        {
            res += v[i];
            continue;
        }

    
        if( z[i] < _z )
        {
            double a = r[i] - (_z - z[ i ]);
            double b = r[i] - a;        
            
            double ra = r[i];       
            double c = sqrt(sqr(r[i]) - sqr(b));            
            double v0 = pi * (sqr(ra) * (ra - b) - (cub(ra) - cub(b)) /3);          
            res += v[i] - v0;
        }
        else
        {
            double a = r[i] - (z[ i ] - _z);
            double b = r[i] - a;
            double c = sqrt(sqr(r[i]) - sqr(b));                        
            double ra = r[i];           
            double v0 = pi * (sqr(ra) * (ra - b) - (cub(ra) - cub(b)) /3);
            res += v0;
        }
    }
    return res;
}

double solve( double vol )
{
    double lo = 0, hi = 100000.0;
        
    for( int i = 0; i < 50; i++ )
    {
        double mid = ( lo + hi )/ 2.0;      
        double volume = mid * 100000 * 100000;      
        volume -= calc(mid);        
        if(volume > vol)
            hi = mid;
        else lo = mid;      
    }
    
    return lo;
}
int main()
{
    ios::sync_with_stdio( 0 );
    cin.tie( 0 );
    
    cout << setprecision(10) << fixed;
    cin >> n >> s;
    
    tot_vol = 100000LL * 100000 * 100000;   
    for( int i = 0; i < n; i++ )
    {
        cin >> r[i] >> x[i] >> y[i] >> z[i];
        v[i] = (4.0/ 3.0) * pi * cub(r[i]);
        tot_vol -= v[i];
    }
        
    double slice_vol = tot_vol / s; 
    double prev_z = 0;
    
    for( int i = 1; i <= s; i++ )
    {
        double z = solve(slice_vol * i);
        double res = z - prev_z;
        res = res / 1000.0;
        cout << res << endl;
        prev_z = z;
    }
    
    return 0;
}
