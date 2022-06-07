//************************************************************************
// ASU CSE310 Assignment #8 Spring 2022
// ASU ID:1219004800
// Name:Martin Lizarraga
// Description: this is the main program that reads input from keyboard,
// it then use disjoint set data structure to perform Kruskal MST algorithm
// on the graph.
// //---- is where you need to add your own codes
//**************************************************************************

#include "Graph.h"

using namespace std;

void getArrCityInfo(string oneArrCityInfo, string& arrCityName, double& distance);
int searchCity(City* oneCityArray, int size, string oneCityName);

int main()
{
   int V, E;        //number of vertices and edges
   string arrCityName;
   double distance;
   //cout << "Enter number of vertices and edges: " << endl;


   cin >> V >> E;
   cin.ignore(20, '\n');

   //a City array used to store all vertices (Cities) of the graph
   City* cityArray = new City[V];
   int arrayCurrSize = 0;
   int edgeCurrSize = 0;

   //an array used to store all edges of the graph
   Edge* edgeArray = new Edge[E];

   //----
   //----

   int i =0, j=0; //index for cityArray and edgeArray

   //local variables
   City* city1;
   City* city2;
   Edge* aNewEdge;

   string oneLine;

   //cout << "Enter one departure and its arrival city info." << endl;
   getline(cin, oneLine);



   while(oneLine.compare("End") != 0)//while the user hasn't told the program to end
   {


      string depCityName;
      string delimiter = ",";
      int pos = oneLine.find(delimiter);
      string token = oneLine.substr(0, pos);
      depCityName = token;
      oneLine.erase(0, pos+delimiter.length());//extract the departure city name and delete it from the one line user input
      


      int found = searchCity(cityArray,V,depCityName);//see if the city exists in the city array, if it doesn found is the spot in the array where it is, if not found is -1

      if(found == -1){//if not found
         City temp;
         temp.cityName = depCityName;


         cityArray[arrayCurrSize] = temp;
         city1 = &cityArray[arrayCurrSize];//create a new city and insert it into the array at the last empty spot in the array
         arrayCurrSize++;//incremement the spot
      }
      else{
         city1 = &cityArray[found];//if it's already in the array just set city one pointer equal to that for the edge
      }



      while(oneLine.length() > 1){//if the string is greater than one that means there are arrival cities from the departure city
         pos = oneLine.find(delimiter);
         token = oneLine.substr(0, pos);
         getArrCityInfo(token, arrCityName, distance);//get the information such as distance and name from each segment of arrival cities


         found = searchCity(cityArray, V, arrCityName);

         if(found == -1){//if not found
            City temp;
            temp.cityName = arrCityName;

            cityArray[arrayCurrSize] = temp;
            city2 = &cityArray[arrayCurrSize];//create new city and insert in array
            arrayCurrSize++;
         }
         else{
            city2 = &cityArray[found];//have city 2 pointer just point to the city at its spot in the city array
         }

         oneLine.erase(0, pos+delimiter.length());//erase that segment 

         
         aNewEdge = new Edge(city1,city2,distance);//insert the new edge with the extracted distance city1 and city2 pointers and insert it into the edge array
         edgeArray[edgeCurrSize] = *aNewEdge;
         edgeCurrSize++;//increment edge array size
      }




      getline(cin, oneLine);
   } //repeat until the 'End'


   Graph* graph = new Graph(V, E, cityArray, edgeArray);//create new graph given both arrays, vertices, and edges



   graph->MST_Kruskal();//run Kruskal on the graph

}

//****************************************************************
//By giving a string, for example 'Dallas(1456.5)', this function
//extract the arrival city name 'Dallas' and distance '1456.5'
//Note: the delimeter is left or right parenthesis
//****************************************************************
void getArrCityInfo(string oneArrCityInfo, string& arrCityName, double& distance)
{
   string delimiter1 = "(";
   string delimiter2 = ")";

   string hold;


//Arr city is everything up until the '(' delimiter, extract that from the string and set arrCityName to that
   int pos = oneArrCityInfo.find(delimiter1);
   hold = oneArrCityInfo.substr(0, pos);
   arrCityName = hold;
   oneArrCityInfo.erase(0, pos + delimiter1.length());

//the distance is between the other ')' delimiter, extract that from the string and set distance equal to that
   pos = oneArrCityInfo.find(delimiter2);
   hold = oneArrCityInfo.substr(0, pos);
   distance = stod(hold);
   oneArrCityInfo.erase(0 + pos + delimiter2.length());
}

//*********************************************************************
//Given a city name, this function searches cityArray and it return the
//index of the City if it exists, otherwise it returns -1
//****************************************************************
int searchCity(City* oneCityArray, int arraySize, string oneCityName)
{
  for(int i = 0; i<arraySize; i++){//loop through the array
      if(oneCityArray[i].cityName != oneCityName){         
      
      }
      else{//if the city is found in the array return the position where it was
         return i;   
      }
  }
  return -1;//if not found return -1
}