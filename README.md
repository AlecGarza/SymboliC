# SymboliC

Small library for some basic symbolic computation by overriding operators that I made while learning C++. It builds a tree of embedded "operations" then searches through the tree to find operations to simplify.

## Examples in main.cpp
- Example 1:
    Takes the equation (x + x) * y * x and simplifies to y(2x<sup>2</sup>). 
- Example 2:
    Then replacing x for 3 to simplify to 18y.
- Example 3:
    Takes the equation (x<sup>x</sup>) * y * x and simplifies to y(x<sup>x+1</sup>). 