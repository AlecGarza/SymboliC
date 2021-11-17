#include "Value.h"

Value* Simplify(Value* V) {
	if (typeid(*V).name() == typeid(Operation).name()) {
		
	}
	return V;
}

Value* Simplify(Value* V, bool verbose) {
	if (typeid(*V) == typeid(Operation)) {
		Operation* O = dynamic_cast<Operation*>(V);
		Value* V1 = O->V1;
		Value* V2 = O->V2;
		OperatorType Op = O->Op;
		
		if (typeid(*V1) == typeid(Operation)) {
			Operation* V = dynamic_cast<Operation*>(V1);
			O->V1 = Simplify(V,verbose);
			if (V->getDisplayName() != O->V1->getDisplayName() && verbose) {
				O->updateDisplayName();
				cout << "To : " +O->getDisplayName() << endl << endl;
			}
		}
		if (typeid(*V2) == typeid(Operation)) {
			Operation* V = dynamic_cast<Operation*>(V2);
			O->V2 = Simplify(V,verbose);
			if (V->getDisplayName() != O->V2->getDisplayName() && verbose) {
				O->updateDisplayName();
				cout << "To : " +O->getDisplayName() << endl << endl;
			}
		}
		
		Value* VV;
		
		switch (Op) {
			case Addition:
				VV = *V1 + V2;
				if (O->getDisplayName() != VV->getDisplayName() && verbose) {
					cout << "Edit : " +O->getDisplayName() << endl;
					cout << "To : " +VV->getDisplayName() << endl << endl;
				}
				return VV;
			case Subtraction:
				VV = *V1 - V2;
				if (O->getDisplayName() != VV->getDisplayName() && verbose) {
					cout << "Edit : " +O->getDisplayName() << endl;
					cout << "To : " +VV->getDisplayName() << endl << endl;
				}
				return VV;
			case Multiplication:
				VV = *V1 * V2;
				if (O->getDisplayName() != VV->getDisplayName() && verbose) {
					cout << "Edit : " +O->getDisplayName() << endl;
					cout << "To : " +VV->getDisplayName() << endl << endl;
				}
				return VV;
			case Division:
				VV = *V1 / V2;
				if (O->getDisplayName() != VV->getDisplayName() && verbose) {
					cout << "Edit : " +O->getDisplayName() << endl;
					cout << "To : " +VV->getDisplayName() << endl << endl;
				}
				return VV;
			case Exponent:
				VV = *V1 ^ V2;
				if (O->getDisplayName() != VV->getDisplayName() && verbose) {
					cout << "Edit : " +O->getDisplayName() << endl;
					cout << "To : " +VV->getDisplayName() << endl << endl;
				}
				return VV;
			default:
				break;
		}
		return O;
	}
	return V;
}
Value* Factor(Operation* O) {
	
	return O;
}

Character* findCharacter(Operation* operation, char character) {
	if (typeid(*(operation->V1)).name() == typeid(Character).name()) {
		Character* C = dynamic_cast<Character*>(operation->V1);
		if (C->C == character) {
			return C;
		}
	}
	if (typeid(*(operation->V2)).name() == typeid(Character).name()) {
		Character* C = dynamic_cast<Character*>(operation->V2);
		if (C->C == character) {
			return C;
		}
	}
	if (typeid(*(operation->V1)).name() == typeid(Operation).name()) {
		Operation* O = dynamic_cast<Operation*>(operation->V1);
		Character* C = findCharacter(O, character);
		if (C->C == character) {
			return C;
		}
	}
	if (typeid(*(operation->V2)).name() == typeid(Operation).name()) {
		Operation* O = dynamic_cast<Operation*>(operation->V2);
		Character* C = findCharacter(O, character);
		if (C->C == character) {
			return C;
		}
	}
	return NULL;
}

Operation* inverseParent(Value* value) {
	int parentOP = value->Parent->Op;
	bool second = false;
	Value* sibling = NULL;
	if (value == value->Parent->V1) {
		sibling = value->Parent->V2;
	}
	else if (value == value->Parent->V2) {
		sibling = value->Parent->V1;
		second = true;
	}
	switch (parentOP) {
  		case Addition:
			return new Operation(value->Parent, Subtraction, sibling);
			break;
		case Subtraction:
			if (second) {
				return new Operation(sibling, Subtraction, value->Parent);
			}
			else {
				return new Operation(sibling, Addition, value->Parent);
			}
			break;
		case Multiplication:
			return new Operation(value->Parent, Division, sibling);
			break;
		case Division:
			if (second) {
				return new Operation(sibling, Division, value->Parent);
			}
			else {
				return new Operation(sibling, Multiplication, value->Parent);
			}
			break;
		case Exponent:
			
  		default:
			return NULL;
			break;
	}
}

Value* SolveFor(Character* character) {
	
	Operation* inversedParent = inverseParent(character);
	Operation* currentParent = character->Parent;
	
	while (inversedParent != NULL) {
		currentParent = inversedParent;
		inversedParent = inverseParent(currentParent);
	}
	return Simplify(currentParent);
}

Value* inverseOperation(Operation* operation) {
	return operation;
}

Operation* setForVariable(Operation* operation, char character, Value* newValue) {
	Operation* newOperation = new Operation(operation->V1, operation->Op, operation->V2);
	if (typeid(*(newOperation->V1)).name() == typeid(Character).name()) {
		Character* v1 = dynamic_cast<Character*>(newOperation->V1);
		if (v1->C == character) {
			newOperation->V1 = newValue;
		}
	}
	else if (typeid(*(operation->V1)).name() == typeid(Operation).name()) {
		newOperation->V1 = setForVariable(dynamic_cast<Operation*>(operation->V1), character, newValue);
	}
	if (typeid(*(newOperation->V2)).name() == typeid(Character).name()) {
		Character* v2 = dynamic_cast<Character*>(newOperation->V2);
		if (v2->C == character) {
			newOperation->V2 = newValue;
		}
	}
	else if (typeid(*(operation->V2)).name() == typeid(Operation).name()) {
		newOperation->V2 = setForVariable(dynamic_cast<Operation*>(operation->V2), character, newValue);
	}
	return newOperation;
}
