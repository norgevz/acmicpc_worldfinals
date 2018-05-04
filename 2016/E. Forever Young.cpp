#include<bits/stdc++.h>

using namespace std;

long long y , l;

const int MAXBASE = 300000;
const long long oo = 1LL << 60;

bool check(long long base){

    long long num = 0;
    long long value = y;
    long long pot = 1;

    do{
        int c = value % base;
        if(c < 0 || c > 9)return false;
        num += c * pot;
        value /= base;
        pot *= 10;
    }while(value > 0);

    return num >= l;
}

long long get(int num , long long base){
    long long pot = 1;
    long long res = 0;
    while(num > 0){
        res += num % 10 * pot;
        num /= 10;
        if(pot > oo / base && num > 0)
        return oo;
        pot = pot * base;
    };

    return res;
}

long long find_base(int num){
    long long lo = 2, hi = y;
    
    while(lo < hi){
        long long m = (lo + hi) / 2;
        long long value = get(num , m);     
        if(value >= y)
            hi = m;
        else lo = m + 1;
    }
    
    return get(num , lo) == y ? lo : oo;
}

int main(){

    cin >> y >> l;

    long long res = 0;
    for( int base = 2; base <= MAXBASE; base++ ){
        if(check(base)){
            res = base;
        }
    }

    for(int i = 1; i <= 9999; i++ ){
        long long base = find_base(i);  
        if(base != oo && check(base)){      
            res = max(res , base);          
        }
    }

    cout << res << endl;
}