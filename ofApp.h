#pragma once

#include "ofMain.h"

//RAY_MARCHING===============================================
//RAY: defines ray w/ origin and distance
class Ray {
public:
    //Ray constructor(s)
    Ray() {}
    Ray(glm::vec3 origin, glm::vec3 direction) {
        p = origin;
        d = direction;
    }
    
    glm::vec3 p;        //origin of ray
    glm::vec3 d;    //direction of ray
};

//Shape: Base class FOR ALL PRIMITIVES (to be put into dynamic vector)
class Shape {
public:
    Shape() {}     //constructor
    
    virtual float sdf(const glm::vec3 &p) { return 0.0; }
    
    //Attributes---------------------------------------------
    glm::vec3 position;     //position of shape
    ofColor color;          //color of shape by default

	//phong shading
	ofColor ambient;
	ofColor diffuse;
	ofColor specular;
	float shininess;
	//float reflectivity;
    
};

//Sphere: sphere w/ inherited position/color and radius
class Sphere : public Shape {
public:
    //constructor(s)-----------------------------------------
    Sphere() {
        position = glm::vec3(0, 0, 9);      //center of sphere @ origin
        radius = 3.0;
        color = ofColor::blue;

		//phong shading
		ambient = ofColor(5, 5, 25);			//natural color in darkness
		diffuse = ofColor(0, 127, 127);			//when shined upon
		specular = ofColor(55, 55, 55);			//sparkle upon object
		shininess = 2.0;
    }
    Sphere(glm::vec3 p, float r, ofColor c);
    //end constructor(s)-------------------------------------
    
    //Sphere::sdf: based on CS116B.Lec6----------------------
	float sdf(const glm::vec3 &p) {					
		return glm::length(p - position) - radius;		//glm::length -> return distance between 2 vecs
	} 
    float radius;       //radius of circle
};

//Plane: plane w/ inherited position/color
class Plane : public Shape {
public:
	Plane() {
		position = glm::vec3(0, -6, -2);
		color = ofColor::green;

		ambient = ofColor(20, 20, 20);
		diffuse = ofColor(150, 150, 150);
		specular = ofColor(25, 25, 25);
		shininess = 1.0;
	}
	
	//Plane::sdf: replicated from CS116B.Lec6----------------
	float sdf(const glm::vec3 &p) { return p.y - position.y; }		//only consider the ground plane
};


//Plane: plane w/ inherited position/color
class Torus : public Shape {
public:
	Torus() {
		position = glm::vec3(15, 4, 2);
		color = ofColor::orange;

		//phong shading
		ambient = ofColor(25, 5, 25);
		diffuse = ofColor(255, 69, 0);
		specular = ofColor(55, 55, 55);
		shininess = 5.0;
	}

	//Plane::sdf: replicated from CS116B.Lec6----------------
	float sdf(const glm::vec3 &p);		//only consider the ground 

	glm::vec2 t = glm::vec2(5, 1);		//radius/thickness
};


//Capped Cylinder: cylinder w/ inherited position/color w/ height & radius
class Cylinder: public Shape {
public:
	Cylinder() {
		position = glm::vec3(0, 9, -2);
		color = ofColor::violet;

		//phong shading
		ambient = ofColor(50, 10, 10);
		diffuse = ofColor(255, 50, 50);
		specular = ofColor(50, 50, 50);
		shininess = 2.0;
	}

	//Cylinder::sdf - obtained from [ https://www.iquilezles.org/www/articles/distfunctions/distfunctions.htm ]
	float sdf(const glm::vec3 &p);
	glm::vec3 c = glm::vec3(0, 0, 0);

};



//Plane: plane w/ inherited position/color

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
    
    
    //ofEasyCam marchCam;
    
    //RAY_MARCH COMPONENTS-----------------------------------
    vector<Shape *> scene;      //scene of pointer to objects within scene
	vector<glm::vec3> lights;	//lights

	//ofLight light;			//light scene
    
    ofImage img;          //image output for scene
    
    float sceneSDF(const glm::vec3 &p, int &shape);     //sceneSDF (based on CS116B.Lec6 pseudocode)
    bool rayMarch(Ray &r, glm::vec3 &p, int &shape);   //ray-marching algorithm (replicated from CS116B.Lec6)
    void rayMarchLoop();                  //begin rendering img using raymarch (based on CS116B.Lec6 pseudocode)

	//phong shading
	ofColor phongRM(const glm::vec3 &p, const glm::vec3 &norm, const ofColor ambient, const ofColor diffuse, const ofColor specular, float shininess);		//provided in CS116B.Lec6 slides
    glm::vec3 getNormalRM(const glm::vec3 &p);      //normal after hit (replicated from CS116B.Lec6)
};
