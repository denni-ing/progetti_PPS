#include <stdio.h>
#include <iostream>

class Point{
    private:
        float x;
        float y;

    public:
        Point(){
            x = 0.0f;
            y = 0.0f;
        }
        Point(float x_, float y_){
            x = x_;
            y = y_;
        }
        float GetX(){
            return x;
        }
        float GetY(){
            return y;
        }
        void SetX(float x_){
            x = x_;
        }
        void SetY(float y_){
            y = y_;
        }
};

class Rectangle{
    private:
        Point anchor; //punto di ancoraggio
        float width; //base
        float height; //altezza

    public:
        Rectangle(){
            width = 0.0f;
            height = 0.0f;
        }
        Rectangle(Point anchor_, float width_, float height_){
            anchor = anchor_;
            width = width_;
            height = height_;
        }
        float GetWidth(){
            return width;
        }
        float GetHeight(){
            return height;
        }
        float Area(){
            return width * height;
        }
        float Perimeter(){
            if (width == height){
                return width * 4;
            }else{
                return (width * 2) + (height * 2);
            }
        }
        void Center(Point* center){
            float x = center->GetX();
            float y = center->GetY();

            float cx = x + width/2;
            float cy = y + height/2;

            center->SetX(cx);
            center->SetY(cy);
        }
};

int main(){

    Point anchor(0.0f, 0.0f);
    std::cout << "Anchor: " << anchor.GetX() << " " << anchor.GetY() << std::endl;
    Rectangle rect(anchor, 10.0f, 10.0f);
    std::cout << "Rectangle: " << rect.GetWidth() << " " << rect.GetHeight() << std::endl;
    std::cout << "Area: " << rect.Area() << std::endl;
    std::cout << "Perimeter: " << rect.Perimeter() << std::endl;

    Point center(0.0f, 0.0f);
    rect.Center(&center);
    std::cout << "Centro: " << center.GetX() << " " << center.GetY() << std::endl;

    return 0;
}
