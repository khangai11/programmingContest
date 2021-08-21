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
#include<deque>
#include<set>
#include<numeric>
#include<bitset>


using namespace std;

#define ll long long
#define INF ((1<<30)-1)
#define MOD 1000000007
#define rep(a,b) for(ll a=0;a<b;++a)
#define rrep(a,b) for(ll a=1;a<=b;++a)
#define vll	vector<ll>
#define vi vector<int>
#define vb vector<bool>

class UnionFindTree {
public:
	vector<int> parent;
	vector<int> union_size;
	int len;
	ll value = 0;

	UnionFindTree(int n) {
		len = n;
		parent.resize(n + 1, 0);
		union_size.resize(n + 1, 1);
		value = 0;
		rrep(i, n) parent[i] = i;
	}

	int root(int a) {
		if (parent[a] == a)
			return a;
		parent[a] = root(parent[a]);
		return parent[a];
	}

	void join(int a, int b) {
		int ra = root(a);
		int rb = root(b);
		if (ra == rb)
			return;
		if (union_size[ra] > union_size[rb]) {
			parent[rb] = ra;
			union_size[ra] += union_size[rb];
		}
		else {
			parent[ra] = rb;
			union_size[rb] += union_size[ra];
		}
		len--;
	}

	int size(int a) {
		return union_size[root(a)];
	}

};

class segmentTree {
public:
	vector<ll> v;
	int n;
	ll(*func)(ll, ll);

	segmentTree(int s, ll(*f)(ll, ll)) {
		n = 1;
		while (n < s) n *= 2;
		v.resize(2 * n, 0);
		func = f;
	}

	void setNode(int ind, ll val) {
		v[ind + n - 1] = val;
	}

	ll calculateTree() {
		for (int i = n - 2; i >= 0; i--)
			v[i] = func(v[i * 2 + 1], v[i * 2 + 2]);
		return v[0];
	}
	/// <summary>
	/// add val to value[index]
	/// </summary>
	void addValue(int ind, ll val) {
		updateNode(ind, val + v[ind + n - 1]);
	}
	/// <summary>
	/// set value[ind] to val
	/// </summary>
	void updateNode(int ind, ll val) {
		v[ind + n - 1] = val;
		for (int i = (ind + n - 2) / 2; i != 0; i = (i - 1) / 2) {
			v[i] = func(v[i * 2 + 1], v[i * 2 + 2]);
		}
	}

	/// <summary>
	/// query sum of [l,r] from [st,en] range
	/// </summary>
	/// <param name="ind"></param>
	/// <param name="st"></param>
	/// <param name="en"></param>
	/// <param name="l"></param>
	/// <param name="r"></param>
	/// <returns></returns>
	ll queryInternal(int ind, int st, int en, int l, int r) {
		if (st >= l && en <= r)
			return v[ind];
		if (l > en || r < st)
			return 0;
		int mid = st + (en - st) / 2;
		return func(queryInternal(ind * 2 + 1, st, mid, l, r),
			queryInternal(ind * 2 + 2, mid + 1, en, l, r));
	}

	/// <summary>
	/// returns sum between [l,r]
	/// </summary>
	ll query(int l, int r) {
		return queryInternal(0, 0, n - 1, l, r);
	}

	/// <summary>
	/// returns minimum x which is SUM(0,x) >= sum
	/// ind should be 0
	/// </summary>
	int querySumIndex(int ind, ll sum) {
		int left, right;
		left = ind * 2 + 1;
		right = left + 1;
		if (ind >= n - 1) {
			return (ind - n + 1);
		}
		//if (v[ind] < sum)
		//	return 0;
		if (v[left] >= sum) {
			return querySumIndex(left, sum);
		}
		else {
			return querySumIndex(right, sum - v[left]);
		}
	}
};


ll st_gcd(ll a, ll b) {
	return gcd(a, b);
}

ll st_min(ll a, ll b) {
	return min(a, b);
}

ll st_max(ll a, ll b) {
	return max(a, b);
}

ll st_and(ll a, ll b) {
	return (a & b);
}

ll st_or(ll a, ll b) {
	return (a | b);
}

ll st_sum(ll a, ll b) {
	return (a + b);
}

/// <summary>
/// index starts 0
/// </summary>
class SparseTable {

public:
	vector< vector<ll> > table;
	ll(*func)(ll, ll);
	ll deep = 0;

	SparseTable(vector<ll> vec, ll(*f)(ll, ll)) {
		this->func = f;
		ll s = vec.size();
		deep = floor(log2(s));
		table.resize(deep + 1);
		table[0].resize(s);
		rep(i, s)
			table[0][i] = vec[i];
		rrep(k, deep) {
			ll g = pow(2, k - 1);
			table[k].resize(s);
			rep(i, s - (g * 2 - 1)) {
				table[k][i] = f(table[k - 1][i], table[k - 1][i + g]);
			}
		}
	}

	/// <summary>
	/// index starts 0
	/// </summary>
	/// <param name="st">index of start pos</param>
	/// <param name="size">size of query</param>
	/// <returns></returns>
	ll query(ll st, ll size) {
		ll g = floor(log2(size));
		ll ret = this->func(table[g][st], table[g][st + size - pow(2, g)]);
		return ret;
	}

};

/// <summary>
/// index starts 1
/// </summary>
class BITree {
public:
	vector<ll> v;
	int sz;

	BITree(int n) {
		v.resize(n + 1, 0);
		sz = n;
	}

	void add(int ind, ll val) {
		int i = ind;
		while (i <= sz) {
			v[i] += val;
			i += (i & (-i));
		}
	}

	ll query(int ind) {
		ll r = 0;
		int i = ind;
		if (i > sz) i = sz;
		while (i > 0) {
			r += v[i];
			i -= (i & (-i));
		}
		return r;
	}
};

vector<ll> primes;
void prepare() {
	primes.push_back(2);
	primes.push_back(3);
	for (ll i = 5; i < 100100; i += 2) {
		int j = 0;
		bool isprime = true;
		while (primes[j] * primes[j] <= i) {
			if (i % primes[j] == 0) {
				isprime = false;
				break;
			}
			j++;
		}
		if (isprime)
			primes.push_back(i);
	}
}

int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int q; cin >> q;
	int t, x;
	segmentTree st(200100,st_sum);
	rep(i, q) {
		cin >> t >> x;
		if (t == 1) {
			st.updateNode(x, 1);
		}
		else {
			int re = st.querySumIndex(0, x);
			st.updateNode(re, 0);
			cout << re << "\n";
		}
	}

	return 0;
}