#include<bits/stdc++.h>

using namespace std;

string line;

map<string, int> dic;
map<int, string> rev;


int idx;
int get_id(string &s){
	if(dic.find(s) == dic.end()){
		rev[++idx] = s;
		return dic[s] = idx;
	}
	return dic[s];
}

const int N = 2e6+100;

bool en[N];
bool good[N + 100];
vector<int> g[N];
bool comma[N];
bool dot[N];
int ids[N];
bool mk[N];
bool show[N];


int go(int u){
	mk[u] = true;
	int sum = good[u];
	for(auto v : g[u]){
		if(!mk[v]){
			sum += go(v);
		}
	}
	return sum;
}

void paint(int u){
	show[u] = true;
	
	for(auto v : g[u]){
		if(!show[v]){
			paint(v);
		}
	}
	return;
}

int main(){
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);

	getline(cin, line);

	istringstream reader(line);

	int n = 0;
	string tok;
	int id;
	while(reader >> tok){
		if (tok.back() == ','){
			tok = tok.substr(0, tok.size() - 1);
			comma[n] = true;
		}
		if (tok.back() == '.'){
			tok = tok.substr(0, tok.size() - 1);
			dot[n] = true;
		}
		id = get_id(tok);
		ids[n++] = id;
	}

	for( int i = 0; i < n - 1; i++ ){
		if(comma[i]){
			good[2 * ids[i]] = true;
			good[2 * ids[i + 1] + 1] = true;
		}

		if(!dot[i]){
			g[2 * ids[i]].push_back(2 * ids[i+1] + 1);
			g[2 * ids[i+1] + 1].push_back(2 * ids[i]);		
		}
		
	}

	for( int i = 1; i < N; i++ ){

		if(!mk[i]){
			int sum = go(i);
			if(sum > 0){
				paint(i);
			}
		}
	}

	for( int i = 0; i < n - 1; i++ ){
		int ida = ids[i];
		cout << rev[ida];
		if(show[2 * ida] && !dot[i]){
			cout << ", ";
		}
		else if (dot[i]){
			cout << ". ";
		}
		else{
			cout << " ";
		}
	}
	cout << rev[ids[n - 1]] << "." << endl;

}