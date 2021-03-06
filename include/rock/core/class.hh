#ifndef rock_core_class_hh
#define rock_core_class_hh

#include <map>
#include <set>
#include <string>
#include <vector>

#include "rock/core/object.hh"

namespace rock {

class Class;

extern Class *classClass;

bool instanceof(Reference, const Class*);

class Class final: public Object {
  /** The cls variable holds the class of this class.
   * If null, we default to classClass.
   */
  const Reference cls;
public:
  const std::string name;

private:
  const std::vector<Reference> bases;
  const std::vector<Class*> mro;

public:
  /** User constructible means that you can create an instance of this
   * type by calling a constructor in Rock.
   * Most builtin types are *not* user constructible. To create them,
   * you must either use special functions or use special syntaxes.
   *
   * If a class is user constructible, you can create one by calling the
   * '__call', method on the class object.
   */
  const bool userConstructible;

private:
  const std::set<std::string> fields;
  const std::map<std::string,Method> methods;

  std::vector<Class*> makeMro(Class*, const std::vector<Reference>&);
public:
  Class(
      const std::string&,
      const std::vector<Reference>&,
      const std::map<std::string,Method>&);
  Class(
      Reference,
      const std::string&,
      const std::vector<Reference>&,
      const std::map<std::string,Method>&);
  Class(
      const std::string&,
      const std::vector<Reference>&,
      bool,
      const std::set<std::string>&,
      const std::map<std::string,Method>&);
  Class(
      Reference,
      const std::string&,
      const std::vector<Reference>&,
      bool,
      const std::set<std::string>&,
      const std::map<std::string,Method>&);
  Reference getClass() const override;
  Method getDirectMethod(const std::string&) const;
  Class *findClassWithMethod(const std::string&);
  Class *findClassWithMethod(Class*, const std::string&);
  const std::set<std::string> &getFields() const;
  const std::vector<Class*> &getMro() const;
  std::string debug() const override;
  bool extends(Class*) const;
};

}

#endif//rock_core_class_hh
