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
#include<iomanip>


using namespace std;

#ifdef _DEBUG
#define prnt(a) cout<<#a<<"="<<a<<endl
#else
#define prnt(a) (void)0
#endif // _DEBUG

#define ll long long
#define INF (1LL<<30)
#define INFLL (1LL<<60)
//#define MOD 1000000007
#define MOD 998244353
#define rep(i,st,en) for(int i=st;i<en;++i)
#define vll	vector<ll>
#define vvll	vector<vll>
#define vi vector<int>
#define vvi vector<vi>
#define vb vector<bool>
#define vvb vector<vb>
#define M_PI           3.141592653589793238462643383279502884L
#define all(v) (v).begin(), (v).end()

#define rd(...) __VA_ARGS__; read(__VA_ARGS__)
#define rdv(value,...) value(__VA_ARGS__);cin >> value
template <class T> auto& operator>>(istream & is, vector<T> &xs) {
	for (auto& x : xs) is >> x;
	return is;
}
template <class T> auto& operator<<(ostream& is, vector<T>& xs) {
	for (auto& x : xs) is << x << " ";
	return is;
}
template <class T,class Y> auto& operator>>(istream& is, vector<pair<T,Y>>& xs) {
	for (auto& [x1,x2] : xs) is >> x1>>x2;
	return is;
}
template <class  ...Args> auto& read(Args & ...args) { return (cin >> ... >> args); }

#define write(...) writemy(__VA_ARGS__);cout<<"\n"
void writemy() {}
template <typename Head, class  ...Args>
void writemy(Head& head, Args & ...args) {
	cout << head << " ";
	writemy(args...);
}



class UnionFindTree {
public:
	vector<int> parent;
	vector<int> union_size;
	vector<ll> w;
	int len;
	ll value = 0;

	UnionFindTree(int n) {
		len = n;
		parent.resize(n + 1, 0);
		w.resize(n + 1, 0);
		union_size.resize(n + 1, 1);
		value = 0;
		rep(i,0, n) parent[i] = i;
	}

	int root(int a) {
		if (parent[a] == a)
			return a;
		parent[a] = root(parent[a]);
		return parent[a];
	}

	void setWeight(int a, ll we) {
		w[a] = we;
	}

	ll getWeight(int a) {
		int ra = root(a);
		return w[ra];
	}

	void join(int a, int b) {
		int ra = root(a);
		int rb = root(b);
		if (ra == rb)
			return;
		if (union_size[ra] > union_size[rb]) {
			parent[rb] = ra;
			union_size[ra] += union_size[rb];
			w[ra] += w[rb];
		}
		else {
			parent[ra] = rb;
			union_size[rb] += union_size[ra];
			w[rb] += w[ra];
		}
		len--;
	}

	int size(int a) {
		return union_size[root(a)];
	}

};

template <typename T>
class segmentTree {
public:
	vector<T> v;
	int n;
	T(*func)(T, T);
	T defval = 0;

	segmentTree(int s, T(*f)(T, T)) {
		n = 1;
		while (n < s) n *= 2;
		v.resize(2 * n, defval);
		func = f;
	}
	/// <summary>
	/// use this before calculateTree()
	/// index starts 0
	/// </summary>
	void setNode(int ind, T val) {
		v[ind + n - 1] = val;
	}

	ll calculateTree() {
		for (int i = n - 2; i >= 0; i--)
			v[i] = func(v[i * 2 + 1], v[i * 2 + 2]);
		return v[0];
	}
	/// <summary>
	/// add val to value[index]
	/// index starts 0
	/// </summary>
	void addValue(int ind, T val) {
		updateNode(ind, val + v[ind + n - 1]);
	}

	T getValue(int ind) {
		return v[ind + n - 1];
	}
	/// <summary>
	/// set value[ind] to val
	/// index starts 0
	/// </summary>
	void updateNode(int ind, T val) {
		v[ind + n - 1] = val;
		for (int i = (ind + n - 2) / 2; i != 0; i = (i - 1) / 2) {
			v[i] = func(v[i * 2 + 1], v[i * 2 + 2]);
		}
		v[0] = func(v[1], v[2]);
	}

	/// <summary>
	/// query sum of [l,r] from [st,en] range
	/// </summary>
	/// <returns></returns>
	T queryInternal(int ind, int st, int en, int l, int r) {
		if (st >= l && en <= r)
			return v[ind];
		if (l > en || r < st)
			return defval;
		int mid = st + (en - st) / 2;
		return func(queryInternal(ind * 2 + 1, st, mid, l, r),
			queryInternal(ind * 2 + 2, mid + 1, en, l, r));
	}

	/// <summary>
	/// returns sum between [l,r]
	/// index starts 0
	/// </summary>
	T query(int l, int r) {
		if (l > r)
			return 0;
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

template <typename T> T my_gcd(T a, T b) { return gcd(a, b); }
template <typename T> T my_min(T a, T b) { return min(a, b); }
template <typename T> T my_max(T a, T b) { return max(a, b); }
template <typename T> T my_and(T a, T b) { return (a & b); }
template <typename T> T my_xor(T a, T b) { return (a ^ b); }
template <typename T> T my_or(T a, T b) { return (a | b); }
template <typename T> T my_sum(T a, T b) { return (a + b); }
template <typename T> T my_sum_mod(T a, T b) { return (a + b) % MOD; }

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
		rep(i,0, s)
			table[0][i] = vec[i];
		rep(k,1, deep) {
			ll g = pow(2, k - 1);
			table[k].resize(s);
			rep(i, 0, s - (g * 2 - 1)) {
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
void prepare(int max_val) {
	primes.push_back(2);
	primes.push_back(3);
	for (ll i = 5; i <= max_val; i += 2) {
		int j = 0;
		ll max_val = sqrt(i);
		bool isprime = true;
		while (primes[j] <= max_val) {
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


//baruun tiishee yavah bol return 1
int bs_compare(ll target, ll b) {
	if (target > b) return 1;
	else if (target < b) return -1;
	else return 0;//equal
}


ll my_binary_search(vi &v, int size, ll target) {
	if (size == 0) {
		size = v.size();
	}
	ll ans = -1;
	int l = 0;
	int r = size - 1;
	int mid;
	while (l <= r) {
		mid = l + (r - l) / 2;
		int val = bs_compare(target, v[mid]);
		if (val == 0) {
			ans = mid;
			r = mid - 1;
			break;
		}
		else if (val > 0) {
			//ans = mid;
			l = mid + 1;
		}
		else {
			//ans = mid;
			r = mid - 1;
		}
	}
	return ans;
}


class lazySegmentTree {
public:
	vll v;
	vll b, c;
	int n;
	ll defval = 0;

	lazySegmentTree(int s) {
		n = 1;
		while (n < s) n *= 2;
		v.resize(2 * n, defval);
		b.resize(2 * n, 1);
		c.resize(2 * n, defval);
	}
	
	void setNode(int ind, ll val) {
		v[ind + n - 1] = val;
	}

	ll calculateTree() {
		for (int i = n - 2; i >= 0; i--)
			v[i] = (v[i * 2 + 1] + v[i * 2 + 2])%MOD;
		return v[0];
	}
	
	void updateNodeRange(int ind, int st, int en, int us, int ue, ll bb, ll cc) {
		//update value if there is update
		if (b[ind] != 1 || c[ind] != 0) {
			int len = en - st + 1;
			v[ind] = (v[ind] * b[ind] + len*c[ind]) % MOD;
			if (st != en) {
				int ch = 2 * ind + 1;
				b[ch] = (b[ch] * b[ind]) % MOD;
				c[ch] = (c[ch] * b[ind] + c[ind]) % MOD;
				ch = 2 * ind + 2;
				b[ch] = (b[ch] * b[ind]) % MOD;
				c[ch] = (c[ch] * b[ind] + c[ind]) % MOD;
			}
			b[ind] = 1;
			c[ind] = 0;
		}
		if (us > en || ue < st) {
			//out of range
			return;
		}
		if (us <= st && en <= ue) {
			//completely inside
			int len = en - st + 1;
			v[ind] = (v[ind] * bb + len * cc) % MOD;
			if (st != en) {
				int ch = 2 * ind + 1;
				b[ch] = (b[ch] * bb) % MOD;
				c[ch] = (c[ch] * bb + cc) % MOD;
				ch = 2 * ind + 2;
				b[ch] = (b[ch] * bb) % MOD;
				c[ch] = (c[ch] * bb + cc) % MOD;
			}
			b[ind] = 1;
			c[ind] = 0;
			return;
		}
		//intersect
		int mid = st + (en - st) / 2;
		updateNodeRange(ind * 2 + 1, st, mid, us, ue, bb, cc);
		updateNodeRange(ind * 2 + 2, mid + 1, en, us, ue, bb, cc);
		v[ind] = (v[ind*2+1]+v[ind*2+2])%MOD;
	}

	ll queryInternal(int ind, int st, int en, int l, int r) {
		if (b[ind] != 1 || c[ind] != 0) {
			int len = en - st + 1;
			v[ind] = (v[ind] * b[ind] + len * c[ind]) % MOD;
			if (st != en) {
				int ch = 2 * ind + 1;
				b[ch] = (b[ch] * b[ind]) % MOD;
				c[ch] = (c[ch] * b[ind] + c[ind]) % MOD;
				ch = 2 * ind + 2;
				b[ch] = (b[ch] * b[ind]) % MOD;
				c[ch] = (c[ch] * b[ind] + c[ind]) % MOD;
			}
			b[ind] = 1;
			c[ind] = 0;
		}
		if (r < st || l >= en) {
			//out of range
			return 0LL;
		}
		if (l <= st && en <= r) {
			//completely inside
			return v[ind];
		}
		int mid = st + (en - st) / 2;
		return (queryInternal(ind * 2 + 1, st, mid, l, r)+
			queryInternal(ind * 2 + 2, mid + 1, en, l, r))%MOD;
	}

	ll query(int l, int r) {
		if (l > r)
			return 0;
		return queryInternal(0, 0, n - 1, l, r);
	}

	void updateRange(int l, int r, ll bb, ll cc) {
		if (l > r)
			return;
		updateNodeRange(0, 0, n - 1, l, r,bb,cc);
	}
};

void solve() {
	int rd(n, q);
	lazySegmentTree s(n + 1);
	rep(i, 0, n) {
		ll rd(a);
		s.setNode(i, a);
	}
	s.calculateTree();
	rep(i, 0, q) {
		int rd(t, l, r);
		if (t == 0) {
			ll rd(b, c);
			s.updateRange(l, r - 1, b, c);
		}
		else {
			cout << s.query(l, r - 1) << "\n";
		}
	}
}


int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	int test;
	//cin >> test; for (int t = 1; t <= test; t++)
		solve();
	return 0;
}

