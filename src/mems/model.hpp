#pragma once

#include <deque>
#include <map>
#include <set>
#include <string>

#include "mems/token.hpp"

namespace mems {
  using namespace std;
  
  struct Model {
    int max_generate_tokens = 1024;
    int max_repeat_tokens = 4;
    int max_repeat_window_size = 64;

    set<Token *> context;
    map<string, Token *> tokens;
    deque<Token *> window;

    void generate(const string &in, ostream &out);

    bool push_window(Token *t) {
      if (window.size() == max_repeat_window_size) {
	window.pop_front();
      }

      window.push_back(t);

      if (window.size() < max_repeat_tokens*2) {
	return true;
      }
      
      const auto
	i1 = window.begin(),
	i2 = window.end() - max_repeat_tokens,
	j1 = i2,
	j2 = window.end();
      
      return search(i1, i2, j1, j2) == window.end();
    }
    
    void read_punctuation(istream &in, vector<Token *> &out);
    void read_tokens(istream &in, vector<Token *> &out);
    void read_whitespace(istream &in, vector<Token *> &out);
    void read_word(istream &in, vector<Token *> &out);
  };
}
