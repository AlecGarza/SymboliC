#include "Value.h"

Character::Character() {}
Character::Character(char V) {
	C = V;
	DisplayValue = V;
	this->positive = true;
}

string Character::getDisplayName() {
	if (DisplayValue.size() == 0) DisplayValue = C;
	return DisplayValue;
}
void Character::updateDisplayName() {
	DisplayValue = C;
}
// Character & Number
Value* Character::operator + (Number* N) {
	Value* V = this;
	V = new Operation(this, Addition, N);
	return V;
}
Value* Character::operator - (Number* N) {
	Value* V = this;
	V = new Operation(this, Subtraction, N);
	return V;
}
Value* Character::operator * (Number* N) {
	Value* V = this;
	V = new Operation(this, Multiplication, N);
	return V;
}
Value* Character::operator / (Number* N) {
	Value* V = this;
	V = new Operation(this, Division, N);
	return V;
}
Value* Character::operator ^ (Number* N) {
	if (N->N == 0) {
		return new Number(1);
	}
	else if (N->N == 1) {
		return this;
	}
	return new Operation(this, Exponent, N);
}

// Character & Character
Value* Character::operator + (Character* C) {
	Value* V = this;
	if (operator==(C)) {
		V = new Operation(new Number(2), Multiplication, this);
		return V;
	}
	else {
		V = new Operation(this, Addition, C);
		return V;
	}
}
Value* Character::operator - (Character* C) {
	Value* V = this;
	if (operator==(C)) {
		V = new Number(0);
		return V;
	}
	else {
		V = new Operation(this, Subtraction, C);
		return V;
	}
}
Value* Character::operator * (Character* C) {
	Value* V = this;
	if (operator==(C)) {
		V = new Operation(this, Exponent, new Number(2));
		return V;
	}
	else {
		V = new Operation(this, Multiplication, C);
		return V;
	}
}
Value* Character::operator / (Character* C) {
	Value* V = this;
	if (operator==(C)) {
		V = new Number(1);
		return V;
	}
	else {
		V = new Operation(this, Division, C);
		return V;
	}
}
Value* Character::operator ^ (Character* C) {
	Value* V = this;
	V = new Operation(this, Exponent, C);
	return V;
	
}

// Character & Operation
Value* Character::operator + (Operation* F) {
	if (!F->positive) {
		return *this - (*F * new Number(-1));
	}
	if (Compatable(F, Addition)) {
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
				else if (Compatable(F->V2, Addition)) {
					return *F->V1 - (*this + F->V2);
				}
			case Multiplication:
				if (typeid(*F->V1) == typeid(Number)) {
					F->V1 = *F->V1 + new Number(1);
					return *F->V1 * this;
				}
				else if (typeid(*F->V2) == typeid(Number)) {
					F->V2 = *F->V2 + new Number(1);
					return *F->V2 * this;
				}
			case Division:
				break;
			case Exponent:
				break;
			default:
				break;
		}
	}
	
	Value* V = new Operation(this, Addition, F);
	return V;
}
Value* Character::operator - (Operation* F) {
	if (!F->positive) {
		return *this + (*F * new Number(-1));
	}
	if (Compatable(F, Subtraction)) {
		switch (F->Op) {
			case Addition:
				if (Compatable(F->V1, Addition)) {
					return *(*this + F->V1) + F->V2;
				}
				else if (Compatable(F->V2, Addition)) {
					return *(*this + F->V2) + F->V1;
				}
			case Subtraction:
				if (Compatable(F->V1, Subtraction)) {
					return *(*this - F->V1) - F->V2;
				}
				else if (Compatable(F->V2, Subtraction)) {
					return *F->V1 - (*this - F->V2);
				}
			case Multiplication:
				F->V1 = *F->V1 - new Number(1);
				return *F->V1 * this;
			case Division:
				break;
			case Exponent:
				break;
			default:
				break;
		}
	}
	Value* V = new Operation(this, Subtraction, F);
	return V;
}
Value* Character::operator * (Operation* F) {
	if (Compatable(F, Multiplication)) {
		switch (F->Op) {
			case Addition:
				return *(*this * F->V1) + (*this * F->V2);
			case Subtraction:
				return *(*this * F->V1) - (*this * F->V2);
			case Multiplication:
				if (Compatable(F->V1, Multiplication)) {
					return *(*this * F->V1) * F->V2;
				}
				else if (Compatable(F->V2, Multiplication)) {
					return *(*this * F->V2) * F->V1;
				}
			case Division:
				return *(*this / F->V2) * F->V1;
			case Exponent:
				return *this ^ (*F->V2 + new Number(1));
			default:
				break;
		}
	}
	Value* V = new Operation(this, Multiplication, F);
	return V;
}
Value* Character::operator / (Operation* F) {
	if (Compatable(F, Division)) {
		switch (F->Op) {
			case Addition:
				return *(*this / F->V1) + (*this / F->V2);
			case Subtraction:
				return *(*this / F->V1) - (*this / F->V2);
			case Multiplication:
				if (Compatable(F->V1, Division)) {
					return *(*this / F->V1) / F->V2;
				}
				else if (Compatable(F->V2, Division)) {
					return *(*this / F->V2) / F->V1;
				}
			case Division:
				break;
			case Exponent:
				return *new Number(1) / (*this ^ *F->V2 - new Number(1));
			default:
				break;
		}
	}
	Value* V = new Operation(this, Division, F);
	return V;
}
Value* Character::operator ^ (Operation* F) {
	if (F->Op == Division) {
		return *(*this ^ F->V1) ^ (*new Number(1) / F->V2);
	}
	Value* V = new Operation(this, Exponent, F);
	return V;
}

// Compatable // Character & Number
bool Character::Compatable(Number* N,OperatorType oP){
	if (N->N == 0) {
		return true;
	}
	switch (oP) {
		case Addition:
			if (!N->positive) {
				return true;
			}
			return false;
			break;
		case Subtraction:
			if (!N->positive) {
				return true;
			}
			return false;
		case Multiplication:
			if (N->N == 1 || N->N == 0) {
				return true;
			}
			else {
				return false;
			}
			break;
		case Division:
			if (N->N == 1) {
				return true;
			}
			else {
				return false;
			}
			break;
		case Exponent:
			if (N->N == 1 || N->N == 0) {
				return true;
			}
			else {
				return false;
			}
			break;
		default:
			return false;
			break;
	}
	return false;
}
// Compatable // Character & Character
bool Character::Compatable(Character* C,OperatorType oP){
	if (operator==(C) && oP != Exponent) {
		return true;
	}
	else {
		return false;
	}
}
// Compatable // Character & Operation
bool Character::Compatable(Operation* F,OperatorType oP){
	switch (oP) {
		case Addition:
			if (!F->positive) {
				return true;
			}
			if ((F->Op == Addition || F->Op == Subtraction) && (this->Compatable(F->V1, Addition) || this->Compatable(F->V2, Addition))){
				return true;
			}
			else if (F->Op == Multiplication) {
				if (typeid(*F->V1) == typeid(Number) && this->Compatable(F->V2, Addition)) {
					return true;
				}
				else if (typeid(*F->V2) == typeid(Number) && this->Compatable(F->V1, Addition)) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
			
			break;
		case Subtraction:
			if (!F->positive) {
				return true;
			}
			if ((F->Op == Addition || F->Op == Subtraction) && (this->Compatable(F->V1, Addition) || this->Compatable(F->V2, Addition))){
				return true;
			}
			else if (F->Op == Multiplication) {
				if (typeid(*F->V1) == typeid(Number) && this->Compatable(F->V2, Addition)) {
					return true;
				}
				else if (typeid(*F->V2) == typeid(Number) && this->Compatable(F->V1, Addition)) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
			
			break;
		case Multiplication:
			if ((F->Op == Addition || F->Op == Subtraction) && (this->Compatable(F->V1, Multiplication) && this->Compatable(F->V2, Multiplication))) {
				return true;
			}
			else if (F->Op == Multiplication && (this->Compatable(F->V1, Multiplication) || this->Compatable(F->V2, Multiplication))) {
				return true;
			}
			else if (F->Op == Division && this->Compatable(F->V2, Division)) {
				return true;
			}
			else if (operator==(F->V1) && F->Op == Exponent) {
				return true;
			}
			else {
				return false;
			}
			
			break;
		case Division:
			if ((F->Op == Addition || F->Op == Subtraction)  && (this->Compatable(F->V1, Division) && (this->Compatable(F->V2, Division)))) {
				return true;
			}
			else if (F->Op == Multiplication && (this->Compatable(F->V1, Division) || (this->Compatable(F->V2, Division)))) {
				return true;
			}
			else if (operator==(F->V1) && F->Op == Exponent) {
				return true;
			}
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

Value* Character::operator + (Value* V) {
	
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
Value* Character::operator - (Value* V) {
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
Value* Character::operator * (Value* V) {
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
Value* Character::operator / (Value* V) {
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
Value* Character::operator ^ (Value* V) {
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
bool Character::operator == (Value* V) {
	if (typeid(*V) == typeid(Character)) {
		if (C == dynamic_cast<Character*>(V)->C) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

bool Character::Compatable(Value * V,OperatorType op) {
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

