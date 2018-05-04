#include<bits/stdc++.h>

using namespace std;

#define endl '\n'

const int N = 1e6;

int s[N], foo[N];
int n , m;

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m;

	for( int i = 0; i < m; i++ ){
		int u , v;
		cin >> u >> v;
		s[u]++, s[v]++;
	}

	vector<pair<int, int>> deg(n);

	for( int i = 0; i < n; i++ ){
		deg[i] = {s[i] , i};
	}

	sort(deg.begin(), deg.end());

	for( int i = 0; i < n; i++ ){
		foo[i] = 1;
	}

	int have = n - 2;

	for( int i = 0; i < n; i++ ){
		int idx = deg[i].second;
		while(have > 0 && foo[idx] < deg[i].first){
			have--;
			foo[idx]++;
		}
	}

	int ans = 0;
	for( int i = 0; i < n; i++ ){
		if(foo[i] != s[i]){
			ans++;
		}
	}


	cout << ans << endl;

	set<pair<int, int>> S;
	for( int i = 0; i < n; i++ ){
		S.insert({foo[i] , i});
	}

	vector<pair<int, int>> e;
	while(S.size() > 0){
		auto u = *S.rbegin();
		auto v = *(S.begin());
		e.push_back({u.second , v.second});

		foo[u.second]--;
		foo[v.second]--;

		S.erase(u);
		S.erase(v);


		if(foo[u.second] > 0){
			S.insert({foo[u.second] , u.second});
		}

		if(foo[v.second] > 0){
			S.insert({foo[v.second] , v.second});
		}
	}

	cout << n << " " << n - 1 << endl;

//	assert(e.size() == n - 1);
	for(auto pp : e){
		cout << pp.first << " " << pp.second << endl; 
	}
	
}