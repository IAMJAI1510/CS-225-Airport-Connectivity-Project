//#include "../cs225/catch/catch.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <cmath>
#include "../src/graph.h"
#include "../src/airport.h"
#include "../src/flights.h"
#include "../src/utils.h"
#include "../src/minheap.h"
#include <catch2/catch_test_macros.hpp>



 TEST_CASE("test true"){
    REQUIRE(true);
}


TEST_CASE("testing airportExists on dataset"){
    Graph* g= new Graph("../airports.dat","../routes.dat");

   
    REQUIRE(g->airportExists("Chicago O'Hare International Airport")==true);    //  a valid airport
    REQUIRE(g->airportExists("Chicago Airport")==false);   // any random incorrect airport (not in the dataset)
}




TEST_CASE("testing locateAll airports in a city on dataset"){
    Graph* g= new Graph("../airports.dat","../routes.dat");

    std::vector<std::string> allAirports=g->locateAll("Chicago");
    std::vector<std::string> correctAirports={"Chicago Midway International Airport", "Waukegan National Airport",
  "Chicago O'Hare International Airport", "Chicago Meigs Airport"};

   std::vector<std::string> correctAirport={"Mouilla Ville Airport"};


    REQUIRE(allAirports.size()==4);    //  a valid airport
    REQUIRE(allAirports==correctAirports);   // any random incorrect airport (not in the dataset)
    REQUIRE(g->locateAll("Mouila").size()==1);
    REQUIRE(g->locateAll("Mouila")==correctAirport);
}




TEST_CASE("testing amount of neighbors on an airport on dataset"){
    Graph* g = new Graph("../airports.dat","../routes.dat");


    REQUIRE(g->noNeighbors("Dongshan Airport")==false);    //  airport with neighbors
    std::vector<std::string> m={"Baita International Airport", "Chita-Kadala Airport", "Beijing Capital International Airport", "Chifeng Airport", "Taiping Airport","Jiagedaqi Airport", "Tongliao Airport", "Beijing Nanyuan Airport", "Choibalsan Airport"};
    std::vector<std::string> n;
    for(Airport* a: g->getNeighbors("Dongshan Airport"))
        n.push_back(a->getName());

    REQUIRE(g->getNeighbors("Dongshan Airport").size()==9); 
    REQUIRE(n==m)  ;
    REQUIRE(g->getNeighbors("Mouilla Ville Airport").size()==0);
    REQUIRE(g->noNeighbors("Mouilla Ville Airport"));
  
}





TEST_CASE("testing distance function"){ //tests all distance functions and find functions
    Graph* g= new Graph("../airports.dat","../routes.dat");
    REQUIRE(floor(g->distance(-31.0839004517,150.847000122, 22.608299255371094,108.1719970703125))==7504);
    REQUIRE(floor(g->distance(g->find("La Guardia Airport"),g->find("Chicago O'Hare International Airport")))==1177);
    REQUIRE(floor(g->distance(g->find("La Guardia Airport")->getLat(),g->find("La Guardia Airport")->getLong(),g->find("Chicago O'Hare International Airport")->getLat(),g->find("Chicago O'Hare International Airport")->getLong()))==1177);
}


TEST_CASE("testing distance between airports in a city on dataset"){//uses distance function on lat and long of airports
    Graph* g= new Graph("../airports.dat","../routes.dat");
   
    REQUIRE(floor(g->distance("Mouilla Ville Airport", "Chicago O'Hare International Airport"))==10884);
    REQUIRE(floor(g->distance("La Guardia Airport", "Chicago O'Hare International Airport"))==1177);
}



    







//ALGORITHMS TESTS


//______________________________________________________

//BFS and Djikstra Tests when inputs are AIRPORTS

//BFS AIRPORT TESTS
TEST_CASE("testing num components"){
    Graph* g= new Graph("../airports.dat","../routes.dat");

   
        REQUIRE(g->numComponents() == 4468);
    
}


TEST_CASE("testing BFS airport"){
    Graph* g= new Graph("../airports.dat","../routes.dat");
    std::vector<std::string> path= g->BFSpath("Muskegon County Airport", "Chicago O'Hare International Airport");
    std::vector<std::string> correct_path={"Muskegon County Airport", "Chicago O'Hare International Airport"};
    REQUIRE(path==correct_path);
   
}


TEST_CASE("testing BFS airport complex"){
    Graph* g= new Graph("../airports.dat","../routes.dat");
    std::vector<std::string> path= g->BFSpath("Columbia Regional Airport", "Marseille Provence Airport");
    std::vector<std::string> correct_path={"Columbia Regional Airport", "Dallas Fort Worth International Airport", "Charles de Gaulle International Airport", "Marseille Provence Airport"};
    REQUIRE(path==correct_path);
   
}

TEST_CASE("testing BFS airport no connection to exact airport"){
    Graph* g= new Graph("../airports.dat","../routes.dat");
    std::vector<std::string> path= g->BFSpath("Chicago O'Hare International Airport", "Salon-de-Provence (BA 701) Air Base");
    std::vector<std::string> correct_path={"Chicago O'Hare International Airport", "Charles de Gaulle International Airport","Marseille Provence Airport"};
    REQUIRE(path==correct_path);
   
}


TEST_CASE("testing BFS airport no source airport no connected to anything"){
    Graph* g= new Graph("../airports.dat","../routes.dat");
    std::vector<std::string> path= g->BFSpath("Mouilla Ville Airport", "Salon-de-Provence (BA 701) Air Base");
    std::vector<std::string> correct_path={"Mouilla Ville Airport"};
    REQUIRE(path==correct_path);
   
}


//SHORTEST PATH AIRPORT TESTS
TEST_CASE("testing Djikstra airport"){
    Graph* g= new Graph("../airports.dat","../routes.dat");
    std::vector<std::string> path= g->DjikstraPath("Muskegon County Airport", "Chicago O'Hare International Airport");
    std::vector<std::string> correct_path={"Muskegon County Airport", "Chicago O'Hare International Airport"};
    REQUIRE(path==correct_path);
   
}


TEST_CASE("testing Djikstra airport complex"){
    Graph* g= new Graph("../airports.dat","../routes.dat");
    std::vector<std::string> path= g->DjikstraPath("Columbia Regional Airport", "Marseille Provence Airport");
    std::vector<std::string> correct_path={"Columbia Regional Airport","Chicago O'Hare International Airport","Montreal / Pierre Elliott Trudeau International Airport", "Marseille Provence Airport"};
    REQUIRE(path==correct_path);
   
}

TEST_CASE("testing Djikstra airport no connection to exact airport"){
    Graph* g= new Graph("../airports.dat","../routes.dat");
    std::vector<std::string> path= g->DjikstraPath("Chicago O'Hare International Airport", "Salon-de-Provence (BA 701) Air Base");
    std::vector<std::string> correct_path={ "Chicago O'Hare International Airport", "Montreal / Pierre Elliott Trudeau International Airport", "Marseille Provence Airport" };
    REQUIRE(path==correct_path);
   
}


TEST_CASE("testing Djikstra airport no source airport no connected to anything"){
    Graph* g= new Graph("../airports.dat","../routes.dat");
    std::vector<std::string> path= g->DjikstraPath("Mouilla Ville Airport", "Salon-de-Provence (BA 701) Air Base");
    std::vector<std::string> correct_path={"Mouilla Ville Airport"};
    REQUIRE(path==correct_path);
   
}
//____________________________________________________________________
//BFS and Djikstra algorithm tests where inputs are CITIES


//BFS algorithms with CITIES
TEST_CASE("testing BFS city"){
    Graph* g= new Graph("../airports.dat","../routes.dat");
    std::vector<std::string> path= g->findMinPath("Muskegon", "Chicago", true);
    std::vector<std::string> correct_path={"Muskegon County Airport", "Chicago O'Hare International Airport"};
    REQUIRE(path==correct_path);
   
}


TEST_CASE("testing BFS city complex"){
    Graph* g= new Graph("../airports.dat","../routes.dat");
    std::vector<std::string> path= g->findMinPath("Columbia", "Marseille" ,true);
    std::vector<std::string> correct_path={ "Columbia Metropolitan Airport", "Charlotte Douglas International Airport","Charles de Gaulle International Airport", "Marseille Provence Airport" };
    REQUIRE(path==correct_path);
   
}

TEST_CASE("testing BFS city no connection to destination city"){
    Graph* g= new Graph("../airports.dat","../routes.dat");
    std::vector<std::string> path= g->findMinPath("Chicago", "Salon", true);
    std::vector<std::string> correct_path=  { "Chicago Midway International Airport", "Hartsfield Jackson Atlanta International Airport", "London Heathrow Airport", "Marseille Provence Airport" };
    REQUIRE(path==correct_path);
   
}


TEST_CASE("testing BFS airport source city not connected to anything"){
    Graph* g= new Graph("../airports.dat","../routes.dat");
    std::vector<std::string> path= g->findMinPath("Mouila", "Salon", true);
    std::vector<std::string> correct_path={"Mouilla Ville Airport"};
    REQUIRE(path==correct_path);
   
}

//Djikstra algorithms with CITIES
TEST_CASE("testing Djikstra city"){
    Graph* g= new Graph("../airports.dat","../routes.dat");
    std::vector<std::string> path= g->findMinPath("Muskegon", "Chicago", false);
    std::vector<std::string> correct_path={"Muskegon County Airport", "Chicago O'Hare International Airport"};
    REQUIRE(path==correct_path);
   
}


TEST_CASE("testing Djikstra city complex"){
    Graph* g= new Graph("../airports.dat","../routes.dat");
    std::vector<std::string> path= g->findMinPath("Columbia", "Marseille" ,false);
    std::vector<std::string> correct_path={ "Columbia Metropolitan Airport", "Washington Dulles International Airport", "Montreal / Pierre Elliott Trudeau International Airport", "Marseille Provence Airport" };
    REQUIRE(path==correct_path);
   
}

TEST_CASE("testing Djikstra city no connection to destination city"){
    Graph* g= new Graph("../airports.dat","../routes.dat");
    std::vector<std::string> path= g->findMinPath("Chicago", "Salon", false);
    std::vector<std::string> correct_path=  { "Chicago Midway International Airport", "Billy Bishop Toronto City Centre Airport", "Montreal / Pierre Elliott Trudeau International Airport","Marseille Provence Airport" };
    REQUIRE(path==correct_path);
   
}


TEST_CASE("testing Djikstra airport source city not connected to anything"){
    Graph* g= new Graph("../airports.dat","../routes.dat");
    std::vector<std::string> path= g->findMinPath("Mouila", "Salon", false);
    std::vector<std::string> correct_path={"Mouilla Ville Airport"};
    REQUIRE(path==correct_path);
   
}

//tests that when cities are entered rather than specific airports located in the cities, the path will always be less than or equal (since the airport paths are included)
TEST_CASE("testing cityLess"){
    Graph* g= new Graph("../airports.dat","../routes.dat");
    std::vector<std::string> DJIcity_path= g->findMinPath("Columbia", "Marseille", false);
    std::vector<std::string> DJIairport_path= g->DjikstraPath("Columbia Metropolitan Airport", "Marseille Provence Airport");
    REQUIRE(DJIcity_path<=DJIairport_path);

    std::vector<std::string> BFScity_path= g->findMinPath("Columbia", "Marseille", true);
    std::vector<std::string> BFSairport_path= g->BFSpath("Columbia Metropolitan Airport", "Marseille Provence Airport");
    REQUIRE(BFScity_path<=BFSairport_path);
   
}

TEST_CASE("Centrality Test 1") {
    Graph* g= new Graph("../airports.dat","../routes.dat");
    REQUIRE(std::abs(g->Centrality("Columbia Metropolitan Airport") - 2.766563) < 0.2);
    REQUIRE(g->Centrality("Mouilla Ville Airport") == 0);
}
TEST_CASE("Centrality Test 2") {
    Graph* g= new Graph("../airport1.dat","../routesairport1.dat");
    REQUIRE(g->Centrality("Goroka Airport") == 0);
}
TEST_CASE("Centrality Test 3") {
    Graph* g= new Graph("../airports_connected.dat","../routes_connected.dat");
    REQUIRE(g->moreConnected("Chicago O'Hare International Airport", "St Louis Lambert International Airport"));
    //REQUIRE(g->Centrality("Mouilla Ville Airport") == 0);
}
TEST_CASE("Centrality Test 4") {
    Graph* g= new Graph("../airports.dat","../routes.dat");
    REQUIRE(g->moreConnected("Chicago O'Hare International Airport", "St Louis Lambert International Airport"));

}
TEST_CASE("Simple Graph Test") {
    Graph* g = new Graph("../airport1.dat","../routesairport1.dat");
    REQUIRE(g->noNeighbors("Goroka Airport"));
}
TEST_CASE("Simple Graph Test 2") {
    Graph* g = new Graph("../airport5.dat","../routes5.dat");
    REQUIRE(g->getNeighbors("Goroka Airport").size() == 0);
    REQUIRE(g->noNeighbors("Madang Airport"));
    REQUIRE(g->noNeighbors("Mount Hagen Kagamuga Airport"));
    REQUIRE(g->noNeighbors("Nadzab Airport"));
    REQUIRE(g->noNeighbors("Port Moresby Jacksons International Airport"));
}
TEST_CASE("Simple Graph Shortest Path Test for Airports") {
    Graph* g = new Graph("../airports_connected.dat","../routes_connected.dat");
    std::vector<std::string> optimalpath = g->DjikstraPath("Chicago O'Hare International Airport", "St Louis Lambert International Airport");
    std::vector<double> distanceVector = g->distancesVector(optimalpath);
    double totaldistance = g->distanceSum(distanceVector);
    double min_path_distance=std::min(g->distance("Chicago O'Hare International Airport", "Decatur Airport")+g->distance("Decatur Airport", "St Louis Lambert International Airport"), g->distance("Chicago O'Hare International Airport", "Southeast Iowa Regional Airport")+g->distance("Southeast Iowa Regional Airport", "St Louis Lambert International Airport"));
    REQUIRE(totaldistance == min_path_distance);
}

TEST_CASE("Simple Graph Shortest Path Test for Cities") {
    Graph* g = new Graph("../airportsforcities.dat","../routesforcities.dat");

    std::vector<std::string> optimalpath=g->findMinPath("Chicago","New York", false);
    std::vector<double> distanceVector = g->distancesVector(optimalpath);
    double totaldistance = g->distanceSum(distanceVector);
    double min_path_distance=std::min(g->distance("Chicago O'Hare International Airport", "Louis Armstrong New Orleans International Airport")+g->distance("Louis Armstrong New Orleans International Airport", "La Guardia Airport"), g->distance("Chicago Midway International Airport", "Ministro Pistarini International Airport")+g->distance("Ministro Pistarini International Airport", "John F Kennedy International Airport"));
    REQUIRE(totaldistance == min_path_distance);
}
