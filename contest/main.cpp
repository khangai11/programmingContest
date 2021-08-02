#include<iostream>
#include<string>
#include<algorithm>
#include<functional>
#include<cmath>
#include<queue>
#include<vector>
#include<map>
#include<stack>
#include<list>
#include<numeric>


using namespace std;

#define ll long long
#define INF ((1<<30)-1)
#define MOD 1000000007
#define rep(a,b) for(int a=0;a<b;++a)
#define rrep(a,b) for(int a=1;a<=b;++a)

vector<ll> primes;
ll primemax = 2;
ll num = 1;

ll myGcd(ll a, ll b) {
	return gcd(a, b);
}

ll myMin(ll a, ll b) {
	return min(a, b);
}

ll myMax(ll a, ll b) {
	return max(a, b);
}

class SparseTable {
	vector< vector<ll> > table;
	ll(*func)(ll, ll);

public:
	SparseTable(vector<ll> vec, ll (*f)(ll,ll)) {
		this->func = f;
		size_t s = vec.size();
		int col = floor(log2(s));
		table.resize(col+1);
		table[0].resize(s);
		rep(i, s)
			table[0][i] = vec[i];
		rrep(k, col) {
			ll g = pow(2, k-1);
			table[k].resize(s);
			rep(i, s - (g * 2 - 1)) {
				table[k][i] = f(table[k - 1][i], table[k - 1][i + g]);
			}
		}
	}

	bool query(ll l, ll r) {
		ll g = floor(log2(r));
		ll ret = this->func(table[g][l],table[g][l+r-pow(2,g)]);
		return (ret > 1);
	}
};

void solveTest() {
	int res = 1;
	int n; cin >> n;
	vector<ll> a(n);
	vector<ll> d(n-1);
	rep(i, n) cin >> a[i];
	rep(i, n - 1) d[i] = abs(a[i] - a[i + 1]);
	SparseTable st = SparseTable(d, myGcd);
	for (int i = 0; i < n - 1; i++) {
		for (int j = res+1; j < n - i-1; j++) {
			if (st.query(i, j)) res = j + 1;
			else break;
		}
	}
	cout << (res + 1) << "\n";
}

int main() {
	int test; cin >> test;
	while (test--) {
		solveTest();
	}
}