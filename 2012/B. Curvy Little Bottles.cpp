#include<bits/stdc++.h>

#define OUT(a , n) for( int I = 0; I < (n); I++ ) cout << (a)[I] << " \n"[I == (n)-1]
#define DB(x) cout << #x << " " << x << endl;
#define endl '\n'

using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const double pi = 2 * acos(0.0);

const int MAXDEG = 50;
double c[MAXDEG];
double cc[MAXDEG];

double xlow , xhi, inc;

int deg;


double pre( double x )
{
	double res = 0;
	double pot = 1.0;
	for( int i = 0; i < deg; i++ )
	{
		pot = pot * x;
		double aux = cc[i] * pot / (double)(i+1);

		res = res + aux;
	}

	return pi * res;
}


double volumen( double a , double b )
{
	return pre(b) - pre(a);
}

double solve( double vol )
{
	double lo = xlow , hi = xhi;

	for( int i = 0; i < 50 ; i++ )
	{
		double mid = (lo + hi) / 2.0;
		if(volumen(xlow , mid) > vol)
			hi = mid;
		else lo = mid;
	}
	return lo;
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	
	cout << setprecision(2) << fixed;

	int tc=0;
	while( cin >> deg)
	{
		for( int i = 0; i < MAXDEG; i++ )
			cc[i] = c[i] = 0;
		
		deg++;

		for( int i = 0; i < deg; i++ )
			cin >> c[i];

		for( int i = 0; i < deg; i++ )
			for( int j = 0; j < deg; j++ )
				cc[i + j] += c[i] * c[j];

	 	deg = (deg-1) * 2 + 1;


		cin >> xlow >> xhi >> inc;
		double tot_vol =volumen(xlow , xhi);
		
		cout << "Case " << ++tc << ": " <<tot_vol << endl;

		if(tot_vol < inc){
			cout << "insufficient volume\n";
			continue;
		}

		for( int i = 1; i <= 8; i++ ){
			
			double to = inc * i;
			if( to > tot_vol)
				break;
			double x = solve(to);
			if(i == 1)
				cout << x - xlow;
			else cout << " " << x - xlow;
		}

		cout << endl;

	}


}
