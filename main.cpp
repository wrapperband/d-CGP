#include <iostream>
#include <iomanip>
#include <ctime>
#include <random>
#include <audi/gdual.hpp>

#include "include/dcgp.hpp"

using namespace dcgp;

int main() {
    // Random seed
    std::random_device rd;

    // We define the set of functions we want to use
    function_set basic_set({"sum","diff","mul", "sig"});

    // We instantiate a d-CGP expression
    unsigned int n_inputs = 3;
    unsigned int n_outputs = 1;
    unsigned int n_rows = 1;
    unsigned int n_columns = 15;
    unsigned int n_level_backs = 16;
    unsigned int arity = 3;
    expression simple(n_inputs,
        n_outputs,
        n_rows,
        n_columns,
        n_level_backs,
        arity,
        basic_set(),
        rd()
    );

    // We inspect it
    stream(std::cout,  simple, '\n');

    // We compute the d-CGP expression in a point
    std::vector<double> in_num({0.3,-0.2,0.1});
    stream(std::cout,  "Point is:", in_num, "\n");
    stream(std::cout,  "Numerical value = ", simple(in_num), "\n");

    // We compute the d-CGP jet of derivatives up to order 2
    std::vector<audi::gdual<double>> jet = simple.taylor(in_num,2);
    stream(std::cout,  "Numerical values d/dx = ", jet[0].get_derivative({1,0,0}) , "\n");
    stream(std::cout,  "Numerical values d/dy = ", jet[0].get_derivative({0,1,0}) , "\n");
    stream(std::cout,  "Numerical values d/dz = ", jet[0].get_derivative({0,0,1}) , "\n");

    stream(std::cout,  "Numerical values d^2/dx^2 = ", jet[0].get_derivative({2,0,0}) , "\n");
    stream(std::cout,  "Numerical values d^2/dy^2 = ", jet[0].get_derivative({0,2,0}) , "\n");
    stream(std::cout,  "Numerical values d^2/dz^2 = ", jet[0].get_derivative({0,0,2}) , "\n");
    stream(std::cout,  "Numerical values d^2/dxdy = ", jet[0].get_derivative({1,1,0}) , "\n");
    stream(std::cout,  "Numerical values d^2/dydz = ", jet[0].get_derivative({0,1,1}) , "\n");
    stream(std::cout,  "Numerical values d^2/dxdz = ", jet[0].get_derivative({1,0,1}) , "\n");

    // We compute the symbolic representation of the d-CGP expression
    std::vector<std::string> in_sym({"x","y","z"});
    stream(std::cout,  "Symbolic value = ", simple(in_sym) , "\n");

    return 0;
}

/* Possible output:

d-CGP Expression:
    Number of inputs:       3
    Number of outputs:      1
    Number of rows:         1
    Number of columns:      50
    Number of levels-back allowed:  51

    Resulting lower bounds: [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  ... ]
    Resulting upper bounds: [3, 2, 2, 3, 3, 3, 3, 4, 4, 3, 5, 5, 3, 6, 6, 3, 7, 7, 3, 8,  ... ]

    Current expression (encoded):   [1, 0, 2, 0, 1, 2, 3, 3, 0, 3, 1, 2, 3, 5, 4, 0, 5, 2, 3, 7,  ... ]
    Active nodes:           [0, 1, 2, 3, 4, 5, 7]
    Active genes:           [0, 1, 2, 3, 4, 5, 6, 7, 8, 12, 13, 14, 150]

    Function set:           [sum, diff, mul, div]

Point is:[2, 3, 4]
Numerical value = [-0.14285714285714285]
Numerical values d/dx = 0.142857
Numerical values d/dy = 0.0204082
Numerical values d/dz = -0.0510204
Numerical values d^2/dx^2 = -0.142857
Numerical values d^2/dy^2 = -0.0058309
Numerical values d^2/dz^2 = 0.0145773
Numerical values d^2/dxdy = -0.0204082
Numerical values d^2/dydz = 0.00437318
Numerical values d^2/dxdz = 0.0153061
Symbolic value = [(((x-z)/x)/(y+z))]

**/
