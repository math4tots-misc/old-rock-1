#include "rock.hh"
namespace rock {

Class *classClass = new Class();
Class *classException = new Class();
Reference classClassReference(classClass);
Reference classExceptionReference(classException);

void acquire(Value *v) {
  v->reference_count++;
}

void release(Value *v) {
  v->reference_count--;
  if (v->reference_count <= 0) {
    delete v;
  }
}

Result Reference::call(const std::string& name, const Args& args) const {
  Class *cls = pointer->getClass();
  auto pair = cls->method_table.find(name);
  if (pair == cls->method_table.end()) {
    return Result(
        EXCEPTION,
        Reference(new Exception("No such method: " + name)));
  }
  Method *method = pair->second;
  return (*method)(*this, args);
}

}