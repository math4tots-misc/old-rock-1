#ifndef rock_core_exception_hh
#define rock_core_exception_hh

#include <string>
#include <vector>

#include "rock/core/object.hh"

namespace rock {

class Class;

extern Class *classException;

// TODO: Save stack trace.
class Exception final: public Object {
public:
  const std::string message;
  const std::vector<const Token*> stacktrace;
  Exception(const std::string&);
  Reference getClass() const override;
  std::string debug() const override;
  std::string str() const override;
};

Reference exception(const std::string&);

}

#endif//rock_core_exception_hh
