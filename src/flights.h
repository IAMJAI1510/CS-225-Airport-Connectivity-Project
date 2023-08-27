#pragma once
#include <string>
#include <vector>
#include "airport.h"
#include "flights.h"
#include <cmath>

class Flights{

    public:
    Flights(std::string s, std::string d){source=s; dest=d; explored=false;}
    // long double toRadians(const long double ree);
    // double distance(long double lat1, long double long1, long double lat2, long double long2);
    void setLabel(bool label){explored=label;}
    bool getLabel(){return explored;}

    private:
    std::string source;
    std::string dest;
    bool explored=false;


};
