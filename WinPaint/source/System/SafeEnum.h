#pragma once


///////////////////////////////////////////////////////////////////////////////
// Safe enum implementation

template<typename Def, typename StorageType = typename Def::type>
class SafeEnum : public Def
{
	StorageType val;

public:
	typedef typename Def::type type;

	SafeEnum() {}
	SafeEnum(type v) : val((StorageType)v) {}
	explicit SafeEnum(int v) : val((StorageType)v) {}
	StorageType value() const { return val; }

	const char* name() const { return Def::name((type)val); }

	bool operator==(const SafeEnum & s) const { return this->val == s.val; }
	bool operator!=(const SafeEnum & s) const { return this->val != s.val; }
	bool operator< (const SafeEnum & s) const { return this->val < s.val; }
	bool operator<=(const SafeEnum & s) const { return this->val <= s.val; }
	bool operator> (const SafeEnum & s) const { return this->val > s.val; }
	bool operator>=(const SafeEnum & s) const { return this->val >= s.val; }
};

///////////////////////////////////////////////////////////////////////////////
// Helpers to convert enums to string 
// Add a name function in your struct definition

#define ENUM_START(t) switch(t) {
#define ENUM_CASE(type) case type: return #type; 
#define ENUM_END() } return "";
