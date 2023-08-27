#include <string>
#include <vector>
#include "airport.h"
#include "flights.h"
#include "utils.h"
#include <map>
#include "minheap.h"

class Graph{
    public:
    /* Constructor */
    Graph(const std::string & , const std::string & );

    /* Rule of five destructor */
    ~Graph();

    /* Print functions for debugging */
    std::string  printClosest(std::string s, std::string d);
    void printDistance(std::string source, std::string dest);
    void printAirports();
    void printConnections();
    void printAdjacent(unsigned);
    void printAdjacent(std::string airport);
    void printBFSpath(std::vector<std::string> p);
    void printBFSpath(std::string start, std::string end);
    void printDjiPath(std::vector<std::string> p);
    void printDjiPath(std::string start, std::string end);
    void printDjiDistances(std::string start, std::string end);
    void printShortestStringAndDistance(std::string s, std::string e);
    void printShortestStringAndDistanceCities(std::string s, std::string e);
    void printBFSStringAndDistance(std::string s, std::string e);
    void printBFSStringAndDistanceCities(std::string s, std::string e);




    void createVertices(const std::string & filename);
    void assignNeighbors(const std::string & filename);


    void BFS(Airport* source, bool start);
    void BFS(Airport* a,int);
    std::vector<std::string> BFSpath(std::string start, std::string end);


    void Djikstra(Airport*);
    std::vector<std::string> DjikstraPath(std::string start, std::string end);

    double Centrality(std::string airport);

    int numComponents();
    int count(int);

    std::vector<std::string> findMinPath(std::vector<std::vector<std::string>>, std::string city);   //test case
    std::vector<std::string> findMinPath(std::string city1,std::string city2, bool bfs);     //test case

    std::vector<double> findMinPathDistances(std::vector<std::string> airportString);   //test case
    




    

    long double toRadians(const long double ree);
    double distance(long double lat1, long double long1,long double lat2, long double long2);    //test case
    double distance(Airport* source, Airport* dest);
    double distance(std::string source, std::string dest);       //test case

    std::vector<double> distancesVector(std::vector<std::string> s);     //test case

    double distanceSum(std::vector<double>);     //test case
    bool cityLess(std::string startAirport, std::string endAirport, std::string startCity, std::string endCity, bool bfs);



    Airport*  closest(std::string s, std::string d);     // maybe test case
    
    bool validName(std::string s);
    bool airportExists(std::string);
    bool validCity(std::string s);
    bool cityNoNeighbors(std::string s);
    bool cityExists(std::string);
    bool moreConnected(std::string airport1, std::string airport2);
    /* Needs test case */
    bool noNeighbors(std::string s)
    {
        return nameMap.find(s)->second->getAdjacent().size()==0;

    }

    /* Needs test case */
    std::vector<Airport*> getNeighbors(std::string s)
    {
        return nameMap.find(s)->second->getAdjacent();
    }

    /* Needs test case */
    Airport* find(std::string s)
    {
        return nameMap.find(s)->second;
    }

    /* Needs test case */
    std::vector<std::string> locateAll(std::string);

    std::string Name(unsigned i)
    {   
        return airports[i]->getName();
    }

    std::string City(unsigned i)
    {
        return airports[i]->getCity();
    }

    uint Size();

    int n();



    private:
        /* Storing all vertex as a vector of airports */
        std::vector<Airport*> airports; 

        std::vector<std::pair<std::string,std::string>> connections; 
        std::vector<Flights*> flights; 
        std::map<std::string,Airport*> nameMap;
        std::map<std::string,Airport*> IcaoMap;
        std::map<std::string,Airport*> IataMap;
        std::vector<std::string> names;
        std::vector<std::string> cities;
        
        

};
