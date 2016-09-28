#include <stdio.h>
#include <math.h>
#include <algorithm>

using namespace std;

struct point{
	ll x, y;
	point(ll x = 0, ll y = 0) :x(x), y(y){}
	bool operator<(const point &A)const{
		if (x == A.x)return y < A.y;
		return x < A.x;
	}
};

class edge{
	point A, B;
	edge(){}
	edge(point _A, point _B){
		A = _A, B = _B;
	}
};

int ccw(point &a, point &b, point &c) {
	ll dx1, dx2, dy1, dy2;
	dx1 = b.x - a.x;
	dy1 = b.y - a.y;
	dx2 = c.x - b.x;
	dy2 = c.y - b.y;

	ll ret = dx1*dy2 - dx2*dy1;
	if (ret < 0)return -1;
	else if (ret > 0)return 1;
	else
		return 0;
}

bool specialmeets(const edge &L, const edge &R){
	
	int Llx = min(L.A.x, L.B.x), Lrx = max(L.A.x, L.B.x);
	int Lly = min(L.A.y, L.B.y), Lry = max(L.A.y, L.B.y);

	int Rlx = min(R.A.x, R.B.x), Rrx = max(R.A.x, R.B.x);
	int Rly = min(R.A.y, R.B.y), Rry = max(R.A.y, R.B.y);

	if(max(Llx, Rlx) <= min(Lrx, Rrx)){
		if(max(Lly, Rly) <= min(Lry, Rry)){
			return true;
		}
	}

	return false;

}

bool meets(const edge &L, const edge &R){

	if(ccw(L.A, L.B, R.A) == 0 && 0 == ccw(L.A, L.B, R.B)){
		
		// on same line
		return specialmeets(L, R);

	}

	if(ccw(L.A, L.B, R.A) * ccw(L.A, L.B, R.B) <= 0){
		if(ccw(R.A, R.B, L.A) * ccw(R.A, R.B, L.B) <= 0){
			return true;
		}
	}

	return false;

}

class ConvexHull {
public:

	int n;

	vector <point> v, u, d;
	vector <point> c;

	ConvexHull(int _n) {
		n = _n;
		v.resize(n), u.resize(n), d.resize(n);
		c.resize(n << 1);
	}

	void getInput(int p) {
		scanf("%lld %lld", &v[p].x, &v[p].y);
	}

	/* return convex hull's size. and v-1 is the number of convex hull's points */
	int solve() {

		int iu, id;
		id = iu = -1;

		sort(v.begin(), v.end());

		int cnt;

		for (int i = 0; i < n; i++) {
			while (iu>0 && ccw(u[iu - 1], u[iu], v[i]) >= 0)iu--;
			u[++iu] = v[i];
			while (id > 0 && ccw(d[id - 1], d[id], v[i]) <= 0)id--;
			d[++id] = v[i];
		}


		for (cnt = 0; cnt <= iu; cnt++) {
			c[cnt] = u[cnt];
		}
		for (int i = id - 1; i >= 0; i--) {
			c[cnt++] = d[i];
		}

		return cnt;

	}
};

ll getDistance(point a, point b) {
	return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

typedef point Vector;

Vector operator +(Vector A, Vector B)
{
	return Vector(A.x + B.x, A.y + B.y);
}
Vector operator -(Vector A, Vector B)
{
	return Vector(A.x - B.x, A.y - B.y);
}
Vector operator *(Vector A, double p)
{
	return Vector(A.x*p, A.y*p);
}
Vector operator /(Vector A, double p)
{
	return Vector(A.x / p, A.y / p);
}

double Dot(Vector A, Vector B){
	// Inner Product (Scalar product or Dot Product)
	return A.x*B.x + A.y*B.y;
}

double Length(Vector A){
	// Vector A's Length
	return sqrt(Dot(A, A));
}

Vector Unit(Vector A){
	// Unit Vector (Normalization)
	double L = Length(A);
	return Vector(A.x / L, A.y / L);
}

Vector Normal(Vector A){
	// Normal Unit Vector
	Vector B(-A.y, A.x);
	return Unit(B);
}

double Angle(Vector A){
	// atan2 is more accuracy than atan
	return atan2(A.y, A.x);
}

point GetCircleCenterTwo(point &a, point &b, double r){ // know two points
	r *= 2.0; // diameter (radius * 2)
	point mid = (a + b) / 2.0;
	double d = sqrt(r*r / 4.0 - Length(mid - a)*Length(mid - a));
	double rad = Angle(Normal(b - a));
	return point(mid.x + d*cos(rad), mid.y + d*sin(rad));
}

point GetCircleCenterThree(point p1, point p2, point p3) { // know three points by kcm1700
	double cx, cy;
	{
		double x1 = p1.x, x2 = p2.x, x3 = p3.x;
		double y1 = p1.y, y2 = p2.y, y3 = p3.y;
		double a = x1*(y2 - y3) + y1*(x3 - x2) + x2*y3 - y2*x3;
		double f1 = x1*x1 + y1*y1;
		double f2 = x2*x2 + y2*y2;
		double f3 = x3*x3 + y3*y3;
		double bx = +(y2*(f3 - f1) + y3*(f1 - f2) + y1*(f2 - f3));
		double by = -(x2*(f3 - f1) + x3*(f1 - f2) + x1*(f2 - f3));
		cx = -bx / (2 * a);
		cy = -by / (2 * a);
	}
	return point(cx, cy);
}

// on same line segments, maximum points

class line_points {

	int gcd(int a, int b) {

		int m = 1;

		while (m) {
			m = a % b;
			a = b;
			b = m;
		}

		return a;

	}

	class ele {
	public:

		int dx, dy;
		int y;

		ele() {}
		ele(int a, int b, int c) { dx = a, dy = b, y = c; }

		bool operator<(const ele &A)const {
			if (dx == A.dx) {
				if (dy == A.dy)return y < A.y;
				return dy < A.dy;
			}
			return dx < A.dx;
		}

		bool operator*(const ele &A)const {
			return dx == A.dx && dy == A.dy && y == A.y;
		}

	}J[20003];

	class point {
	public:
		int x, y;
		bool operator<(const point &A)const {
			if (x == A.x)return y < A.y;
			return x < A.x;
		}
	}I[203];

	int par[20003];

	int howmany() {

		int n;
		while (scanf("%d", &n) == 1) {

			if (n == 1)printf("1\n");
			else {

				for (int i = 0; i < n; i++) {
					scanf("%d %d", &I[i].x, &I[i].y);
				}

				for (int i = 2; i <= n; i++) {
					par[i*(i - 1) / 2] = i;
				}

				sort(I, I + n);

				int top = 0;

				// nC2 = (n-1)n/2
				for (int i = 0; i < n; i++) {
					for (int j = i + 1; j < n; j++) {
						if (I[i].x == I[j].x) {
							J[top++] = ele(I[i].x, 0, 0);
						}
						else if (I[i].y == I[j].y) {
							J[top++] = ele(0, I[i].y, 0);
						}
						else {
							int dx = I[i].x - I[j].x, dy = I[i].y - I[j].y;
							int g = gcd(abs(dx), abs(dy));

							dx /= g, dy /= g;

							if (dx < 0)dx *= -1, dy *= -1;

							// y = dy/dx * (x-x_0)+y_0
							// dx * y = dy * (x-x_0) + dx * y_0
							// dx * y = dy * (0-x_0) + dx * y_0

							J[top++] = ele(dx, dy, dx*I[j].y - dy*I[j].x);
						}
					}
				}

				sort(J, J + top);

				int c = 1, f = 0;

				int ans = 0;

				for (int i = 1; i < top; i++) {
					if (J[f] * J[i])c++;
					else {

						ans = max(ans, par[c]);

						f = i;
						c = 1;
					}
				}

				ans = max(ans, par[c]);

				printf("%d\n", ans);

			}

		}

	}
};
