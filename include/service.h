#ifndef SERVICE_H_INCLUDED
#define SERVICE_H_INCLUDED

#include "person.h"
#include "Time.h"

/**
 * @brief Class to store all the information concerning a transport service.
 */
class Service{
private:
    const Client *client_;
    Person contact1_;
    Person contact2_;
    std::string cargo_type_;
    double cargo_amount_;
    int cargo_danger_;
    Time t_begin_;
    Time t_end_;
    Address a_begin_;
    Address a_end_;
    //vector<Truck*> trucks_;
public:
    /**
     * @brief Constructor that accepts all the information concerning a transport service.
     * @param   client          Pointer to @ref Client to which the service will be provided
     * @param   contact1        @ref Person that should be contacted on loading
     * @param   contact2        @ref Person that should be contacted on arrival and unloading
     * @param   cargo_type      String denoting the type of cargo
     * @param   cargo_amount    Amount of cargo that will be transported, in kilograms
     * @param   cargo_danger    Danger of the cargo
     * @param   t_begin         @ref Time at which the driver should leave the headquarters
     * @param   t_end           @ref Time at which the driver is expected to reach the headquarters
     * @param   a_begin         @ref Address at which the cargo should be loaded
     * @param   a_end           @ref Address at which the cargo should be unloaded
     */
    Service(const Client *client, const Person &contact1, const Person &contact2,
            const std::string &cargo_type, double cargo_amount, int cargo_danger,
            Time t_begin, Time t_end,
            Address a_begin, Address a_end);
};

#endif //SERVICE_H_INCLUDED
