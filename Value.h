#include <math.h>
#include <iostream>
#include <string>

using namespace std;

enum OperatorType {
	Addition,
	Subtraction,
	Multiplication,
	Division,
	Exponent
};

enum ValueType {
	NONE,
	CONSTANT,
	VARIABLE,
	OPERATION
};

class Operation;
class Number;
class Character;

class Value {
	
public:

	virtual string getDisplayName() = 0;
	virtual void updateDisplayName() = 0;
	
	virtual Value* operator + (Value*) = 0;
	virtual Value* operator - (Value*) = 0;
	virtual Value* operator * (Value*) = 0;
	virtual Value* operator / (Value*) = 0;
	virtual Value* operator ^ (Value*) = 0;
	virtual bool operator == (Value*) = 0;
	
	virtual	bool Compatable(Value *, OperatorType) = 0;
	
	bool positive;
	
	
	Operation* Parent;
	
	~Value(){};
	
};

class Number : public Value {
	string DisplayValue;
public:
	double N;
	
	Number();
	Number(double V);
	
	void Change(double);
	string getDisplayName();
	void updateDisplayName();
	
	Value* operator + (Value*);
	Value* operator - (Value*);
	Value* operator * (Value*);
	Value* operator / (Value*);
	Value* operator ^ (Value*);
	bool operator == (Value*);
	
	Value* operator + (Number*);
	Value* operator - (Number*);
	Value* operator * (Number*);
	Value* operator / (Number*);
	Value* operator ^ (Number*);
	
	Value* operator + (Character*);
	Value* operator - (Character*);
	Value* operator * (Character*);
	Value* operator / (Character*);
	Value* operator ^ (Character*);
	
	Value* operator + (Operation*);
	Value* operator - (Operation*);
	Value* operator * (Operation*);
	Value* operator / (Operation*);
	Value* operator ^ (Operation*);
	bool operator == (Operation*);
	
	
	bool Compatable(Value *,OperatorType);
	bool Compatable(Character *,OperatorType);
	bool Compatable(Number *,OperatorType);
	bool Compatable(Operation *,OperatorType);
	
};

class Character : public Value {
	string DisplayValue;
public:
	Character();
	Character(char V);
	
	char C;
	void Change(char);
	string getDisplayName();
	void updateDisplayName();
	
	Value* operator + (Value*);
	Value* operator - (Value*);
	Value* operator * (Value*);
	Value* operator / (Value*);
	Value* operator ^ (Value*);
	bool operator == (Value*);
	
	Value* operator + (Number*);
	Value* operator - (Number*);
	Value* operator * (Number*);
	Value* operator / (Number*);
	Value* operator ^ (Number*);
	
	Value* operator + (Character*);
	Value* operator - (Character*);
	Value* operator * (Character*);
	Value* operator / (Character*);
	Value* operator ^ (Character*);
	
	Value* operator + (Operation*);
	Value* operator - (Operation*);
	Value* operator * (Operation*);
	Value* operator / (Operation*);
	Value* operator ^ (Operation*);
	bool operator == (Operation*);
	
	bool Compatable(Value *,OperatorType);
	bool Compatable(Character *,OperatorType);
	bool Compatable(Number *,OperatorType);
	bool Compatable(Operation *,OperatorType);
	
};

class Operation : public Value {
	string DisplayValue;
public:
	OperatorType Op;
	
	Operation();
	Operation(Value*, OperatorType op, Value*);
	
	string getDisplayName();
	void updateDisplayName();
	string opString;
	
	Value *V1;
	Value *V2;
	
	Value* operator + (Value*);
	Value* operator - (Value*);
	Value* operator * (Value*);
	Value* operator / (Value*);
	Value* operator ^ (Value*);
	bool operator == (Value*);
	
	Value* operator + (Number*);
	Value* operator - (Number*);
	Value* operator * (Number*);
	Value* operator / (Number*);
	Value* operator ^ (Number*);
	
	Value* operator + (Character*);
	Value* operator - (Character*);
	Value* operator * (Character*);
	Value* operator / (Character*);
	Value* operator ^ (Character*);
	
	Value* operator + (Operation*);
	Value* operator - (Operation*);
	Value* operator * (Operation*);
	Value* operator / (Operation*);
	Value* operator ^ (Operation*);
	bool operator == (Operation*);
	
	
	void Change(Value* , OperatorType, Value*);
	
	bool isTerm;
	
	bool Compatable(Value *,OperatorType);
	bool Compatable(Character *,OperatorType);
	bool Compatable(Number *,OperatorType);
	bool Compatable(Operation *,OperatorType);
	
};

Value* Simplify(Value*,bool);
Value* SolveFor(Character*);
Operation* setForVariable(Operation*, char, Value*);