#include <stdio.h>
#include <math.h>

/*
Scrivi una funzione void Rotate(Point* p, float angle) che ruota un punto attorno all'origine (0,0) di un angolo angle (espresso in radianti).
Usa la libreria <math.h> per cos() e sin().
Testa la funzione ruotando un punto di 90° (pi/2 radianti) e verifica il risultato.
*/


struct Point{
    float x;
    float y;
};

void Rotate(Point* p, const float angle){
    float temp_x = p->x;
    float temp_y = p->y;

    p->x = temp_x*cos(angle) - temp_y*sin(angle);
    p->y = temp_x*sin(angle) + temp_y*cos(angle);
}

int main(){
    Point p;
    p.x = 1.0f;
    p.y = 0.0f;

    float angle = M_PI/2;

    Rotate(&p, angle);

    printf("rotation: %f %f\n",p.x,p.y);

    return 0;
}