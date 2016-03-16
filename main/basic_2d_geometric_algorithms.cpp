struct point{
    double x, y;
};
struct circle{
    point c;
    double r;
};
// compare two double value with maximum relative error EPS(epsilon).
bool lt(double x, double y){ return x < y - EPS; }
bool gt(double x, double y){ return x > y + EPS; }
bool nlt(double x, double y){ return x > y - EPS; }
bool ngt(double x, double y){ return x < y + EPS; }
bool eq(double x, double y){ return fabs(x - y) < EPS; }

bool operator<(const point& a, const point& b){
    return eq(a.x, b.x) ? lt(a.y, b.y) : lt(a.x, b.x);
}

// point-to-point distance
double distance_p2p(const point& p1, const point& p2){
    return hypot(p1.x - p2.x, p1.y - p2.y);
}
// check if two cirles intersect
bool is_intersect_c2c(const circle& a, const circle& b){
    return lt(distance_p2p(a.c, b.c), a.r + b.r)
           && gt(distance_p2p(a.c, b.c), fabs(a.r - b.r));
}
// check if two cirles touch(either internally or externally)
bool is_touch_c2c(const circle& a, const circle& b){
    return eq(distance_p2p(a.c, b.c), a.r + b.r)
           || eq(distance_p2p(a.c, b.c), fabs(a.r - b.r));
}
// touching point of two touching circles.
// invalid if two circles don't touch.
point touching_point_c2c(const circle& a, const circle& b){
    point t;
    if(eq(distance_p2p(a.c, b.c), a.r + b.r)){
        t.x = (a.r * b.c.x + b.r * a.c.x) / (a.r + b.r);
        t.y = (a.r * b.c.y + b.r * a.c.y) / (a.r + b.r);
        return t;
    }
    t.x = (a.r * b.c.x - b.r * a.c.x) / (a.r - b.r);
    t.y = (a.r * b.c.y - b.r * a.c.y) / (a.r - b.r);
    return t;
}
// intersection point of two lines (u1, u2) and (v1, v2).
// NOTE that when the two lines are parrellel or coincident
// the demoninator is ZERO:
// ((u1.x - u2.x)*(v1.y - v2.y) - (u1.y - u2.y)*(v1.x - v2.x)) = 0
// extra judgement can be added to handle this.(return UNDEF or something)
//
// the intersection point is found by substitling the parametric equation of
// (u1, u2) into standard form of (v1, v2).
point intersection_point_l2l(const point& u1, const point& u2,
                             const point& v1, const point& v2){
    point ans = u1;
    double t = ((u1.x - v1.x)*(v1.y - v2.y) - (u1.y - v1.y)*(v1.x - v2.x))/
               ((u1.x - u2.x)*(v1.y - v2.y) - (u1.y - u2.y)*(v1.x - v2.x));
    ans.x += (u2.x - u1.x) * t;
    ans.y += (u2.y - u1.y) * t;
    return ans;
}
// intersection points of the circle c and the line (l1, l2).
// invalid if they are disjoint.
// TODO(zyidong.zheng@gmail.com): need to add some NOTES for disjoint case.
void intersection_points_l2c(const circle& c,
                            const point& l1, const point& l2,
                            point &p1, point &p2){
    point p = c.c;
    double t;
    p.x += l1.y - l2.y;
    p.y += l2.x - l1.x;
    p = intersection_point_l2l(p, c.c, l1, l2);
    t = sqrt(c.r*c.r-distance_p2p(p, c.c)*distance_p2p(p,c.c))/distance_p2p(l1,l2);
    p1.x = p.x + (l2.x - l1.x)*t;
    p1.y = p.y + (l2.y - l1.y)*t;
    p2.x = p.x - (l2.x - l1.x)*t;
    p2.y = p.y - (l2.y - l1.y)*t;
}
// intersection points of two circles c1 and c2.
void intersection_points_c2c(const circle& c1, const circle& c2,
                             point &p1, point &p2){
    point u,v;
    double t;
    t = (1+(c1.r*c1.r-c2.r*c2.r)/distance_p2p(c1.c,c2.c)/distance_p2p(c1.c,c2.c))/2;
    u.x = c1.c.x + (c2.c.x - c1.c.x)*t;
    u.y = c1.c.y + (c2.c.y - c1.c.y)*t;
    v.x = u.x + c1.c.y - c2.c.y;
    v.y = u.y - c1.c.x + c2.c.x;
    intersection_points_l2c(c1, u, v, p1, p2);
}

// cross product of (p1 - p0) and (p2 - p0)
double cross_product(const point& p1, const point& p2, const point& p0) {
    return((p1.x-p0.x) * (p2.y-p0.y) - (p2.x-p0.x) * (p1.y-p0.y));
}

/* Graham's scan for convex hull. */
/* pnt[0..n-1]      :point set */
/* time complexity  : O(nlogn) */
/* space complexity : O(n) */
/* n                :number of points */
/* res[0..n-1]      :vertex of convex hull in counterclockwise order */
/* usage            :
 *     1. the sort strategy used here:
              sorted by y-axis and sorted by x-axis if the y-aixs is the same.
              e.g.
                bool operator<(const point& a, const point& b){
                    return a.y == b.y ? a.x < b.x : a.y < b.y;
                }
       2. call grahams_scan(pnt, n, res);
       3. function returns number of vertex in convex hull and store
          them in res[] in counterclockwise order.
*/
int grahams_scan(point pnt[], int n, point res[]){
    int i, len, top = 1;
    sort(pnt, pnt + n);
    if (n == 0) return 0; res[0] = pnt[0];
    if (n == 1) return 1; res[1] = pnt[1];
    if (n == 2) return 2; res[2] = pnt[2];
    for (i = 2; i<n; ++i){
        while (top && cross_product(pnt[i], res[top], res[top-1]) >= 0)
            top--;
        res[++top] = pnt[i];
    }
    len = top; res[++top] = pnt[n - 2];
    for (i = n - 3; i >= 0; i--) {
        while (top!=len && cross_product(pnt[i], res[top], res[top-1]) >= 0) top--;
        res[++top] = pnt[i];
    }
    return top; // number of vertex of convex hull.
}
