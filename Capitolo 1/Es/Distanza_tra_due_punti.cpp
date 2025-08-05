#include <stdio.h>
#include <cmath>

//scrivi una funzione float Distance(Point p1, Point p2) che calcola la distanza tra due punti
//Definisci la struct Point come negli esercizi precedenti.
//Testa la funzione nel main() con due punti a tua scelta.

struct Point{
    float x;
    float y;
};

float Distance(const Point& p1, const Point& p2){
    float dx = p2.x - p1.x;
    float dy = p2.y - p1.y;
    return sqrt(dx*dx + dy*dy);
}

int main(){
    Point p1;
    p1.x = 0.3f;
    p1.y = 0.5f;

    Point p2;
    p2.x = 0.4f;
    p2.y = 0.6f;

    float distance=Distance(p1, p2);
    printf("distance: %f\n",distance);

    return 0;
}