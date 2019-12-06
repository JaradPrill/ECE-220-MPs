#include "shape.hpp"
#include <math.h>



//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable 
Shape::Shape(string name){
	name_ = name;
}

string Shape::getName(){
	return name_;
}



//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Rectangle::Rectangle(double width, double length):Shape("Rectangle"){
	width_ = width;
	length_ = length;
}

double Rectangle::getArea() const{return width_*length_;}
double Rectangle::getVolume() const{return 0;}

Rectangle Rectangle::operator+(const Rectangle &rec){
	return Rectangle(width_+rec.width_,length_+rec.length_);
} 

Rectangle Rectangle::operator-(const Rectangle &rec){
	double new_l = (length_-rec.length_)>0 ? length_-rec.length_ : 0;
	double new_w = (width_-rec.width_)>0 ? width_-rec.width_ : 0;
	return Rectangle(new_w, new_l);
}


double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}


//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Circle::Circle(double radius):Shape("Circle"){
	radius_ = radius;
}

double Circle::getArea() const{return radius_*radius_*M_PI;}
double Circle::getVolume() const{return 0;}

Circle Circle::operator+(const Circle &cir){
	return Circle(radius_+cir.radius_);
} 

Circle Circle::operator-(const Circle &cir){
	return Circle((radius_-cir.radius_) > 0 ? radius_-cir.radius_ : 0);
}

double Circle::getRadius()const{return radius_;}

//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
Sphere::Sphere(double radius):Shape("Sphere"){
	radius_ = radius;
}

double Sphere::getArea() const{return radius_*radius_*4*M_PI;}
double Sphere::getVolume() const{return (4.0/3.0)*radius_*radius_*radius_*M_PI;}

Sphere Sphere::operator+(const Sphere &sph){
	return Sphere(radius_+sph.radius_);
} 

Sphere Sphere::operator-(const Sphere &sph){
	return Sphere((radius_-sph.radius_) > 0 ? radius_-sph.radius_ : 0);
}


double Sphere::getRadius()const{return radius_;}

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here


double RectPrism::getWidth()const{return width_;}
double RectPrism::getHeight()const{return height_;}
double RectPrism::getLength()const{return length_;}


 
// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
vector<Shape*> CreateShapes(char* file_name){
	//@@Insert your code here
	vector<Shape*> myshapes;
	int number_shapes;
	string name;
	ifstream ifs ("test.txt", std::ifstream::in);
	ifs >> number_shapes; 
	for (int i = 0; i<number_shapes; i++)
	{
		ifs >> name;
		if (name == "Circle"){
			double r;
			ifs >> r;
			Shape* shape_ptr = new Circle(r);
		}
		if (name == "Rectangle"){
			double w,h;
			ifs >> w >> h;
			Shape* shape_ptr = new Rectangle(w,h);

		}
		if (name == "Sphere"){
			double r;
			ifs >> r;
			Shape* shape_ptr = new Sphere(r);
		}
		if (name == "RectPrism"){
			double w,l,h;
			ifs >> w >> l >> h;
			Shape* shape_ptr = new RectPrism(w,l,h);
		}
	}
	ifs.close;
	return myshapes; // please remeber to modify this line to return the correct value
}

// call getArea() of each object 
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
	int i;
	for(i=0; i<sizeof(shapes); i++) {
		if(shapes[i]->getArea() > max_area) {
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
	int i;
	for(i=0; i<sizeof(shapes); i++) {
		if(shapes[i]->getVolume() > max_volume) {
			max_volume = shapes[i]->getVolume();
		}
	}
	return max_volume;
}
