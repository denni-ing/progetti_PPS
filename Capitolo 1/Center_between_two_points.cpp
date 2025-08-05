#include <stdio.h>

struct Point{
    float x; // x coordinates of a point
    float y; // y coordinates of a point
};

void Center(const Point& p1, const Point& p2, Point* center){
    center->x = (p1.x + p2.x)/2;
    center->y = (p1.y + p2.y)/2;
}

int main(){

    Point p1;
    p1.x = 0.03f;
    p1.y = 0.05f;

    Point p2;
    p2.x = 0.06f;
    p2.y = 0.04f;

    Point center;
    Center(p1, p2, &center);

    printf("%f %f\n",center.x,center.y);

    return 0;

}
