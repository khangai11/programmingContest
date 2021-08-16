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
#include<numeric>
#include<bitset>


using namespace std;


#define ll long long
#define INF ((1<<30)-1)
#define MOD 1000000007
#define rep(a,b) for(int a=0;a<b;++a)
#define rrep(a,b) for(int a=1;a<=b;++a)


class setJoin {

public:
	vector<int> par;
	vector<int> siz;

	setJoin(int n) {
		par.resize(n, -1);
		siz.resize(n, 1);
	}

	int root(int a) {
		int r = a;
		while (par[r] != -1)
			r = par[r];
		if (a != r)
			par[a] = r;
		return r;
	}

	void joinTwo(int a, int b) {
		int ra, rb;
		ra = root(a);
		rb = root(b);
		if (ra == rb)
			return;
		par[ra] = rb;
		siz[rb] += siz[ra];
	}

	int solve(int a) {
		int ra = root(a);
		return (siz[ra]);
	}
};