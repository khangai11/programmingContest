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
			return (ind-n+1);
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

class SparseTable {
	vector< vector<ll> > table;
	ll(*func)(ll, ll);

public:
	SparseTable(vector<ll> vec, ll(*f)(ll, ll)) {
		this->func = f;
		ll s = vec.size();
		ll col = floor(log2(s));
		table.resize(col + 1);
		table[0].resize(s);
		rep(i, s)
			table[0][i] = vec[i];
		rrep(k, col) {
			ll g = pow(2, k - 1);
			table[k].resize(s);
			rep(i, s - (g * 2 - 1)) {
				table[k][i] = f(table[k - 1][i], table[k - 1][i + g]);
			}
		}
	}

	bool query(ll l, ll r) {
		ll g = floor(log2(r));
		ll ret = this->func(table[g][l], table[g][l + r - pow(2, g)]);
		return (ret > 1);
	}
};

class BITree {
public:
	vector<ll> v;
	int sz;

	BITree(int n) {
		v.resize(n + 1,0);
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


int main() {
	ll n; cin >> n;
	int c;
	vector<ll> b(n,0),a(n,0);
	map<int, int> mp,mpi;
	//1,2,3,4,5 < a
	//1,4,3,2,5 < b
	rep(i, n) {
		cin >> c;
		mp[c] = i;
		mpi[i] = c;
	}
	rep(i, n) {
		cin >> c;
		b[i] = mp[c];
	}
	//0,1,2,3,4 < a
	//0,3,2,1,4 < b
	ll dist = 0;
	segmentTree st(n+1);
	mp.clear();
	rep(i, n) {
		st.updateNode(b[i], 1);
		int les = st.query(0, b[i]);
		dist += (i - les+1);
		mp[b[i]] = (i - les + 1);
	}
	if (dist % 2 != 0) {
		cout << "-1\n";
		return 0;
	}
	else {
		dist /= 2;
		rep(i, n) {
			if (mp[i] >= dist) {
				mp[i] -= dist;
				dist = 0;
				break;
			}
			else {
				dist -= mp[i];
				mp[i] = 0;
			}
		}
		segmentTree st1(n);
		rep(i, n) st1.setNode(i, 1);
		st1.calculateTree();
		rep(i, n) {
			int ind = st1.querySumIndex(0, 1 + mp[i]);
			st1.updateNode(ind, 0);
			b[ind] = i;
		}

		rep(i, n) {
			cout << mpi[b[i]] << " ";
		}
	}
	return 0;
}