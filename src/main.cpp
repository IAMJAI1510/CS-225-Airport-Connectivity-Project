#include <iostream>
#include "airport.h"
#include "graph.h"
#include <string>


int main() {

    
        
    //std::cout << "Hello world" << std::endl;
    std::string source;
    std::string dest;
    std::string airport;
    std::string airport2;
    std::cout<<std::endl;

    Graph* g= new Graph("../airports.dat","../routes.dat");
    std::cout<<"Please enter a starting airport:  ";
    
    

    std::getline(std::cin, source);
    while(!g->validName(source)){
        if(!g->airportExists(source))
            std::cout<<"Invalid: Please enter a valid airport source:  ";
        else if(g->noNeighbors(source))
            std::cout<<"This airport has no neighboring airports. Try entering another airport nearby:  ";
        std::getline(std::cin, source);
    }

//std::count(names.begin(),names.end(),airport_name)&&!noNeighbors(airport_name);
    std::cout<<"Please enter a destination airport:  ";
    std::getline(std::cin, dest);
    
    while(!g->airportExists(dest)){
        std::cout<<"Invalid: Please enter a valid airport destination:  ";
        std::getline(std::cin, dest);
    }
    std::cout<<std::endl;

    std::cout<<"(BFS)"<<std::endl<<std::endl;
    g->printBFSStringAndDistance(source, dest);
    std::cout<<"(SHORTEST)"<<std::endl<<std::endl;
      g->printShortestStringAndDistance(source, dest);
    
   //________________________________________

   std::cout<<"Please enter a starting location city:  ";
    
    std::getline(std::cin, source);
    while(!g->validCity(source)){
         if(!g->cityExists(source))
            std::cout<<"Invalid: Please enter a valid city source:  ";
        else if(g->cityNoNeighbors(source))
            std::cout<<"This city has no neighboring airports. Try entering another city nearby:  ";
        std::getline(std::cin, source);
    }


    std::cout<<"Please enter a destination city:  ";
    std::getline(std::cin, dest);
    
    while(!g->validCity(dest)){
        std::cout<<"Invalid: Please enter a valid city destination:  ";
        std::getline(std::cin, dest);
    }
    std::cout<<std::endl;

    std::cout<<"(BFS)"<<std::endl<<std::endl;
    g->printBFSStringAndDistanceCities(source, dest);
    std::cout<<"(SHORTEST)"<<std::endl<<std::endl;
      g->printShortestStringAndDistanceCities(source, dest);
    
   //________________________________________


   std::cout << "[Centrality]" << std::endl<<std::endl;
std::cout << "Please Enter an Airport: ";
    std::getline(std::cin, airport);

    while (!g -> airportExists(airport)) {
        std::cout << "Invalid: Please enter a valid airport destination: ";
        std::getline(std::cin, airport);
    }
    while (g -> noNeighbors(airport)) {
        std::cout << "The airport you selected has no Neighbors so this function cannot be used on it" << std::endl;
        std::getline(std::cin, airport); 
    }


    std::cout << "Please Enter a second Airport: " ;
    std::getline(std::cin, airport2);

    while (!g -> airportExists(airport2)) {
        std::cout << "Invalid: Please enter a valid airport destination: ";
        std::getline(std::cin, airport2);
    }
    while (g -> noNeighbors(airport2)) {
        std::cout << "The airport you selected has no Neighbors so this function cannot be used on it" << std::endl;
        std::getline(std::cin, airport2); 
    }
    std::cout << std::endl;
    
    if (g->moreConnected(airport, airport2)) {
        std::cout << airport << " is more connected to the rest of the network than " << airport2 << std::endl;
    } else {
        std::cout << airport2 << " is less connected to the rest of the network than " << airport << std::endl;
    } 
    std::cout<<std::endl;


    
    return 0;
}


//airports.dat
//../tests/data/c5_s10_3_roster.csv
