/**
 * @file app.h
 */

#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED

#include "person.h"
#include "truck.h"
#include "service.h"

#include <fstream>

#if defined(_WIN32)
    #define CLEAR_MACRO() system("cls"  )
#elif defined(unix) || defined(__unix__) || defined(__unix)
    #define CLEAR_MACRO() system("clear")
#endif

/**
 * @brief Clears the screen.
 *
 * Designed to work at least in Windows32/64 and Unix.
 */
void CLEAR();

/** @brief Main class of the application. */
class App{
public:
    static const float rate;
private:
    ///PRIVATE VARIABLES
    // Command string
    static const std::string OPSTR;
    //Paths
    const std::string base_path_    ;
    const std::string managers_path_;
    const std::string drivers_path_ ;
    const std::string clients_path_ ;
    const std::string trucks_path_  ;
    const std::string services_path_;
    //Vectors
    std::vector<User*> users_ ;
    std::vector<Truck*> trucks_  ;
    std::vector<Service*> services_;
    ///PRIVATE FUNCTIONS
    ///File IO
    template<class Base, class Deriv, class ID> static size_t load_ptr(std::ifstream &is,       std::vector<Base*> &m_in );
    template<class Base, class Deriv          > static size_t save_ptr(std::ofstream &os, const std::vector<Base*> &m_out);
    bool load_all();
    void save_all();
    ///Display
    static void print_list(const std::vector<const Manager*> &v);
    static void print_list(const std::vector<const Driver *> &v);
    static void print_list(const std::vector<const Client *> &v);
    static void print_list(const std::vector<const Truck  *> &v);
           void print_list(const std::vector<const Service*> &v) const;
    static void display(const Client                 *p);
    static void display(const Driver                 *p);
    static void display(const Manager                *p);
    static void display(const Truck                  *p);
    static void display(const Cargo                  *p);
    static void display(const CargoAnimal            *p);
    static void display(const CargoRefrigerated      *p);
    static void display(const CargoDangerous         *p);
    static void display(const CargoTrans             *p);
    static void display(const CargoTransAnimal       *p);
    static void display(const CargoTransRefrigerated *p);
    static void display(const CargoTransDangerous    *p);
           void display(const Service                *p) const;
    ///Lists
    template<class Base, class Deriv, class Type> static std::vector<const Deriv*> filter(const std::vector<const Base*> &v, const Type &t);
    static void list_clients_commands();
    static void list_drivers_commands();
    static void list_managers_commands();
    template<class T> static bool extra_commands(const std::vector<std::string> &s, std::vector<const T*> &v);
    template<class T> static void list_commands();
    static void list_sort_getcomp(int i, std::function<bool(const Client *, const Client *)> &cmp);
    static void list_sort_getcomp(int i, std::function<bool(const Driver *, const Driver *)> &cmp);
    static void list_sort_getcomp(int i, std::function<bool(const Manager*, const Manager*)> &cmp);
    static void list_sort_getcomp(int i, std::function<bool(const Truck  *, const Truck  *)> &cmp);
    static void list_sort_getcomp(int i, std::function<bool(const Service*, const Service*)> &cmp);
    static void list_filter_getvalid(int i, const std::string &str, std::function<bool(const Client *)> &cmp);
    static void list_filter_getvalid(int i, const std::string &str, std::function<bool(const Driver *)> &cmp);
    static void list_filter_getvalid(int i, const std::string &str, std::function<bool(const Manager*)> &cmp);
    static void list_filter_getvalid(int i, const std::string &str, std::function<bool(const Truck  *)> &cmp);
    static void list_filter_getvalid(int i, const std::string &str, std::function<bool(const Service*)> &cmp);
    template<class T> void list(std::vector<const T*> v) const;
    ///Commands
    static std::string prompt();
    static void wait();
    /**
     * @brief Confirms user input via a yes/no validation.
     * @param msg Message to display before asking for input
     * @return True if input is 'yes', false if inputs a 'no'
     */
    static bool confirm(const std::string &msg);
    static void error(const std::string &s);
    ///Operations
    void list_clients () const;
    void list_drivers () const;
    void list_managers() const;
    void list_trucks  () const;
    void list_services() const;
    void list_services(const User *user) const;
    bool addUser(const User::Type &user_type);
    template<class Deriv> bool deleteUser(const User::Type &type);
    template<class Deriv> User* chooseUser(const User::Type &type);
    template<class Deriv> bool editUser(const User::Type &type); // manager function
    template<class Deriv> bool editUser(User *user); // edit own account

    bool addTruck();
    Truck* chooseTruck();
    bool deleteTruck();
    bool editTruck();
    bool change_truck_cargo(CargoTrans *&cargo, const Cargo::Type &type);
    bool edit_truck_cargo(CargoTrans *&cargo, int property);

    bool addService();
    bool addService(const User *user);
    Service* chooseService();
    Service* chooseService(const User *user);
    bool deleteService();
    bool deleteService(const User *user);

    std::vector<User*> filter_user_by_type(const std::vector<User*> &v, const User::Type &t) const;
    std::vector<Service*> filter_services_by_user(const std::vector<Service*> &v, const User *user) const;
    User* find_user(const User::Username &u) const;
    Truck* find_truck(const Truck::NumberPlate &np) const;
    Service* find_service(const Service::ID &id) const;
    User* verifyUser(const std::string &username, const std::string &password);

    //Functions
    bool get_schedule(const Driver *p, std::vector<std::pair<std::pair<Time,Time>, Service::ID> > &ret) const;
    bool get_schedule(const Truck  *p, std::vector<std::pair<std::pair<Time,Time>, Service::ID> > &ret) const;
    std::vector<Driver*> get_available_drivers(const Time &tbegin, const Time &tend) const;
    std::vector<Truck *> get_available_trucks (const Time &tbegin, const Time &tend, const Cargo *c) const;

    // Menus
    bool guestMenu(User* &user);
    bool printUserMenu(User::Type user_type);
    bool userMenu(User *user, User::Type user_type);
public:
    App(const std::string &base    ,
        const std::string &managers, const std::string &drivers ,
        const std::string &clients ,
        const std::string &trucks  , const std::string &services);

    ~App();

    void start();

    /** @brief Exception class to report invalid credentials */
    class InvalidCredentials: public std::runtime_error {
    private:
        std::string msg_;
    public:
        InvalidCredentials(const std::string &msg);
        const std::string& getMsg() const;
    };

    /** @brief Exception class to report repeated IDs */
    class RepeatedId: public std::runtime_error {
    private:
        std::string id_;
    public:
        RepeatedId(const std::string &id);
        const std::string& get_id() const;
    };

    /** @brief Exception class to report an invalid schedule */
    class InvalidSchedule: public std::logic_error {
    private:
        std::string id_;
    public:
        /**
         * @brief Constructor accepting ID that caused the exception.
         * @param   id  ID that caused the exception
         */
        InvalidSchedule(const std::string &id);
        /// @brief Get ID that caused the exception
        const std::string& get_id() const;
    };
};

template<class Base, class Deriv, class Type>
std::vector<const Deriv*> App::filter(const std::vector<const Base*> &v, const Type &t){
    std::vector<const Base*> v1 = utils::filter(v,
        [&t](const Base *p){
            return (p->get_type() == t);
        }
    );
    std::vector<const Deriv*> retv = std::vector<const Deriv*>(v1.size());
    std::transform(v1.begin(), v1.end(), retv.begin(), [](const Base *p){
        const Deriv *ret = dynamic_cast<const Deriv*>(p);
        if(ret == nullptr) throw std::bad_cast();
        return ret;
    });
    return retv;
}

template<class Deriv> User* App::chooseUser(const User::Type &type) {
    std::cout << "Choosing user.\n";
    std::vector<const User*> v(users_.begin(), users_.end());
    std::vector<const Deriv*> users_filter = App::filter<User,Deriv,User::Type>(v, type);
    while (true) {
        print_list(users_filter);
        std::string id;
        if (!utils::input("Choose user (username): ", id, std::cin, std::cout)) return NULL;
        User::Username username = User::Username(id);
        User *it = find_user(username);
        if (it == NULL) {
            error("User doesn't exist (username doesn't have matches).");
            continue;
        } else {
            return it;
        }
    }
}

template<class Deriv> bool App::deleteUser(const User::Type &type) {
    CLEAR();
    std::cout << "Deleting user.\n";
    while (true) {
        User *user = App::chooseUser<Deriv>(type);
        if (user == NULL) return false;
        std::vector<User*>::iterator user_it = std::find(users_.begin(), users_.end(), user);
        if (!confirm("Confirm the deletion of user \'" + std::string((*user_it)->get_username()) + "\' (yes/no): ")) return false;
        delete *user_it;
        users_.erase(user_it);
        std::cout << "User deleted.\n";
        return true;
    }
    return false;
}

template<class Deriv> bool App::editUser(const User::Type &type) {
    CLEAR();
    std::cout << "Editing user.\n";
    User *user = App::chooseUser<Deriv>(type);
    if (user == NULL) return false;
    User::Type user_type = user->get_type();
    int no_properties = 4 + (user_type == User::Type::manager || user_type == User::Type::driver);
    int option;
    Deriv user_copy = *dynamic_cast<Deriv*>(user);
    bool is_edited = false;
    while (true) {
        option = 0;
        App::display(&user_copy);
        if (!utils::input("Choose property to change (type cancel to finish): ", option, std::cin, std::cout)) break;
        if (option <= 0 || option > no_properties) { App::error("Option outside of range."); continue; }
        if(user_copy.edit(option, std::cin, std::cout)) is_edited = true;
    }
    if (is_edited) {
        if (!confirm("Confirm the edition of user \'" + std::string(user_copy.get_username()) + "\' (yes/no): ")) return false;
        *user = user_copy;
        std::cout << "User edited.\n";
    }
    return true;
}

template<class Deriv> bool App::editUser(User *user) {
    CLEAR();
    std::cout << "Editing user.\n";
    User::Type user_type = user->get_type();
    int no_properties = 4 + (user_type == User::Type::manager || user_type == User::Type::driver);
    int option;

    Deriv user_copy = *dynamic_cast<Deriv*>(user);
    bool is_edited = false;
    while (true) {
        option = 0;
        App::display(&user_copy);
        if (!utils::input("Choose property to change (type cancel to finish): ", option, std::cin, std::cout)) break;
        if (option <= 0 || option > no_properties) { App::error("Option outside of range."); continue; }
        if (user_copy.edit(option, std::cin, std::cout)) is_edited = true;
    }
    if (is_edited) {
        if (!confirm("Confirm the changes (yes/no): ")) return false;
        *user = user_copy;
        std::cout << "Saved changes.\n";
    }
    return true;
}

#endif //APP_H_INCLUDED