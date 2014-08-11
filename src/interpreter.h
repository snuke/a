/*
 Interpreter of a programming language "A" (not APL)
 Author: snuke
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
    void* p;
    Data();
    Data(Type type, void* p);
    bool operator<(const Data& x) const;
    bool operator==(const Data& x) const;
    inline long long& Int() const { return *(long long*)p;}
    inline double& Float() const { return *(double*)p;}
    inline std::string& Str() const { return *(std::string*)p;}
    inline std::vector<Data>& Array() const { return *(std::vector<Data>*)p;}
  };
  static const double EPS;
  static const int MAX_POOL_INT;
  static const int MAX_POOL_FLOAT;
  static const int MAX_POOL_STR;
  static const int MAX_POOL_ARRAY;
  std::vector<long long> pool_int_;
  std::vector<double> pool_float_;
  std::vector<std::string> pool_str_;
  std::vector<std::vector<Data> > pool_array_;
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
  Data Exec(State& cur, State& fcur);
  Data Func(State& cur);
  Data Num(State& cur);
  Data Str(State& cur);
  Data SubStr(State& cur);
  Data EditStr(State& cur);
  Data Assign(State& cur);
  Data Input(State& cur);
  Data Length(State& cur);
  char tmp_s[128];
  Data Format(State& cur);
  Data Pair(State& cur);
  void Print(Data x);
  Data Output(State& cur);
  void Skip(State& cur);
  Data Cond(State& cur);
  Data Repeat(State& cur);
  Data Loop(State& cur);
  Data Operate(State& cur);
};

#endif