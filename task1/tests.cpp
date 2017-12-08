#include <iostream>
#include <fstream>
#include "lib_tritset.hpp"

#define ASSERT_EQ(a,b) testObj.assert((a) == (b), #a)
#define LOCATE(a) testObj.locate(#a)

namespace trits {
	class startTest {
		private:
			int all, right;
			char *str;
			char *loc;
		public:
			startTest() : all(0), right(0), str(0), loc(0) {};
			void assert(bool rez, const char* str){
				this->all++;
				if(rez){
					this->right++;
				} else {
					if(this->str == 0){
						this->str = (char*)str;
					}
				}
			}
			void result(std::ostream& str){
				if(this->all == this->right){
					str << "[All tests passed]";
				} else {
					str << "[Error at '" << this->str << "' test in '" << this->loc << "' locate]";
				}
			}
			void locate(const char* str){
				if(this->str == 0)
					this->loc = (char*)str;
				std::cout << "\n[Testing locate '" << str << "'...]\n";
			}
	};
	
	void runMyTests(){
		using trits::TritSet;
		TritSet test;
		startTest testObj;
		
		#define True TritSet::Trit::TRUE
		#define False TritSet::Trit::FALSE
		#define Unknown TritSet::Trit::UNKNOWN
		
		size_t tritPerUint = sizeof(unsigned int) * 4;
		
		// Test empty
		LOCATE(empty);
		test[100] = Unknown;
		ASSERT_EQ(test[0], Unknown);
		ASSERT_EQ(test[100], Unknown);
		ASSERT_EQ(test.capacity(), 0);
		
		// Test memory
		LOCATE(memory);
		ASSERT_EQ(test.length(), 0);
		test[1] = True;
		test[2] = False;
		ASSERT_EQ(test.capacity(), tritPerUint / 4);
		test[tritPerUint] = test[1];
		ASSERT_EQ(test.capacity(), 2 * tritPerUint / 4);
		
		// Test values
		LOCATE(values);
		test[5 * tritPerUint + 1] = False;
		test[3 * tritPerUint + 2] = True;
		ASSERT_EQ(test[0], Unknown);
		ASSERT_EQ(test[1], True);
		ASSERT_EQ(test[2], False);
		ASSERT_EQ(test[3 * tritPerUint + 2], True);
		ASSERT_EQ(test[5 * tritPerUint + 1], False);
		ASSERT_EQ(test[tritPerUint], True);
		ASSERT_EQ(test[1000000], Unknown);
		ASSERT_EQ(test[5], Unknown);
		ASSERT_EQ(test.capacity(), 6 * tritPerUint / 4);
		
		// Test shrink()
		LOCATE(shrink);
		size_t size = test.capacity();
		test[1000000] = True;
		test[1000000] = Unknown;
		test.shrink();
		ASSERT_EQ(test.capacity(), size);
		
		// Test length()
		LOCATE(length);
		ASSERT_EQ(test.length(), 5 * tritPerUint + 2);
		size = test.length();
		test[100] = True;
		test[100] = Unknown;
		ASSERT_EQ(test.length(), size);
		
		// Test copy constructor
		LOCATE(copy);
		ASSERT_EQ(test[0], Unknown);
		ASSERT_EQ(test[1], True);
		ASSERT_EQ(test[2], False);
		TritSet test2 = test;
		ASSERT_EQ(test2[0], Unknown);
		ASSERT_EQ(test2[1], True);
		ASSERT_EQ(test2[2], False);
		
		// Test accept
		LOCATE(accept);
		TritSet test1(4);
		test1 = test2;
		ASSERT_EQ(test2[0], Unknown);
		ASSERT_EQ(test2[1], True);
		ASSERT_EQ(test2[2], False);
		
		// Test NOT
		LOCATE(not);
		test2 = !test2;
		ASSERT_EQ(test2[0], Unknown);
		ASSERT_EQ(test2[1], False);
		ASSERT_EQ(test2[2], True);
		
		// Test OR
		LOCATE(or);
		test2[2] = False;
		TritSet test3 = test | test2;
		// U T F
		// U F F
		// U T F
		ASSERT_EQ(test3[0], Unknown);
		ASSERT_EQ(test3[1], True);
		ASSERT_EQ(test3[2], False);
		
		// Test AND
		LOCATE(and);
		test3 = test & !test2;
		// U T F
		// U T T
		// U T F
		ASSERT_EQ(test3[0], Unknown);
		ASSERT_EQ(test3[1], True);
		ASSERT_EQ(test3[2], False);
		
		// Test size afte logic
		LOCATE(capacity_logic);
		ASSERT_EQ(test.capacity(), test3.capacity());
		
		// Test cardinality
		LOCATE(cardinality);
		ASSERT_EQ(test.cardinality(True), 3);
		ASSERT_EQ(test.cardinality(False), 2);
		ASSERT_EQ(test.cardinality(Unknown), test.length() - test.cardinality(True) - test.cardinality(False));
		ASSERT_EQ(test.cardinality(True), 3);
		ASSERT_EQ(test.cardinality(False), 2);
		
		// Test map
		LOCATE(map);
		test.shrink();
		TritSet::TritMap map = test.cardinality();
		ASSERT_EQ(map[True], test.cardinality(True));
		ASSERT_EQ(map[False], test.cardinality(False));
		ASSERT_EQ(map[Unknown], test.cardinality(Unknown));
		size = test.cardinality(True);
		test[1000] = True;
		ASSERT_EQ(test.cardinality(True), size + 1);
		test[1000] = Unknown;
		ASSERT_EQ(test.cardinality(True), size);
		
		// Test trim
		LOCATE(trim);
		size = test.length();
		test[size + 10] = True;
		test[size + 15] = False;
		test.trim(size + 12);
		ASSERT_EQ(test[size + 10], True);
		ASSERT_EQ(test[size + 15], Unknown);
		ASSERT_EQ(test.length(), size + 10 + 1);
		map = test.cardinality();
		ASSERT_EQ(map[True], 4);
		ASSERT_EQ(map[False], 2);
		test.shrink();
		
		// Test iterator
		LOCATE(iterator);
		TritSet test4;
		TritSet::Trit for_test_iterator[] = {True, False, Unknown, False, True};
		unsigned int i;
		for(i = 0; i < sizeof(for_test_iterator) / sizeof(unsigned int); i++)
			test4[i] = for_test_iterator[i];
		i = 0;
		for(auto&& iter : test4){
			ASSERT_EQ(iter, for_test_iterator[i]);
			iter = Unknown;
			i++;
		}
		ASSERT_EQ(test4.length(), 0);
		
		// Test unitar
		LOCATE(unitar);
		TritSet newnew;
		newnew[5] = True;
		newnew[6] = False;
		newnew[7] = newnew[6] | (newnew[5] & ~newnew[6]);
		ASSERT_EQ(newnew[7], True);
		
		// Stream
		LOCATE(stream);
		
		std::ofstream of("test.txt");
		newnew.saveToStream(of);
		of.close();
		
		ASSERT_EQ(newnew[5], True);
		ASSERT_EQ(newnew[6], False);
		ASSERT_EQ(newnew[7], True);
		
		TritSet newnew2;
		
		std::ifstream iff("test.txt");
		newnew2.loadFromStream(iff);
		iff.close();
		
		ASSERT_EQ(newnew2[5], True);
		ASSERT_EQ(newnew2[6], False);
		ASSERT_EQ(newnew2[7], True);
				
		testObj.result(std::cout);
	}
}

using namespace trits;

	int main()
	{
		runMyTests();
		return 0;
	}