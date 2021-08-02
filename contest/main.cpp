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


using namespace std;

#define ll long long
#define INF ((1<<30)-1)
#define MOD 1000000007
#define rep(a,b) for(int a=0;a<b;a++)
#define rrep(a,b) for(int a=1;a<=b;a++)

vector<ll> primes;
ll primemax = 2;
ll num = 1;

bool checkPrime(ll n) {
	bool ret = true;
	size_t s = primes.size();
	for (ll k = primemax + 1; k <= n; k++) {

	}
	for (size_t i = 0; i < primes.size(); i++) {
		if (v % primes[i] == 0) {
			ret = false;
			break;
		}
	}
	if (ret) {
		primes.push_back(v);
	}
	return ret;
}

void solveTest() {
	int n; cin >> n;
	int val = 0;
	long long mi = 1100100100100100100, ma = 0;
	vector<long long> a(n + 1);
	rep(i, n) {
		cin >> a[i];
		mi = min(mi, a[i]);
		ma = max(ma, a[i]);
	}
	ll max_div = 0;
	val = (n + 1) / 2;
	max_div = (ma - mi) / val;
	for (ll d = 3; d <= max_div; d++) {
		if (isPrime(d)) {
			vector<ll> rem(d, 0);
			ll maxva = 0;
			for (int i = 0; i < n;i++) {
				ll t = a[i] % d;
				rem[t] ++;
				maxva = max(maxva, rem[t]);
			}
			val = max((ll)val, maxva);
		}
	}
	cout << val << "\n";
}

int main() {
	int test; cin >> test;
	primes[0] = 2;
	while (test--)
		solveTest();
}