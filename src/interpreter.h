/*
 Interpreter of a programming language "A" (not APL)
 Author: snuke
 Github: https://github.com/snuke/a
*/

#ifndef A_INTERPRETER_H_
#define A_INTERPRETER_H_

#include <string>
#include <vector>
#include <sstream>

class Interpreter {
 public:
  void Run(const std::string& code,
                 std::istream* input,
                 std::ostream* output);
 private:
  enum Type { NONE, DEF, INT, FLOAT, STR, ARRAY};
  typedef std::string::const_iterator State;
  struct Data {
    Type type;
    int i;
    Data();
    Data(Type type, int i);
    bool operator<(const Data& x) const;
    bool operator==(const Data& x) const;
    inline long long& Int() const { return pool_int_[i];}
    inline double& Float() const { return pool_float_[i];}
    inline std::string& Str() const { return pool_str_[i];}
    inline std::vector<Data>& Array() const { return pool_array_[i];}
  };
  static const double EPS;
  static const int MAX_POOL_INT;
  static const int MAX_POOL_FLOAT;
  static const int MAX_POOL_STR;
  static const int MAX_POOL_ARRAY;
  static std::vector<long long> pool_int_;
  static std::vector<double> pool_float_;
  static std::vector<std::string> pool_str_;
  static std::vector<std::vector<Data> > pool_array_;
  std::istream* input_;
  std::ostream* output_;
  std::ostringstream error_;
  std::vector<Data> vars_;
  void InitVars();
  Data NewInt(long long x);
  Data NewFloat(double x);
  Data NewStr(const std::string& x);
  Data NewArray(const std::vector<Data>& x);
  Data Expr(State& cur);
  Data& Vector(State& cur, Data& x);
  Data& Var(State& cur);
  Data Defined(State& cur);
  Data FuncExec(State& cur, State& fcur);
  Data Func(State& cur);
  Data Num(State& cur);
  Data Str(State& cur);
  Data SubStr(State& cur);
  Data EditStr(State& cur);
  Data Assign(State& cur);
  Data Input(State& cur);
  Data Length(State& cur);
  char tmp_s[1024];
  Data Format(State& cur);
  Data Paragraph(State& cur);
  void Print(Data x);
  Data Output(State& cur);
  void Skip(State& cur);
  Data Cond(State& cur);
  Data Repeat(State& cur);
  Data Loop(State& cur);
  Data Operate(State& cur);
};

#endif