#include "address.h"

#include "utils.h"

Address::Address(){}
Address::Address(const std::string &street, const std::string &postal_code, const std::string &city, const std::string &district, const std::string &country):
                 street_(street), postal_code_(postal_code), city_(city), district_(district), country_(country){}

std::string Address::format(const std::string &s) const{
    std::string ret = s;
    ret = utils::strrep(ret, "%street", street_);
    ret = utils::strrep(ret, "%postal", postal_code_);
    ret = utils::strrep(ret, "%city", city_);
    ret = utils::strrep(ret, "%district", district_);
    ret = utils::strrep(ret, "%country", country_);
    return ret;
}

std::ostream& operator<<(std::ostream &os, const Address &a){
    return os << a.format();
}

std::istream& operator>>(std::istream &is, Address &a){
    std::getline(is, a.street_);
    std::getline(is, a.postal_code_);
    std::getline(is, a.city_);
    std::getline(is, a.district_);
    std::getline(is, a.country_);
    return is;
}

const std::string Address::DEFAULT_FORMAT = "%street\n%postal\n%city\n%district\n%country";
