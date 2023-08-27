#pragma once
#include <string>
#include <vector>
#include "airport.h"
class Airport {
    public:
        Airport(std::string name, std::string city, std::string country, std::string iata, std::string icao, double longitude, double latitude);
        bool areConnected(std::string airport_name1, std::string airport_name2);     //test case
        std::vector<int> getCoordinates(std::string airport_name);                      //test case
        std::string getCountry();
        double getLat();
        
        double getLong();
        std::string getIata();
        std::string getIcao();
        std::string getName();
        std::string getCity();

        void addNeighbor(Airport*);

        void printAdjacent();
        bool notNeighbors(Airport*);

        void setDjiDistance(double d){
        
    
}

    //      long double toRadians(const long double ree);
    // double distance(long double lat1, long double long1,
    //                 long double lat2, long double long2);


void setLabel(bool label){explored=label;}
    bool getLabel(){return explored;}

    std::vector<Airport*>& getAdjacent(){        //test case
        return neighbors;
    }

    void setDjiExplored(bool label){djiExplored=label;}
    bool wasDjiExplored(){return djiExplored;}

    



    void setBFSPred(Airport*);
    Airport* getBFSPred()
    {
        return bfsPred;
    }

    void setDjiPred(Airport* d){djiPred=d;}
    Airport* getDjiPred()
    {
        return djiPred;
    }
    void setDjiDist(double d){djiDist=d;}
    double getDjiDist()
    {
        return djiDist;
    }

    int getComp(){return component;}
    void setComp(int i){component=i;}
        


    private:
    std::string name;
    std::string city;
    std::string iata;
    std::string icao;
    std::string country;
    double longitude;
    double latitude;
    Airport* bfsPred;
    //double distance;
    bool explored;
    bool djiExplored;
    bool inDjiSet;
    double djiDist;
    Airport* djiPred;
    int component;


    
    std::vector<Airport*> neighbors;


};