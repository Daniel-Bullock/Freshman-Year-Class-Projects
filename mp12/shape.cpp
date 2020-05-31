#include "shape.hpp"
#include <math.h>


//Base class
//Please implement Shape's member functions
//constructor, getName()
  Shape::Shape(string name){
    name_ = name;
  }
  string Shape::getName(){
    return name_;
  }


//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable



//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here


Rectangle::Rectangle(double width, double length):Shape("Rectangle"){

  width_ = width;
  length_ = length;
}
double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}
double Rectangle::getArea()const {return (length_ * width_); //ar
}
double Rectangle::getVolume()const {
  return 0;
}
Rectangle Rectangle::operator + (const Rectangle& rec) {
  Rectangle *NewRectangle = new Rectangle(0,0); //making a new rectangle
  NewRectangle->width_ = fmax(0,width_ + rec.getWidth());
  NewRectangle->length_ = fmax(0,length_ + rec.getLength());
  return *NewRectangle;

}
Rectangle Rectangle::operator - (const Rectangle& rec) {
  Rectangle *NewRectangle = new Rectangle(0,0);
  NewRectangle->width_ = fmax(0,width_ - rec.getWidth());
  NewRectangle->length_ = fmax(0,length_ - rec.getLength());
  return *NewRectangle;

}

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Circle::Circle(double radius):Shape("Circle"){
  radius_=radius;
}
double Circle::getRadius()const{return radius_;}
double Circle::getArea()const{
  return (M_PI * radius_ * radius_ );
}
double Circle::getVolume()const{
  return 0;
}
Circle Circle::operator + (const Circle& cir) {
  Circle *NewCircle = new Circle(0);
  NewCircle->radius_ = fmax(0,radius_ + cir.getRadius());
  return *NewCircle;
}
Circle Circle::operator - (const Circle& cir) {
  Circle *NewCircle = new Circle(0);
  NewCircle->radius_ = fmax(0,radius_ - cir.getRadius());
  return *NewCircle;
}
//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Sphere::Sphere(double radius):Shape("Sphere"){
  radius_ = radius;
}
double Sphere::getVolume()const{
  return (4.0/3.0) * radius_ * radius_ * radius_ * M_PI; // equation for volume sphere
}
double Sphere::getArea() const { // equation for area of a sphere
  return 4 * M_PI * radius_ * radius_;
}
Sphere Sphere::operator + (const Sphere& sph) { //add spheres
  Sphere *NewSphere = new Sphere(0);
  NewSphere->radius_ = fmax(0,radius_ + sph.getRadius());
  return *NewSphere;
}
Sphere Sphere::operator - (const Sphere& sph) { // subtract spheres
  Sphere *NewSphere = new Sphere(0);
  NewSphere->radius_ = fmax(0,radius_ - sph.getRadius());
  return *NewSphere;
}
double Sphere::getRadius()const{return radius_;}

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

RectPrism::RectPrism(double width, double length, double height):Shape("RectPrism") {
  width_ = width; // intialize width_
  length_ = length; //initialize length_
  height_= height; //initialize height_
}
double RectPrism::getWidth()const{return width_;} // pull the data
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}
double RectPrism::getVolume()const{
  return width_ * height_ * length_; //get volume given inputs
}
double RectPrism::getArea()const{
  return 2.0 * (width_ * height_ + width_*length_ + height_*length_); // find the area of the rectangle
}
RectPrism RectPrism::operator + (const RectPrism& rectp) {
  width_ += rectp.getWidth();
  length_ += rectp.getLength();
  height_ += rectp.getHeight();
  return *this; //adds the rectangles
}
RectPrism RectPrism::operator - (const RectPrism& rectp) {
  width_ -= rectp.getWidth();
  length_ -= rectp.getLength();
  height_ -= rectp.getHeight();
  if (length_ < 0) {
    length_ = 0;
  }
  if (width_ < 0) {
    width_ = 0;
  }
  if (height_ < 0) {
    height_ = 0;
  }
  return *this;
} //subtracts rectangles

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
vector<Shape*> CreateShapes(char* file_name){
	//@@Insert your code here

  vector<Shape*> shapevct;
  int count;
  string shapetype;
  ifstream ifs (file_name, std::ifstream::in);
  ifs >> count;
  while(count!=0){
    count = count - 1;
    ifs >> shapetype;
    if(shapetype == "Circle"){
      double r;
      ifs >> r;
      Shape* shape_ptr = new Circle(r);
      shapevct.push_back(shape_ptr);
    }
    if(shapetype == "Rectangle"){
      double w;
      double h;
      ifs >> w >> h;
      Shape* shape_ptr = new Rectangle(w,h);
      shapevct.push_back(shape_ptr);
    }
    if(shapetype == "Sphere"){
      double r;
      ifs >> r;
      Shape* shape_ptr = new Sphere(r);
      shapevct.push_back(shape_ptr);
    }
    if(shapetype == "RectPrism"){
      double w;
      double h;
      double l;
      ifs >> w >> h >> l;
      Shape* shape_ptr = new RectPrism(w,h,l);
      shapevct.push_back(shape_ptr);
    }
  }

  ifs.close();

	return shapevct; // please remeber to modify this line to return the correct value
}

// call getArea() of each object
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
  for(int i = 0; i < shapes.size();i++){
    if(shapes[i]->getArea()>max_area){
      max_area = shapes[i]->getArea();
    }
  }
	return max_area;
}


// call getVolume() of each object
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here
  for(int i = 0; i < shapes.size();i++){
    if(shapes[i]->getVolume()>max_volume){
      max_volume = shapes[i]->getVolume();
    }
  }
	return max_volume;
}
