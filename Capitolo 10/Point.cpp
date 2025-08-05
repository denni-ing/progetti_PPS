#include <iostream>

template <typename Element>
class Point{
private:
  Element x;
  Element y;

  void Init(const Element x_, const Element y_){
    x=x_; 
    y=y_;
  }
  
  template <typename T>
  friend Point<T>& operator++(Point<T>& p);
  template <typename T>
  friend bool operator==(const Point<T>& p1, const Point<T>& p2);
  
public:
  Point() {}
  Point(const Element x_, const Element y_) {Init(x_, y_);}
        
  inline Element GetX() const {return x;}
  inline Element GetY() const {return y;}
  inline Element SetX(const Element x_) {x=x_;}
  inline Element SetY(const Element y_) {y=y_;}
};

template <typename Element>
Point<Element>& operator++(Point<Element>& p){
  p.x++;
  p.y++;
  return p;
}

template <typename Element>
bool operator==(const Point<Element>& p1, const Point<Element>& p2){
  return p1.GetX()==p2.GetX() && p1.GetY()==p2.GetY();
}

int main(){

  Point<float> p1(1.2, 1.4);
  Point<float> p2(1.5, 1.7);

  ++p1;
  
  if(p1==p2){
    std::cout << "Sono uguali" << std::endl;
  }else{
    std::cout << "Non sono uguali" << std::endl;
  }
  
  return 0;
}
