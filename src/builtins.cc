#include "rock/all.hh"

#include <functional>
#include <iostream>
#include <map>
#include <vector>

namespace rock {

namespace {

Reference *brp;  // pointer to builtins reference

Init init(50, __FILE__, []() {
  builtins = new Scope();
  brp = new Reference(builtins);  // live until explicitly deleted
}, []() {
  delete brp;
});

void declareFunc(
    Scope *scope, const std::string &name,
    std::function<Result(const Args&)> f) {
  scope->declare(name, new Function(name, f));
}
}

Scope *builtins;

// NOTE: Not all builtins values are set here.
// Builtin native classes are set in the cc file that implements the class.
Init init(120, __FILE__, []() {
  declareFunc(builtins, "print", [](const Args& args) {
    checkargs(1, args);
    std::cout << args[0]->str() << std::endl;
    return Result(Result::Type::OK, args[0]);
  });
  declareFunc(builtins, "L", [](const Args& args) {
    return Result(Result::Type::OK, new List(args));
  });
});

}
