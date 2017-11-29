#include "lib_tritset.h"

namespace trits {

	TritSet::TritSet(){
		this->tritsTrueFalse[0] = this->tritsTrueFalse[1] = 0;
		this->lastTrit = -1;
		this->size = 0;
		this->array = new uint[0]();
	};
	
	TritSet::TritSet(int size){
		this->tritsTrueFalse[0] = this->tritsTrueFalse[1] = 0;
		this->lastTrit = -1;
		this->size = 0;
		this->array = new uint[0]();
		this->resize(size); 
	};
	
	TritSet::TritSet(const TritSet& other){
		this->tritsTrueFalse[0] = other.tritsTrueFalse[0];
		this->tritsTrueFalse[1] = other.tritsTrueFalse[1];
		this->lastTrit = other.lastTrit;
		this->size = 0;
		this->array = new uint[0]();
		this->resize(other.size);
		int i;
		for(i = 0; i < minSize(this->size); i++)
			this->array[i] = other.array[i];
	};

	TritSet::~TritSet(){};

	TritSet& TritSet::operator= (const TritSet& other){
		if(this == &other) 
			return *this;
		this->tritsTrueFalse[0] = other.tritsTrueFalse[0];
		this->tritsTrueFalse[1] = other.tritsTrueFalse[1];
		this->lastTrit = other.lastTrit;
		this->resize(other.size);
		int i;
		for(i = 0; i < minSize(this->size); i++)
			this->array[i] = other.array[i];
		return *this;
	};
	
	TritSet::TritHolder TritSet::operator[] (int index) {
		return TritHolder(*this, index); 
	};
	
	TritSet::Trit TritSet::operator[] (int index) const {
		Trit buf;
		this->get(index, &buf);
		return buf;
	};
	
	TritSet TritSet::operator& (TritSet other) {
		return this->operation(other, 0);
	};

	TritSet TritSet::operator| (TritSet other) {
		return this->operation(other, 1);
	};
	
	TritSet TritSet::operator! () {
		return this->operation(*this, 2);
	};		

	size_t TritSet::capacity(){
		return minSize(this->size) * sizeof(uint); 
	};
	
	void TritSet::shrink(){
		this->resize(this->lastTrit);
	};
	
	size_t TritSet::cardinality(Trit element){
		switch(element){
			case Trit::TRUE:
				return this->tritsTrueFalse[0];
			case Trit::FALSE:
				return this->tritsTrueFalse[1];
			default:
				return this->lastTrit + 1 - this->tritsTrueFalse[0] - this->tritsTrueFalse[1];
		}
	};
	
	TritSet::TritMap TritSet::cardinality(){
		TritMap map({
			{Trit::TRUE, this->cardinality(Trit::TRUE)},
			{Trit::FALSE, this->cardinality(Trit::FALSE)},
			{Trit::UNKNOWN, this->cardinality(Trit::UNKNOWN)}
		});
		return map;
	};
	
	size_t TritSet::length(){
		return this->lastTrit + 1;
	};
	
	void TritSet::trim(int index){
		int i;
		for(i = this->lastTrit; i >= index; i--){
			if(this->operator[](i) == Trit::TRUE)
				this->tritsTrueFalse[0]--;
			if(this->operator[](i) == Trit::FALSE)
				this->tritsTrueFalse[1]--;
		};
		this->resize(index);
		for(i = index - 1; i >= 0 && this->operator[](i) == Trit::UNKNOWN; i--);
		this->lastTrit = i;
	};
	
	TritSet::TritIterator TritSet::begin(){
		return TritIterator(*this, 0);
	};
	
	TritSet::TritIterator TritSet::end(){
		return TritIterator(*this, this->length());
	};

	TritSet TritSet::operation(TritSet &t2, int typeOperation){
		TritSet &t1 = *this;
		int size_max = t1.size > t2.size ? t1.size : t2.size;
		TritSet tres(size_max);
		int i;
		for(i = 0; i < size_max; i++)
			tres[i] = operationTrit(t1[i], t2[i], typeOperation);
		return tres;
	};
	
	TritSet::Trit TritSet::operationTrit(Trit t1, Trit t2, int typeOperation){
		switch(typeOperation){
			case 0:
				if(t1 == Trit::FALSE || t2 == Trit::FALSE)
					return Trit::FALSE;
				if(t1 == Trit::TRUE && t2 == Trit::TRUE)
					return Trit::TRUE;
				break;
			case 1:
				if(t1 == Trit::TRUE || t2 == Trit::TRUE)
					return Trit::TRUE;
				if(t1 == Trit::FALSE && t2 == Trit::FALSE)
					return Trit::FALSE;
				break;
			case 2:
				if(t1 == Trit::TRUE)
					return Trit::FALSE;
				if(t1 == Trit::FALSE)
					return Trit::TRUE;
				break;
		}
		return Trit::UNKNOWN;
	};
				
	int TritSet::minSize(int size){
		size += TUint - 1;
		return size / TUint;
	};
	
	void TritSet::resize(int size){
		int size_old = minSize(this->size);
		int size_new = minSize(size);
		uint *buf = this->array;
		this->array = new uint[size_new]();
		int i;
		for(i = 0; i < size_new; i++){
			if(i < size_old)
				this->array[i] = buf[i];
			else
				this->array[i] = 0;
		}
		delete[] buf;
		this->size = size;
	};
	
	TritSet::Trit TritSet::uint2Trit(uint val) const { 
		switch(val){
			case 0: return Trit::UNKNOWN;
			case 1: return Trit::TRUE;
			case 2: return Trit::FALSE;
			default: return Trit::UNKNOWN;
		}
	};
	
	TritSet::uint TritSet::Trit2uint(Trit val){ 
		switch(val){
			case Trit::UNKNOWN: return 0;
			case Trit::TRUE: return 1;
			case Trit::FALSE: return 2;
			default: return 3;
		}
	};
	
	void TritSet::get(int index, Trit* element) const {
		*element = Trit::UNKNOWN;
		if(index < 0 || index >= this->size) 
			return;
		uint val = this->array[index / TUint];
		val >>= sizeof(uint) * 8 - 2 * (index % TUint);
		val = val % 4; 
		*element = uint2Trit(val);
	};
	
	void TritSet::set(int index, Trit element){
		if(index < 0)
			throw std::runtime_error("Out of range");
		if(index >= this->size){
			if(element == Trit::UNKNOWN)
				return;
			this->resize(index + 1);
		}
		Trit old;
		this->get(index, &old);
		uint val = this->array[index / TUint];
		val -= Trit2uint(old) << (sizeof(uint) * 8 - 2 * (index % TUint));
		val += Trit2uint(element)  << (sizeof(uint) * 8 - 2 * (index % TUint));
		this->array[index / TUint] = val;
		this->mathTrueFalse(old, element, index);
	};
	
	void TritSet::mathTrueFalse(Trit one, Trit two, int index){
		switch(one){
			case Trit::FALSE:
				this->tritsTrueFalse[1]--;
				break;
			case Trit::TRUE:
				this->tritsTrueFalse[0]--;
				break;
			default:
				break;
		}
		switch(two){
			case Trit::FALSE:
				this->tritsTrueFalse[1]++;
				break;
			case Trit::TRUE:
				this->tritsTrueFalse[0]++;
				break;
			default:
				break;
		}
		if(one == Trit::UNKNOWN && two != Trit::UNKNOWN && index > this->lastTrit) 
			this->lastTrit = index;
		if(one != Trit::UNKNOWN && two == Trit::UNKNOWN && index == this->lastTrit){ 
			int i;
			for(
				i = this->lastTrit;
				i >= 0 && this->operator[](i) == Trit::UNKNOWN;
				i--
			);
			this->lastTrit = i;
		}
	};

	void TritSet::saveToStream(std::ostream &stream){

		stream << magic_constant 
			   << '|' 
			   << this->size 
			   << '|';

		stream.write(reinterpret_cast<char*>(this->array), this->minSize(this->size) * sizeof(uint));	   
	}

	TritSet& TritSet::loadFromStream(std::istream &stream){

		std::string s;
		getline(stream, s, '|');

		if (magic_constant != s)
			throw std::runtime_error("Bad start, bro");

		getline(stream, s, '|');

		int size;
		try {size = stoi(s);}	

		catch(std::invalid_argument){
			std::runtime_error("Bad, bro");
		}

		*this = TritSet(size);

		stream.get(reinterpret_cast<char*>(this->array),this->minSize(this->size) * sizeof(uint));
		
		return *this;
	}

	TritSet::TritHolder::TritHolder(TritSet& ts, int index) : ts(ts), index(index) {};

	TritSet::TritHolder::~TritHolder(){};

	TritSet::TritHolder& TritSet::TritHolder::operator= (TritSet::Trit value){
		this->ts.set(index, value);
		return *this;
	};

	TritSet::TritHolder& TritSet::TritHolder::operator= (TritSet::TritHolder& value){
		this->ts.set(index, value); 
		return *this;
	};
	
	TritSet::TritHolder::operator TritSet::Trit() const {
		TritSet::Trit ret = TritSet::Trit::UNKNOWN;
		this->ts.get(index, &ret); 
		return ret;
	};

	TritSet::Trit TritSet::TritHolder::operator& (TritSet::Trit other){

		return this->ts.operationTrit(*this, other, 0);
	}

	TritSet::Trit TritSet::TritHolder::operator| (TritSet::Trit other){

		return this->ts.operationTrit(*this, other, 1);
	}

	TritSet::Trit TritSet::TritHolder::operator~ (){

		return this->ts.operationTrit(*this, *this, 2);
	}

	TritSet::TritIterator::TritIterator(TritSet& ts, int index) : ts(ts), index(index) {};

	TritSet::TritIterator::~TritIterator(){};

	TritSet::TritHolder TritSet::TritIterator::operator*(){
		return this->ts[this->index];
	};
	
	TritSet::TritIterator& TritSet::TritIterator::operator++(){
		this->index++;
		return *this;
	};
	
	TritSet::TritIterator TritSet::TritIterator::operator++(int){
		TritSet::TritIterator another = *this;
		this->index++;
		return another;
	};
	
	bool TritSet::TritIterator::operator==(TritSet::TritIterator other){
		return this->index == other.index;
	};
	
	bool TritSet::TritIterator::operator!=(TritSet::TritIterator other){
		return this->index != other.index;	
	};

	TritSet::TritCIterator::TritCIterator(TritSet& ts, int index) : ts(ts), index(index) {};

	TritSet::TritCIterator::~TritCIterator(){};

	TritSet::Trit TritSet::TritCIterator::operator*() const{
		return this->ts[this->index];
	};
	
	TritSet::TritCIterator& TritSet::TritCIterator::operator++(){
		this->index++;
		return *this;
	};
	
	TritSet::TritCIterator TritSet::TritCIterator::operator++(int){

		TritSet::TritCIterator another = *this;
		this->index++;
		return another;
	};
	
	bool TritSet::TritCIterator::operator==(TritSet::TritCIterator other){
		return this->index == other.index;
	};
	
	bool TritSet::TritCIterator::operator!=(TritSet::TritCIterator other){
		return this->index != other.index;	
	};

	TritSet::TritHash::TritHash(){};

	TritSet::TritHash::~TritHash(){};
	
	TritSet::uint TritSet::TritHash::operator()(const TritSet::Trit& element) const{
		switch(element){
			case TritSet::Trit::TRUE:
				return 1;
			case TritSet::Trit::FALSE:
				return 2;
			default:
				return 0;
		};
	};
};