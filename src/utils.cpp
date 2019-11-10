#include "utils.h"

#include <iomanip>
#include <sstream>
#include <algorithm>
#include <iostream>
#include <cctype>

void utils::ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) { return !std::isspace(ch); }));
}

void utils::rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) { return !std::isspace(ch); }).base(), s.end());
}

void utils::trim(std::string &s) {
    utils::ltrim(s); utils::rtrim(s);
}

void utils::to_lower(std::string &s) {
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) -> unsigned char { return std::tolower(c); });
}

bool utils::confirm(std::string msg, std::istream &is, std::ostream &os) {
    std::string input;
    while (true) {
        if (!utils::input(msg, input, is, os)) return false;
        to_lower(input);
        if (input == "yes" || input == "y" || input == "no" || input == "n") break;
        std::cout << "Error: Only \'yes\'/\'y\' or \'no\'/\'n\' are valid options.\n";
    }
    if (input == "yes" || input == "y") return true;
    os << "Operation cancelled.\n"; return false;
}

std::string utils::itos(const long long int &i){
    std::stringstream ss;
    ss << i;
    return ss.str();
}

std::string utils::ftos(const std::string &fmt, const double &n){
    char buf[127];
    sprintf(buf, fmt.c_str(), n);
    return std::string(buf);
}

int utils::stoi(const std::string &str){
    size_t sz;
    int ret = std::stoi(str, &sz);
    if(sz != str.size())
        throw std::invalid_argument("invalid argument "+str);
    return ret;
}

std::string utils::strrep(const std::string &s, const std::string &fr, const std::string &to){
    std::string ret = s;
    size_t i;
    do{
        i = ret.find(fr);
        if(i != std::string::npos)
            ret = ret.replace(i, fr.size(), to);
    }while(i != std::string::npos);
    return ret;
}

std::string utils::urlencode(const std::string &s){
    std::ostringstream ss;
    ss.fill('0');
    ss << std::hex;
    for(const char &c:s){
        if(isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            ss << c;
        }else{
            ss << std::uppercase << '%'
               << std::setw(2) << int((unsigned char)c)
               << std::nouppercase;
        }
    }
    return ss.str();
}

std::string utils::urldecode(const std::string &s){
    std::string ret;
    size_t i = 0;
    while(i < s.size()){
        if(s[i] == '%'){
            if(i+2 >= s.size()) throw std::invalid_argument("invalid argument "+s);
            std::stringstream ss;
            ss << std::hex << s.substr(i+1,2);
            int a; ss >> a;
            ret += char(a);
            i += 3;
        }else{
            ret += s[i++];
        }
    }
    return ret;
}

std::string utils::ljust(std::string s, size_t sz){
    if(sz < 3) throw std::invalid_argument("size less than 3");
    if(s.size() < sz) s = s + std::string(sz-s.size(), ' ');
    if(s.size() > sz) s = s.substr(0,sz-3) + "...";
    return s;
}

std::string utils::rjust(std::string s, size_t sz){
    if(sz < 3) throw std::invalid_argument("size less than 3");
    if(s.size() < sz) s = std::string(sz-s.size(), ' ') + s;
    if(s.size() > sz)s = s.substr(0,sz-3) + "...";
    return s;
}

std::vector<std::string> utils::parse_command(const std::string &s){
    std::vector<std::string> ret;
    std::string t = "";
    char quote = ' ';
    for(const char &c:s){
        if(c == '\"' || c == '\''){
            if     (quote == ' ') quote =  c;
            else if(quote ==  c ) quote = ' ';
            else                  t    += c;
        }else if(c == ' '){
            if(t != "") ret.push_back(t);
            t = "";
        }else t += c;
    }
    if(t != "") ret.push_back(t);
    return ret;
}

///STRING_REGEX
utils::string_regex& utils::string_regex::operator=(const std::string &s){
    if(!std::regex_match(s, std::regex(REGEX_STR_)))
        throw FailedRegex(s, REGEX_STR_);
    s_ = s;
    return *this;
}
utils::string_regex::operator std::string() const{
    return s_;
}
bool utils::string_regex::operator<(const utils::string_regex &s) const{
    return ((std::string)*this < (std::string)s);
}
bool utils::string_regex::operator==(const utils::string_regex &s) const{
    return ((std::string)*this == (std::string)s);
}
namespace utils{
    std::istream& operator>>(std::istream &is,       utils::string_regex &s){
        std::string ss; is >> ss;
        s = utils::urldecode(ss);
        return is;
    }
    std::ostream& operator<<(std::ostream &os, const utils::string_regex &s){
        return (os << utils::urlencode(s.s_));
    }
}
utils::string_regex::FailedRegex::FailedRegex(const std::string &s, const std::string &REGEX_STR):
    std::invalid_argument("Invalid string ("+s+") does not match regex ("+REGEX_STR+")"),
    s_(s){}

///OBJECT INPUT
template<> bool utils::input<std::string>(const std::string &msg, std::string &object, std::istream &is, std::ostream &os) {
    std::string input;

    while (true) {
        os << msg; std::getline(is, input); utils::trim(input);
        if (utils::isCancel(input)) {
            os << "Operation cancelled.\n"; return false;
        }
        try {
            object = input;
            return true;
        } catch (const std::ios_base::failure &ios_fail) {
            std::cerr << "ERROR: Input failed.\n";
        } catch (const std::exception &ex) {
            std::cerr << "ERROR: " << ex.what() << "\n";
        }
    }
}

///INVALID ITERATOR
utils::InvalidIterator::InvalidIterator():
    std::invalid_argument("Invalid iterator (iterator is out of the range)") {}
