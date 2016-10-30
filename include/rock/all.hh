// ls include/rock/ | awk '{ print "#include \"rock/"$0"\"" }' | tail -n +2
#include "rock/ast.hh"
#include "rock/builtins.hh"
#include "rock/class.hh"
#include "rock/exception.hh"
#include "rock/file.hh"
#include "rock/init.hh"
#include "rock/lex.hh"
#include "rock/nil.hh"
#include "rock/number.hh"
#include "rock/object.hh"
#include "rock/parse.hh"
#include "rock/scope.hh"
#include "rock/string.hh"
