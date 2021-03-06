#ifndef rock_core_ast_hh
#define rock_core_ast_hh

#include <map>
#include <set>
#include <vector>

#include "rock/core/token.hh"
#include "rock/core/reference.hh"
#include "rock/core/object.hh"

namespace rock {

class Scope;

// TODO: Use unique_ptr<Ast> when holding children Ast nodes.
// For now, just leaking memory should be ok.
// Throughout the life of a program, there shouldn't be many
// places where we discard the results of a parsed program.

class Ast {
public:
  const Token token;
  Ast(const Token &t);
  virtual Reference eval(Scope&) const;
  virtual std::string debug() const;
};

class ParseError final: public Ast {
public:
  const std::string message;
  ParseError(const Token&, const std::string&);
  Reference eval(Scope&) const override;
  std::string debug() const override;
  std::string str() const;
};

class Block final: public Ast {
public:
  const std::vector<Ast*> expressions;
  Block(const Token&, const std::vector<Ast*>&);
  Reference eval(Scope&) const override;
  Reference evalWithoutNewScope(Scope&) const;
  std::string debug() const override;
};

class If final: public Ast {
public:
  Ast *const condition;
  Ast *const body;
  Ast *const other;
  If(const Token&, Ast*, Ast*, Ast*);
  Reference eval(Scope&) const override;
};

class Switch final: public Ast {
public:
  Ast *const target;
  const std::vector<std::tuple<Ast*,Ast*>> conditions;
  Ast *const default_;
  Switch(const Token&, Ast*, const std::vector<std::tuple<Ast*,Ast*>>&, Ast*);
  Reference eval(Scope&) const override;
};

class Or final: public Ast {
public:
  Ast *const left;
  Ast *const right;
  Or(const Token&, Ast*, Ast*);
  Reference eval(Scope&) const override;
};

class And final: public Ast {
public:
  Ast *const left;
  Ast *const right;
  And(const Token&, Ast*, Ast*);
  Reference eval(Scope&) const override;
};

class Arguments final {
public:
  const Token token;
  const std::vector<Ast*> args;
  Ast *const vararg; // TODO: support varargs and iterables.
  Arguments(const Token&, const std::vector<Ast*>&);
  Arguments(const Token&, const std::vector<Ast*>&, Ast*);
  std::vector<Reference> evalargs(Scope&) const;
};

class MethodCall final: public Ast {
public:
  Ast *const owner;
  const std::string name;
  const Arguments *args;
  MethodCall(const Token&, Ast*, const std::string&, Arguments*);
  Reference eval(Scope&) const override;
};

class SuperCall final: public Ast {
public:
  const std::string name;
  const Arguments *args;
  SuperCall(const Token&, const std::string&, Arguments*);
  Reference eval(Scope&) const override;
};

class While final: public Ast {
public:
  Ast *const condition;
  Ast *const body;
  While(const Token&, Ast*, Ast*);
  Reference eval(Scope&) const override;
};

class Declaration final: public Ast {
public:
  const std::string name;
  Ast *const value;
  Declaration(const Token&, const std::string&, Ast*);
  Reference eval(Scope&) const override;
};

class Assignment final: public Ast {
public:
  const std::string name;
  Ast *const value;
  Assignment(const Token&, const std::string&, Ast*);
  Reference eval(Scope&) const override;
};

class Name final: public Ast {
public:
  const std::string name;
  Name(const Token&, const std::string&);
  Reference eval(Scope&) const override;
};

class Literal final: public Ast {
public:
  const Reference value;
  Literal(const Token&, Reference);
  Reference eval(Scope&) const override;
};

class Signature final {
public:
  const Token token;
  const std::vector<std::string> argnames;
  const std::vector<std::string> optargnames;
  const std::string varargname;
  Signature(
      const Token&,
      const std::vector<std::string>&,
      const std::vector<std::string>&,
      const std::string&);
  void resolve(Scope&, const Args&);
};

class FunctionDisplay final: public Ast {
public:
  const std::string name;
  Signature *args;
  Ast *const body;
  FunctionDisplay(const Token&, const std::string&, Signature*, Ast*);
  Reference eval(Scope&) const override;
};

class ClassDisplay final: public Ast {
public:
  const std::string name;
  Arguments *const bases;
  const std::set<std::string> fields;
  const std::map<std::string,FunctionDisplay*> methods;
  ClassDisplay(
      const Token&, const std::string&, Arguments*,
      const std::set<std::string>&,
      const std::map<std::string,FunctionDisplay*>&);
  Reference eval(Scope&) const override;
};

}

#endif//rock_core_ast_hh
