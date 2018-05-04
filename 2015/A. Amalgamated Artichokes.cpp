#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

typedef pair<int, int> pii;
typedef long long ll;



double n , p , a , b , c , d;

double eval( double x )
{
    return p * (sin(a * x + b) + cos(c * x + d) + 2);
}

int main()
{
    ios::sync_with_stdio( 0 );
    cin.tie( 0 );
    
    cin >> p >> a >>b >> c >> d >> n;
    
    double maxi = -HUGE_VAL;
    
    double ans = 0;
    
    for( int i = 1; i <= n; i++ )
    {
        double e = eval(i);
        
        if(e < maxi)
            ans = max(ans , maxi - e);
        maxi = max(maxi , e);
    }
    
    cout << setprecision(10) << fixed << ans << endl;
    return 0;
}