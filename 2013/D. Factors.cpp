#include<bits/stdc++.h>

using namespace std;

#define forn(i , n) for( int i = 0; i < n; i++ )

typedef long long ll;

const ll
		MAXN = 200;

ll n;
map<ll , ll > dic;

ll p[MAXN], primes[MAXN], P;
map<ll , ll> mem;
ll dp[MAXN];

ll find_tot()
{
	if(mem.size() == 0)return 0;
	int tot = 0;
	memset(dp , 0 ,sizeof dp);
 
	for( map<ll , ll>:: iterator v = mem.begin(); v != mem.end(); v++ )
	{
		ll val = (*v).first;
		ll cnt = (*v).second;
		dp[cnt]--;
		tot += cnt;
	}
	

	dp[tot]++;	
	for( int i = tot; i > 0; i-- )
		dp[i - 1] += dp[i];

	for( int i = tot; i > 1; i-- )		
	{
		ll a = i / p[i];
		ll b = p[i];
		
		if(p[i] != i)	
		{
			dp[a] += dp[i];
			dp[b] += dp[i];
			dp[i] = 0;
		}
	}
	
	ll res = 1;
	for( ll i = 1; i <= tot ; i++ )
		for( int j = 0; j < dp[i]; j++ )
		{
			if(res * i < res || (res * i/res) != i )return -1;
			res = res * i;
		}
	return res;
}


bool valid(ll x)
{
	ll res = 1;
	for( map<ll , ll>:: iterator v = mem.begin(); v != mem.end(); v++ )
	{
		ll val = (*v).first;
		ll cnt = (*v).second;
		forn(i , cnt)
			   x = x / val;
	}
	return 1 == x;
}


void go(ll x , int curr, int deg)
{
	ll tot = find_tot();
	if(tot == -1 || !valid(x))return;

	if(dic.find(tot) == dic.end())
	   dic.insert(make_pair(tot , x));
	else if(dic[tot] > x)
	      dic[tot] = x;
	
	ll aux = x;
	
	for( int i = 1; i <= deg; i++ )
	{
		if(aux * primes[curr] < aux && (aux * primes[curr]) / aux == primes[i])break;
		aux = aux * primes[curr];		
		mem.insert(make_pair(primes[curr] , i));
		go(aux , curr + 1, i);
		mem.erase(primes[curr]);
	}
}

void build()
{

	for( int i = 2; i < MAXN; i++ )
	{
		if(!p[i])
		{
			p[i] = i;
			for( int j = i * 2; j < MAXN; j += i)						
				if(!p[j])p[j] = i;
		}
	}
	
	for( int i = 2; i < MAXN; i++ )
		if(p[i] == i)primes[P++] = i;	

	go(1 , 0 , 63);
}

int main()
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);	
	
	build();
	while( cin >> n)
		cout << n << " " << dic[n] << endl;
}
