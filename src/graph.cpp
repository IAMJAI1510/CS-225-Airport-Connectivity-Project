#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <queue>
#include <limits>

#include "utils.h"
#include "graph.h"

using namespace std;


/**
 * makes a graph with airports defined by their 3-letter (IATA) or 4-letter (ICAO) code of the source airport and 3-letter (IATA) or 4-letter (ICAO) code of * the destination airport (depending on which is known)
 **/
 Graph::Graph(const string & vertices, const string & edges)
 {
   createVertices(vertices);
   assignNeighbors(edges);
 }

/* Destructor for a graph object */
Graph::~Graph()
{
    for (Airport* a: airports) delete a;
    for (Flights* f: flights) delete f;
}

void Graph::createVertices(const string & filename)
{
    string s = file_to_string(filename);
    stringstream text(s);

    /* Creates the vertices */
    while (text.good()) {

        string the_line;
        
        getline(text, the_line, '\n');
        if(the_line=="") break;
        
        stringstream the_line1(the_line);

        string substr;
        for(uint i = 0; i < 2; i++) getline(the_line1, substr, ',');

        string name=Trim(substr);

        for(uint i = 0; i < 1; i++) getline(the_line1, substr, ',');
        
        string city =  Trim(substr);

        getline(the_line1, substr, ',');
        
        string country=Trim(substr);
           
        getline(the_line1, substr, ',');
        
        string IATA=Trim(substr);
        getline(the_line1, substr, ',');
        string ICAO=Trim(substr);
           
            
        getline(the_line1, substr, ',');

    while(substr.substr(0,1)=="\""){ 
        getline(the_line1, substr, ',');
    }


        substr=substr.substr(0,13);
        double lat=stod(substr);

        getline(the_line1, substr, ',');
        substr=substr.substr(0,13);
        double lon=stod(substr);
        
        
        Airport* a= new Airport( name,city, country, IATA, ICAO, lat, lon);
        airports.push_back(a);
        names.push_back(name);
        cities.push_back(city);
        nameMap.insert({a->getName(),a});
        IcaoMap.insert({a->getIcao(),a});
        IataMap.insert({a->getIata(),a});
        

    }
        
 }
void Graph::assignNeighbors(const string & filename){
    string s= file_to_string(filename);
   stringstream text(s);

    //creates the vertices
   while (text.good()) {

        string the_line;
        
        getline(text, the_line, '\n');
        if(the_line=="") break;
        
        stringstream the_line1(the_line);
        
            string substr;
            for(uint i=0; i<3; i++){
                getline(the_line1, substr, ',');
            }
            string source=Trim(substr);

            for(uint i=0; i<2; i++){
                getline(the_line1, substr, ',');
            }
            
            string dest=Trim(substr);
           
    
        connections.push_back({source,dest});
        Flights* f= new Flights(source, dest);
        flights.push_back(f);
   }


    for(uint j=0; j<connections.size(); j++){
        Airport* source_a=NULL;
        Airport* dest_a=NULL;
        string source= connections[j].first;
        string dest=connections[j].second;

        auto it_source= IataMap.find(source);
        if(it_source==IataMap.end()){
            it_source=IcaoMap.find(source);
        }
        if(it_source!=IcaoMap.end()){
            source_a= it_source->second;
        }
        

        auto it_dest= IataMap.find(dest);
        if(it_dest==IataMap.end()){
            it_dest=IcaoMap.find(dest);
        }
        if(it_dest!=IcaoMap.end()){
             dest_a= it_dest->second;
            if(source_a!=NULL&&source_a->notNeighbors(dest_a))source_a->addNeighbor(dest_a);
        }

    }
}

int Graph::numComponents(){

    for (Airport* a : airports){
        a->setLabel(false);

    }
    int i=1;
    for (Airport* a : airports){
        if (a->getLabel() == false){
        BFS(a, i);
        i++;
        }

    }   
    return i;
    
}


void Graph::BFS(Airport* source, bool start){
    
    for (Airport* a : airports){
        a->setLabel(false);
        a->setBFSPred(NULL);

    }
    
    int i=0;
    BFS(source, 0);
    
    for (Airport* a : airports){
        
        if (a->getLabel() == false){
            i++;
            BFS(a,i);
            
            
            
        }   

    }
    source->setBFSPred(NULL);

}


//test case with airports
void Graph::BFS(Airport* a, int i){
    
    queue<Airport*> q;
    a->setLabel( true);
    q.push(a);
    a->setComp(i);
    while (!q.empty()){
        a=q.front();
        q.pop();
        for (Airport* b : a->getAdjacent()){
            if(b->getLabel() == false){
                b->setLabel(true);
                b->setBFSPred(a);
                 q.push(b);
                 b->setComp(i);
            }
        }
            
    }
    
}


//test case with airports calls BFS
vector<string> Graph::BFSpath(string startAirport, string endAirport){
    vector<string> path;
    Airport* starting;
    Airport* ending;
    if(startAirport==endAirport){
        path.push_back(startAirport);
        return path;
    }
    starting=nameMap.find(startAirport)->second;
    ending=nameMap.find(endAirport)->second;
    BFS(starting,true);
    

    if(starting->getComp()==ending->getComp()){
        
        Airport* traverse=ending;
          while(traverse!=NULL){
                path.push_back(traverse->getName());
                 traverse=traverse->getBFSPred();
                 //cout<<traverse->getName();
                 
        
            }
            //cout<<startAirport<<endAirport;return path;
            
        reverse(path.begin(), path.end());
    }
    else{//cout<<"NOT CONNECTED";
    
        Airport* closest=NULL;
        for(Airport* a: airports){
            if(a->getComp()==starting->getComp()){
                if(closest==NULL||distance(a,ending)<distance(closest,ending)){
                    closest=a;
                    
                }
            }
        }
       
       return BFSpath(startAirport, closest->getName());
       
    } 


    return path;
}


//test case with airports
void Graph::Djikstra(Airport* source){
    for(Airport* a: airports){
        a->setDjiDist(99999999);
        a->setDjiPred(NULL);
        a->setDjiExplored(false);
    }
    source->setDjiDist(0);
    

    MinHeap m=MinHeap(airports);
     

for(int i=0; i<airports.size();i++){
    Airport* min=m.pop();
    min->setDjiExplored(true);
  
    if(min->getDjiDist()==99999999)      break;        

    for(Airport* neighbor: min->getAdjacent()){
        if(neighbor->wasDjiExplored()==false){
                
                double dist=distance(min,neighbor)+min->getDjiDist();
                if(dist<neighbor->getDjiDist()){
                    neighbor->setDjiPred(min);
                    neighbor->setDjiDist(dist);
                
                }
            
        }
    }

    m.update();
}
source->setDjiPred(NULL);

}


//test case with airports calls Djikstra
vector<string> Graph::DjikstraPath(string startAirport, string endAirport){

    vector<string> path;
    Airport* starting;
    Airport* ending;
    
    starting=nameMap.find(startAirport)->second;
    ending=nameMap.find(endAirport)->second;
    
    

    BFS(starting, true);
    if(starting->getComp()==ending->getComp()){

        Djikstra(starting);
        Airport* traverse=ending;
        while(traverse!=NULL){
            path.push_back(traverse->getName());
            traverse=traverse->getDjiPred();
        
        }

        reverse(path.begin(), path.end());
    }
    else{
        Airport* closest=NULL;
        for(Airport* a: airports){
            if(a->getComp()==starting->getComp()){
                if(closest==NULL||distance(a,ending)<distance(closest,ending)){
                    closest=a;
                }
            }
        }
        
       return DjikstraPath(startAirport, closest->getName());
    }
   
    return path;
}








 void Graph::printAirports(){
    
    for(Airport* a: airports){
        
        cout<<"COUNTRY is: "<<a->getCountry()<<"           ";
        cout<<"IATA is: "<<a->getIata()<<"           ";
        cout<<"ICAO is: "<<a->getIcao()<<"           ";
        cout<<"LAT is: "<<a->getLat()<<"           ";
        cout<<"LONG is: "<<a->getLong()<<"           "<<endl;
    }
    cout<<"__________________________"<<endl;
    cout<<"there are "<<airports.size()<<" airports :)"<<endl<<endl;
 }

 void Graph::printConnections(){
    for(auto c: connections){
        
        cout<<"SOURCE is: "<<c.first<<"           ";
        cout<<"DEST is: "<<c.second<<"           "<<endl;
    }
    cout<<"__________________________"<<endl;
    cout<<"there are "<<connections.size()<<" connections :)"<<endl<<endl;
 

 }

 void Graph::printAdjacent(unsigned i){
    airports[i]->printAdjacent();
 }


 //test case
 void Graph::printAdjacent(string airport){
    Airport* a=nameMap.find(airport)->second;
    a->printAdjacent();
 }


void Graph::printBFSpath(vector<string> airportsVector){
    cout<<" BFS path from "<<airportsVector.front()<<" to "<< airportsVector.back()<<" is:  ";
    uint c=0;
    for(string s: airportsVector){
            c++;
            cout<<s;
            if(c<airportsVector.size())cout<<"----->";   
    }

    cout<<endl<<endl;
   
}

void Graph::printBFSpath(string startAirport, string endAirport){

vector<string> airportPath=BFSpath( startAirport,  endAirport);
cout<<"A BFS path from "<<startAirport<<" to "<< endAirport<<" is:  ";
uint c=0;
 for(string s: airportPath){
        c++;
        cout<<s;
        if(c<airportPath.size())
            cout<<"----->";
        
    }
    cout<<endl<<endl;
   
}

void Graph::printDjiPath(vector<string> airportsVector){
    
    cout<<"The shortest path from "<<airportsVector.front()<<" to "<< airportsVector.back()<<" is:  ";
    uint c=0;
 for(string s: airportsVector){
        c++;
        cout<<s;
        if(c<airportsVector.size())
            cout<<"----->";
        
    }
    cout<<endl<<endl;
   
}

void Graph::printDjiPath(string startAirport, string endAirport){
if(closest(startAirport,endAirport)->getName()!=endAirport){
    cout<<"There is no connection between "<<startAirport<<" and "<<endAirport<<", but the closest airport is "<<closest(startAirport,endAirport)->getName()<<endl<<endl;
}
vector<string> airportPath=DjikstraPath( startAirport,  endAirport);
cout<<"The shorest path from "<<startAirport<<" to "<< endAirport<<" is:  ";
uint c=0;
 for(string s: airportPath){
    c++;
        
        cout<<s;
        if(c<airportPath.size())
        cout<<"----->";
        
    }
    cout<<endl<<endl;
   
}



    
 long double Graph::toRadians(const long double degree)
{
    // cmath library in C++
    // defines the constant
    // M_PI as the value of
    // pi accurate to 1e-30
    long double one_deg = (M_PI) / 180;
    return (one_deg * degree);
}


 //test case
 double Graph::distance(string start, string end){
    bool startFound=false;
    bool endFound=false;
    Airport* starting;
    Airport* ending;
    for(Airport* a: airports){
        if(a->getName()==start){
             starting=a;
            startFound=true;
            if(endFound)
                break;
        }
        if(a->getName()==end){
            ending= a;
            endFound=true;
            if(startFound)
                break;
        }
    }
    return distance(starting, ending);
 }

double Graph::distance(Airport* source, Airport* dest){
    return distance(source->getLat(), source->getLong(), dest->getLat(), dest->getLong());
}


 //test case
 double Graph::distance(long double lat1, long double long1,
                     long double lat2, long double long2)
{
     // Convert the latitudes
    // and longitudes
    // from degree to radians.
    lat1 = toRadians(lat1);
    long1 = toRadians(long1);
    lat2 = toRadians(lat2);
    long2 = toRadians(long2);
     
    // Haversine Formula found online
    long double dlong = long2 - long1;
    long double dlat = lat2 - lat1;
 
    long double dist = pow(sin(dlat / 2), 2) + cos(lat1) * cos(lat2) *pow(sin(dlong / 2), 2);
 
    dist = 2 * asin(sqrt(dist));
 
    // Radius of Earth in Kilometers, R = 6371
    long double radius = 6371;
     
    dist *=radius;
 
    return dist;
}


void  Graph::printDistance(string sourceAirport, string destAirport){
    cout<<"distance from "<<sourceAirport<<" to "<<destAirport<<" is "<<distance(sourceAirport,destAirport)<<" KM"<<endl<<endl;
}

int Graph::count(int c){
    int i=0;
    for(Airport* a: airports){
        if(a->getComp()==c)
            i++;
    }
    return i;
}

vector<double> Graph::distancesVector(vector<string> airportsVector){
    vector<double> distances;
    for(uint i=0; i<airportsVector.size()-1;i++){
        
         distances.push_back(distance(airportsVector[i],airportsVector[i+1]));
    }
    return distances;
}


void Graph::printDjiDistances(string start, string end){
    vector<string> p=DjikstraPath( start,  end);
   vector<double> distances= distancesVector(p);
cout<<"The shorest path from "<<start<<" to "<< end<<" is:  ";
uint c=0;
 for(double s: distances){
    c++;
        
        cout<<s;
        if(c<distances.size())
        cout<<"----->";
        
    }
    cout<<endl<<endl;
}

void Graph::printShortestStringAndDistance(string start, string end){

    if(noNeighbors(start)){
         cout<<start<< " has no neigboring airports."<<endl;
        cout<<"Total km traveled is: "<<0<<endl;
        cout<<"Distance from "<<end<<" is: " <<distance(start,end)<<endl;
        cout<<endl<<endl;
        return;
    }
    vector<string> s=DjikstraPath(start,end);
    vector<double> d=distancesVector(s);

    if(s.back()!=end){
    cout<<"There is no connection between "<<start<<" and "<<end<<", but the closest airport is "<<s.back()<<" at a distance in km of: "<<distance(s.back(),end)<<endl;
}
    double km=0;
    for(double f: d){
        km+=f;
    }
    for(uint i=0; i<d.size();i++){
        cout<<s[i]<<"----->"<<s[i+1]<<"  ("<<d[i]<<")"<<endl;
    }
    cout<<"Total km traveled is: "<<km<<endl;
    cout<<endl<<endl;
}


void Graph::printBFSStringAndDistance(string start, string end){
    if(noNeighbors(start)){
         cout<<start<< " has no neigboring airports."<<endl;
        cout<<"Total km traveled is: "<<0<<endl;
        cout<<"Distance from "<<end<<" is: " <<distance(start,end)<<endl;
        cout<<endl<<endl;
        return;
    }
    vector<string> s=BFSpath(start,end);
    vector<double> d=distancesVector(s);

   if(s.size()==1||end!=nameMap.find(s.back())->second->getName()){
        
    cout<<"There is no connection between "<<start<<" and "<<end<<", but the closest airport is "<<nameMap.find(s.back())->second->getName()<<" in "<<nameMap.find(s.back())->second->getCity()<<" at a distance in km of: "<<distance(end,s.back())<<endl;
}
    double km=0;
    for(double f: d){
        km+=f;
    }
    for(uint i=0; i<d.size();i++){
        cout<<s[i]<<"----->"<<s[i+1]<<"  ("<<d[i]<<")"<<endl;
    }
    cout<<"Total km traveled is: "<<km<<endl;
    cout<<endl<<endl;

}


//maybe test case
Airport* Graph::closest(string startAirport, string destAirport){
   
    Airport* starting=nameMap.find(startAirport)->second;
    Airport* ending=nameMap.find(destAirport)->second;
    int num=numComponents();
    if(noNeighbors(startAirport)){
        cout<<startAirport<< " has no neigboring airports."<<endl;
    }

    if(starting->getComp()==ending->getComp()){
        return ending;
    }
    Airport* closest=NULL;
        for(Airport* a: airports){
            if(a->getComp()==starting->getComp()){
                if(closest==NULL||(distance(a,ending)<distance(closest,ending)&&closest->getName()!=destAirport)){
                    closest=a;
                }
            }
        }
        return closest;
    
}

string Graph::printClosest(string startAirport, string destAirport){
    Airport* c= closest(startAirport,destAirport);
    return c->getName();
}

// //test case
bool Graph::validName(string airport_name){
    return std::count(names.begin(),names.end(),airport_name)&&!noNeighbors(airport_name);
}

bool Graph::airportExists(string airport_name){
    return std::count(names.begin(),names.end(),airport_name);
}

// //test case
bool Graph::validCity(string city){
    return std::count(cities.begin(),cities.end(),city)&&!cityNoNeighbors( city);
}

bool Graph::cityExists(string cityName){
     return std::count(cities.begin(),cities.end(),cityName);
}

bool Graph::cityNoNeighbors(string city){
    //bool hasNeighbor=true;
    for(string airport: locateAll(city))
        if(nameMap.find(airport)->second->getAdjacent().size()>0)    return false;
    return true;
}


//will be called in test case
vector<string> Graph::locateAll(string city){
    vector<string> loc;
    for(Airport *a: airports){
        if(a->getCity()==city)
        {
            loc.push_back(a->getName());
        }
    }
    return loc;
}


vector<string> Graph::findMinPath(vector<vector<string>> paths, string endCity){
    vector<string> toReturn;
    int min_dist=999999;
    // for(vector<string> s: paths){
    //     for( string l: s){
    //         cout<<l<<" ";
    //     }
    //     cout<<endl;
    // }
    std::string closeAirport;
    for(Airport* a: airports){
        if(a->getCity()==endCity){
            closeAirport=a->getName();
        }
    }
    
    std::string bestAirport;
    bool none=true;
    bool ret_is_direct=false;
    bool curr_is_direct=false;
    for(uint i=0; i<paths.size(); i++){
        int pathSum=0;
        if(nameMap.find(paths[i].back())->second->getCity()==endCity)
            curr_is_direct=true;
        else
            curr_is_direct=false;
        
        
        for(uint j=0; j<paths[i].size()-1;j++){
        
         pathSum+=distance(paths[i][j],paths[i][j+1]);
        }
        if ((none||(ret_is_direct&&curr_is_direct&&pathSum<min_dist&&curr_is_direct)||(ret_is_direct==curr_is_direct&&!ret_is_direct&&distance(paths[i].back(), closeAirport)<distance(bestAirport,closeAirport)))){
            toReturn=paths[i];
            min_dist=pathSum;
            ret_is_direct=curr_is_direct;
            none=false;
            bestAirport=paths[i].back();
        }
    }
    
    return toReturn;
}



void Graph::printShortestStringAndDistanceCities(string startCity, string endCity){
    if(startCity==endCity){
        cout<<"The cities entered: "<<startCity<<" and "<<endCity<<" are the same. This is the same city"<<endl<<endl;
        return;
    }
    vector<vector<string>> paths2D;
    for(string st: locateAll(startCity)){
        for(string en: locateAll(endCity)){
            paths2D.push_back(DjikstraPath(st,en));
        }
    }
     vector<string> s= findMinPath(paths2D, endCity);
    
     vector<double> d=distancesVector(s);


if(noNeighbors(s[0])){
        cout<<startCity<< " has no neigboring airports."<<endl;
    }

    if(s.size()==1||endCity!=nameMap.find(s.back())->second->getCity()){
       Airport* other= NULL;
        for(Airport* a: airports){
            if(a->getCity()==endCity){
                if(other==NULL||distance(a->getName(),nameMap.find(s.back())->second->getName())<distance(other->getName(),nameMap.find(s.back())->second->getName()))
                 other= a;
            }
        }
    cout<<"There is no connection between "<<startCity<<" and "<<endCity<<", but the closest airport is "<<nameMap.find(s.back())->second->getName()<<" in "<<nameMap.find(s.back())->second->getCity()<<" at a distance in km of: "<<distance(other->getName(),s.back())<<endl;
    }

    double km=0;
    for(double f: d){
        km+=f;
    }
    for(uint i=0; i<d.size();i++){
        cout<<s[i]<<"----->"<<s[i+1]<<"  ("<<d[i]<<")"<<endl;
    }
    cout<<"Total km traveled is: "<<km<<endl;
    cout<<endl<<endl;
}



void Graph::printBFSStringAndDistanceCities(string startCity, string endCity){
    if(startCity==endCity){
        cout<<"The cities entered: "<<startCity<<" and "<<endCity<<" are the same. This is the same city"<<endl<<endl;
        return;
    }
   

   
    vector<vector<string>> paths2D;
    for(string st: locateAll(startCity)){
        
        for(string en: locateAll(endCity)){
            
            //if(!noNeighbors(st)){
                {//cout<<st;
                 paths2D.push_back(BFSpath(st,en));
                //}
            }
        }
    }
   

    //  for(vector<string> v: paths2D){
    //     for(string st: v){
    //         cout<<st<<" ";
    //     }
    //     cout<<endl;
    //  }
   
     vector<string> s= findMinPath(paths2D, endCity);
    
      if(s.empty()){
         cout<<startCity<< " has no neigboring airports."<<endl;
        cout<<"Total km traveled is: "<<0<<endl;
        cout<<endl<<endl;
        return;
      }
            
        
     if(noNeighbors(s[0])){
        cout<<startCity<< " has no neigboring airports."<<endl;
    }
     
    
     vector<double> d=distancesVector(s);

    if(s.size()==1||endCity!=nameMap.find(s.back())->second->getCity()){
        Airport* other= NULL;
        for(Airport* a: airports){
            if(a->getCity()==endCity){
                if(other==NULL||distance(a->getName(),nameMap.find(s.back())->second->getName())<distance(other->getName(),nameMap.find(s.back())->second->getName()))
                 other= a;
                
            }
        }
    cout<<"There is no connection between "<<startCity<<" and "<<endCity<<", but the closest airport is "<<nameMap.find(s.back())->second->getName()<<" in "<<nameMap.find(s.back())->second->getCity()<<" at a distance in km of: "<<distance(other->getName(),s.back())<<endl;
    }

    double km=0;
    for(double f: d){
        km+=f;
    }
    for(uint i=0; i<d.size();i++){
        cout<<s[i]<<"----->"<<s[i+1]<<"  ("<<d[i]<<")"<<endl;
    }
    cout<<"Total km traveled is: "<<km<<endl;
    cout<<endl<<endl;
}


//will call djikstra and possibly bfs in test case
vector<string> Graph::findMinPath(string startCity,string endCity, bool bfs){
    vector<string> ret;
     if(startCity==endCity){
        ret.push_back(startCity);
        return ret;
    }
    vector<vector<string>> paths2D;
    for(string st: locateAll(startCity)){
        for(string en: locateAll(endCity)){
            if(bfs)paths2D.push_back(BFSpath(st,en));
            else paths2D.push_back(DjikstraPath(st,en));
        }
    }
     ret= findMinPath(paths2D,endCity);
     return ret;
}



// will call findMinPath(string,string,bfs) in test case
vector<double> Graph::findMinPathDistances(vector<string> airportsVector){

    vector<double> distances;
    if(airportsVector.size()==1){
        distances.push_back(0);
        return distances;
    }

    for(uint i=0; i<airportsVector.size()-1;i++){
        
         distances.push_back(distance(airportsVector[i],airportsVector[i+1]));
    }
    return distances; 
}

//calls findMinPathDistances on airport and city vectors to test cities<=airports
double Graph::distanceSum(vector<double> distances){
    double sum=0;
    for(double d: distances) sum+=d;
    return sum;

}

//test case to check if cities path is less than airport path
bool Graph::cityLess(string startAirport, string endAirport, string startCity, string endCity, bool bfs){
    double airportDistanceSum;
     double cityPathDistanceSum;

    if(nameMap.find(startAirport)->second->getCity()==startCity&&nameMap.find(endAirport)->second->getCity()==endCity){
        if(bfs){
             vector<string> airportPath=BFSpath(startAirport,endAirport);
             vector<double> airportPathDistances=findMinPathDistances(airportPath);
             vector<string> cityPath=findMinPath(startCity,endCity, bfs);
             vector<double> cityPathDistances=findMinPathDistances(cityPath);
            airportDistanceSum=distanceSum(airportPathDistances);
            cityPathDistanceSum=distanceSum(cityPathDistances);
        }
        else{

            vector<string> airportPath=DjikstraPath(startAirport,endAirport);
             vector<double> airportPathDistances=findMinPathDistances(airportPath);
             vector<string> cityPath=findMinPath(startCity,endCity, bfs);
             vector<double> cityPathDistances=findMinPathDistances(cityPath);
            airportDistanceSum=distanceSum(airportPathDistances);
            cityPathDistanceSum=distanceSum(cityPathDistances);
        }

        return cityPathDistanceSum<=airportDistanceSum;
    
    
    }
    return true;
}




uint Graph::Size(){
    return airports.size();
}

int Graph::n(){
    int i=0;
    for(Airport* a: airports)
    if(noNeighbors(a->getName())) i++;

    return i;
}

bool Graph::moreConnected(std::string airport1, std::string airport2) {
    return (Centrality(airport1) > Centrality(airport2));
}

double Graph::Centrality(std::string airport) {
   
    if(noNeighbors(airport)) return 0;
    Airport* a= nameMap.find(airport)->second;
  
    //https://neo4j.com/docs/graph-data-science/current/algorithms/closeness-centrality/
    //This is the link to the algorithm we used. We made some slight modifications 
    //for it to fit in with our dataset. 
    BFS(a, true);
    Djikstra(a);
    double sum=0;
    for(Airport* a1: airports){
        if(a1->getComp()==a->getComp())
            sum+=  a1->getDjiDist();
    }
    return 10000 * airports.size()/sum;


}
