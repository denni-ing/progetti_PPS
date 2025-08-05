#include <stdio.h>

/*
Scrivi una funzione void Translate(Point* p, float dx, float dy) che trasla un punto aggiungendo dx e dy alle sue coordinate.
Il punto deve essere passato per indirizzo per modificare direttamente i suoi valori.
Nel main(), inizializza un punto, traslalo e stampa le nuove coordinate.
*/

struct Point{
    float x;
    float y;
};

void Translate(Point* p, const float dx, const float dy){
    p->x=p->x + dx;
    p->y=p->y + dy;
}

int main(){
    float dx = 0.2f;
    float dy = 0.3f;

    Point p;
    p.x=0.4f;
    p.y=0.5f;

    Translate(&p, dx, dy);

    printf("Traslation: %f %f\n",p.x,p.y);

    return 0;
}
