/*
 * Animal.h
 *
 *  Created on: Apr 13, 2020
 *      Author: 1727788_snhu
 */

#ifndef ANIMAL_H_
#define ANIMAL_H_
#include<string>
using namespace std;

class Animal {
public:
	Animal();
	Animal(string, string, string, string);
	virtual void PrintItem() {
		/*cout << "| " << m_TrackNum << */
		cout << "| " << m_TrackNum << "         " << "| " << m_name <<  "| " << m_type <<  "| " << m_SubType  << "| " << endl;
		}
    string GetSubType();
	//virtual ~Animal();
	string m_name;
	string m_TrackNum;
    string m_SubType;
	string m_type;
	void SetAnimalName(string);
	void SetTrackNum(string);
	string GetAnimalName();
	string GetTrackNum();
    void SetSubType(string);
	void SetType(string);
	string GetType();
	string m_NumberOfEggsVoid;
	string m_NursingStatusVoid;
	// methods from sub to override
	virtual string GetNumberOfEggs() {
		return "0";
	}
	virtual string GetNursingStatus(){
		return "0";
	}
	virtual void SetNumberOfEggs() {
		m_NumberOfEggsVoid = "0";
	}
	virtual void SetNursingStatus() {
		m_NursingStatusVoid = "0";
	}

};
// subclass for setting eggs in oviparous animal
class Oviparous : public Animal {
public:
	Oviparous();
	Oviparous(string, string, string, string, string);
	void PrintItem() {
		cout << "| " << m_TrackNum << "         ";
		cout << "| " << m_name;
		cout << "| " << m_type;
		cout << "| " << m_SubType;
		cout << "| " << m_NumberOfEggs << "              ";
		cout  << "| 0             |" << endl;
	}
	//virtual ~Oviparous();
	string m_NumberOfEggs;
	void SetNumberOfEggs(int);
	string GetNumberOfEggs();
};
// subclass for setting nursing status for mammal animal
class Mammal : public Animal {
public:
	Mammal();
	Mammal(string, string, string, string, string);
	void PrintItem() {
		cout << "| " << m_TrackNum << "         ";
		cout << "| " << m_name;
		cout << "| " << m_type;
		cout << "| " << m_SubType;
		cout << "| 0              ";
		cout << "| " << m_NursingStatus << "             |";
		cout << endl;
	}
	//virtual ~Mammal();
	string m_NursingStatus;
	void SetNursingStatus(string);
	string GetNursingStatus();
};

#endif /* ANIMAL_H_ */
