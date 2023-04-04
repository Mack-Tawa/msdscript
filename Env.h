//
// Created by Mack on 4/3/23.
//

#ifndef CLION_BULL_ENV_H
#define CLION_BULL_ENV_H
#include "pointer.h"
#include "val.h"
#include "Expr.h"
#include <memory>


class Env {
public:
    virtual PTR(Val) lookup(std::string find_name) = 0;
};

class emptyEnv : public Env {
    PTR(Val) lookup(std::string find_name) {
        throw std::runtime_error("free variable: "
                                 + find_name);
    }
};

class ExtendedEnv : public Env {
public:
    ExtendedEnv(std::string name, PTR(Val) val, PTR(Env) env) {
        this->val = val;
        this->name = name;
        this->env = env;
    }
    std::string name;
    PTR(Val) val;
    PTR(Env) env;
    PTR(Val) lookup(std::string find_name) {
        if (find_name == name)
            return val;
        else
            return env->lookup(find_name);
    }

};



#endif //CLION_BULL_ENV_H
