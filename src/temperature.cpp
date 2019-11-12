#include "temperature.h"

#include "utils.h"

Temperature::Temperature():Temperature(20.0){}
Temperature::Temperature(float temp){
    if(temp < -273.15 || 100.00 < temp)
        throw InvalidTemperature(temp);
    temp_ = temp;
}
Temperature Temperature::operator+(const Temperature &t) const{ return Temperature(temp_+t.temp_); }
Temperature Temperature::operator-(const Temperature &t) const{ return Temperature(temp_-t.temp_); }
bool Temperature::operator< (const Temperature &t)const{ return (temp_ < t.temp_); }
bool Temperature::operator> (const Temperature &t)const{ return (t < *this); }
bool Temperature::operator==(const Temperature &t)const{ return !(*this < t || t < *this); }
bool Temperature::operator>=(const Temperature &t)const{ return !(*this < t); }
bool Temperature::operator<=(const Temperature &t)const{ return !(*this > t); }

std::istream& operator>>(std::istream &is,       Temperature &t){
    float f;
    is >> f;
    try{ t = Temperature(f); }catch(...){ is.setstate(std::ios::failbit); }
    return is;
}
std::ostream& operator<<(std::ostream &os, const Temperature &t){ return (os << t.temp_); }

Temperature::InvalidTemperature::InvalidTemperature(const float &temp):
    std::invalid_argument("invalid temperature "+utils::ftos("+%.2f", temp)),
    temp_(temp){}
const float& Temperature::InvalidTemperature::get_temperature() const{ return temp_; }

TemperatureRange::TemperatureRange(const Temperature &tmin, const Temperature &tmax){
    if(tmin > tmax)
        throw TemperatureRange::InvalidTemperatureRange(tmin, tmax);
    range_ = std::pair<Temperature,Temperature>(tmin, tmax);
}


std::istream& operator>>(std::istream &is,       TemperatureRange &r){ return (is >> r.range_.first        >> r.range_.second); }
std::ostream& operator<<(std::ostream &os, const TemperatureRange &r){ return (os << r.range_.first << " " << r.range_.second); }

TemperatureRange::InvalidTemperatureRange::InvalidTemperatureRange(const Temperature &tmin, const Temperature &tmax):
    std::invalid_argument("Invalid temperature range"),
    range_(tmin, tmax){}
const std::pair<Temperature,Temperature>& TemperatureRange::InvalidTemperatureRange::get_temperature_range() const{ return range_; }
