#include <sstream>

#include "mems/model.hpp"
#include "mems/utilities.hpp"

namespace mems {
  void Model::generate(const string &in, ostream &out) {
    stringstream is(in);
    vector<Token *> tokens;
    read_tokens(is, tokens);
    context.insert(tokens.begin(), tokens.end());
    auto i = 0;
    
    sort(tokens.begin(), tokens.end(), [](auto &x, auto &y) {
      return x->weight < y->weight;
    });

    while (i < max_generate_tokens && !tokens.empty()) {
      auto t = tokens.back();
      tokens.pop_back();
      
      if (i++) {
	out << ' ';
      }
      
      out << t->text;
      t->sort_next(*this);
      auto found = false;
      
      for (const auto &nt: t->next) {
	t = nt.first;

	if (push_window(t)) {
	  tokens.push_back(t);
	  found = true;
	  break;
	}
      }

      if (!found && i < max_generate_tokens && !tokens.empty()) {
	out << endl;
      }
    }

    out << endl;
  }

  void Model::read_punctuation(istream &in, vector<Token *> &out) {
  }

  void Model::read_tokens(istream &in, vector<Token *> &out) {
  }

  void Model::read_whitespace(istream &in, vector<Token *> &out) {
  }
 
  void Model::read_word(istream &in, vector<Token *> &out) {
  }
}
