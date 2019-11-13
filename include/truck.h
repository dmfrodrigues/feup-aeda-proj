/**
 * @file truck.h
 */

#ifndef TRUCK_H_INCLUDED
#define TRUCK_H_INCLUDED

#include "currency.h"
#include "cargo.h"
#include "Time.h"

#include <vector>
#include <utility>

/** @brief %Distance */
typedef utils::ufloat<float> Distance;

/**
 * @brief Superclass of all transports of the company.
 * @ref   Cargo
 */
class Truck {
public:
    /** @brief Class to store number plates. */
    class NumberPlate{
    public:
        /** @brief Class to store number plate number (i.e., excluding country and other info) */
        class Number: public utils::string_regex{
        public:
            /** @brief   Regular expression string that describes a valid number plate. */
            static const std::string REGEX_STR;
            /** @brief   Empty constructor. */
            explicit Number();
            /**
             * @brief   Constructs from string containing number plate.
             * @param   plate   String with numberplate
             */
            explicit Number(const std::string &plate);
            /** @brief Overload of operator=. */
            Number& operator=(const std::string &s);
        };
        /*
        enum Country : int{
            Portugal = 0
        };
        */
    private:
        Number number_;
        //Country country_;
    public:
        /** @brief Empty constructor. */
        explicit NumberPlate();
        /** @brief Constructor accepting string */
        explicit NumberPlate(const Number &number);
        /** @brief Convert to std::string */
        explicit operator std::string() const;
        /** @brief Overload of operator<. */
        bool operator< (const NumberPlate &n) const;
        /** @brief Overload of operator==.*/
        bool operator==(const NumberPlate &n) const;
        /** @brief Overload of operator>> */
        friend std::istream& operator>>(std::istream &is,       NumberPlate &n);
        /** @brief Overload of operator<< */
        friend std::ostream& operator<<(std::ostream &os, const NumberPlate &n);
    };
    /** @brief Vehicle category. */
    class Category: public utils::string_regex{
    public:
        /** @brief Regex a vehicle category is supposed to match. */
        static const std::string REGEX_STR;
        /** @brief Empty constructor. */
        explicit Category();
        /** @brief Constructor accepting string as argument for construction. */
        explicit Category(const std::string &category);
        /** @brief Overload of operator= */
        Category& operator=(const std::string &category);
    };
    /** @brief %Fuel */
    enum Fuel : int{
        Biodiesel = 0,
        Diesel = 1,
        Electric,
        Gas,
        Gasoline,
        Hybrid,
        Hydrogen
    };
    /** @brief Convert Fuel to string to present in tables. */
    static std::string fuel_string(const Fuel &f);
    /** @brief Type of truck (always truck, made to conform with Users that also have types) */
    enum Type{
        truck
    };
private:
    //std::vector<Event> logs_;
    NumberPlate number_plate_;
    Time plate_register_date_;
    Fuel fuel_;
    Distance max_reach_;
    Category category_; //A,B,C,D

    //second in pair is cost per kilometer of transporting a given Cargo
    CargoTrans *cargo_ = NULL;

public:
    Truck(){}
    /**
     * @brief Copy Constructor.
     * @param truck Truck that will be used to form the new truck
     */
    Truck(const Truck& t);
    /**
     * @brief Constructor of all information of a general truck.
     * @param number_plate              Number plate of truck
     * @param max_replate_register_date Number plate register date
     * @param fuel                      Fuel
     * @param max_reach                 Maximum reach of truck
     * @param category                  Category of truck
     * @param cargo                     Pointer to cargo the truck can transport
     */
    Truck(const NumberPlate &number_plate, const Time     &plate_register_date,
          const Fuel        &fuel        , const Distance &max_reach          ,
          const Category    &category    , CargoTrans *cargo);

    /** @brief Destructor */
    virtual ~Truck();

    /// @brief Get number plate.
    const NumberPlate& get_numberplate      () const{ return number_plate_       ; }
    /// @brief Get number plate (in this case the same as number plate).
    const NumberPlate& get_id               () const{ return get_numberplate()   ; }
    /// @brief Get number plate register date.
    const Time&        get_plateregisterdate() const{ return plate_register_date_; }
    /// @brief Get fuel.
    const Fuel&        get_fuel             () const{ return fuel_               ; }
    /// @brief Get maximum reach/range of the truck.
    const Distance&    get_range            () const{ return max_reach_          ; }
    /// @brief Get category.
    const Category&    get_category         () const{ return category_           ; }
    /// @brief Get cargo pointer.
    const CargoTrans* get_cargo() const;
    /// @brief Get type of vehicle (always Truck)
    virtual Type get_type(void) const;

    static Fuel processFuel(const std::string &s);

    static Truck* deep_copy(const Truck *truck);

    /** @brief   Overload of <em> operator>> </em>. */
    friend std::istream& operator>>(std::istream &is,       Truck &t);
    /** @brief   Overload of <em> operator<< </em>. */
    friend std::ostream& operator<<(std::ostream &os, const Truck &t);

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param command Command to add/edit cargo
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    bool edit(std::string command, std::istream &is, std::ostream &os);
};

#endif /* end of include guard: TRUCK_H_INCLUDED */
