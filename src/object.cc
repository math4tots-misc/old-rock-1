#include "rock/all.hh"

#include <sstream>

namespace rock {

namespace {
Init init(100, __FILE__, []() {
  classObject = new Class("Object");
  builtins->declare("Object", classObject);
});
}

Class *classObject;

Result Object::call(const std::string &name, const Args &args) {
  Reference clsref = getClass();
  Class *cls = clsref.as<Class>();
  Method method = cls->getMethod(name);
  if (!method) {
    const std::string message =
        "No such method: " + name + " for class " + cls->name;
    return Result(
        Result::Type::EXCEPTION,
        new Exception(message));
  }
  return method(this, args);
}

bool Object::hasMethod(const std::string &name) const {
  Reference clsref = getClass();
  Class *cls = clsref.as<Class>();
  return (bool) cls->getMethod(name);
}

std::string Object::debug() const {
  std::stringstream ss;
  ss << "<Object("
      << std::string(typeid(*this).name())
      << "," << this << ")>";
  return ss.str();
}

bool Object::truthy() const {
  return true;
}

std::string Object::str() const {
  return debug();
}

}  // namespace rock
