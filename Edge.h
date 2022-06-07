//******************************************************************************
// ASU CSE310 Assignment #8 Spring 2022
// Name of Author:Martin Lizarraga
// ASU ID:1219004800
// Description: this header file defines an edge in the graph. Each edge
//              has 3 attributes, namely two Cities and the distance between them
//*******************************************************************************
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//City represents one vertex of the graph
struct City
{
   string cityName;
   int rank;
   struct City* parent;

   //constructor
   City(string name)
   {
      cityName = name;
      rank = 0;
      parent = NULL;
   }

   //default constructor. C++ don't provide one, need it here.
   City()
   {
      cityName;
      rank = NULL;
      parent = NULL;
   }
};

//class Edge represents one edge of the graph which connects two City objects
class Edge
{
   private:
   struct City* city1;
   struct City* city2;
   double distance;

   public:
   Edge(City* city1, City* city2, double distance);
   Edge();  //default constructor
   ~Edge();
   City* getCity1();
   City* getCity2();
   double getDistance();
   void printEdge();
   void setCity1(City* param);
   void setCity2(City* param);
   void setDistance(double distance);
};

Edge::Edge(City* city1, City* city2, double distance){//constructor
   this->city1 = city1;
   this->city2 = city2;
   this->distance = distance;
}

Edge::Edge(){//default constructor

}

Edge::~Edge(){//destructor
   delete city1, city2;
}

City* Edge::getCity1(){//city1 getter
   return city1;
}

void Edge::setCity1(City* param){//setter for city1
   this->city1 = param;
}

void Edge::setCity2(City* param){//setter for city2
   this->city2 = param;
}

void Edge::setDistance(double distance){//set the distance for the edge
   this->distance = distance;
}

City* Edge::getCity2(){//return city2
   return city2;
}

double Edge::getDistance(){//return distance
   return distance;
}


void Edge::printEdge()
{
   cout << left;
   cout << setw(15) << city1->cityName
   << setw(8) << "<--->"
   << setw(15) << city2->cityName
   << setw(3) << " = "
   << setw(8) << right << fixed << setprecision(2) << getDistance()
   << endl;
}