#include <stdio.h>

/*
Scrivi una funzione Point Sum(Point p1, Point p2) che restituisce un nuovo punto ottenuto sommando le coordinate di p1 e p2.
Il risultato deve essere ritornato per valore.
Stampa il risultato nel main().
*/

struct Point{
    float x;
    float y;
};

Point sum(const Point p1, const Point p2){
    Point p;
    p.x = p1.x + p2.x;
    p.y = p1.y + p2.y;
    return p;
}

int main(){
    Point p1;
    p1.x = 0.1f;
    p1.y = 0.3f;

    Point p2;
    p2.x = 0.4f;
    p2.y = 0.1f;

    Point p = sum(p1, p2);

    printf("risultato somma: %f %f\n",p.x,p.y);

    return 0;
}