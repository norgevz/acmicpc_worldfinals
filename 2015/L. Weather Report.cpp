#include<bits/stdc++.h>

#define OUT( a , n ) for( int I = 0; I < (n) ; I++ )cout << (a)[I] << " \n"[I == (n)-1]

using namespace std;

const int MAX = 4, LEN = 50;

int n;
double p[MAX];

int id[MAX], len[LEN], cnt[MAX];
int par[MAX * MAX];

typedef long long ll;

typedef pair<double, ll > pdi;
typedef pair<int , vector<int> > piv;

ll cmb[LEN][LEN];

double pow2( double x , int n )
{
    double sol = 1.0;
    for( int i = 0; i < n; ++i )
        sol = sol * x;
    return sol;
}       


priority_queue<pdi, vector<pdi> , greater<pdi> > Q;

int main()
{
    ios_base::sync_with_stdio(0);   
    cout << setprecision(10) << fixed;
    
    for( int i = 0; i < LEN; i++ )
        cmb[0][i] = cmb[i][0] = 1, cmb[i][i] = 1;
        
    for( int i = 1; i < LEN; i++ )  
    {       
        for( int j = 1; j < i; j++  )
            cmb[i][j] = cmb[i-1][j] + cmb[i-1][j-1];
    }   
    
    
    cin >> n;   
    for( int i = 0; i < 4; i++ )
        cin >> p[i];
        
    
    double sum_p = 0;
    for( int i = 0; i <= n; i++ )   
    for( int j = 0; j <= n - i; j++ )
    for( int x = 0; x <= n - i - j; x++ )           
    {
        int y = n - i - j - x;
        
        ll tot = cmb[n][i] * cmb[n - i][j] * cmb[n - i - j][x];     
        assert(cmb[n - i - j - x][y] == 1);
        
        double prob = pow2(p[0] , i) * pow2(p[1] , j) * pow2(p[2] , x) * pow2(p[3] , y);                
        Q.push(pdi(prob , tot));                
    }   
    
    double res = 0;
    
    while( Q.size() > 1 )
    {
        pdi top1 = Q.top();
        Q.pop();
        

        assert(top1.second > 0);
        
        if(top1.second > 1)
        {
            ll mod = top1.second % 2;
            res = res + top1.first * (top1.second - mod);
            Q.push(pdi(top1.first * 2, top1.second / 2));
            
            if(mod)         
                Q.push(pdi(top1.first, 1));
        }       
        else
        {
            pdi top2 = Q.top();Q.pop();
            
            res = res + top1.first + top2.first;
            if(top2.second > 1)
            {
                Q.push(pdi(top1.first + top2.first, 1));                
                Q.push(pdi(top2.first, top2.second-1));
            }
            else
                Q.push(pdi(top1.first + top2.first, 1));            
        }
    }
    
    cout << res << endl;
}