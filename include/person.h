#ifndef PERSON_H_INCLUDED
#define PERSON_H_INCLUDED

#include "address.h"
#include "vat.h"
#include "phonenumber.h"
#include "currency.h"

/**
 * @brief %Person class.
 */
class Person {
public:
    typedef unsigned int IdType;
private:
    IdType      id_ = 0;
    std::string name_;
    PhoneNumber phonenumber_;
protected:
    virtual std::istream& input(std::istream &is);
public:
    /**
     * @brief Constructor accepting a name and a phone number.
     * @param   name        String containing name of person
     * @param   phonenumber Phone number
     */
    Person(const std::string &name, const PhoneNumber &phonenumber);

    virtual Person::IdType get_id() const final;

    friend std::istream& operator>>(std::istream &is,       Person &p);
    friend std::ostream& operator<<(std::ostream &os, const Person &p);
};

/**
 * @brief %User class.
 *
 * A user must have his/her own credentials to login to the system.
 */
class User : public Person{
private:
    std::string user_;
    std::string pswd_;
protected:
    virtual std::istream& input(std::istream &is);
public:
    /**
     * @brief Constructor accepting a name, a phone number and credentials.
     * @param   name        String containing name of user
     * @param   phonenumber Phone number
     * @param   user        Unique username in the program
     * @param   pswd        Password of the user
     */
    User(const std::string &name, const PhoneNumber &phonenumber,
         const std::string &user, const std::string &pswd       );

    friend std::istream& operator>>(std::istream &is,       User &p);
    friend std::ostream& operator<<(std::ostream &os, const User &p);
};

/**
 * @brief %Client class.
 *
 * A client is a user with privileges to request new services.
 * In order to issue bills, a client must have an Address and a VAT number.
 */
class Client: public User {
private:
    Address address_;
    VAT vat_;
protected:
    virtual std::istream& input(std::istream &is);
public:
    /**
     * @brief Constructor accepting all information to construct a client.
     * @param   name        String containing name of client
     * @param   phonenumber Phone number
     * @param   user        Unique username in the program
     * @param   pswd        Password of the client
     * @param   address     Billing address of the client
     * @param   vat         VAT number of the client for billing purposes
     */
    Client(const std::string &name   , const PhoneNumber &phonenumber,
           const std::string &user   , const std::string &pswd       ,
           const Address     &address, const VAT         &vat        );

    friend std::istream& operator>>(std::istream &is,       Client &p);
    friend std::ostream& operator<<(std::ostream &os, const Client &p);
};

/**
 * @brief %Employee class.
 *
 * An employee is a User that is paid by the company.
 */
class Employee: public User {
private:
    Currency base_salary_;
protected:
    virtual std::istream& input(std::istream &is);
public:
    /**
     * @brief Constructor accepting all information to construct an employee.
     * @param   name        String containing name of employee
     * @param   phonenumber Phone number
     * @param   user        Unique username in the program
     * @param   pswd        Password of the client
     * @param   base_salary Base salary of the employee
     */
    Employee(const std::string &name, const PhoneNumber &phonenumber,
             const std::string &user, const std::string &pswd,
             const Currency    &base_salary);

    /**
     * @brief Types of employees there are; makes it easier to implement @ref Employee::get_type() for inheriting classes.
     */
    enum Type{
        Manager,
        Driver
    };

    /**
     * @brief Get type of employee.
     * @return  %Employee type
     */
    virtual Employee::Type get_type() const = 0;

    friend std::istream& operator>>(std::istream &is,       Employee &p);
    friend std::ostream& operator<<(std::ostream &os, const Employee &p);
};

/**
 * @brief %Manager class.
 *
 * A manager has permissions to make any modification to data in the program.
 */
class Manager: public Employee {
protected:
    virtual std::istream& input(std::istream &is);
public:
    /**
     * @brief Constructor accepting all information to construct a manager.
     * @param   name        String containing name of manager
     * @param   phonenumber Phone number
     * @param   user        Unique username in the program
     * @param   pswd        Password of the manager
     * @param   base_salary Base salary of the manager
     */
    Manager(const std::string &name, const PhoneNumber &phonenumber,
            const std::string &user, const std::string &pswd,
            const Currency    &base_salary);

    /**
     * @brief Get type of employee. Always returns \a Employee::Type::Manager.
     * @return  %Employee type
     */
    Employee::Type get_type() const;

    friend std::istream& operator>>(std::istream &is,       Manager &p);
    friend std::ostream& operator<<(std::ostream &os, const Manager &p);
};

/**
 * @brief %Driver class.
 *
 * A driver makes deliveries.
 */
class Driver: public Employee {
protected:
    virtual std::istream& input(std::istream &is);
public:
    /**
     * @brief Constructor accepting all information to construct a driver.
     * @param   name        String containing name of driver
     * @param   phonenumber Phone number
     * @param   user        Unique username in the program
     * @param   pswd        Password of the driver
     * @param   base_salary Base salary of the driver
     */
    Driver(const std::string &name, const PhoneNumber &phonenumber,
           const std::string &user, const std::string &pswd,
           const Currency    &base_salary);

   /**
    * @brief Get type of employee. Always returns \a Employee::Type::Driver.
    * @return  %Employee type
    */
    Employee::Type get_type() const;

    friend std::istream& operator>>(std::istream &is,       Driver &p);
    friend std::ostream& operator<<(std::ostream &os, const Driver &p);
};

#endif //PERSON_H_INCLUDED
