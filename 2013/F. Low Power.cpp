#include<bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;
typedef long long ll;

const int MAXN =1e6+10;

int vals[MAXN];
int n , k;

bool check( int d )
{
	if(vals[1] - vals[0] > d) return false;

	int found = 1;
	int iter = 0;
	for( int i = 2; i < 2 * n * k - 1 ; )
	{
		if(found >= n)return true;
		if(vals[i+1] - vals[i] <= d) {
			if(i > 2 * found * k)return false;
			i+=2;
			found++;
		}
		else
		{
			i++;
		}
	}
	return found >= n;
}
int main()
{
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );

	cin >> n >> k;
	int l = 2 * n * k;
	for( int i = 0; i < l; i++ )
		cin >> vals[i];
		
	sort(vals , vals + l);

	int lo = 0, hi = 2e9;

	while( lo < hi )
	{
		int mid = lo + (hi - lo) / 2;
		if(check(mid))
			hi = mid;
		else lo = mid + 1;
	}

	cout << lo << "\n";
	
	return 0;
}
