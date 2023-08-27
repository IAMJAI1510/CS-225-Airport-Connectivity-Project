#include "utils.h"
#include <sstream>
#include <fenv.h>
#include <signal.h>
#include <vector>
#include <iostream>

std::string file_to_string(const std::string& filename){
  std::ifstream text(filename);

  std::stringstream strStream;
  //std::cout<<"trying to open..."<<std::endl;
  if (text.is_open()) {
    //std::cout<<"OPENED"<<std::endl;
    strStream << text.rdbuf();
  }
  else{
    //std::cout<<"error opening";
  }
  return strStream.str();
}

std::string TrimRight(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(tmp.find_last_not_of("\"") + 1);
}

std::string TrimLeft(const std::string & str) {
    std::string tmp = str;
    return tmp.erase(0, tmp.find_first_not_of("\""));
}

std::string Trim(const std::string & str) {
    std::string tmp = str;
    return TrimLeft(TrimRight(str));
}

int SplitString(const std::string & str1, char sep, std::vector<std::string> &fields) {
    std::string str = str1;
    std::string::size_type pos;
    while((pos=str.find(sep)) != std::string::npos) {
        fields.push_back(str.substr(0,pos));
        str.erase(0,pos+1);  
    }
    fields.push_back(str);
    return fields.size();
}