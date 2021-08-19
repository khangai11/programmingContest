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

	segmentTree(int s) {
		n = 1;
		while (n < s) n *= 2;
		v.resize(2 * n, 0);
	}

	void setNode(int ind, ll val) {
		v[ind + n - 1] = val;
	}

	ll calculateTree() {
		for (int i = n - 2; i >= 0; i--)
			v[i] = v[i * 2 + 1] + v[i * 2 + 2];
		return v[0];
	}
	/// <summary>
	/// add val to value[index]
	/// </summary>
	void addValue(int ind, ll val) {
		for (int i = (ind + n - 1); i != 0; i = (i - 1) / 2) {
			v[i] += val;
		}
		v[0] += val;
	}
	/// <summary>
	/// set value[ind] to val
	/// </summary>
	void updateNode(int ind, ll val) {
		ll prev = v[ind + n - 1];
		ll dif = val - prev;
		addValue(ind, dif);
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
		return queryInternal(ind * 2 + 1, st, mid, l, r) +
			queryInternal(ind * 2 + 2, mid + 1, en, l, r);
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

ll ones[11] = {
1,	//0
11,
111,
1111,
11111,
111111,
1111111,
11111111,
111111111,
1111111111,
11111111111 };

ll getOnes(int dig) {
	if (dig >= 0)
		return ones[dig];
	else
		return 0;
}

ll pow10s[] = {
1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000,10000000000,10000000000 };
;

ll nearString(ll target, int a, int b, int len, ll bv) {
	//make sure a>b
	ll init_value = a * pow10s[len - 1];
	if (a < b) swap(a, b);
	rep(i, pow(2, len - 1)) {
		ll r = init_value;
		rep(j, len - 1) {
			if ((i >> j) & 0x01)
				r += a * pow10s[j];
			else
				r += b * pow10s[j];
		}
		if (r >= bv)
			return bv;
		if (r >= target)
			return r;
	}
	return pow10s[len];
}

void solve() {
	ll n, k;
	cin >> n >> k;
	string m = to_string(n);
	int fd = m[0] - '0';
	int dig = m.size();
	ll val = 1;
	if (k == 1) {
		val = getOnes(dig - 1);
		if (val * fd < n)
			val = (fd + 1) * val;
		else
			val = val * fd;
		cout << val << "\n";
		return;
	}
	else if (k == 2) {
		if (dig == 1) {
			cout << m << "\n";
			return;
		}
		ll ret = pow10s[dig];
		for (int sd = 0; sd <= 9; sd++) {
			ll f = nearString(n, fd, sd, dig,ret);
			if (f < ret)
				ret = f;
		}
		cout << ret << "\n";
	}
	else {
		cout << "0";
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	int t;
	cin >> t;
	while (t--)
		solve();
	return 0;
}