#include "Value.h"

Number::Number() {}
Number::Number(double V) {
	N = V;
}
string Number::getDisplayName() {
	if (DisplayValue.size() == 0) updateDisplayName();
	return DisplayValue;
}
void Number::updateDisplayName() {
	if (N == (int) N) DisplayValue = to_string((int)N);
	else DisplayValue = to_string(N);
}

// Number & Number
Value* Number::operator + (Number* N) {
	double answer = this->N + N->N;
	Value* V = new Number(answer);
	//V = new Number(answer);
	return V;
}
Value* Number::operator - (Number* N) {
	double answer = this->N - N->N;
	//	V = new Number(answer);
	return new Number(answer);
}
Value* Number::operator * (Number* N) {
	double answer = this->N * N->N;
	//	V = new Number(answer);
	return new Number(answer);
}
Value* Number::operator / (Number* N) {
	double answer = this->N / N->N;
	//V = new Number(answer);
	return new Number(answer);
}
Value* Number::operator ^ (Number* N) {
	double answer = pow(this->N, N->N);
	//	V = new Number(answer);
	return new Number(answer);
}
// Number & Character
Value* Number::operator + (Character* C) {
	return new Operation(this, Addition, C);
}
Value* Number::operator - (Character* C) {
	return new Operation(this, Subtraction, C);
}
Value* Number::operator * (Character* C) {
	if (N == 0) {
		return this;
	}
	else if (N == 1) {
		return C;
	}
	return new Operation(this, Multiplication, C);
}
Value* Number::operator / (Character* C) {
	return new Operation(this, Division, C);
}
Value* Number::operator ^ (Character* C) {
	return new Operation(this, Exponent, C);
}
// Number & Operation
Value* Number::operator + (Operation* F) {
	if (N == 0) {
		return F;
	}
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
				
			case Division:
				return *(*F->V1 + (*this * F->V2)) / F->V2;
			case Exponent:
				
			default:
				break;
		}
	}
	Value* V = new Operation(this, Addition, F);
	return V;
}
Value* Number::operator - (Operation* F) {
	if (N == 0) {
		return F;
	}
	if (!F->positive) {
		return *this + (*F * new Number(-1));
	}
	if (Compatable(F, Subtraction)) {
		switch (F->Op) {
			case Addition:
				if (Compatable(F->V1, Subtraction)) {
					return *(*this - F->V1) + F->V2;
				}
				else if (Compatable(F->V2, Subtraction)) {
					return *(*this - F->V2) + F->V1;
				}
			case Subtraction:
				if (Compatable(F->V1, Subtraction)) {
					return *(*this - F->V1) - F->V2;
				}
				else if (Compatable(F->V2, Subtraction)) {
					return *F->V1 - (*this - F->V2);
				}
			case Multiplication:
				
			case Division:
				return *(*(*this * F->V2) - F->V1) / F->V2;
			case Exponent:
				
			default:
				break;
		}
	}
	Value* V = new Operation(this, Subtraction, F);
	return V;
}
Value* Number::operator * (Operation* F) {
	if (N == 0) {
		return this;
	}
	else if(N == 1) {
		return F;
	}
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
				break;
			case Division:
				return *(*this * F->V1) / F->V2 ;
			case Exponent:
				return *this ^ (*F->V2 + new Number(1));
			default:
				break;
		}
	}
	Value* V = new Operation(this, Multiplication, F);
	return V;
}
Value* Number::operator / (Operation* F) {
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
				return *new Number(1) / (*this ^ (*F->V2 - new Number(1)));
			default:
				break;
		}
	}
	Value* V = new Operation(this, Division, F);
	return V;
}
Value* Number::operator ^ (Operation* F) {
	if (N == 0) {
		return this;
	}
	if (F->Op == Division) {
		return *(*this ^ F->V1) ^ (*new Number(1) / F->V2);
	}
	Value* V = new Operation(this, Exponent, F);
	return V;
}

// Compatable // Number & Number
bool Number::Compatable(Number* N,OperatorType oP){
	return true;
}
// Compatable // Number & Character
bool Number::Compatable(Character* C,OperatorType oP){
	if (N == 0) {
		return true;
	}
	switch (oP) {
		case Addition:
			return false;
			break;
		case Subtraction:
			return false;
			break;
		case Multiplication:
			if (N == 1 || N == 0) {
				return true;
			}
			else {
				return false;
			}
			break;
		case Division:
			if (N == 1) {
				return true;
			}
			else {
				return false;
			}
			break;
		case Exponent:
			return false;
			break;
		default:
			return false;
	}
	return false;
}
// Compatable // Number & Operation
bool Number::Compatable(Operation* F,OperatorType oP){
	if (N == 0) {
		return true;
	}
	switch (oP) {
		case Addition:
			if (F->Op == Addition || F->Op == Subtraction) {
				if ((this->Compatable(F->V1, Addition) || (this->Compatable(F->V2, Addition))) && F->Op == Addition || F->Op == Subtraction){
					return true;
				}
				else {
					return false;
				}
			}
			else if (F->Op == Multiplication) {
				return false;
			}
			else if (F->Op == Division && typeid(*F->V2) == typeid(Number)) {
				return true;
			}
			else {
				return false;
			}
			
			break;
		case Subtraction:
			if (F->Op == Addition || F->Op == Subtraction) {
				if ((this->Compatable(F->V1, Subtraction) || (this->Compatable(F->V2, Subtraction))) && F->Op == Subtraction || F->Op == Subtraction){
					return true;
				}
				else {
					return false;
				}
			}
			else if (F->Op == Multiplication) {
				return false;
			}
			else if (F->Op == Division && typeid(*F->V2) == typeid(Number)) {
				return true;
			}
			else {
				return false;
			}
			
			break;
		case Multiplication:
			if (N == 1 || N == 0) {
				return true;
			}
			if (F->Op == Addition || F->Op == Subtraction) {
				return true;
			}
			else if (F->Op == Multiplication) {
				if (this->Compatable(F->V1, Multiplication) || this->Compatable(F->V2, Multiplication)) {
					return true;
				}
			}
			else if (F->Op == Division && this->Compatable(F->V2, Division) ) {
				return true;
			}
			else if (F->Op == Exponent && operator==(F->V1) ) {
				return true;
			}
			else {
				return false;
			}
			
			break;
		case Division:
			if (F->Op == Addition || F->Op == Subtraction) {
				if (this->Compatable(F->V1, Division) && this->Compatable(F->V2, Division)) {
					return true;
				}
			}
			else if (F->Op == Multiplication) {
				if (this->Compatable(F->V1, Division) || this->Compatable(F->V2, Division)) {
					return true;
				}
			}
			else if (F->Op == Exponent && operator==(F->V1) ) {
				return true;
			}
			else {
				return false;
			}
			
			break;
		case Exponent:
			return false;
		default:
			return false;
	}
	return false;
}

Value* Number::operator + (Value* V) {
	if (N == 0) {
		return V;
	}
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
Value* Number::operator - (Value* V) {
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
Value* Number::operator * (Value* V) {
	
	if (N == 0) {
		return this;
	}
	else if (N == 1) {
		return V;
	}
	
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
Value* Number::operator / (Value* V) {
	
	if (N == 0) {
		return this;
	}
	
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
Value* Number::operator ^ (Value* V) {
	
	if (N == 0) {
		return this;
	}
	
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
bool Number::operator == (Value* V) {
	if (typeid(*V) == typeid(Number)) {
		if (N == dynamic_cast<Number*>(V)->N) {
			return true;
		}
	}
	
	return false;
}

bool Number::Compatable(Value * V,OperatorType op) {
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
