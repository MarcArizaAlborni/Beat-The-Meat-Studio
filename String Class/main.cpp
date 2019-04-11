#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
using namespace std;

class String {
private:
	int l = 0;
	char* buffer = nullptr;
public:
	// Contructors and destructors
	String() {
		buffer = nullptr;
		l = 0;
	}
	String(const char* str) {
		
		buffer = new char[strlen(str) +1];
		strcpy(buffer, str);
		l = strlen(buffer);
	}
	String(const String &str) {
		buffer = new char[str.size() +1];
		strcpy(buffer, str.rStr());
		l = strlen(str.rStr());
	}
	~String() {
		delete[] buffer;
	}
	// Methods
	const char* rStr() const {
		return buffer;
	}
	bool empty() const{
		return (l == 0);
	}
	int size()const {
		return l;
	}
	void clear() {
		delete[] buffer;
		l = 0;
	}
	// Operators
	void operator= (const String &str) {
		delete[] buffer; //just in case it was pointing to something already
		buffer = new char[strlen(str.rStr()) + 1];
		strcpy(buffer, str.rStr());
		l = strlen(buffer);
	}
	void operator+= (const String &str) {
		char* array = new char[l + str.l +1];
		strcpy(array, buffer);
		strcat(array, str.rStr());
		delete[] buffer;
		buffer = array;
		l = strlen(buffer);
	}
	bool operator==(const String &str)const {
		return (strcmp(buffer, str.rStr()) == 0);
	}
	bool operator!=(const String &str)const {
		return (strcmp(buffer, str.rStr()) != 0);
	}
};


int main() {

	String str1;
	String str2;
	str1 = "Operator= test";
	cout << str1.rStr() << endl;
	str2 = "concatenations";
	str1 = "Hellow world of ";
	str1 += str2; //If you use "hola", it will temporarily create a String class which will use it's contructor and destructor.
	cout << str1.rStr() << endl << "Size test: "<< str1.size() << endl;
	str1.clear();
	if (str1.empty()) {
		cout << "String is empty" << endl;
	}
	else {
		cout << "String is not empty" << endl;
	}




	system("pause");
	return 0;
}