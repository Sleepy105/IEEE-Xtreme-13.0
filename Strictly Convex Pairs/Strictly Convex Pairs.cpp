#include <iostream>
#include <list>
#include <cmath>
#include <assert.h>

using namespace std;

class Point {
public:
    long x;
    long y;
};

class Line {
    public:
        Line ();
        Point* point1;
        Point* point2;
        bool intersects (Line& line);
    private:
        inline double Det(double a, double b, double c, double d) { return a*d - b*c; }
};

Line::Line () {
    point1 = NULL;
    point2 = NULL;
}

bool colinear(Point* p, Point* q, Point* r) {
    if (q->x <= max(p->x, r->x) &&
        q->x >= min(p->x, r->x) && 
        q->y <= max(p->y, r->y) &&
        q->y >= min(p->y, r->y))
       return true;
    return false; 
} 

int orientation(Point* p, Point* q, Point* r) {
    int val = (q->y - p->y) * (r->x - q->x) - 
              (q->x - p->x) * (r->y - q->y); 

    if (!val)
        return 0;

    return (val > 0) ? 1 : 2;
} 

bool Line::intersects(Line& line1) {

    int o1 = orientation(point1, point2, line1.point1); 
    int o2 = orientation(point1, point2, line1.point2); 
    int o3 = orientation(line1.point1, line1.point2, point1); 
    int o4 = orientation(line1.point1, line1.point2, point2); 
  
    if (o1 != o2 && o3 != o4) 
        return true; 
  
    // Edge Cases
    if (!o1 && colinear(point1, line1.point1, point2))
        return true;
    if (!o2 && colinear(point1, line1.point2, point2))
        return true;
    if (!o3 && colinear(line1.point1, point1, line1.point2))
        return true;
    if (!o4 && colinear(line1.point1, point2, line1.point2))
        return true;
  
    return false;
} 


class Polygon {
public:
    list <Point*> points;
    list <Line*> lines;
};

int main() {
    int n, m;
    cin >> n >> m;
    
    Point poly_points[n];
    for (int i = 0; i < n; i++) {
        cin >> poly_points[i].x >> poly_points[i].y;
    }
    
    Point points[m];
    for (int i = 0; i < m; i++) {
        cin >> points[i].x >> points[i].y;
    }
    
    uint64_t out = 0;
    for (int i = 0; i < m-1; i++) {
        for (int j = i+1; j < m; j++) {
            bool clash = false;
            // Verify if clashes with Polygon
            Line line_tt;
            line_tt.point1 = &points[i];
            line_tt.point2 = &points[j];
            
            for (int k = 0; k < n-1; k++) {
                Line line_poly;
                line_poly.point1 = &poly_points[k];
                line_poly.point2 = &poly_points[k+1];
                if(line_tt.intersects(line_poly)) {
                    clash = true;
                    break;
                }
            }
            if (clash)
                continue;
            else {
                Line line_poly;
                line_poly.point1 = &poly_points[n-1];
                line_poly.point2 = &poly_points[0];
                if(line_tt.intersects(line_poly)) {
                    continue;
                }
            }
            out++;
        }
    }
    
    cout << out << endl;
    
    
    return 0;
}
