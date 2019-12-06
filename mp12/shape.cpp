#include "shape.hpp"



//Base class
//Please implement Shape's member functions
//constructor, getName()
//
//Base class' constructor should be called in derived classes'
//constructor to initizlize Shape's private variable 



//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
double Rectangle::getArea()const{return width_*length_;}
double Rectangle::getVolume()const{return 0;}

double Rectangle::getWidth()const{return width_;}
double Rectangle::getLength()const{return length_;}


//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

double Circle::getRadius()const{return radius_;}

//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here



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
	int num_of_shapes, i;
	vector<Shape*> vector_array;
	string shape_name;
	ifstream ifs ("test.txt", std::ifstream::in);
	ifs >> num_of_shapes;
	for (i=0;i<num_of_shapes;i++){
		ifs >> shape_name;
		if (shape_name=="circle"){
			int radius;
			ifs >> radius;
			Shape* shape_ptr = new Circle(radius);
			vector_array.push_back(shape_ptr);
		}
		else if (shape_name == "rectangle"){
			int width, length;
			ifs >> width >> length;
			Shape* shape_ptr = new Rectangle(width, length);
			vector_array.push_back(shape_ptr);
		}
		else if (shape_name == "RectPrism"){
			int width, height, length;
			ifs >> width >> height >> length;
			Shape* shape_ptr = new RectPrism(width, height, length);
			vector_array.push_back(shape_ptr);
		}
		else{
			int radius;
			ifs >> radius;
			Shape* shape_ptr = new Sphere(radius);
			vector_array.push_back(shape_ptr);
		}
	}
	ifs.close();
	return vector_array; // please remeber to modify this line to return the correct value
}

// call getArea() of each object 
// return the max area
double MaxArea(vector<Shape*> shapes){
	double max_area = 0;
	//@@Insert your code here
	
	return max_area;
}


// call getVolume() of each object 
// return the max volume
double MaxVolume(vector<Shape*> shapes){
	double max_volume = 0;
	//@@Insert your code here

	
	return max_volume;
}

