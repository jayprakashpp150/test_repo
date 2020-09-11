#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> ii;
typedef vector<ii> vii;
typedef vector<int> vi;
typedef long long ll;
typedef pair<ll, ll> pll;
#define sz(x) int(x.size())
#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define rep(i, begin, end) for(__typeof(end) i=begin; i<end; i++)
#define per(i, begin, end) for(__typeof(end) i=begin; i>=end; i--)
#define fi first
#define se second
#define fastio ios_base::sync_with_stdio(false),cin.tie(0),cout.tie(0)
constexpr int INF = 1e9 + 1;
constexpr ll LLINF = 1e18 + 1;

#define LOCAL

#ifdef LOCAL
#define dbg(...) DEBUG(#__VA_ARGS__, __VA_ARGS__);
#else
#define dbg(...)
#endif
 
template<typename T, typename S> ostream& operator << (ostream &os, const pair<T, S> &p) {return os << "(" << p.first << ", " << p.second << ")";}
template<typename C, typename T = decay<decltype(*begin(declval<C>()))>, typename enable_if<!is_same<C, string>::value>::type* = nullptr>
ostream& operator << (ostream &os, const C &c) {bool f = true; os << "["; for (const auto &x : c) {if (!f) os << ", "; f = false; os << x;} return os << "]";}
template<typename T> void DEBUG(string s, T x) {cerr << s << " = " << x << "\n";}
template<typename T, typename... Args> void DEBUG(string s, T x, Args... args) {cerr << s.substr(0, s.find(',')) << " = " << x << " | "; DEBUG(s.substr(s.find(',') + 2), args...);}
 

template<typename T>
T gcd(T a, T b){	return b ? gcd(b, a%b): a; }
template<typename T>
T lcm(T a, T b){	return a/gcd(a, b) * b;		}


int main()
{
	fastio;
	int t;
	string s;
	char c;
	cin >> t;
	while(t--){
		cin >> s;
		ll tot = s.length(), cur=0;
		for(int i=0; i<(int)s.length(); i++){
			c = s[i];
			if(c=='+')
				cur = max(1LL, cur+1);
			else
				cur--;
			if(cur < 0)
				tot += i+1;
		}
		printf("%lld\n", tot);
	}
}


