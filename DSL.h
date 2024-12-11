#ifndef DSL_H
#define DSL_H

#define _NUM(number_) \
    newNode(TYPE_NUMBER, number_, NULL, NULL)    

#define _VAR(variable_) \
    newNode(TYPE_VARIABLE, variable_, NULL, NULL)   

#define _ADD(firstNumber_, secondNumber_) \
    newNode(TYPE_OPERATION, OPERATION_ADD, firstNumber_, secondNumber_)

#define _SUB(firstNumber_, secondNumber_) \
    newNode(TYPE_OPERATION, OPERATION_SUB, firstNumber_, secondNumber_)

#define _MUL(firstNumber_, secondNumber_) \
    newNode(TYPE_OPERATION, OPERATION_MUL, firstNumber_, secondNumber_)    

#define _DIV(firstNumber_, secondNumber_) \
    newNode(TYPE_OPERATION, OPERATION_DIV, firstNumber_, secondNumber_)  

#define _POW(firstNumber_, secondNumber_) \
    newNode(TYPE_OPERATION, OPERATION_POW, firstNumber_, secondNumber_) 

#define _ROOT(firstNumber_, secondNumber_) \
    newNode(TYPE_OPERATION, OPERATION_ROOT, firstNumber_, secondNumber_) 

#define _LOG(firstNumber_, secondNumber_) \
    newNode(TYPE_OPERATION, OPERATION_LOG, firstNumber_, secondNumber_)

#define _SIN(argument_) \
    newNode(TYPE_OPERATION, OPERATION_SIN, NULL, argument_)

#define _LN(argument_) \
    newNode(TYPE_OPERATION, OPERATION_LN, NULL, argument_)

#define _COS(argument_) \
    newNode(TYPE_OPERATION, OPERATION_COS, NULL, argument_)

#define _SQRT(argument_) \
    _ROOT(_NUM(2), argument_)

#define _NULL_NODE \
    _NUM(0)

#endif