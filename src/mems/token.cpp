#include "mems/model.hpp"
#include "mems/token.hpp"

namespace mems {
  void Token::sort_next(Model &m) {
    sort(next.begin(), next.end(), [&m](const auto &x, const auto &y) {
      auto xw = x.second;
      
      if (m.context.contains(x.first)) {
	xw *= x.first->weight;
      }
      
      return xw > y.second;
    });
  }
}
