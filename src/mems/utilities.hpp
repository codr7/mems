#pragma once

#include <string>
#include <vector>

namespace mems {
  using namespace std;
  
  inline vector<string> split(const string &s, const string &delimiter) {
    auto i = 0, j = -1;
    const auto dl = delimiter.length();
    vector<string> result;
    
    while ((j = s.find(delimiter, i)) != string::npos) {
      result.push_back(s.substr(i, j - i));
      i = j + dl;
    }
    
    result.push_back (s.substr(i));
    return result;
  }
}
