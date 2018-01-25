#include "lib_tritset.hpp"
#include <fstream>

using namespace trits;

#define ASSERT_EQ(a,b) (a)==(b)

bool empty(TritSet tritset){

	bool result = true;

	result &= ASSERT_EQ(tritset.capacity(), 0);
	tritset[100] = Unknown;
	result &= ASSERT_EQ(tritset[0], Unknown);
	result &= ASSERT_EQ(tritset[100], Unknown);

	return result;
}

bool shrink(TritSet tritset){

	size_t size = tritset.capacity();
	tritset[55555] = True;
	tritset[55555] = Unknown;
	tritset.shrink();
	return ASSERT_EQ(tritset.capacity(), size);
}

bool memory(TritSet tritset, size_t UNINTx4){

	bool result = true;

	result &= ASSERT_EQ(tritset.length(), 0);
	tritset[1] = True;
	result &= ASSERT_EQ(tritset.capacity(), UNINTx4 / 4);
	tritset[UNINTx4] = tritset[1];
	result &= ASSERT_EQ(tritset.capacity(), 2 * UNINTx4 / 4);

	return result;
}

bool values(TritSet tritset, size_t UNINTx4){

	bool result = true;

	tritset[1] = True;
	tritset[2] = False;
	tritset[UNINTx4] = tritset[1];	

	tritset[5 * UNINTx4 + 1] = False;
	tritset[3 * UNINTx4 + 2] = True;
	result &= ASSERT_EQ(tritset[55555], Unknown);
	result &= ASSERT_EQ(tritset[5], Unknown);
	result &= ASSERT_EQ(tritset.capacity(), 6 * UNINTx4 / 4);
	result &= ASSERT_EQ(tritset[0], Unknown);
	result &= ASSERT_EQ(tritset[1], True); 
	result &= ASSERT_EQ(tritset[2], False); 
	result &= ASSERT_EQ(tritset[3 * UNINTx4 + 2], True);
	result &= ASSERT_EQ(tritset[5 * UNINTx4 + 1], False);
	result &= ASSERT_EQ(tritset[UNINTx4], True); 

	return result;
}

bool cardinality(TritSet tritset, size_t UNINTx4){

	bool result = true;

	tritset[1] = True;
	tritset[2] = False;
	tritset[UNINTx4] = tritset[1];	
	tritset[5 * UNINTx4 + 1] = False;
	tritset[3 * UNINTx4 + 2] = True;

	result &= ASSERT_EQ(tritset.cardinality(True), 3); 
	result &= ASSERT_EQ(tritset.cardinality(False), 2); 
	result &= ASSERT_EQ(tritset.cardinality(Unknown), tritset.length() - tritset.cardinality(True) - tritset.cardinality(False));
	result &= ASSERT_EQ(tritset.cardinality(True), 3); 
	result &= ASSERT_EQ(tritset.cardinality(False), 2); 

	return result;
}

bool length(TritSet tritset, size_t UNINTx4){

	bool result = true;
	
	tritset[5 * UNINTx4 + 1] = False;

	result &= ASSERT_EQ(tritset.length(), 5 * UNINTx4 + 2);
	size_t size = tritset.length();
	tritset[100] = True;
	tritset[100] = Unknown;
	result &= ASSERT_EQ(tritset.length(), size);

	return result;
}

bool copy(TritSet tritset){

	bool result = true;

	tritset[1] = True;
	tritset[2] = False;

	result &= ASSERT_EQ(tritset[0], Unknown);
	result &= ASSERT_EQ(tritset[1], True); 
	result &= ASSERT_EQ(tritset[2], False); 
	TritSet tritset1 = tritset;
	result &= ASSERT_EQ(tritset1[0], Unknown);
	result &= ASSERT_EQ(tritset1[1], True); 
	result &= ASSERT_EQ(tritset1[2], False); 

	return result;
}

bool accept(TritSet tritset){

	bool result = true;

	tritset[1] = True;
	tritset[2] = False;

	TritSet tritset1(4);
	tritset1 = tritset;
	result &= ASSERT_EQ(tritset1[0], Unknown);
	result &= ASSERT_EQ(tritset1[1], True); 
	result &= ASSERT_EQ(tritset1[2], False);

	return result;
}

bool operation_not(TritSet tritset){

	bool result = true;

	tritset[1] = True;
	tritset[2] = False;

	TritSet tritset1 = tritset;
	tritset1 = !tritset1;
	result &= ASSERT_EQ(tritset1[0], Unknown);
	result &= ASSERT_EQ(tritset1[1], False); 
	result &= ASSERT_EQ(tritset1[2], True); 

	return result;
}

bool operation_or(TritSet tritset){

	bool result = true;

	tritset[1] = True;
	tritset[2] = False;

	TritSet tritset1 = tritset;
	tritset1 = !tritset1;
	tritset1[2] = False;
	TritSet tritset2 = tritset | tritset1;
	result &= ASSERT_EQ(tritset2[0], Unknown);
	result &= ASSERT_EQ(tritset2[1], True); 
	result &= ASSERT_EQ(tritset2[2], False); 

	return result;
}

bool operation_and(TritSet tritset){

	bool result = true;

	tritset[1] = True;
	tritset[2] = False;

	TritSet tritset1 = tritset;
	tritset1 = !tritset1;
	tritset1[2] = False;
	TritSet tritset2 = tritset & !tritset1;
	result &= ASSERT_EQ(tritset2[0], Unknown);
	result &= ASSERT_EQ(tritset2[1], True); 
	result &= ASSERT_EQ(tritset2[2], False); 

	return result;
}

bool capacity_logic(TritSet tritset){

	tritset[2] = False;

	TritSet tritset1 = tritset;
	tritset1 = !tritset1;
	tritset1[2] = False;
	TritSet tritset2 = tritset & !tritset1;

	return ASSERT_EQ(tritset.capacity(), tritset2.capacity()); 
}

bool map(TritSet tritset){

	bool result = true;

	TritSet::TritMap map = tritset.cardinality();
	result &= ASSERT_EQ(map[True], tritset.cardinality(True));
	result &= ASSERT_EQ(map[False], tritset.cardinality(False));
	result &= ASSERT_EQ(map[Unknown], tritset.cardinality(Unknown));
	size_t size = tritset.cardinality(True);
	tritset[1000] = True;
	result &= ASSERT_EQ(tritset.cardinality(True), size + 1);
	tritset[1000] = Unknown;
	result &= ASSERT_EQ(tritset.cardinality(True), size);	

	return result;
}

bool trim(TritSet tritset, size_t UNINTx4){

	bool result = true;

	tritset[1] = True;
	tritset[2] = False;
	tritset[UNINTx4] = tritset[1];	
	tritset[5 * UNINTx4 + 1] = False;
	tritset[3 * UNINTx4 + 2] = True;

	size_t size = tritset.length();
	tritset[1000] = Unknown;
	tritset[size + 10] = True;
	tritset[size + 15] = False;
	tritset.trim(size + 12);
	result &= ASSERT_EQ(tritset[size + 10], True);
	result &= ASSERT_EQ(tritset[size + 15], Unknown);
	result &= ASSERT_EQ(tritset.length(), size + 10 + 1);
	TritSet::TritMap map = tritset.cardinality();

	result &= ASSERT_EQ(map[True], 4); 
	result &= ASSERT_EQ(map[False], 2); 

	return result;
}

bool iterator(){

	bool result = true;

	TritSet tritset;
	TritSet::Trit trit[] = {True, False, Unknown, False, True};

	unsigned int i;
	for(i = 0; i < sizeof(trit) / sizeof(unsigned int); i++)
		tritset[i] = trit[i];

	i = 0;
	for(auto&& it : tritset){
		result &= ASSERT_EQ(it, trit[i]);
		it = Unknown;
		i++;
	}

	result &= ASSERT_EQ(tritset.length(), 0);

	return result;
}

bool unitar(){

	TritSet tritset;
	tritset[5] = True;
	tritset[6] = False;
	tritset[7] = tritset[6] | (tritset[5] & ~tritset[6]);
	return ASSERT_EQ(tritset[7], True);
}

bool stream(){

	bool result = true;

	TritSet tritset;

	tritset[5] = True;
	tritset[6] = False;
	tritset[7] = tritset[6] | (tritset[5] & ~tritset[6]);

	std::ofstream of("test");
	tritset.saveToStream(of);
	of.close();
		
	result &= ASSERT_EQ(tritset[5], True);
	result &= ASSERT_EQ(tritset[6], False);
	result &= ASSERT_EQ(tritset[7], True);
		
	TritSet tritset1;
		
	std::ifstream iff("test");
	tritset1.loadFromStream(iff);
	iff.close();
		
	result &= ASSERT_EQ(tritset1[5], True);
	result &= ASSERT_EQ(tritset1[6], False);
	result &= ASSERT_EQ(tritset1[7], True);

	return result;
}

int main()
{
	TritSet tritset;
	size_t UNINTx4 = sizeof(unsigned int) * 4;

	if(empty(tritset)) std::cout << "Correct empty\n";
	if(shrink(tritset)) std::cout << "Correct shrink\n";
	if(memory(tritset, UNINTx4)) std::cout << "Correct memory\n";
	if(values(tritset, UNINTx4)) std::cout << "Correct values\n";
	if(cardinality(tritset,UNINTx4)) std::cout << "Correct cardinality\n";
	if(length(tritset, UNINTx4)) std::cout << "Correct length\n";
	if(copy(tritset)) std::cout << "Correct copy\n";
	if(accept(tritset)) std::cout << "Correct accept\n";
	if(operation_not(tritset)) std::cout << "Correct operation_not\n";
	if(operation_or(tritset)) std::cout << "Correct operation_or\n";
	if(operation_and(tritset)) std::cout << "Correct operation_and\n";
	if(capacity_logic(tritset)) std::cout << "Correct capacity_logic\n";
	if(map(tritset)) std::cout << "Correct map\n";
	if(trim(tritset, UNINTx4)) std::cout << "Correct trim\n";
	if(iterator()) std::cout << "Correct iterator\n";
	if(unitar()) std::cout << "Correct unitar\n";
	if(stream()) std::cout << "Correct stream\n";

	return 0;
}