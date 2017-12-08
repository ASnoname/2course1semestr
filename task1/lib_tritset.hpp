#ifndef TRITSET
#define TRITSET

#include <vector>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <string>

namespace trits {
	
	class TritSet {
		public:

			class TritHolder; 
			class TritIterator;
			class TritCIterator; 
			class TritHash; 
			enum class Trit { 
				TRUE = 1,
				FALSE = -1,
				UNKNOWN = 0
			};
			typedef unsigned int uint;
			typedef std::unordered_map<Trit, size_t, TritHash> TritMap;
			
			TritSet();
			TritSet(int);
			TritSet(const TritSet& other);

			~TritSet();			
			
			TritSet& operator= (const TritSet&);
			TritHolder operator[] (int);
			Trit operator[] (int) const;
			TritSet operator& (TritSet);
			TritSet operator| (TritSet);
			TritSet operator! ();
			
			size_t capacity();
			void shrink();
			size_t cardinality(Trit);
			TritMap cardinality();
			void trim(int);
			size_t length();

			TritSet& loadFromStream(std::istream&);
			void saveToStream(std::ostream&);

			TritIterator begin();
			TritIterator end();
			
			TritCIterator cbegin();
			TritCIterator cend();

		private:

			friend class TritHolder;

			static const int TUint = sizeof(uint) * 8 / 2;
			const std::string magic_constant = "BEGIN";

			uint *array; 
			int size; 
			int lastTrit;
			int tritsTrueFalse[2];
			
			void mathTrueFalse(Trit, Trit, int);
			TritSet operation(TritSet&, int);
			Trit operationTrit(Trit, Trit, int);
			int minSize(int); 
			void resize(int); 
			uint Trit2uint(Trit);
			Trit uint2Trit(uint) const; 
			void get(int, Trit*) const; 
			void set(int, Trit); 
	};
	
	class TritSet::TritHolder {
		public:
			TritHolder(TritSet&, int);
			~TritHolder(); 
			TritHolder& operator= (TritSet::Trit); 
			TritHolder& operator= (TritHolder&); 
			operator TritSet::Trit() const; 
			TritSet::Trit operator& (TritSet::Trit);
			TritSet::Trit operator| (TritSet::Trit);
			TritSet::Trit operator~ ();
		private:
			TritSet& ts; 
			int index; 
	};
	
	class TritSet::TritIterator {
		public:
			TritIterator(TritSet&, int); 
			~TritIterator();
			TritSet::TritHolder operator*();
			TritIterator& operator++();
			TritIterator operator++(int);
			bool operator==(TritIterator);
			bool operator!=(TritIterator);
		private:
			TritSet& ts; 
			int index; 
	};
	
	class TritSet::TritCIterator {
		public:
			TritCIterator(TritSet&, int); 
			~TritCIterator();
			TritSet::Trit operator*() const;
			TritCIterator& operator++();
			TritCIterator operator++(int);
			bool operator==(TritCIterator);
			bool operator!=(TritCIterator);
		private:
			TritSet& ts; 
			int index; 
	};
	
	class TritSet::TritHash {
		public:
			TritHash();
			~TritHash();
			TritSet::uint operator()(const TritSet::Trit&) const;
	};
};

#endif 