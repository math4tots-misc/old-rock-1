#ifndef rock_core_object_hh
#define rock_core_object_hh

#include <functional>
#include <set>
#include <vector>

namespace rock {

class Object;
class Reference;
class Result;
class Class;

using Args = std::vector<Reference>;
using Method = std::function<Result(Reference, const Args&)>;

extern Class *classObject;

// NOTE: DEBUG
// extern std::set<Object*> allObjects;

class Object {
  friend class Reference;
  int refcnt = 0;
public:
  Object();
  virtual ~Object();
  Result call(const std::string&, const Args&);
  bool hasMethod(const std::string&) const;
  virtual Reference getClass() const=0;

  /** Return a simple string to debug this object.
   * Should be as dumb as possible and have no chance of throwing.
   * It's less helpful if your debug string throws or can fail.
   */
  virtual std::string debug() const;

  /* The C++ interface methods really should not error out.
   * But sometimes, I really do want users to be able to customize
   * them (e.g. hash). But that leaves open the possibility of users
   * throwing exceptions in their implementations.
   * For now, we'll use real C++ exceptions in those cases.
   */

  /* Everything should ideally be done through calling methods.
   * However, sometimes References must interact with C++ types during
   * interpretation, e.g. to figure out the truthiness of a value.
   * If there is a problem in any of these methods, they should throw
   * a Reference with an Exception in it.
   */
  virtual bool truthy() const;
  virtual std::string str() const;
};

}  // namespace rock

#endif//rock_core_object_hh
