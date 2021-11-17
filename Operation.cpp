#include "Value.h"

Operation::Operation() {
	
}
Operation::Operation(Value* v1, OperatorType op, Value* v2) {
	
	V1 = v1;
	V2 = v2;
	Op = op;
	
	V1->Parent = this;
	V2->Parent = this;
}

string Operation::getDisplayName() {
	if (DisplayValue.size() == 0) updateDisplayName();
	return DisplayValue;
}
void Operation::updateDisplayName() {
	V1->updateDisplayName();
	V2->updateDisplayName();
	
	switch (Op) {
		case Addition:
			opString = "+";
			break;
		case Subtraction:
			opString = "-";
			break;
		case Multiplication:
			opString = "*";
			break;
		case Division:
			opString = "/";
			break;
		case Exponent:
			opString = "^";
			break;
		default:
			break;
	}
	
	if (Op == Multiplication) {
		if (V1->positive) {
			if (V2->positive) {
				positive = true;
			}
			else {
				positive = false;
			}
		}
		else if (V2->positive) {
			positive = false;
		}
		else {
			positive = true;
		}
		if (typeid(*V1) == typeid(Character)) {
			if (typeid(*V2) == typeid(Number)) {
				DisplayValue = V2->getDisplayName();
				DisplayValue += V1->getDisplayName();
			}
			else if (typeid(*V2) == typeid(Operation)) {
				DisplayValue = V1->getDisplayName();
				DisplayValue += "(" +V2->getDisplayName() +")";
			}
			else {
				DisplayValue = V1->getDisplayName();
				DisplayValue += V2->getDisplayName();
			}
		}
		else if (typeid(*V1) == typeid(Operation)) {
			if (typeid(*V2) == typeid(Operation)) {
				if (dynamic_cast<Operation*>(V1)->Op == Multiplication) {
					if (dynamic_cast<Operation*>(V2)->Op == Multiplication) {
						DisplayValue = V1->getDisplayName();
						DisplayValue += V2->getDisplayName();
					}
					else if (dynamic_cast<Operation*>(V2)->Op == Exponent) {
						DisplayValue = V1->getDisplayName();
						DisplayValue += V2->getDisplayName();
					}
					else {
						DisplayValue = V1->getDisplayName();
						DisplayValue += "(" +V2->getDisplayName() +")";
					}
				}
				else if (dynamic_cast<Operation*>(V1)->Op == Exponent) {
					if (dynamic_cast<Operation*>(V2)->Op == Multiplication) {
						DisplayValue = V2->getDisplayName();
						DisplayValue += V1->getDisplayName();
					}
					else {
						DisplayValue = "(" +V1->getDisplayName() +")";
						DisplayValue += "(" +V2->getDisplayName() +")";
					}
				}
				else {
					DisplayValue = "(" +V1->getDisplayName() +")";
					DisplayValue += "(" +V2->getDisplayName() +")";
				}
			}
			else {
				DisplayValue = V2->getDisplayName();
				DisplayValue += "(" +V1->getDisplayName() +")";
			}
		}
		else if (typeid(*V1) == typeid(Number) && typeid(*V2) == typeid(Number)) {
			DisplayValue = V1->getDisplayName();
			DisplayValue += " * ";
			DisplayValue += V2->getDisplayName();
		}
		else {
			DisplayValue = V1->getDisplayName();
			DisplayValue += V2->getDisplayName();
		}
		if (typeid(*V1) == typeid(Number)) {
			if (dynamic_cast<Number*>(V1)->N == 0) {
				DisplayValue = V1->getDisplayName();
			}
			else if (dynamic_cast<Number*>(V1)->N == 1) {
				DisplayValue = V2->getDisplayName();
			}
			else if (dynamic_cast<Number*>(V1)->N == -1) {
				DisplayValue = "-" +V2->getDisplayName();
			}
		}
		else if (typeid(*V2) == typeid(Number)) {
			if (dynamic_cast<Number*>(V2)->N == 0) {
				DisplayValue = V2->getDisplayName();
			}
			else if (dynamic_cast<Number*>(V2)->N == 1) {
				DisplayValue = V1->getDisplayName();
			}
			else if (dynamic_cast<Number*>(V2)->N == -1) {
				DisplayValue = "-" +V1->getDisplayName();
			}
		}
	}
	else if (Op == Exponent) {
		if (typeid(*V2) == typeid(Operation) ) {
			Operation* F = dynamic_cast<Operation*>(V2);
			if (F->Op == Division) {
				DisplayValue = "(" +F->V1->getDisplayName() +")";
				DisplayValue += "-\/";
				DisplayValue += V1->getDisplayName();
				DisplayValue += opString;
				DisplayValue += "(" +F->V2->getDisplayName() +")";
				DisplayValue += "|";
			}
		}
		DisplayValue = V1->getDisplayName();
		DisplayValue += opString;
		DisplayValue += "(" +V2->getDisplayName() +")";
	}
	else {
		if (typeid(*V1) == typeid(Operation)) {
			if (dynamic_cast<Operation*>(V1)->Op == Exponent) {
				if (typeid(*V2) == typeid(Operation)) {
					if (dynamic_cast<Operation*>(V2)->Op == Exponent) {
						if (dynamic_cast<Number*>(dynamic_cast<Operation*>(V1)->V2)->N >= dynamic_cast<Number*>(dynamic_cast<Operation*>(V2)->V2)->N) {
							DisplayValue = V1->getDisplayName();
							DisplayValue += " ";
							DisplayValue += opString;
							DisplayValue += " ";
							DisplayValue += V2->getDisplayName();
						}
						else {
							DisplayValue = V2->getDisplayName();
							DisplayValue += " ";
							DisplayValue += opString;
							DisplayValue += " ";
							DisplayValue += V1->getDisplayName();
						}
					}
					else {
						DisplayValue = V1->getDisplayName();
						DisplayValue += " ";
						DisplayValue += opString;
						DisplayValue += " ";
						DisplayValue += V2->getDisplayName();
					}
				}
				else {
					DisplayValue = V1->getDisplayName();
					DisplayValue += " ";
					DisplayValue += opString;
					DisplayValue += " ";
					DisplayValue += V2->getDisplayName();
				}
				
			}
			else if (typeid(*V2) == typeid(Operation)) {
				if (dynamic_cast<Operation*>(V2)->Op == Exponent) {
					DisplayValue = V2->getDisplayName();
					DisplayValue += " ";
					DisplayValue += opString;
					DisplayValue += " ";
					DisplayValue += V1->getDisplayName();
				}
				else {
					DisplayValue = V1->getDisplayName();
					DisplayValue += " ";
					DisplayValue += opString;
					DisplayValue += " ";
					DisplayValue += V2->getDisplayName();
				}
			}
			else {
				DisplayValue = V1->getDisplayName();
				DisplayValue += " ";
				DisplayValue += opString;
				DisplayValue += " ";
				DisplayValue += V2->getDisplayName();
			}
		}
		else if (typeid(*V2) == typeid(Operation) && Op != Division) {
			DisplayValue = V2->getDisplayName();
			DisplayValue += " ";
			DisplayValue += opString;
			DisplayValue += " ";
			DisplayValue += V1->getDisplayName();
		}
		else {
			DisplayValue = V1->getDisplayName();
			DisplayValue += " ";
			DisplayValue += opString;
			DisplayValue += " ";
			DisplayValue += V2->getDisplayName();
		}
	}
}

Value* Operation::operator + (Value* V) {
	if (typeid(*V).name() == typeid(Number).name()) {
		Number* VV = dynamic_cast<Number*>(V);
		return *this + VV;
	}
	else if (typeid(*V).name() == typeid(Character).name()) {
		Character* VV = dynamic_cast<Character*>(V);
		return *this + VV;
	}
	else if (typeid(*V).name() == typeid(Operation).name()) {
		Operation* VV = dynamic_cast<Operation*>(V);
		return *this + VV;
	}
	return new Operation(this, Addition, V);
}
Value* Operation::operator - (Value* V) {
	
	if (typeid(*V).name() == typeid(Number).name()) {
		Number* VV = dynamic_cast<Number*>(V);
		return *this - VV;
	}
	else if (typeid(*V).name() == typeid(Character).name()) {
		Character* VV = dynamic_cast<Character*>(V);
		return *this - VV;
	}
	else if (typeid(*V).name() == typeid(Operation).name()) {
		Operation* VV = dynamic_cast<Operation*>(V);
		return *this - VV;
	}
	return new Operation(this, Subtraction, V);
}
Value* Operation::operator * (Value* V) {
	
	if (typeid(*V).name() == typeid(Number).name()) {
		Number* VV = dynamic_cast<Number*>(V);
		return *this * VV;
	}
	else if (typeid(*V).name() == typeid(Character).name()) {
		Character* VV = dynamic_cast<Character*>(V);
		return *this * VV;
	}
	else if (typeid(*V).name() == typeid(Operation).name()) {
		Operation* VV = dynamic_cast<Operation*>(V);
		return *this * VV;
	}
	return new Operation(this, Multiplication, V);
}
Value* Operation::operator / (Value* V) {
	
	if (typeid(*V).name() == typeid(Number).name()) {
		Number* VV = dynamic_cast<Number*>(V);
		return *this / VV;
	}
	else if (typeid(*V).name() == typeid(Character).name()) {
		Character* VV = dynamic_cast<Character*>(V);
		return *this / VV;
	}
	else if (typeid(*V).name() == typeid(Operation).name()) {
		Operation* VV = dynamic_cast<Operation*>(V);
		return *this / VV;
	}
	return new Operation(this, Division, V);
}
Value* Operation::operator ^ (Value* V) {
	
	if (typeid(*V).name() == typeid(Number).name()) {
		Number* VV = dynamic_cast<Number*>(V);
		return *this ^ VV;
	}
	else if (typeid(*V).name() == typeid(Character).name()) {
		Character* VV = dynamic_cast<Character*>(V);
		return *this ^ VV;
	}
	else if (typeid(*V).name() == typeid(Operation).name()) {
		Operation* VV = dynamic_cast<Operation*>(V);
		return *this ^ VV;
	}
	return new Operation(this, Exponent, V);
}
bool Operation::operator == (Value* V) {
	if (typeid(*V) == typeid(Operation)) {
		Operation* VV = dynamic_cast<Operation*>(V);
		return operator==(VV);
	}
	return false;
	
}
bool Operation::operator == (Operation* V) {
	if (V1->operator==(V->V1) && Op == V->Op && V2->operator==(V->V2)) {
		return true;
	}
	else if ((V1->operator==(V->V2) && Op == V->Op && V2->operator==(V->V1)) && (Op == Multiplication || Op == Addition)) {
		return true;
	}
	return false;
}
bool Operation::Compatable(Value * V,OperatorType op) {
	if (typeid(*V) == typeid(Number)) {
		Number* N = dynamic_cast<Number*>(V);
		return Compatable(N, op);
	}
	if (typeid(*V) == typeid(Character)) {
		Character* N = dynamic_cast<Character *>(V);
		return Compatable(N, op);
	}
	if (typeid(*V) == typeid(Operation)) {
		Operation* N = dynamic_cast<Operation*>(V);
		return Compatable(N, op);
	}
	return false;
}

// Compatable // Operation & Number
bool Operation::Compatable(Number* N,OperatorType oP){
	
	if (N->N == 0) return true;
	
	switch (oP) {
		case Addition:
			if (Op == Addition || Op == Subtraction) {
				if (V1->Compatable(N, Addition) || V1->Compatable(N, Subtraction)) return true;
				if (V2->Compatable(N, Addition) || V2->Compatable(N, Subtraction)) return true;
				else return false;
			}
			else if (Op == Multiplication) return false;
			else if (Op == Division && typeid(*V2) == typeid(Number)) return true;
			else return false;
			
			break;
		case Subtraction:
			if (Op == Addition || Op == Subtraction) {
				if (V1->Compatable(N, Subtraction) || V2->Compatable(N, Subtraction)) return true;
				else return false;
			}
			else if (Op == Multiplication) return false;
			else if (Op == Division && typeid(*V2) == typeid(Number)) return true;
			else return false;
			
			break;
		case Multiplication:
			if (N->N == 1 || N->N == 0) return true;
			if (Op == Addition || Op == Subtraction) return true;
			else if (Op == Multiplication)
				if (V1->Compatable(N, Multiplication) || V2->Compatable(N, Multiplication)) return true;
				else if (Op == Division) return true;
				else if (Op == Exponent && N->operator==(V1)) return true;
				else return false;
			
			break;
		case Division:
			if (Op == Addition || Op == Subtraction) {
				if (V1->Compatable(N, Division) && V2->Compatable(N, Division)) return true;
			}
			else if (Op == Multiplication) {
				if (V1->Compatable(N, Division) || V2->Compatable(N, Division)) return true;
			}
			else if (Op == Exponent && V1->operator==(N)) return true;
			else {
				return false;
			}
			
			break;
		case Exponent:
			return true;
		default:
			return false;
	}
	return false;
	
}
// Compatable // Operation & Character
bool Operation::Compatable(Character* C,OperatorType oP){
	switch (oP) {
		case Addition:
			if ((Op == Addition || Op == Subtraction) && (V1->Compatable(C, Addition) || V2->Compatable(C, Addition)))return true;
			else if (Op == Multiplication) {
				if (typeid(*V1) == typeid(Number) && V2->Compatable(C, Addition)) return true;
				else if (typeid(*V2) == typeid(Number) && V1->Compatable(C, Addition)) return true;
				else {
					return false;
				}
			}
			else {
				return false;
			}
			
			break;
		case Subtraction:
			if ((Op == Addition || Op == Subtraction) && (V1->Compatable(C, Subtraction) || V2->Compatable(C, Subtraction))) return true;
			else if (Op == Multiplication) {
				if (typeid(*V1) == typeid(Number) && V2->Compatable(C, Subtraction)) return true;
				else if (typeid(*V2) == typeid(Number) && V1->Compatable(C, Subtraction)) return true;
			}
			else {
				return false;
			}
			
			break;
		case Multiplication:
			if ((Op == Addition || Op == Subtraction) && (V1->Compatable(C, Multiplication) || V2->Compatable(C, Multiplication))) return true;
			else if ((Op == Multiplication) && (V1->Compatable(C, Multiplication) || V2->Compatable(C, Multiplication))) return true;
			else if (Op == Division && C->Compatable(V2, Division)) return true;
			else if (V1->operator==(C) && Op == Exponent) return true;
			else {
				return false;
			}
			
			break;
		case Division:
			if (Op == Multiplication && (V1->Compatable(C, Division) || (V2->Compatable(C, Division)))) return true;
			else if ((Op == Addition || Op == Subtraction)  && (V1->Compatable(C, Division) && (V2->Compatable(C, Division)))) return true;
			else if (V1->operator==(C) && Op == Exponent) return true;
			else {
				return false;
			}
			
			break;
		case Exponent:
			return  true;
			
		default:
			return false;
	}
	
	return false;
}
// Compatable // Operation & Operation
bool Operation::Compatable(Operation* F,OperatorType oP){
	switch (oP) {
		case Addition:
			if (this->Op == Addition || this->Op == Subtraction) {
				if (!F->positive) return true;
				if (F->Op == Addition || F->Op == Subtraction) {
					if (this->Compatable(F->V1, Addition) || this->Compatable(F->V2, Addition)) return true;
					else {
						return false;
					}
				}
				else if (F->Op == Multiplication) {
					if (V1->Compatable(F, Addition)) return true;
					else if (V2->Compatable(F, Addition) && Op == Addition) return true;
					else if (F->Compatable(V2, Subtraction) && Op == Subtraction) return true;
				}
				else if (F->Op == Division) {
					if ((*this * F->V2)->Compatable(F->V1, Addition))return true;
				}
			}
			else if (this->Op == Multiplication) {
				if (F->Op == Addition || F->Op == Subtraction) {
					if (this->Compatable(F->V1, Addition)) return true;
					else if ((this->Compatable(F->V2, Addition) && F->Op == Addition) || (this->Compatable(F->V2, Subtraction) && F->Op == Subtraction)) return true;
				}
				else if (F->Op == Multiplication) {
					if (typeid(*V1) != typeid(Number) && typeid(*V2) == typeid(Number)) {
						if (typeid(*F->V1) != typeid(Number) && typeid(*F->V2) == typeid(Number)) {
							if (V1->Compatable(F->V1, Addition)) return true;
						}
						else if (typeid(*F->V2) != typeid(Number) && typeid(*F->V1) == typeid(Number)) {
							if (V1->Compatable(F->V2, Addition)) return true;
						}
					}
					if (typeid(*V2) != typeid(Number) && typeid(*V1) == typeid(Number)) {
						if (typeid(*F->V1) != typeid(Number) && typeid(*F->V2) == typeid(Number)) {
							if (V2->Compatable(F->V1, Addition)) return true;
						}
						else if (typeid(*F->V2) != typeid(Number) && typeid(*F->V1) == typeid(Number)) {
							if (V2->Compatable(F->V2, Addition)) return true;
						}
					}
				}
				else if (F->Op == Division) {
					if (Compatable(F->V1, Subtraction)) return true;
				}
				else {
					return false;
				}
			}
			else if (this->Op == Division) {
				if (F->Op == Addition || F->Op == Subtraction) {
					if ((this->Compatable(F->V1, Addition) || this->Compatable(F->V2, Addition)) || this->Compatable(F->V2, Subtraction)) return true;
				}
				else if (F->Op == Division) {
					if (V2->operator==(F->V2)) return true;
				}
				else {
					return false;
				}
			}
			else if (operator==(F)) return true;
			
			break;
		case Subtraction:
			if (this->Op == Addition || this->Op == Subtraction) {
				if (!F->positive) return true;
				if (F->Op == Addition) {
					if ((this->Compatable(F->V1, Subtraction) || this->Compatable(F->V2, Subtraction))) return true;
				}
				else if (F->Op == Subtraction) {
					if ((this->Compatable(F->V1, Subtraction) || this->Compatable(F->V2, Addition))) return true;
					else return true;
				}
			 
				else if (F->Op == Multiplication) {
					if (V1->Compatable(F, Subtraction)) return true;
					else if (Op == Addition && V2->Compatable(F, Subtraction)) return true;
					else if (Op == Subtraction && V2->Compatable(F, Addition)) return true;
				}
				else {
					return false;
				}
			}
			else if (this->Op == Multiplication) {
				if (F->Op == Addition || F->Op == Subtraction) {
					if (this->Compatable(F->V1, Subtraction)) return true;
					else if ((this->Compatable(F->V2, Subtraction) && F->Op == Addition) || (this->Compatable(F->V2, Addition) && F->Op == Subtraction) )return true;
				}
				else if (F->Op == Multiplication) {
					if (typeid(*V1) != typeid(Number) && typeid(*V2) == typeid(Number)) {
						if (typeid(*F->V1) != typeid(Number) && typeid(*F->V2) == typeid(Number)) {
							if (V1->Compatable(F->V1, Subtraction)) return true;
						}
						else if (typeid(*F->V2) != typeid(Number) && typeid(*F->V1) == typeid(Number)) {
							if (V1->Compatable(F->V2, Subtraction)) return true;
						}
					}
					if (typeid(*V2) != typeid(Number) && typeid(*V1) == typeid(Number)) {
						if (typeid(*F->V1) != typeid(Number) && typeid(*F->V2) == typeid(Number)) {
							if (V2->Compatable(F->V1, Subtraction)) return true;
						}
						else if (typeid(*F->V2) != typeid(Number) && typeid(*F->V1) == typeid(Number)) {
							if (V2->Compatable(F->V2, Subtraction)) return true;
						}
					}
				}
				else if (F->Op == Division) {
					if (Compatable(F->V1, Subtraction)) return true;
				}
				else {
					return false;
				}
			}
			else if (this->Op == Division) {
				if (F->Op == Addition || F->Op == Subtraction) {
					if ((this->Compatable(F->V1, Subtraction) || this->Compatable(F->V2, Subtraction)) || this->Compatable(F->V2, Addition)) return true;
				}
				else if (F->Op == Multiplication) {
					if (V1->Compatable(F, Addition)) return true;
				}
				else if (F->Op == Division) {
					if (V2->operator==(F->V2)) return true;
				}
				else {
					return false;
				}
			}
			else if (operator==(F)) return true;
			
			break;
		case Multiplication:
			if (this->Op == Addition || this->Op == Subtraction ) {
				if (F->Op == Addition || F->Op == Subtraction) {
					if (this->Compatable(F->V1, Multiplication) || this->Compatable(F->V2, Multiplication)) return true;
				}
				else if (F->Op == Exponent || F->Op == Multiplication) {
					if ((F->Compatable(V1, Multiplication) || F->Compatable(V2, Multiplication))) return true;
					else if (F->Op == Exponent && operator==(F->V1)) return true;
				}
				else if (F->Op == Division && this->Compatable(F->V1, Multiplication)) return true;
			}
			else if (this->Op == Multiplication) {
				if (F->Op == Addition || F->Op == Subtraction) {
					if (this->Compatable(F->V1, Multiplication) || this->Compatable(F->V2, Multiplication)) return true;
				}
				else if (F->Op == Multiplication) {
					if (this->Compatable(F->V1, Multiplication) || this->Compatable(F->V2, Multiplication)) return true;
				}
				else if (F->Op == Division) {
					if (this->Compatable(F->V2, Division) || Compatable(F->V1, Multiplication)) return true;
				}
				else if (F->Op == Exponent) {
					if (V1->Compatable(F, Multiplication) || V2->Compatable(F, Multiplication)) return true;
				}
			}
			else if (this->Op == Division) {
				if (F->Op == Addition || F->Op == Subtraction) {
					if (V1->Compatable(F, Multiplication)) return true;
				}
				else if (F->Op == Multiplication) {
					if (F->Compatable(V2, Division) || F->Compatable(V1, Multiplication)) return true;
				}
				else if (F->Op == Division) {
					if (V1->Compatable(F->V1, Multiplication) && V2->Compatable(F->V2, Multiplication)) return true;
				}
				else if (F->Op == Exponent) {
					if (F->Compatable(V2, Division)) return true;
				}
			}
			else if (this->Op == Exponent) {
				if (F->Op == Addition || F->Op == Subtraction) {
					if (this->Compatable(F->V1, Multiplication) || this->Compatable(F->V2, Multiplication)) return true;
				}
				else if (F->Op == Multiplication) {
					if (F->V1->Compatable(this, Multiplication) || F->V2->Compatable(this, Multiplication)) return true;
				}
				else if (F->Op == Division) {
					if (this->Compatable(F->V2, Division)) return true;
				}
				else if (F->Op == Exponent) {
					if (V1->operator==(F->V1)) return true;
				}
			}
			
			break;
		case Division:
			if (this->Op == Addition || this->Op == Subtraction ) {
				if (F->Op == Addition || F->Op == Subtraction) {
					if (V1->Compatable(F, Division) && V2->Compatable(F, Division)) return true;
				}
				else if (F->Op == Multiplication) {
					if (this->Compatable(F->V1, Division) || this->Compatable(F->V2, Division)) return true;
				}
				else if (F->Op == Division) return true;
				else if (F->Op == Exponent) {
					if (operator==(F->V1)) return true;
				}
			}
			else if (this->Op == Multiplication) {
				if (F->Op == Addition || F->Op == Subtraction) {
					if (V1->Compatable(F, Division) || V2->Compatable(F, Division)) return true;
				}
				else if (F->Op == Multiplication) {
					if (this->Compatable(F->V1, Division) || this->Compatable(F->V2, Division)) return true;
				}
				else if (F->Op == Division) return true;
				else if (F->Op == Exponent) {
					if (V1->Compatable(F, Division)) return true;
					else if (V2->Compatable(F, Division)) return true;
				}
			}
			else if (this->Op == Division) return true;
			else if (this->Op == Exponent) {
				if (F->Op == Addition || F->Op == Subtraction) {
					if (V1->operator == (F)) return true;
				}
				else if (F->Op == Multiplication) {
					if (Compatable(F->V1, Division)) return true;
					else if (Compatable(F->V2, Division)) return true;
				}
				else if (F->Op == Division) return true;
				else if (F->Op == Exponent) {
					if (V1->operator==(F->V1)) return true;
				}
			}
			
			break;
		case Exponent:
			if (F->Op == Division) return true;
			
			break;
		default:
			return false;
	}
	return false;
}

// Operation & Number
Value* Operation::operator + (Number* N) {
	if (N->N == 0) {
		return this;
	}
	if (Compatable(N, Addition)) {
		switch (Op) {
			case Addition:
				if (V1->Compatable(N, Addition)) return *(*V1 + N) + V2;
				else if (V2->Compatable(N, Addition)) return *(*V2 + N) + V1;
			case Subtraction:
				if (V1->Compatable(N, Addition)) return *(*V1 + N) - V2;
				else if (N->Compatable(V2, Subtraction)) return *V1 + (*N + V2);
			case Multiplication:
				break;
			case Division:
				return *(*V1 + (*N * V2)) / V2;
			case Exponent:
				break;
			default:
				break;
		}
	}
	
	Value* V = new Operation(this, Addition, N);
	return V;
}
Value* Operation::operator - (Number* N) {
	if (N->N == 0) return this;
	if (Compatable(N, Subtraction)) {
		switch (Op) {
			case Addition:
				if (V1->Compatable(N, Subtraction)) return *(*V1 - N) + V2;
				else if (V2->Compatable(N, Subtraction)) return *(*V2 - N) + V1;
			case Subtraction:
				if (V1->Compatable(N, Subtraction)) return *(*V1 - N) - V2;
				else if (V2->Compatable(N, Subtraction)) return *V1 - (*V2 - N);
			case Multiplication:
				break;
			case Division:
				return *(*V1 - (*N * V2)) / V2;
			case Exponent:
				break;
			default:
				break;
		}
	}
	Value* V = new Operation(this, Subtraction, N);
	return V;
}
Value* Operation::operator * (Number* N) {
	if (N->N == 0) return N;
	if (N->N == 1) return this;
	if (Compatable(N, Multiplication)) {
		switch (Op) {
			case Addition:
				return *(*V1 * N) + (*V2 * N);
			case Subtraction:
				return *(*V1 * N) - (*V2 * N);
			case Multiplication:
				if (V1->Compatable(N, Multiplication)) return *(*V1 * N) * V2;
				else if (V2->Compatable(N, Multiplication)) return *(*V2 * N) * V1;
				break;
			case Division:
				return *(*V1 * N) / V2;
			case Exponent:
				
			default:
				break;
		}
	}
	Value* V = new Operation(this, Multiplication, N);
	return V;
}
Value* Operation::operator / (Number* N) {
	if (N->N == 1) return this;
	if (Compatable(N, Division)) {
		switch (Op) {
			case Addition:
				return *(*V1 / N) + *(*V2 / N) / N;
			case Subtraction:
				return *(*V1 * N) - *(*V2 * N) / N;
			case Multiplication:
				if (V1->Compatable(N, Division)) return *(*V1 / N) * V2;
				else if (V2->Compatable(N, Division)) return *V1 * (*V2 / N);
			case Division:
				return *V1 / (*V2 * N);
			case Exponent:
				return *V1 ^ (*V2 - new Number(1.0));
			default:
				break;
		}
	}
	Value* V = new Operation(this, Division, N);
	return V;
}
Value* Operation::operator ^ (Number* N) {
	if (N->N == 1) return this;
	if (N->N == 0) return new Number(1);
	if (N->N < 0) {
		Value* V = *this ^ new Number(N->N * -1);
		V = *new Number(1) / V;
		return this;
	}
	if (Compatable(N, Exponent)) {
		Value* V = new Operation(*this);
		for (int i = 1; i < N->N; i++)
			V = *V * this;
		
		return V;
	}
	Value* V = new Operation(this, Exponent, N);
	return V;
}
// Operation & Character
Value* Operation::operator + (Character* C) {
	if (Compatable(C, Addition)) {
		switch (Op) {
			case Addition:
				if (V1->Compatable(C, Addition)) return *(*V1 + C) + V2;
				else if (V2->Compatable(C, Addition)) return *(*V2 + C) + V1;
			case Subtraction:
				if (V1->Compatable(C, Addition)) return *(*V1 + C) - V2;
				else if (V2->Compatable(C, Addition)) return *V1 - (*V2 + C);
			case Multiplication:
				return *(*V1 + new Number(1)) * V2;
			case Division:
				break;
			case Exponent:
				break;
			default:
				break;
		}
	}
	Value* V = new Operation(this, Addition, C);
	return V;
}
Value* Operation::operator - (Character* C) {
	if (Compatable(C, Subtraction)) {
		switch (Op) {
			case Addition:
				if (V1->Compatable(C, Subtraction)) return *(*V1 - C) + V2;
				else if (V2->Compatable(C, Subtraction)) return *(*V2 - C) + V1;
			case Subtraction:
				if (V1->Compatable(C, Subtraction)) return *(*V1 - C) - V2;
				else if (V2->Compatable(C, Subtraction)) return *V1 - (*V2 - C);
			case Multiplication:
				return *(*V1 - new Number(1)) * V2;
			case Division:
				break;
			case Exponent:
				break;
			default:
				break;
		}
	}
	Value* V = new Operation(this, Subtraction, C);
	return V;
}
Value* Operation::operator * (Character* C) {
	if (Compatable(C, Multiplication)) {
		switch (Op) {
			case Addition:
				return *(*V1 * C) + (*V2 * C);
			case Subtraction:
				return *(*V1 * C) - (*V2 * C);
			case Multiplication:
				if (V1->Compatable(C, Multiplication)) return *(*V1 * C) * V2;
				else if (V2->Compatable(C, Multiplication)) return *(*V2 * C) * V1;
			case Division:
				return *(*V1 * C) / V2;
			case Exponent:
				return *C ^ *V2 + new Number(1);
			default:
				break;
		}
	}
	Value* V = new Operation(this, Multiplication, C);
	return V;
}
Value* Operation::operator / (Character* C) {
	if (Compatable(C, Division)) {
		switch (Op) {
			case Addition:
				return *(*V1 / C) + (*V2 / C);
			case Subtraction:
				return *(*V1 / C) - (*V2 / C);
			case Multiplication:
				if (V1->Compatable(C, Division)) return *(*V1 / C) * V2;
				else if (V2->Compatable(C, Division)) return *(*V2 / C) * V1;
			case Division:
				break;
			case Exponent:
				return *V1 ^ *V2 - new Number(1);
			default:
				break;
		}
	}
	Value* V = new Operation(this, Division, C);
	return V;
}
Value* Operation::operator ^ (Character* C) {
	Value* V = new Operation(this, Exponent, C);
	return V;
}
// Operation & Operation
Value* Operation::operator + (Operation* F) {
	if (!F->positive) return *this - (*F * new Number(-1));
	if (Compatable(F, Addition)) {
		switch (Op) {
			case Addition:
				switch (F->Op) {
					case Addition:
						if (Compatable(F->V1, Addition)) return *(*this + F->V1) + F->V2;
						else if (Compatable(F->V2, Addition)) return *F->V1 + (*this + F->V2);
					case Subtraction:
						if (Compatable(F->V1, Addition)) {
							return *(*this + F->V1) - F->V2;
						}
						else if (Compatable(F->V2, Addition)) {
							return *F->V1 + (*this - F->V2);
						}
					case Multiplication:
						if (V1->Compatable(F, Addition)) {
							return *(*V1 + F) + V2;
						}
						else if (V2->Compatable(F, Addition)) {
							return *(*V2 + F) + V1;
						}
					case Division:
						return *(*(*this * F->V2) + F->V1) / F->V2;
					case Exponent:
						break;
					default:
						break;
				}
			case Subtraction:
				switch (F->Op) {
					case Addition:
						if (Compatable(F->V1, Addition)) {
							return *(*this + F->V1) - F->V2;
						}
						else if (Compatable(F->V2, Addition)) {
							return *F->V1 + (*this + F->V2);
						}
					case Subtraction:
						if (Compatable(F->V1, Addition)) {
							return *(*this + F->V1) - F->V2;
						}
						else if (Compatable(F->V2, Addition)) {
							return *F->V1 - (*this + F->V2);
						}
					case Multiplication:
						if (V1->Compatable(F, Addition)) {
							return *(*V1 + F) - V2;
						}
						// Sketchy
						else if (F->Compatable(V2, Subtraction)) {
							return *V1 + (*F - V2);
						}
					case Division:
						return *(*(*this * F->V2) + F->V1) / F->V2;
					case Exponent:
						break;
					default:
						break;
				}
			case Multiplication:
				switch (F->Op) {
					case Addition:
						if (Compatable(F->V1, Addition)) {
							return *(*this + F->V1) + F->V2;
						}
						else if (Compatable(F->V2, Addition)) {
							return *(*this + F->V2) + F->V1;
						}
					case Subtraction:
						if (Compatable(F->V1, Addition)) {
							return *(*this + F->V1) - F->V2;
						}
						else if (Compatable(F->V2, Subtraction)) {
							return *(*this - F->V2) + F->V1;
						}
					case Multiplication:
						// Sketchy
						if (V2->Compatable(F->V2, Addition)) {
							return *(*V1 + F->V1) * V2;
						}
						else if (V2->Compatable(F->V1, Addition)) {
							return *(*V1 + F->V2) * V2;
						}
					case Division:
						return *(*this + F->V1) / F->V2;
					case Exponent:
						break;
					default:
						break;
				}
			case Division:
				switch (F->Op) {
					case Addition:
						if (this->Compatable(F->V1, Addition)) {
							return *(*this + F->V1) + F->V2;
						}
						else if (this->Compatable(F->V2, Addition)) {
							return *(*this + F->V2) + F->V1;
						}
					case Subtraction:
						if (this->Compatable(F->V1, Addition)) {
							return *(*this + F->V1) - F->V2;
						}
						else if (this->Compatable(F->V2, Subtraction)) {
							return *(*this - F->V2) + F->V1;
						}
					case Multiplication:
						return *(*V1 + F) / V2;
					case Division:
						return *(*V1 + F->V1) / V2;
					case Exponent:
						break;
					default:
						break;
				}
			case Exponent:
				switch (F->Op) {
					case Addition:
						break;
					case Subtraction:
						break;
					case Multiplication:
						break;
					case Division:
						break;
					case Exponent:
						if (this->operator==(F)) {
							Value* V = new Operation(new Number(2), Multiplication, this);
							return V;
						}
						break;
					default:
						break;
				}
			default:
				break;
		}
		
	}
	
	Value* V = new Operation(this, Addition, F);
	return V;
}
Value* Operation::operator - (Operation* F) {
	if (operator==(F)) {
		Value* V = this;
		V = new Number(0);
		return V;
	}
	if (!F->positive) {
		return *this + (*F * new Number(-1));
	}
	if (Compatable(F, Subtraction)) {
		switch (Op) {
			case Addition:
				switch (F->Op) {
					case Addition:
						if (Compatable(F->V1, Subtraction)) {
							return *(*this - F->V1) - F->V2;
						}
						else if (Compatable(F->V2, Subtraction)) {
							return *(*this - F->V2) - F->V1;
						}
					case Subtraction:
						if (Compatable(F->V1, Subtraction)) {
							return *(*this - F->V1) - F->V2;
						}
						else if (Compatable(F->V2, Addition)) {
							return *(*this + F->V2) - F->V1;
						}
						else {
							return *(*this + F->V2) - F->V1;
						}
					case Multiplication:
						if (V1->Compatable(F, Subtraction)) {
							return *(*V1 - F) + V2;
						}
						else if (V2->Compatable(F, Subtraction)) {
							return *(*V2 - F) + V1;
						}
					case Division:
						return *(*(*this * F->V2) - F->V1) / F->V2;
					case Exponent:
						break;
					default:
						break;
				}
			case Subtraction:
				switch (F->Op) {
					case Addition:
						if (Compatable(F->V1, Subtraction)) {
							return *(*this - F->V1) - F->V2;
						}
						else if (Compatable(F->V2, Subtraction)) {
							return *(*this - F->V2) - F->V1;
						}
					case Subtraction:
						if (Compatable(F->V1, Subtraction)) {
							return *(*this - F->V1) + F->V2;
						}
						else if (Compatable(F->V2, Addition)) {
							return *(*this + F->V2) - F->V1;
						}
						else {
							return *(*this + F->V2) - F->V1;
						}
					case Multiplication:
						if (V1->Compatable(F, Subtraction)) {
							return *(*V1 - F) - V2;
						}
						else if (V2->Compatable(F, Addition)) {
							return *V1 - (*V2 + F);
						}
					case Division:
						return *(*(*this * F->V2) - F->V1) / F->V2;
					case Exponent:
						break;
					default:
						break;
				}
			case Multiplication:
				switch (F->Op) {
					case Addition:
						if (Compatable(F->V1, Subtraction)) {
							return *(*this - F->V1) - F->V2;
						}
						else if (Compatable(F->V2, Subtraction)) {
							return *(*this - F->V2) - F->V1;
						}
					case Subtraction:
						if (Compatable(F->V1, Subtraction)) {
							return *(*this - F->V1) + F->V2;
						}
						else if (Compatable(F->V2, Addition)) {
							return *(*this + F->V2) - F->V1;
						}
					case Multiplication:
						// Sketchy
						if (typeid(*V1) != typeid(Number) && typeid(*V2) == typeid(Number)) {
							if (typeid(*F->V1) != typeid(Number) && typeid(*F->V2) == typeid(Number)) {
								if (V1->Compatable(F->V1, Subtraction)) {
									return *(*V2 - F->V2) * V1;
								}
							}
							else if (typeid(*F->V2) != typeid(Number) && typeid(*F->V1) == typeid(Number)) {
								if (V1->Compatable(F->V2, Subtraction)) {
									return *(*V2 - F->V1) * V1;
								}
							}
						}
						if (typeid(*V2) != typeid(Number) && typeid(*V1) == typeid(Number)) {
							if (typeid(*F->V1) != typeid(Number) && typeid(*F->V2) == typeid(Number)) {
								if (V2->Compatable(F->V1, Subtraction)) {
									return *(*V1 - F->V2) * V2;
								}
							}
							else if (typeid(*F->V2) != typeid(Number) && typeid(*F->V1) == typeid(Number)) {
								if (V2->Compatable(F->V2, Subtraction)) {
									return *(*V1 - F->V1) * V2;
								}
							}
						}
						/*
						 if (V2->Compatable(F->V2, Subtraction)) {
							return *(*V1 - F->V1) * V2;
						 }
						 else if (V2->Compatable(F->V1, Subtraction)) {
							return *(*V1 - F->V2) * V2;
						 }
						 */
					case Division:
						return *(*this - F->V1) / F->V2;
					case Exponent:
						break;
					default:
						break;
				}
			case Division:
				switch (F->Op) {
					case Addition:
						if (Compatable(F->V1, Subtraction)) {
							return *(*this - F->V1) - F->V2;
						}
						else if (Compatable(F->V2, Subtraction)) {
							return *(*this - F->V2) - F->V1;
						}
					case Subtraction:
						if (Compatable(F->V1, Subtraction)) {
							return *(*this - F->V1) + F->V2;
						}
						else if (Compatable(F->V2, Addition)) {
							return *(*this + F->V2) + F->V1;
						}
					case Multiplication:
						return *(*V1 - F) / F->V2;
					case Division:
						return *(*V1 - F->V1) / V2;
					case Exponent:
						break;
					default:
						break;
				}
			case Exponent:
				switch (F->Op) {
					case Addition:
						break;
					case Subtraction:
						break;
					case Multiplication:
						break;
					case Division:
						break;
					case Exponent:
						break;
					default:
						break;
				}
			default:
				break;
		}
		
	}
	Value* V = new Operation(this, Subtraction, F);
	return V;
}
Value* Operation::operator * (Operation* F) {
	if (Compatable(F, Multiplication)) {
		switch (Op) {
			case Addition:
				switch (F->Op) {
					case Addition:
						return *(*this * F->V1) + (*this * F->V2);
					case Subtraction:
						return *(*this * F->V1) - (*this * F->V2);
					case Multiplication:
						return *(*V1 * F) + (*V2 * F);
					case Division:
						return *(*this * F->V1) / F->V2;
					case Exponent:
						return *(*V1 * F) + (*V2 * F);
					default:
						break;
				}
			case Subtraction:
				switch (F->Op) {
					case Addition:
						return *(*this * F->V1) + (*this * F->V2);
					case Subtraction:
						return *(*this * F->V1) - (*this * F->V2);
					case Multiplication:
						return *(*V1 * F) - (*V2 * F);
					case Division:
						return *(*this * F->V1) / F->V2;
					case Exponent:
						return *(*V1 * F) - (*V2 * F);
					default:
						break;
				}
			case Multiplication:
				switch (F->Op) {
					case Addition:
						return *(*this * F->V1) + (*this * F->V2);
					case Subtraction:
						return *(*this * F->V1) - (*this * F->V2);
					case Multiplication:
						if (Compatable(F->V1, Multiplication)) {
							return *(*this * F->V1) * F->V2;
						}
						else if (V2->Compatable(F, Multiplication)) {
							return *(*this * F->V2) * F->V1;
						}
					case Division:
						return *(*this * F->V1) / F->V2;
					case Exponent:
						if (V1->Compatable(F, Multiplication)) {
							return *(*V1 * F) * V2;
						}
						else if (V2->Compatable(F, Multiplication)) {
							return *(*V2 * F) * V1;
						}
					default:
						break;
				}
			case Division:
				switch (F->Op) {
					case Addition:
						if (Compatable(F->V1, Subtraction)) {
							return *(*this - F->V1) - F->V2;
						}
						else if (Compatable(F->V2, Subtraction)) {
							return *(*this - F->V2) - F->V1;
						}
					case Subtraction:
						if (Compatable(F->V1, Subtraction)) {
							return *(*this - F->V1) + F->V2;
						}
						else if (Compatable(F->V2, Addition)) {
							return *(*this + F->V2) + F->V1;
						}
					case Multiplication:
						return *(*V1 * F) / V2;
					case Division:
						return *(*V1 - F->V1) / (*V2 * F->V2);
					case Exponent:
						return *V1 * (*F / V2);
					default:
						break;
				}
			case Exponent:
				switch (F->Op) {
					case Addition:
						return *(*this * F->V1) + (*this * F->V2);
					case Subtraction:
						return *(*this * F->V1) - (*this * F->V2);
					case Multiplication:
						return *(*this * F->V1) * (*this * F->V2);
					case Division:
						return *(*this / F->V2) * F->V1;
					case Exponent:
						return *V1 ^ (*V2 + F->V2);
					default:
						break;
				}
			default:
				break;
		}
		
	}
	Value* V = new Operation(this, Multiplication, F);
	return V;
}
Value* Operation::operator / (Operation* F) {
	if (operator==(F)) {
		Value* V = this;
		V = new Number(1);
		return V;
	}
	if (Compatable(F, Division)) {
		switch (Op) {
			case Addition:
				switch (F->Op) {
					case Addition:
						return *(*V1 / F) + (*V2 / F);
					case Subtraction:
						return *(*V1 / F) - (*V2 / F);
					case Multiplication:
						if (Compatable(F->V1, Division)) {
							return *(*this / F->V1) / F->V2;
						}
						else if (Compatable(F->V2, Division)){
							return *(*this / F->V2) / F->V1;
						}
					case Division:
						return *(*this * F->V2) / F->V1;
					case Exponent:
						return *new Number(1) / (*this ^ (*F->V2 - new Number(1)));
					default:
						break;
				}
			case Subtraction:
				switch (F->Op) {
					case Addition:
						return *(*this * F->V1) + (*this * F->V2);
					case Subtraction:
						return *(*this * F->V1) - (*this * F->V2);
					case Multiplication:
						if (Compatable(F->V1, Division)) {
							return *(*this / F->V1) / F->V2;
						}
						else if (Compatable(F->V2, Division)){
							return *(*this / F->V2) / F->V1;
						}
					case Division:
						return *(*this * F->V2) / F->V1;
					case Exponent:
						return *new Number(1) / (*this ^ (*F->V2 - new Number(1)));
					default:
						break;
				}
			case Multiplication:
				switch (F->Op) {
					case Addition:
						if (V1->Compatable(F, Division)) {
							return *(*V1 / F) * V2;
						}
						else if (V2->Compatable(F, Division)){
							return *(*V2 / F) * V1;
						}
					case Subtraction:
						if (V1->Compatable(F, Division)) {
							return *(*V1 / F) * V2;
						}
						else if (V2->Compatable(F, Division)){
							return *(*V2 / F) * V1;
						}
					case Multiplication:
						if (V1->Compatable(F, Division)) {
							return *(*V1 / F) * V2;
						}
						else if (V2->Compatable(F, Division)) {
							return *(*V2 / F) * V1;
						}
					case Division:
						return *(*this * F->V1) / F->V2;
					case Exponent:
						if (V1->Compatable(F, Division)) {
							return *(*V1 / F) * V2;
						}
						else if (V2->Compatable(F, Division)) {
							return *(*V2 / F) * V1;
						}
					default:
						break;
				}
			case Division:
				return *V1 / (*V2 * F);
			case Exponent:
				switch (F->Op) {
					case Addition:
						return *V1 ^ (*V2 - new Number(1));
					case Subtraction:
						return *V1 ^ (*V2 - new Number(1));
					case Multiplication:
						if (Compatable(F->V1, Division)) {
							return *(*this / F->V1) / F->V2;
						}
						else if (Compatable(F->V1, Division)) {
							return *(*this / F->V2) / F->V1;
						}
					case Division:
						return *(*this * F->V2) / F->V1;
					case Exponent:
						return *V1 ^ (*V2 - F->V2);
					default:
						break;
				}
			default:
				break;
		}
		
	}
	Value* V = new Operation(this, Division, F);
	return V;
}
Value* Operation::operator ^ (Operation* F) {
	Value* V = new Operation(this, Exponent, F);
	return V;
}

