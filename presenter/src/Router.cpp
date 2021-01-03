#include "presenter/Router.h"

#include <cassert>

#include "GetRouter.h"

namespace presenter {

namespace global {

std::unique_ptr<Router> router;

}

Router* getRouter() {
  assert(global::router && "router is null");
  return global::router.get();
}

void setRouter(std::unique_ptr<Router> router) {
  global::router = std::move(router);
}

}  // namespace presenter
