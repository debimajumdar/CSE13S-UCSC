#include "operators.h"

#include "mathlib.h"
#include "stack.h"

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool apply_binary_operator(binary_operator_fn op) {
    if (stack_size < 2) {
        return false;
    } else {
        double rhs;
        double lhs;

        assert(stack_pop(&rhs));
        assert(stack_pop(&lhs));

        double result = op(lhs, rhs);

        assert(stack_push(result));
        return true;
    }
}

//Function given by Kerry Veenstra, asgn3.pdf page 3
bool apply_unary_operator(unary_operator_fn op) {
    if (stack_size < 1) {
        return false;
    }
    double x;
    assert(stack_pop(&x));
    double result = op(x);
    assert(stack_push(result));
    return true;
}

double operator_add(double lhs, double rhs) {
    double result = lhs + rhs;
    return result;
}

double operator_sub(double lhs, double rhs) {
    double result = lhs - rhs;
    return result;
}

double operator_mul(double lhs, double rhs) {
    double result = lhs * rhs;
    return result;
}

double operator_div(double lhs, double rhs) {
    double result = lhs / rhs;
    return result;
}

double my_fmod(double lhs, double rhs) {
    double result = fmod(lhs, rhs);
    return result;
}

//This function is given to us by Kerry Veenstra asgn3.pdf page 6
bool parse_double(const char *s, double *d) {
    char *endptr;
    double result = strtod(s, &endptr);

    if (endptr != s) {
        *d = result;
        return true;
    } else {
        return false;
    }
}
