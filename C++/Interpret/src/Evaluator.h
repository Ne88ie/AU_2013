#ifndef Evaluator_H_
#define Evaluator_H_

#include <stack>
#include <map>

#include "Visitor.h"
#include "Declarations.h"
#include "Instruction.h"

using std::stack;

typedef std::map<std::string, int> variable_scope;
typedef std::map<std::string, Function const*> function_scope;
typedef std::pair<std::string, int> variable_instance;


class Evaluator: public Visitor {
public:
    Evaluator(program_ptr program);

    void execute_program();
    
private:
    Evaluator(Evaluator const&);
    Evaluator& operator =(Evaluator const&);
    
    int visit(Constant const&);
    int visit(Variable const&);
    int visit(Program const&);
    int visit(Function const&);
    int visit(Assignment const&);
    int visit(Function_Call const&);
    int visit(Arithmetic_Operation const&);
    int visit(Read const&);
    int visit(Print const&);
    int visit(Conditional const&);
    int visit(If_Block const&);
    int visit(While_Block const&);
    int visit(Return const&);
    int visit(Instruction_Block const&);
        
    bool m_has_returned;
    int m_result;
    
    program_ptr m_program;
    function_scope m_function_scope;
    stack<variable_scope> m_variable_scopes;
};

#endif
