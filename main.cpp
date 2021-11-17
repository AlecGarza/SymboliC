#include <iostream>
#include "Value.h"

using namespace std;

int main(int argc, const char * argv[])
{
	// Example #1

	// Define Variables
	Value* x = new Character('x');
	Value* y = new Character('y');
	
	// Define Equation
	Value* V = *(*(*x + x) * y) * x;

	// Symplify and Print
	Value* answer = Simplify(V,true);
	cout << answer->getDisplayName() << endl;

	// -----------------------------------
	// Example #2

	// Set x to 3
	x = new Number(3);

	// Redefine Equation
	V = *(*(*x + x) * y) * x;

	// Symplify and Print
	answer = Simplify(V,true);
	cout << answer->getDisplayName() << endl;

	// -----------------------------------
	// Example #3
	
	// Define Equation with different operations and return x to a variable 
	x = new Character('x');
	V = *(*(*x ^ x) * y) * x; 
	answer = Simplify(V,true);
	cout << answer->getDisplayName() << endl;

	return 0;
}

