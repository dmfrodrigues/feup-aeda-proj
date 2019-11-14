#include "truck.h"

#include "utils.h"

///NUMBERPLATE NUMBER
const std::string Truck::NumberPlate::Number::REGEX_STR = "^[A-Z0-9 -|.]{4,12}*$";
Truck::NumberPlate::Number::Number():utils::string_regex(Truck::NumberPlate::Number::REGEX_STR){}
Truck::NumberPlate::Number::Number(const std::string &plate):Number(){
    *this = plate;
}
Truck::NumberPlate::Number& Truck::NumberPlate::Number::operator=(const std::string &s){
    string_regex::operator=(s);
    return *this;
}

///NUMBERPLATE
Truck::NumberPlate::NumberPlate(){}
Truck::NumberPlate::NumberPlate(const Number &number):number_(number){}
Truck::NumberPlate::operator std::string() const{ return (std::string)number_; }
bool Truck::NumberPlate::operator< (const NumberPlate &n) const{ return ((std::string)*this <  (std::string)n); }
bool Truck::NumberPlate::operator==(const NumberPlate &n) const{ return ((std::string)*this == (std::string)n); }
std::istream& operator>>(std::istream &is,       Truck::NumberPlate &n){
    is >> n.number_;
    return is;
}
std::ostream& operator<<(std::ostream &os, const Truck::NumberPlate &n){
    os << n.number_;
    return os;
}

///CATEGORY
const std::string Truck::Category::REGEX_STR = "^[A-Z+-]{1,4}$";
Truck::Category::Category():utils::string_regex(Truck::Category::REGEX_STR){}
Truck::Category::Category(const std::string &category):Category(){
    *this = category;
}
Truck::Category& Truck::Category::operator=(const std::string &category){
    string_regex::operator=(category);
    return *this;
}

///FUEL
std::string Truck::fuel_string(const Truck::Fuel &f){
    switch(f){
        case Fuel::Gasoline : return "Gasoline" ;
        case Fuel::Diesel   : return "Diesel"   ;
        case Fuel::Biodiesel: return "Biodiesel";
        case Fuel::Gas      : return "Gas"      ;
        case Fuel::Hydrogen : return "Hydrogen" ;
        case Fuel::Electric : return "Electric" ;
        case Fuel::Hybrid   : return "Hybrid"   ;
        default: throw std::invalid_argument("invalid argument");
    }
}

///TRUCK
Truck::Truck(){}
Truck::~Truck() {
    delete cargo_;
}

const Truck::NumberPlate& Truck::get_numberplate      () const{ return number_plate_       ; }
const Truck::NumberPlate& Truck::get_id               () const{ return get_numberplate()   ; }
const Time&               Truck::get_plateregisterdate() const{ return plate_register_date_; }
const Truck::Fuel&        Truck::get_fuel             () const{ return fuel_               ; }
const Distance&           Truck::get_range            () const{ return max_reach_          ; }
const Truck::Category&    Truck::get_category         () const{ return category_           ; }
const CargoTrans*         Truck::get_cargo            () const{ return cargo_              ; }
Truck::Type               Truck::get_type             () const{ return Truck::Type::truck  ; }

Truck::Fuel Truck::processFuel(const std::string &s) {
    if (s == "gasoline") return Truck::Fuel::Gasoline;
    if (s == "diesel") return Truck::Fuel::Diesel;
    if (s == "biodiesel") return Truck::Fuel::Diesel;
    if (s == "gas") return Truck::Fuel::Diesel;
    if (s == "hydrogen") return Truck::Fuel::Diesel;
    if (s == "electric") return Truck::Fuel::Diesel;
    if (s == "hybrid") return Truck::Fuel::Diesel;
    throw std::invalid_argument("Invalid fuel type.");
}

Truck* Truck::deep_copy(const Truck *truck) {
    Truck *copy = new Truck();

    copy->number_plate_         = truck->number_plate_;
    copy->plate_register_date_  = truck->plate_register_date_;
    copy->fuel_                 = truck->fuel_;
    copy->max_reach_            = truck->max_reach_;
    copy->category_             = truck->category_;

    CargoTrans *cargo = truck->cargo_;
    CargoTrans *cargo_copy;
    Cargo::Type cargo_type = cargo->get_type();
    switch(cargo_type) {
        case Cargo::Type::Normal:
            cargo_copy = new CargoTrans();
            *dynamic_cast<CargoTrans*>(cargo_copy) = *dynamic_cast<CargoTrans*>(cargo);
            break;
        case Cargo::Type::Animal:
            cargo_copy = new CargoTransAnimal();
            *dynamic_cast<CargoTransAnimal*>(cargo_copy) = *dynamic_cast<CargoTransAnimal*>(cargo);
            break;
        case Cargo::Type::Refrigerated:
            cargo_copy = new CargoTransRefrigerated();
            *dynamic_cast<CargoTransRefrigerated*>(cargo_copy) = *dynamic_cast<CargoTransRefrigerated*>(cargo);
            break;
        case Cargo::Type::Dangerous:
            cargo_copy = new CargoTransDangerous();
            *dynamic_cast<CargoTransDangerous*>(cargo_copy) = *dynamic_cast<CargoTransDangerous*>(cargo);
            break;
        default:
            delete copy;
            return NULL;
    }
    if (cargo_copy != NULL)     copy->cargo_ = cargo_copy;
    else { delete copy; return NULL; }
    return copy;
}

std::istream& operator>>(std::istream &is,       Truck &t){
    is >> t.number_plate_;
    is >> t.plate_register_date_;
    int i; is >> i; t.fuel_ = static_cast<Truck::Fuel>(i);
    is >> t.max_reach_;
    is >> t.category_;
    t.cargo_ = NULL;
    input_CargoTrans(is, t.cargo_);
    return is;
}
std::ostream& operator<<(std::ostream &os, const Truck &t){
    os << t.number_plate_         << "\n"
       << t.plate_register_date_  << "\n"
       << (int)t.fuel_            << "\n"
       << t.max_reach_            << "\n"
       << t.category_             << "\n";
    output_CargoTrans(os, t.cargo_);
    return os;
}

bool Truck::in(std::istream &is, std::ostream &os) {
    if (!utils::input("Number Plate: ", [](Truck::NumberPlate &np, const std::string &s) { np = Truck::NumberPlate(Truck::NumberPlate::Number(s)); }, number_plate_, is, os)|
        !utils::input("Plate Register Date: ", [](Time &tm, const std::string &s) { tm = Time(s); },  plate_register_date_, is, os)|
        !utils::input("Fuel: ", [](Truck::Fuel &fuel, const std::string &s) { fuel = Truck::processFuel(s); }, fuel_, is, os)|
        !utils::input("Maximum reach: ", max_reach_, is, os)|
        !utils::input("Category: ",[](Truck::Category &cat, const std::string &s) { cat = Truck::Category(s); }, category_, is, os)) return false;

    std::string type;
    while (true) {
        if (!utils::input("Types available: Normal, Animal, Refrigerated, Dangerous.\nCargo Type: ", type, is, os)) return false;

        utils::to_lower(type);
        if (type == "normal") {
            CargoTrans *cargo = new CargoTrans();
            if (!cargo->in(is, os)) { delete cargo; return false; }
            cargo_ = cargo;
            break;
        } else if (type == "animal") {
            CargoTransAnimal *cargo = new CargoTransAnimal();
            if (!cargo->in(is, os)) { delete cargo; return false; }
            cargo_ = cargo;
            break;
        } else if (type == "refrigerated") {
            CargoTransRefrigerated *cargo = new CargoTransRefrigerated();
            if (!cargo->in(is, os)) { delete cargo; return false; }
            cargo_ = cargo;
            break;
        } else if (type == "dangerous") {
            CargoTransDangerous *cargo = new CargoTransDangerous();
            if (!cargo->in(is, os)) { delete cargo; return false; }
            cargo_ = cargo;
            break;
        } else {
            std::cout << "Error: Invalid cargo type.\n";
            continue;
        }
    }
    return true;
}
bool Truck::edit(std::string command, std::istream &is, std::ostream &os) {/*
    std::vector<std::string> cmd = utils::parse_command(command);
    if (cmd.size() == 1) {
        try {
            int property = utils::stoi(cmd.at(0));
            switch (property) {
            case 0:
                if(!utils::input("Number Plate: ", [](Truck::NumberPlate &np, const std::string &s) {
                                                        np = Truck::NumberPlate(Truck::NumberPlate::Number(s)); },
                                                    number_plate_, is, os))                                                                         return false;
                else                                                                                                                                return true;
            break;
            case 1:
                if (!utils::input("Plate Register Date: ", [](Time &tm, const std::string &s) { tm = Time(s); },  plate_register_date_, is, os))    return false;
                else                                                                                                                                return true;
            break;
            case 2:
                if (!utils::input("Fuel: ", [](Truck::Fuel &fuel, const std::string &s) { fuel = Truck::processFuel(s); }, fuel_, is, os))          return false;
                else                                                                                                                                return true;
            break;
            case 3:
                if (!utils::input("Maximum reach: ", max_reach_, is, os))                                                                           return false;
                else                                                                                                                                return true;
            break;
            case 4:
                if (!utils::input("Category :", [](Truck::Category &cat, const std::string &s) { cat = Truck::Category(s); }, category_, is, os))   return false;
                else                                                                                                                                return true;
            break;
            default:
                std::cout << "Error: invalid command\n";
                return false;
                break;
            }
        } catch (std::invalid_argument &ia) {
            std::cout << "Error: invalid command\n";
            return false;
        }
    } else if (cmd.size() == 3) {
        if (cmd.at(0) == "add" && cmd.at(1) == "cargo") {
            std::string type = cmd.at(2);
            utils::to_lower(type);
            if (type == "normal") {
                CargoTrans *cargo = new CargoTrans();
                if (!cargo->in(std::cin, std::cout)) { delete cargo; return false; }
                cargo_.push_back(cargo);
                return true;
            } else if (type == "animal") {
                CargoTrans *cargo = new CargoTransAnimal();
                if (!cargo->in(std::cin, std::cout)) { delete cargo; return false; }
                cargo_.push_back(cargo);
                return true;
            } else if (type == "refrigerated") {
                CargoTrans *cargo = new CargoTransRefrigerated();
                if (!cargo->in(std::cin, std::cout)) { delete cargo; return false; }
                cargo_.push_back(cargo);
                return true;
            } else if (type == "dangerous") {
                CargoTrans *cargo = new CargoTransDangerous();
                if (!cargo->in(std::cin, std::cout)) { delete cargo; return false; }
                cargo_.push_back(cargo);
                std::cout << "Cargo added.\n";
                return true;
            } else {
                std::cout << "Error: Invalid cargo type.\n";
                return false;
            }
        } else if (cmd.at(0) == "delete" && cmd.at(1) == "cargo") {
            try {
                std::size_t order_number = (std::size_t)utils::stoi(cmd.at(2));
                if (!utils::confirm("Confirm the deletion of cargo (yes/no): ", std::cin, std::cout)) return false;
                delete cargo_.at(order_number);
                cargo_.erase(cargo_.begin() + (long)order_number);
                return true;
            } catch (std::invalid_argument &ia) {
                std::cout << "Error: invalid command\n";
                return false;
            }
        } else {
            std::cout << "Error: invalid command\n";
            return false;
        }
    } else if (cmd.size() == 4) {
        if (cmd.at(0) == "edit" && cmd.at(1) == "cargo") {
            try {
                std::size_t order_number = (std::size_t)utils::stoi(cmd.at(2));
                int property = utils::stoi(cmd.at(3));
                printf("%d\n", (order_number >= cargo_.size()));
                if (order_number >= cargo_.size()) {
                    std::cout << "Error: Cargo doesn't exist.\n";
                    return false;
                }
                CargoTrans *cargo_copy;
                Cargo::Type cargo_type = cargo_.at(order_number)->get_type();
                switch(cargo_type) {
                case Cargo::Type::Normal:
                    cargo_copy = new CargoTrans();
                    *dynamic_cast<CargoTrans*>(cargo_copy) = *dynamic_cast<CargoTrans*>(cargo_.at(order_number));
                    break;
                case Cargo::Type::Animal:
                    cargo_copy = new CargoTransAnimal();
                    *dynamic_cast<CargoTransAnimal*>(cargo_copy) = *dynamic_cast<CargoTransAnimal*>(cargo_.at(order_number));
                    break;
                case Cargo::Type::Refrigerated:
                    cargo_copy = new CargoTransRefrigerated();
                    *dynamic_cast<CargoTransRefrigerated*>(cargo_copy) = *dynamic_cast<CargoTransRefrigerated*>(cargo_.at(order_number));
                    break;
                case Cargo::Type::Dangerous:
                    cargo_copy = new CargoTransDangerous();
                    *dynamic_cast<CargoTransDangerous*>(cargo_copy) = *dynamic_cast<CargoTransDangerous*>(cargo_.at(order_number));
                    break;
                default:
                    std::cout << "Invalid cargo type.\n";
                    return false;
                }
                cargo_copy->edit(property, is, os);
                if (!utils::confirm("Confirm the edition of cargo (yes/no): ", std::cin, std::cout)) { delete cargo_copy; return false; }
                *cargo_.at(order_number) = *cargo_copy;
                delete cargo_copy;
                return true;
            } catch (std::invalid_argument &ia) {
                std::cout << "Error: invalid command\n";
                return false;
            }
        }
    }*/
    return true;
}
