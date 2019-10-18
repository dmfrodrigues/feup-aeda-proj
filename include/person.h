#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include "address.h"
#include "vat.h"
#include "phonenumber.h"

class Person{
private:
    std::string name_;
    Address address_;
    VAT vat_;
    PhoneNumber phonenumber_;
public:
    Person(const std::string &name, const Address &address, const VAT &vat, const PhoneNumber &phonenumber);
};

#endif //PERSON_H_INCLUDED