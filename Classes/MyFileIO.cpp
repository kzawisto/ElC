/*
 * MyFileIO.cpp
 *
 *  Created on: Oct 23, 2015
 *      Author: krystian892
 */

#include <MyFileIO.h>



istream & operator>>(istream & input, Person & person){
    input>>person.age;
    input>>person.height;
    return input;
}
ostream & operator<<(ostream & input, const Person & person){
    input<<person.age<<" "<<person.height;
    return input;
}
