#include "app.h"

#include <algorithm>

template<class Base, class Deriv, class ID>
size_t App::load_ptr(std::ifstream &is, std::vector<Base*> &m_in){
    is.exceptions(std::ifstream::eofbit | std::ifstream::badbit | std::ifstream::failbit);
    size_t N; is >> N;
    for(size_t i = 0; i < N; ++i){
        Base *m = new Deriv(); is >> *dynamic_cast<Deriv*>(m);
        if(utils::find_if(m_in.begin(), m_in.end(),
          [&m](const Base* p){ return (p->get_id() == m->get_id()); }) != m_in.end()){
            auto id = m->get_id();
            delete m;
            throw App::RepeatedId((std::string)id);
        }
        m_in.push_back(m);
    }
    return N;
}

template<class Base, class Deriv>
size_t App::save_ptr(std::ofstream &os, const std::vector<Base*> &m_out){
    os.exceptions(std::ifstream::eofbit | std::ifstream::badbit | std::ifstream::failbit);
    os << m_out.size() << "\n";
    for(const Base* p:m_out){
        os << "\n" << *dynamic_cast<const Deriv*>(p) << "\n";
    }
    os << std::flush;
    return m_out.size();
}

bool App::load_all(){
    for(const User *p:users_) delete p;
    users_ = std::vector<User*>();
    {
        std::cout << "Loading managers..." << std::flush;
        std::ifstream is(managers_path_);
        size_t sz = load_ptr<User,Manager,User::Username>(is, users_ );
        std::cout << " loaded " << sz << std::endl;
    }
    {
        std::cout << "Loading drivers ..." << std::flush;
        std::ifstream is(drivers_path_ );
        size_t sz = load_ptr<User,Driver ,User::Username>(is, users_ );
        std::cout << " loaded " << sz << std::endl;
    }
    {
        std::cout << "Loading clients ..." << std::flush;
        std::ifstream is(clients_path_ );
        size_t sz = load_ptr<User,Client ,User::Username>(is, users_ );
        std::cout << " loaded " << sz << std::endl;
    }
    {
        std::cout << "Loading trucks  ..." << std::flush;
        std::ifstream is(trucks_path_  );
        size_t sz = load_ptr<Truck,Truck ,Truck::NumberPlate>(is, trucks_);
        std::cout << " loaded " << sz << std::endl;
    }
    {
        std::cout << "Loading services..." << std::flush;
        std::ifstream is(services_path_);
        is >> Service::next_id_;
        size_t sz = load_ptr<Service,Service,std::string>(is, services_);
        std::cout << " loaded " << sz << std::endl;
        {
            std::vector<const User*> v(users_.begin(), users_.end());
            std::vector<const Driver*> w = App::filter<User,Driver,User::Type>(v, User::Type::driver);
            std::vector<std::pair<std::pair<Time,Time>, Service::ID> > tmp;
            for(const Driver *p:w) if(!get_schedule(p, tmp)) return false;
        }
        {
            std::vector<std::pair<std::pair<Time,Time>, Service::ID> > tmp;
            for(const Truck *p:trucks_) if(!get_schedule(p, tmp)) return false;
        }
    }
    return true;
}

void App::save_all(){
    {
        std::cout << "Saving managers...";
        std::ofstream os(managers_path_);
        size_t sz = save_ptr<User,Manager>(os, filter_user_by_type(users_, User::Type::manager));
        std::cout << " saved " << sz << std::endl;
    }
    {
        std::cout << "Saving drivers ...";
        std::ofstream os(drivers_path_ );
        size_t sz = save_ptr<User,Driver >(os, filter_user_by_type(users_, User::Type::driver ));
        std::cout << " saved " << sz << std::endl;
    }
    {
        std::cout << "Saving clients ...";
        std::ofstream os(clients_path_ );
        size_t sz = save_ptr<User,Client >(os, filter_user_by_type(users_, User::Type::client ));
        std::cout << " saved " << sz << std::endl;
    }
    {
        std::cout << "Saving trucks  ...";
        std::ofstream os(trucks_path_  );
        size_t sz = save_ptr<Truck,Truck >(os, trucks_);
        std::cout << " saved " << sz << std::endl;
    }
    {
        std::cout << "Saving services...";
        std::ofstream os(services_path_);
        os << Service::next_id_ << "\n";
        size_t sz = save_ptr<Service,Service>(os, services_);
        std::cout << " saved " << sz << std::endl;
    }
}


bool App::addUser(const User::Type &user_type) {
    CLEAR();
    std::cout << "Adding user.\n";
    User *user;
    if (user_type == User::Type::client) {
        user = new Client();
        if (!user->in(std::cin, std::cout)) { delete user; return false;}
    } else if (user_type == User::Type::driver) {
        user = new Driver();
        if (!user->in(std::cin, std::cout)) { delete user; return false;}
    } else if (user_type == User::Type::manager) {
        user = new Manager();
        if (!user->in(std::cin, std::cout)) { delete user; return false;}
    } else {
        error("Invalid user type.");
        return false;
    }

    if(utils::find_if(users_.begin(), users_.end(),
      [user](const User* u){ return (u->get_username() == user->get_username()); }) != users_.end()){
        delete user;
        error("Repeated username (username already exists).");
        return false;
    }
    users_.push_back(user);
    std::cout << "User added.\n";
    return true;
}

bool App::addTruck() {
    CLEAR();
    std::cout << "Adding truck.\n";
    Truck *truck = new Truck();
    if (!truck->in(std::cin, std::cout)) { delete truck; return false; }
    if(utils::find_if(trucks_.begin(), trucks_.end(),
      [truck](const Truck* t){ return (t->get_id() == truck->get_id()); }) != trucks_.end()){
        delete truck;
        error("Repeated ID (number plate already exists).");
        return false;
    }
    trucks_.push_back(truck);
    std::cout << "Truck added.\n";
    return true;
}

Truck* App::chooseTruck() {
    std::cout << "Choosing truck.\n";
    std::vector<const Truck*> trucks(trucks_.begin(), trucks_.end());
    while (true) {
        print_list(trucks);
        std::string id;
        if (!utils::input("Choose truck (number plate): ", id, std::cin, std::cout)) return NULL;
        try {
            Truck::NumberPlate number_plate = Truck::NumberPlate(Truck::NumberPlate::Number(id));

            Truck *it = find_truck(number_plate);
            if (it == NULL) {
                error("Truck doesn't exist (number plate doesn't have matches).");
                continue;
            } else {
                return it;
            }
        } catch (utils::string_regex::FailedRegex &fr) {
            error(std::string(fr.what()) + std::string(" (invalid number plate)."));
            continue;
        }
    }
    return NULL;
}

bool App::deleteTruck() {
    CLEAR();
    std::cout << "Deleting truck.\n";
    while (true) {
        Truck *truck = App::chooseTruck();
        if (truck == NULL) return false;
        std::vector<Truck*>::iterator truck_it = std::find(trucks_.begin(), trucks_.end(), truck);
        if (!utils::confirm("Confirm the deletion of truck \'" + (std::string)((*truck_it)->get_numberplate()) + "\' (yes/no): ", std::cin, std::cout)) return false;
        delete *truck_it;
        trucks_.erase(truck_it);
        std::cout << "Truck deleted.\n";
        return true;
    }
    return false;
}

bool App::editTruck() {
    CLEAR();
    std::cout << "Editing truck.\n";
    Truck *truck = App::chooseTruck();
    if (truck == NULL) return false;
    std::vector<Truck*>::iterator it = std::find(trucks_.begin(), trucks_.end(), truck);
    if (it == trucks_.end()) return false;
    bool is_edited = false;
    truck = *it;
    std::string command;
    Truck *truck_copy = Truck::deep_copy(truck);
    while (true) {
        App::display(truck_copy);
        if (!utils::input("To add/change cargo use command:\n"
                          "     add cargo [type]\n"
                          "     edit cargo [order_number] [property]\n"
                          "     delete cargo [order_number]\n"
                          "Types available: Normal, Animal, Refrigerated, Dangerous.\n"
                          "Choose property to change (type cancel to finish): ", command, std::cin, std::cout)) break;
        if (command == "0") { error("Property that can't be changed."); continue; }
        if (truck_copy->edit(command, std::cin, std::cout)) is_edited = true;
    }
    if (is_edited) {
        if (!utils::confirm("Confirm the edition of truck \'" + (std::string)(truck_copy->get_numberplate()) + "\' (yes/no): ", std::cin, std::cout)) { delete truck_copy; return false; }
        *it = truck_copy;
        std::cout << "Truck edited.\n";
    }
    delete truck;
    return true;
}

Service* App::chooseService() {
    std::cout << "Choosing service.\n";
    std::vector<const Service*> services(services_.begin(), services_.end());
    while (true) {
        print_list(services);
        std::string id;
        if (!utils::input("Choose service id: ", id, std::cin, std::cout)) return NULL;
        Service *it = find_service(id);
        if (it == NULL) {
            error("Service doesn't exist (id doesn't have matches).");
            continue;
        } else {
            return it;
        }
    }
    return NULL;
}


Service* App::chooseService(const User *user) {
    std::cout << "Choosing service.\n";
    std::vector<Service*> filtered = filter_services_by_user(services_, user);
    std::vector<const Service*> services(filtered.begin(), filtered.end());

    while (true) {
        print_list(services);
        std::string id;
        if (!utils::input("Choose service id: ", id, std::cin, std::cout)) return NULL;
        Service *it = find_service(id);
        if (it == NULL || std::find(filtered.begin(), filtered.end(), it) == filtered.end()) {
            error("Service doesn't exist (id doesn't have matches).");
            continue;
        } else {
            return it;
        }
    }
    return NULL;
}

bool App::deleteService(const User *user) {
    CLEAR();
    std::cout << "Deleting service.\n";
    while (true) {
        Service *service = App::chooseService(user);
        if (service == NULL) return false;
        std::vector<Service*>::iterator service_it = std::find(services_.begin(), services_.end(), service);
        if (!utils::confirm("Confirm the deletion of service \'" + ((*service_it)->get_id()) + "\' (yes/no): ", std::cin, std::cout)) return false;
        delete *service_it;
        services_.erase(service_it);
        std::cout << "Service deleted.\n";
        return true;
    }
    return false;
}


bool App::deleteService() {
    CLEAR();
    std::cout << "Deleting service.\n";
    while (true) {
        Service *service = App::chooseService();
        if (service == NULL) return false;
        std::vector<Service*>::iterator service_it = std::find(services_.begin(), services_.end(), service);
        if (!utils::confirm("Confirm the deletion of service \'" + ((*service_it)->get_id()) + "\' (yes/no): ", std::cin, std::cout)) return false;
        delete *service_it;
        services_.erase(service_it);
        std::cout << "Service deleted.\n";
        return true;
    }
    return false;
}

bool App::addService() {
    CLEAR();
    std::cout << "Adding service.\n";
    Client *client = dynamic_cast<Client*>(chooseUser<Client>(User::Type::client));
    if (client == NULL) return false;
    Service *service = new Service(client->get_username());
    if (service == NULL) return false;
    if (!service->in(std::cin, std::cout)) { delete service; return false; }
    if(utils::find_if(services_.begin(), services_.end(),
      [service](const Service* s){ return (s->get_id() == service->get_id()); }) != services_.end()){
        delete service;
        error("Repeated ID (service with same ID already exists).");
        Service::next_id_--; //infelizmente
        return false;
    }
    std::vector<Truck*> tv = get_available_trucks(service->get_tbegin(), service->get_tend(), service->get_cargo());
    std::vector<Driver*> dv = get_available_drivers(service->get_tbegin(), service->get_tend());
    if(service->allocate(std::vector<const Truck*>(tv.begin(), tv.end()), std::vector<const Driver*>(dv.begin(), dv.end()))){
        services_.push_back(service);
        std::cout << "Service added.\n";
        return true;
    }else{
        std::cout << "Failed to add service.\n";
        return false;
    }
}

bool App::addService(const User *user) {
    CLEAR();
    std::cout << "Adding service.\n";
    Service *service = new Service(dynamic_cast<const Client*>(user)->get_username());
    if (service == NULL) return false;
    if (!service->in(std::cin, std::cout)) { delete service; return false; }
    if(utils::find_if(services_.begin(), services_.end(),
      [service](const Service* s){ return (s->get_id() == service->get_id()); }) != services_.end()){
        delete service;
        error("Repeated ID (service with same ID already exists).");
        Service::next_id_--; //infelizmente
        return false;
    }
    std::vector<Truck*> tv = get_available_trucks(service->get_tbegin(), service->get_tend(), service->get_cargo());
    std::vector<Driver*> dv = get_available_drivers(service->get_tbegin(), service->get_tend());
    if(service->allocate(std::vector<const Truck*>(tv.begin(), tv.end()), std::vector<const Driver*>(dv.begin(), dv.end()))){
        services_.push_back(service);
        std::cout << "Service added.\n";
        return true;
    }else{
        std::cout << "Failed to add service.\n";
        return false;
    }
}
