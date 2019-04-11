#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
using namespace std;

class String {
private:
	int value = 0;
	char* string2 = nullptr;
public:
	// Contructors and destructors
	String() {
		string2 = nullptr;
		value = 0;
	}
	String(const char* str) {
		
		string2 = new char[strlen(str) +1];
		strcpy(string2, str);
		value = strlen(string2);
	}
	String(const String &str) {
		string2 = new char[str.size() +1];
		strcpy(string2, str.rStr());
		value = strlen(str.rStr());
	}
	~String() {
		delete[] string2;
	}
	// Methods
	const char* rStr() const {
		return string2;
	}
	bool empty() const{
		return (value == 0);
	}
	int size()const {
		return value;
	}
	void clear() {
		delete[] string2;
		value = 0;
	}
	// Operators
	void operator= (const String &str) {
		delete[] string2; //just in case it was pointing to something already
		string2 = new char[strlen(str.rStr()) + 1];
		strcpy(string2, str.rStr());
		value = strlen(string2);
	}
	void operator+= (const String &str) {
		char* array = new char[value + str.value +1];
		strcpy(array,string2);
		strcat(array, str.rStr());
		delete[] string2;
		string2 = array;
		value = strlen(string2);
	}
	bool operator==(const String &str)const {
		return (strcmp(string2, str.rStr()) == 0);
	}
	bool operator!=(const String &str)const {
		return (strcmp(string2, str.rStr()) != 0);
	}
};


int main() {

	String str1;
	String str2;
	str1 = "Operator= test";
	cout << str1.rStr() << endl;
	str2 = "Totoro: The Battle";
	str1 = "PacoPepe VS ";
	str1 += str2; //If you use "hola", it will temporarily create a String class which will use it's contructor and destructor.
	cout << str1.rStr() << endl << "String Size: "<< str1.size() << endl;
	str1.clear();
	if (str1.empty()) {
		cout << "String is empty" << endl;
	}
	else {
		cout << "FULL STRING" << endl;
	}




	system("pause");
	return 0;
}