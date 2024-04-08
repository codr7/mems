#pragma once

#include <string>
#include <vector>

namespace mems {
  using namespace std;

  struct Model;
  
  struct Token {
    string text;
    int weight;
    vector<pair<Token *, int>> next;
    
    Token(const string &text): text(text), weight(text.size()) {}

    void push_next(Token *t) {
      for (auto &np: next) {
	if (np.first == t) {
	  np.second++;
	  return;
	}
      }

      next.push_back(make_pair(t, 1));
    }

    void sort_next(Model &m);
  };
}
