#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

#define OUT(a , n) for( int I = 0; I < (n); I++) cout << (a)[I] << " \n"[I == (n)-1]

const int MAXN = 1 << 20;

const double pi = 2.0 * acos(0.0);
typedef complex<double> point;
int divs[MAXN];


namespace FFT {

  #define FOR(i, a, b) for (int i = (a); i < (b); ++i)
  #define REP(i, n) FOR(i, 0, n)
   
  typedef ll value;
  typedef complex<double> comp;
  const double pi = 2 * acos(0);
  int N;
  comp omega[MAXN];
  comp a1[MAXN], a2[MAXN];
  comp z1[MAXN], z2[MAXN];
  value x[MAXN], y[MAXN], z[MAXN];

  void fft(comp *a, comp *z, int m = N) {
    if (m == 1) {
      z[0] = a[0];
    } else {
      int s = N/m;
      m /= 2;

      fft(a, z, m);
      fft(a+s, z+m, m);

      REP(i, m) {
        comp c = omega[s*i] * z[m+i];
        z[m+i] = z[i] - c;
        z[i] += c;
      }
    }
  }

  void mult(value *a, value *b, value *c, int len) {
    N = 2*len;
    while (N & (N-1)) ++N;
    assert(N <= MAXN);

    REP(i, N) a1[i] = 0;
    REP(i, N) a2[i] = 0;
    REP(i, len) a1[i] = a[i];
    REP(i, len) a2[i] = b[i];

    REP(i, N) omega[i] = polar(1.0, 2*pi/N*i);
    fft(a1, z1, N);
    fft(a2, z2, N);

    REP(i, N) omega[i] = comp(1, 0) / omega[i];
    REP(i, N) a1[i] = z1[i] * z2[i] / comp(N, 0);
    fft(a1, z1, N);

    REP(i, 2*len) c[i] = round(z1[i].real());
  }
}

ll p1[MAXN], p2[MAXN], s[MAXN];

void build()
{   
   
   for( int i = 0; i < MAXN; ++i )         
      p1[i] = p2[i] = divs[i];
         
   FFT::mult(p1 , p2, s , 1 << 19);
}

int main()
{
   ios_base::sync_with_stdio(0);
   cin.tie(0);
   
   fill(divs + 1 , divs + MAXN, 1);   
   
   for( int i = 2; i < MAXN; i++ )
   {
      if(divs[i] == 1)
      {   
         divs[i]++;
         
         for( int j = i + i; j < MAXN; j += i)
         {
            int cnt = 0, aux = j;
            
            while(!(aux % i))
               cnt++, aux /= i;
            
            divs[j] = divs[j] * (cnt+1);
         }
      }
   }
   
   build();
   
   
   int a, b, tc;
   for( cin >> tc; tc; tc-- )
   {
      cin >> a >> b;      
      
      int tot = -1, idx = -1;
      for( int i = a; i <= b; i++ )
         if( s[i] > tot )
         {
            tot = s[i];
            idx = i;
         }

      cout << idx << " " << tot << endl;      
   }   
   
}