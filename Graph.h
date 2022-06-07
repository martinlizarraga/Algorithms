//********************************************************************
// ASU CSE310 Assignment #8 Spring 2022
// Name of Author: Martin Lizarraga
// ASU ID:1219004800
// Description: This is the header file that defines an undirected graph
//              with an array of vertices and edges
//********************************************************************

//include necessary header file here
//----
#include "Edge.h"
using namespace std;

class Graph
{
   private:
      int V, E;         //number of vertices and edges in the graph
      City* cityArr;    //an array of City objects
      Edge* edgeArr;    //an array of Edge objects

   public:
      Graph(int numOfCities, int numOfEdges, City* cityArray, Edge* edgeArray);
      void destructor();
      void make_set(City* aCity);
      City* find_set(City* aCity);
      void link(City* aCity, City* bCity);
      void Union(City* aCity, City* bCity);
      void Quicksort( int p, int r);
      int Partition( int p, int r);
      void Exchange(int a, int b);
      void SortEdges();
  
      void MST_Kruskal();

      //add any auxillary functions in case you need them
      //----
};

Graph::Graph(int numOfCities, int numOfEdges, City* cityArray, Edge* edgeArray){//constructor
   this->V = numOfCities;
   this->E = numOfEdges;
   this->cityArr = cityArray;
   this->edgeArr = edgeArray;
}

void Graph::destructor(){//destructor
   delete cityArr, edgeArr;
}

void Graph::make_set(City* aCity){//set the parent for the city pointer equal to itself and its rank equal to zero
   aCity->parent = aCity;
   aCity->rank = 0;
}

City* Graph::find_set(City* aCity){//see which set a city belongs to by checking who the parent of the set is
   if(aCity->cityName != aCity->parent->cityName){
      aCity->parent = find_set(aCity->parent);//recursively call that city's parent until the overall parent is found
   }
   return aCity->parent;//return the root node
}

void Graph::link(City* aCity, City* bCity){
   if(aCity->rank > bCity->rank){//if city a has a higher rank than city b, have city b join a's set
      bCity->parent = aCity;
   }
   else{
      aCity->parent = bCity;//else set a to be in b's set      
      if(aCity->rank == bCity->rank){//if they have equal ranks then b's rank needs to be incremented
         bCity->rank = bCity->rank+1;
      }
   }
}

void Graph::Union(City* aCity, City* bCity){
   link(find_set(aCity),find_set(bCity));//calls link for the two cities passed in 
}

void Graph::Quicksort(int p , int r){
   if(p<r){//p is from zero, r is from the last edge, so it should loop through all the edges
      int q = Partition(p, r);
      Quicksort(p,q-1);//quicksort from p to q-1 recursively
      Quicksort(q+1,r);//same thing for q+1 to r, second half
   }
}

int Graph::Partition(int p, int r){
   int i = p-1;
   for(int j = p; j<=r-1; j++){
      if(edgeArr[j].getDistance() <= edgeArr[r].getDistance()){//if the city at point j has a smaller distance than the one at r exchange the two cities and increment i
         i++;
         Exchange(i, j);
      }
   }
   Exchange(i+1, r);//exchange the last two at the end
   return (i+1);//return i+1
}



void Graph::Exchange(int a, int b){
   Edge* temp = new Edge;//create temp city to hold all of cityA's information
   
   temp->setCity1(edgeArr[a].getCity1());
   temp->setCity2(edgeArr[a].getCity2());
   temp->setDistance(edgeArr[a].getDistance());

   edgeArr[a] = edgeArr[b];//set the spot where a is equal to city at position b

   edgeArr[b].setCity1(temp->getCity1());//transfer temp's information into the city at spot b
   edgeArr[b].setCity2(temp->getCity2());
   edgeArr[b].setDistance(temp->getDistance());
}

void Graph::SortEdges(){
   Quicksort(0, E-1);//calls quicksort for all the edges
}



//*******************************************************************
//This function performs the Kruskal algorithm on the graph.
void Graph::MST_Kruskal()
{
   cout << "MST Kruskal Algorithm Result\n" << endl;
   double totalDistance = 0.0;

   for(int i = 0; i < V; i++){
      make_set(&cityArr[i]);//make each city have it's own set
   }
   
   SortEdges();//sort the edge array so they're in increasing order


   for(int i = 0; i < E-1; i++){
      City* city1 = edgeArr[i].getCity1();
      City* city2 = edgeArr[i].getCity2();
      if(find_set(city1)->cityName.compare(find_set(city2)->cityName) != 0 ){//check if the cities are in the same array
         totalDistance = totalDistance + edgeArr[i].getDistance();//increment the size when you combine the two cities
         Union(edgeArr[i].getCity1(), edgeArr[i].getCity2());//put the cities in the same set
         edgeArr[i].printEdge();//print the edge
      }      
   }

   cout << "=================================================" << endl;
   cout << "Total Distance: " << totalDistance << endl;
}