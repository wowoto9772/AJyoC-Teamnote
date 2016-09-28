// Author : wowoto9772

class BIT{
public:
	vector <int> T;
	int S;
	
	BIT(int n) : S(n), T(n+1) {}

	void Update(int p, int v){
		while (p <= S){
			T[p] += v;
			p += p & (-p);
		}
	}

	long long Sum(int p){
		long long ret = 0;
		while (p > 0){
			ret += T[p];
			p -= p & (-p);
		}
        return ret;
	}
};

class BIT_2d{
public:
	long long T[3003][3003];
	int N, M;

	void update(int x, int y, int val){
		int y1;
		while (x <= N){
			y1 = y;
			while (y1 <= M){
				T[x][y1] += val;
				y1 += (y1 & -y1);
			}
			x += (x & -x);
		}
	}

	long long read(int x, int y){ // return sum from 1,1 to x,y.
		long long sum = 0;
		while (x){
			int y1 = y;
			while (y1){
				sum += T[x][y1];
				y1 -= y1 & -y1;
			}
			x -= x & -x;
		}
		return sum;
	}

	long long interval_sum(int r1, int c1, int r2, int c2){
		// read(r1, c1, r2, c2) = read(r2, c2) - read(r2, c1 - 1) - read(r1 - 1, c2) + read(r1 - 1, c1 - 1);
		return read(r2, c2) - read(r2, c1 - 1) - read(r1 - 1, c2) + read(r1 - 1, c1 - 1);
	}
};
