#ifndef rock_object_hh
#define rock_object_hh

#include <functional>
#include <vector>

namespace rock {

class Object;
class Reference;
class Result;

using Args = std::vector<Reference>;
using Method = std::function<Result(Reference, const Args&)>;

class Object {
  friend class Reference;
  int refcnt = 0;
public:
  virtual ~Object() {}
  Result call(const std::string&, const Args&);
  virtual Reference getClass() const=0;

  /** Return a simple string to debug this object.
   * Should be as dumb as possible and have no chance of throwing.
   * It's less helpful if your debug string throws or can fail.
   */
  virtual std::string debug() const;

  /*
   * The C++ interface methods really should not error out.
   * But some of them, I really do want users to be able to customize
   * them (e.g. hash). But that leaves open the possibility of users
   * throwing exceptions in their implementations.
   * For now, we'll use real C++ exceptions in those cases.
   */

  /* Everything should ideally be done through calling methods.
   * However, sometimes References must interact with C++ types during
   * interpretation, e.g. to figure out the truthiness of a value.
   */
  virtual bool truthy() const;
};

class Reference final {
  Object *pointer;
  static void acquire(Object*);
  static void release(Object*);
public:
  Reference();
  Reference(Object*);
  Reference(const Reference&);
  ~Reference();
  Reference &operator=(const Reference&);
  Object *operator->() const;
  template <class T> T *as() const { return static_cast<T*>(pointer); }
};

class Result final {
public:
  enum class Type {
    OK, EXCEPTION, RETURN, BREAK, CONTINUE,
  };
  Type type;
  Reference value;
  Result(Reference);
  Result(Type, Reference);
  Reference get() const;
  std::string debug() const;
};

}  // namespace rock

namespace std {

std::string to_string(rock::Result::Type);

}  // namespace std

#endif//rock_object_hh