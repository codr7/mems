#include <sstream>

#include "mems/model.hpp"
#include "mems/utilities.hpp"

namespace mems {
  void Model::generate(const string &in, ostream &out) {
    stringstream is(in);
    vector<Token *> in;
    read_tokens(is, in);
    context.insert(in.begin(), in.end());
    auto i = 0;
    
    sort(in.begin(), in.end(), [](auto &x, auto &y) {
      return x->weight < y->weight;
    });

    while (i < max_generate_tokens && !in.empty()) {
      auto t = in.back();
      in.pop_back();
      
      if (i++) {
	out << ' ';
      }
      
      out << t->text;
      t->sort_next(*this);
      var found = false;
      
      for (const auto &nt: t->next) {
	t = nt.first;

	if (push_window(t)) {
	  in.push_back(t);
	  found = true;
	  break;
	}
      }

      if (!found && i < max_generate_tokens && !in.empty()) {
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
