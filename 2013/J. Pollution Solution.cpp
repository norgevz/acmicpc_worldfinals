#include<bits/stdc++.h>

using namespace std;

#define endl '\n'
#define SZ(c) ((int)(c).size())
#define sqr(x) ((x)*(x))

typedef long long ll;
typedef pair<int, int> pii;
typedef complex<double> P;

const double PI = acos(-1);
const int MAXN = 111;


double cross(const P & a, const P & b) {
    return imag(conj(a)*b);
}

int n, r, x[MAXN], y[MAXN];
P ps[MAXN];


double heading(P & p) {
    return atan2(p.imag(), p.real());
}

double sector(double lo, double hi) {
    return 0.5 * abs(hi-lo) * r*r;
}

P get_point(double px, double py, double vx, double vy, double t) {
    return P(px + vx*t, py + vy*t);
}

vector<P> intersect(int i, int j) {
    double vx = x[j] - x[i];
    double vy = y[j] - y[i];
    double a = sqr(vx) + sqr(vy);
    double b = 2*x[i]*vx + 2*y[i]*vy;
    double c = sqr(x[i]) + sqr(y[i]) - sqr(r);
    double d = b*b - 4*a*c;
    
    vector<P> ip;
    
    if (d <= 0)
        return ip;
    
    double t1 = (-b - sqrt(d)) / (2*a);
    double t2 = (-b + sqrt(d)) / (2*a);
    //cout << t1 << " " << t2 << endl;
    
    if (0 <= t1 && t1 <= 1)
        ip.push_back(get_point(x[i], y[i], vx, vy, t1));
        
    if (0 <= t2 && t2 <= 1)
        ip.push_back(get_point(x[i], y[i], vx, vy, t2));
    
    return ip;
}

double trap(int i, int j) {
    return x[i]*y[j] - x[j]*y[i];
}

double get_area(int i, int j) {
    auto ip = intersect(i, j);
    
    if (SZ(ip) == 2) {
        double s1 = sector(heading(ps[i]), heading(ip[0]));
        double s2 = sector(heading(ip[1]), heading(ps[j]));
        double s3 = abs(cross(ip[0], ip[1])) * 0.5;
        return s1 + s2 + s3;
    }
    if (SZ(ip) == 1) {
        if (abs(ps[i]) < r)
            swap(i, j);
        
        double s1 = sector(heading(ps[i]), heading(ip[0]));
        double s3 = abs(cross(ip[0], ps[j])) * 0.5;
        return s1 + s3;
    }
    if (SZ(ip) == 0) {
        if (abs(ps[i]) < r)
            return abs(trap(i, j)) * 0.5;
        return sector(heading(ps[i]), heading(ps[j]));
    }
    
    return 0;
}


int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout << setprecision(10) << fixed;

    cin >> n >> r;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        ps[i] = P(x[i], y[i]);
    }
    
    double sol = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        double a = get_area(i, j);
        if (trap(i, j) > 0)
            sol += a;
        else
            sol -= a;
    }
    cout << sol << endl;
}
