#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>


#include "utils.h"
#include <algorithm>
#include "airport.h"
#include <vector>
#include <string>
#include<iostream>

Airport::Airport(std::string n, std::string cit, std::string c,std::string ia, std::string ic, double la, double lo)
{
     country = c;
     city = cit;
     name = n;
     iata = ia;
     icao = ic;
     longitude = lo;
     latitude = la;
}


bool Airport::areConnected(std::string airport_name1, std::string airport_name2)
{
  return false;
}

std::vector<int> Airport::getCoordinates(std::string airport_name){
     return std::vector<int>();
}

std::string Airport::getCountry()
{
  return country;
}

double Airport::getLat()
{
    return latitude;
}

double Airport::getLong()
{
    return longitude;
}

std::string Airport::getIata()
{
  return iata;
}

std::string Airport::getIcao()
{
  return icao;
}

std::string Airport::getName()
{
    return name;
}

void Airport::setBFSPred(Airport *b)
{
  bfsPred = b;
}

void Airport::addNeighbor(Airport* b)
{
  neighbors.push_back(b);
}

void Airport::printAdjacent()
{
  std::cout << std::endl << std::endl;
  std::cout << name << "'s destinations are:      ";

  for(Airport* a: neighbors) std::cout << a->name << "       ";
  std::cout << std::endl << std::endl;
}

bool Airport::notNeighbors(Airport* b)
{
  return !std::count(neighbors.begin(), neighbors.end(), b);
}

std::string Airport::getCity()
{
  return city;
}