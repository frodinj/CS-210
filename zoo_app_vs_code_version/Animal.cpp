/*
 * Animal.cpp
 *
 *  Created on: Apr 13, 2020
 *      Author: 1727788_snhu
 */

#include "Animal.h"
using namespace std;
#include<string>


// default constructor
Animal::Animal() {
	m_name = "none";
	m_TrackNum = "-1";
	m_type = "none";
	m_SubType = "none";
}
// animal constructor for building derivatives
Animal::Animal(string t_trackNum, string t_name, string t_type, string t_subType) {
	m_name = t_name;
	m_TrackNum = t_trackNum;
	m_type = t_type;
	m_SubType = t_subType;
}
// set and get type and subtype
void Animal::SetType(string t_type) {
	m_type = t_type;
}
string Animal::GetType() {
	return m_type;
}
string Animal::GetSubType() {
    return m_SubType;
}
void Animal::SetSubType(string t_SubType) {
    m_SubType = t_SubType;
}
// destructor but not sure if it is correct
// should only run after data is stored in vector
// designed to free up memory
/*Animal::~Animal() {
	delete Animal::m_TrackNum;
	delete Animal::m_name;
}*/
// setter functions for animal parent class
void Animal::SetAnimalName(string t_name) {
	m_name = t_name;
}
void Animal::SetTrackNum(string t_trackNum) {
	m_TrackNum = t_trackNum;
}

// getter functions for animal parent class
string Animal::GetAnimalName() {
	return m_name;
}
string Animal::GetTrackNum() {
	return m_TrackNum;
}
// default functions for sub classes
Oviparous::Oviparous() {
	m_NumberOfEggs = '0';
}
Oviparous::Oviparous(string t_trackingNum, string t_name, string t_type, string t_subType, string t_NumberOfEggs) {
	m_TrackNum = t_trackingNum;
	m_name = t_name;
	m_type = t_type;
	m_SubType = t_subType;
	m_NumberOfEggs = t_NumberOfEggs;
}
/*Oviparous::~Oviparous() {
	delete Oviparous::m_NumberOfEggs;
}*/
Mammal::Mammal(){
	m_NursingStatus = '0';
}
Mammal::Mammal(string t_trackingNum, string t_name, string t_type, string t_subType, string t_NursingStatus) {
	m_TrackNum = t_trackingNum;
	m_name = t_name;
	m_type = t_type;
	m_SubType = t_subType;
	m_NursingStatus = t_NursingStatus;
}
/*Mammal::~Mammal() {
	delete Mammal::m_NursingStatus;
}*/
// setter functions for sub classes
void Oviparous::SetNumberOfEggs(int t_NumberOfEggs) {
	m_NumberOfEggs = t_NumberOfEggs;
}
void Mammal::SetNursingStatus(string t_NursingStatus) {
	m_NursingStatus = t_NursingStatus;
}

// getter functions for sub classes
string Oviparous::GetNumberOfEggs() {
	return m_NumberOfEggs;
}
string Mammal::GetNursingStatus() {
	return m_NursingStatus;
}
