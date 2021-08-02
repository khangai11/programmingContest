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
#define rep(a,b) for(int a=0;a<b;++a)
#define rrep(a,b) for(int a=1;a<=b;++a)

vector<ll> primes;
ll primemax = 2;
ll num = 1;

bool checkPrime(ll n) {
	bool ret = true;
	if (primemax > n)
		return true;

	for (ll k = primemax + 1; k <= n; k++) {
		if (k % 2 == 0)
			continue;

		ret = true;
		for (ll i = 0; i < num && primes[i]<k; i++) {
			if (k % primes[i] == 0) {
				ret = false;
				break;
			}
		}
		if (ret) {
			primes.push_back(k);
			num++;
		}
	}
	primemax = n;
	return ret;
}

void solveTest() {
	int n; cin >> n;
	int val = 1;
	long long mi = 1100100100100100100, ma = 0;
	ll max_dif;
	vector<long long> a(n + 1);
	rep(i, n) {
		cin >> a[i];
		mi = min(mi, a[i]);
		ma = max(ma, a[i]);
	}
	max_dif = ma - mi;
	checkPrime(max_dif);
	for (ll i = 0;max_dif >= primes[i] * val && i<num;++i) {
		ll div = primes[i];
		ll remain = a[0]%div;
		int cont = 1;
		for (int j = 1;j < n;j++) {
			if (remain == (a[j] % div)) {
				cont++;
			}
			else {
				val = max(val, cont);
				remain = (a[j] % div);
				cont = 1;
			}
		}
		val = max(val, cont);
		if (val == n)
			break;
	}
	cout << val << "\n";
}

int main() {
	int test; cin >> test;
	primes.push_back(2);
	while (test--)
		solveTest();
}