struct ConvexHull {
    vector <point> pts;
    /* return convex hull's size. and v-1 is the number of convex hull's points */
    vector <point> convex() {
        int n = pts.size();
        vector <point> u, d;

        sort(pts.begin(), pts.end()); // sort x and y
        for (int i = 0; i < n; i++) {
            while (u.size() >= 2 && ccw(u[u.size()-2], u.back(), pts[i]) >= 0)
                u.pop_back();
            
            u.push_back(pts[i]);
            
            while (d.size() >= 2 && ccw(d[d.size()-2], d.back(), pts[i]) <= 0)
                d.pop_back();
            
            d.push_back(pts[i]);
        }
        u.insert(u.end(), next(d.rbegin()), prev(d.rend()));
        return u;
    }
};
