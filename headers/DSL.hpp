#ifndef DSL_H
#define DSL_H

#define OP_VALUE(oper)  \
    Value_t {.op = (oper)}

#define NUM_VALUE(n)  \
    Value_t {.num = (n)}

#define VAR_VALUE(x) \
    Value_t {.var = (x)}

#define _NUM(number_) \
    newNode(TYPE_NUMBER, NUM_VALUE(number_), NULL, NULL)    

#define _VAR(variable_) \
    newNode(TYPE_VARIABLE, VAR_VALUE(variable_), NULL, NULL)   

#define _ADD(firstNumber_, secondNumber_) \
    newNode(TYPE_OPERATION, OP_VALUE(OPERATION_ADD), firstNumber_, secondNumber_)

#define _SUB(firstNumber_, secondNumber_) \
    newNode(TYPE_OPERATION, OP_VALUE(OPERATION_SUB), firstNumber_, secondNumber_)

#define _MUL(firstNumber_, secondNumber_) \
    newNode(TYPE_OPERATION, OP_VALUE(OPERATION_MUL), firstNumber_, secondNumber_)    
    
#define _DIV(firstNumber_, secondNumber_) \
    newNode(TYPE_OPERATION, OP_VALUE(OPERATION_DIV), firstNumber_, secondNumber_)  
    
#define _POW(firstNumber_, secondNumber_) \
    newNode(TYPE_OPERATION, OP_VALUE(OPERATION_POW), firstNumber_, secondNumber_) 
    
#define _SIN(argument_) \
    newNode(TYPE_OPERATION, OP_VALUE(OPERATION_SIN), NULL, argument_)
    
#define _COS(argument_) \
    newNode(TYPE_OPERATION, OP_VALUE(OPERATION_COS), NULL, argument_)

#define _TG(argument_) \
    newNode(TYPE_OPERATION, OP_VALUE(OPERATION_TG), NULL, argument_)

#define _CTG(argument_) \
    newNode(TYPE_OPERATION, OP_VALUE(OPERATION_CTG), NULL, argument_)
    
#define _LN(argument_) \
    newNode(TYPE_OPERATION, OP_VALUE(OPERATION_LN), NULL, argument_)

#define _ARCSIN(argument_) \
    newNode(TYPE_OPERATION, OP_VALUE(OPERATION_ARCSIN), NULL, argument_)

#define _ARCCOS(argument_) \
    newNode(TYPE_OPERATION, OP_VALUE(OPERATION_ARCCOS), NULL, argument_)
    
#define _ARCTG(argument_) \
    newNode(TYPE_OPERATION, OP_VALUE(OPERATION_ARCTG), NULL, argument_)

#define _ARCCTG(argument_) \
    newNode(TYPE_OPERATION, OP_VALUE(OPERATION_ARCCTG), NULL, argument_)

#define _SH(argument_) \
    newNode(TYPE_OPERATION, OP_VALUE(OPERATION_SH), NULL, argument_)

#define _CH(argument_) \
    newNode(TYPE_OPERATION, OP_VALUE(OPERATION_CH), NULL, argument_)

#define _TH(argument_) \
    newNode(TYPE_OPERATION, OP_VALUE(OPERATION_TH), NULL, argument_)

#define _CTH(argument_) \
    newNode(TYPE_OPERATION, OP_VALUE(OPERATION_CTH), NULL, argument_)
    
#define _SQRT(argument_) \
    newNode(TYPE_OPERATION, OP_VALUE(OPERATION_SQRT), NULL, argument_)

#define _NEG(argument_) \
    newNode(TYPE_OPERATION, OP_VALUE(OPERATION_NEG), NULL, argument_)

#define _NULL_NODE \
    _NUM(0)

#endif