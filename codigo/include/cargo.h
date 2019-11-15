/**
 * @file cargo.h
 */

#ifndef CARGO_H_INCLUDED
#define CARGO_H_INCLUDED

#include "currency.h"
#include "temperature.h"
#include "utils.h"

#include <utility>
#include <stdexcept>

/**
 * @brief Description of cargo that a client may request to transport.
 */
class Cargo {
public:
    /**
     * @enum Type
     * @brief Types of cargo.
     */
    enum Type : int {
        Normal = 0,
        Animal,
        Refrigerated,
        Dangerous,
    };
    /**
     * @enum DangerLevel
     * @brief Dangerous goods classification.
     */
    enum DangerLevel : int {
        None = 0,
        Miscellaneous,
        Gases,
        Flammable_Liq,
        Flammable_Sol,
        Oxydizing_Agents,
        Explosives,
        Corrosive,
        Toxic,
        Radioactive,
    };
    /// @brief Convert @ref Cargo::Type to \a std::string to show in tables.
    static std::string type_string(const Type &t);
    /// @brief Convert @ref Cargo::DangerLevel to \a std::string to show in tables.
    static std::string dangerlevel_string(const DangerLevel &d);

    /**
     * @brief Input from file to @ref Cargo pointer.
     *
     * The first element decides what is the real type of the cargo, thus
     * allowing for a \a dynamic_cast and a call to the correct input function.
     * @param   is  Input stream to extract data from
     * @param   c   Pointer to @ref Cargo that will be created from the data read
     * @return      Same as \p is
     */
    friend std::istream& input_Cargo (std::istream &is,       Cargo *&c);
    /**
     * @brief Output to file from @ref Cargo pointer.
     *
     * The appropriate checks are made to determine the real type of \p c, and
     * call the correct output function.
     * @param   os  Output stream to insert data to
     * @param   c   Pointer to cargo to be printed to \p os
     * @return      Same as \p os
     */
    friend std::ostream& output_Cargo(std::ostream &os, const Cargo * c);
private:
    Weight W_;
    std::string description_;
protected:
    /**
     * @brief Input from \a std::istream to current object.
     * @param   is  Input stream to read from
     * @return      Same as \p is
     */
    virtual std::istream& input (std::istream &is);
    /**
     * @brief Output to \a std::ostream from current object.
     * @param   os  Output stream to write to
     * @return      Same as \p os
     */
    virtual std::ostream& output(std::ostream &os) const;
public:
    /// @brief Empty constructor.
    Cargo();
    /// @brief Destructor.
    virtual ~Cargo();

    /**
     * @brief Get cargo type.
     * @return Cargo::Type::Normal
     */
    virtual Cargo::Type get_type      () const;
    /// @brief Get weight.
    const Weight&       get_W          () const;
    /// @brief Get description.
    const std::string&  get_description() const;


    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);
};

/**
 * @brief Description of animal cargo that a client may request to transport.
 */
class CargoAnimal: public Cargo{
    friend std::istream& input_Cargo (std::istream &is,       Cargo *&c);
    friend std::ostream& output_Cargo(std::ostream &os, const Cargo *c);
protected:
    /**
     * @brief Input from \a std::istream to current object.
     * @param   is  Input stream to read from
     * @return      Same as \p is
     */
    virtual std::istream& input (std::istream &is);
    /**
     * @brief Output to \a std::ostream from current object.
     * @param   os  Output stream to write to
     * @return      Same as \p os
     */
    virtual std::ostream& output(std::ostream &os) const;
public:
    /// @brief Empty constructor.
    CargoAnimal();
    /**
     * @brief Get cargo type.
     * @return Cargo::Type::Animal
     */
    virtual Cargo::Type get_type() const;

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);
};

/**
 * @brief Description of refrigerated cargo that a client may request to transport.
 */
class CargoRefrigerated: public Cargo{
    friend std::istream& input_Cargo (std::istream &is,       Cargo *&c);
    friend std::ostream& output_Cargo(std::ostream &os, const Cargo *c);
private:
    /// @brief Range of temperature that cargo must be kept on.
    TemperatureRange Tr_;
protected:
    /**
     * @brief Input from \a std::istream to current object.
     * @param   is  Input stream to read from
     * @return      Same as \p is
     */
    virtual std::istream& input (std::istream &is);
    /**
     * @brief Output to \a std::ostream from current object.
     * @param   os  Output stream to write to
     * @return      Same as \p os
     */
    virtual std::ostream& output(std::ostream &os) const;
public:
    /// @brief Empty constructor.
    CargoRefrigerated();
    /**
     * @brief Get cargo type.
     * @return Cargo::Type::Refrigerated
     */
    virtual Cargo::Type get_type() const;
    /// @brief Get temperature range.
    const TemperatureRange& get_Tr() const;

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);
};

/**
 * @brief Description of dangerous cargo that a client may request to transport.
 */
class CargoDangerous: public Cargo{
    friend std::istream& input_Cargo (std::istream &is,       Cargo *&c);
    friend std::ostream& output_Cargo(std::ostream &os, const Cargo *c);
private:
    DangerLevel danger_level_;
protected:
    /**
     * @brief Input from \a std::istream to current object.
     * @param   is  Input stream to read from
     * @return      Same as \p is
     */
    virtual std::istream& input (std::istream &is);
    /**
     * @brief Output to \a std::ostream from current object.
     * @param   os  Output stream to write to
     * @return      Same as \p os
     */
    virtual std::ostream& output(std::ostream &os) const;
public:
    /// @brief Empty constructor.
    CargoDangerous();
    /**
     * @brief Get cargo type.
     * @return Cargo::Type::Dangerous
     */
    virtual Cargo::Type get_type() const;
    /// @brief Get danger level.
    const Cargo::DangerLevel& get_dangerlevel() const;

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);
};

/**
 * @brief Description of cargo that a truck can transport.
 */
class CargoTrans: public Cargo{
    /**
     * @brief Input from file to CargoTrans pointer.
     *
     * The first element decides what is the real type of the CargoTrans, thus
     * allowing for a dynamic_cast and a call to the correct input function.
     * @param   is  Input stream to extract data from
     * @param   c   Pointer to CargoTrans that will be created from the data read
     * @return      Same as \p is
     */
    friend std::istream& input_CargoTrans (std::istream &is,       CargoTrans *&c);
    /**
     * @brief Output to file from Cargo pointer.
     *
     * The appropriate checks are made to determine the real type of c, and
     * call the correct output function.
     * @param   os  Output stream to insert data to
     * @param   c   Pointer to CargoTrans to be printed to \p os
     * @return      Same as \p os
     */
    friend std::ostream& output_CargoTrans(std::ostream &os, const CargoTrans *c);
private:
    static const Currency P_B_;
    double E_D_;
    double E_W_;
protected:
    /**
     * @brief Input from \a std::istream to current object.
     * @param   is  Input stream to read from
     * @return      Same as \p is
     */
    virtual std::istream& input (std::istream &is);
    /**
     * @brief Output to \a std::ostream from current object.
     * @param   os  Output stream to write to
     * @return      Same as \p os
     */
    virtual std::ostream& output(std::ostream &os) const;
public:
    /// @brief Empty constructor.
    CargoTrans();
    /**
     * @brief Get cargo type.
     * @return Cargo::Type::Normal
     */
    virtual Cargo::Type get_type() const;
    /// @brief Get price base.
    virtual const Currency& get_P_B() const;
    /// @brief Get expenses per km.
    const double& get_E_D() const;
    /// @brief get expenses per kg.
    const double& get_E_W() const;

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);
    /// @brief Return true if this cargo description can carry a given cargo
    virtual bool can_carry(const Cargo *p) const;
    /// @brief Get real amount of expenses per km.
    virtual Currency get_E(Distance D, Weight W) const;
    /// @brief Get real price.
    virtual Currency get_P(Distance D, Weight W) const;
};

/**
 * @brief Description of animal cargo that a truck can transport.
 */
class CargoTransAnimal: public CargoTrans{
    friend std::istream& input_CargoTrans (std::istream &is,       CargoTrans *&c);
    friend std::ostream& output_CargoTrans(std::ostream &os, const CargoTrans *c);
private:
    static const Currency P_B_;
protected:
    /**
     * @brief Input from \a std::istream to current object.
     * @param   is  Input stream to read from
     * @return      Same as \p is
     */
    virtual std::istream& input (std::istream &is);
    /**
     * @brief Output to \a std::ostream from current object.
     * @param   os  Output stream to write to
     * @return      Same as \p os
     */
    virtual std::ostream& output(std::ostream &os) const;
public:
    /// @brief Empty constructor.
    CargoTransAnimal();
    /**
     * @brief Get cargo type.
     * @return Cargo::Type::Animal
     */
    virtual Cargo::Type get_type() const;
    /// @brief Get base price of cargo.
    virtual const Currency& get_P_B() const;

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);
    /// @brief Return true if this cargo description can carry a given cargo
    virtual bool can_carry(const Cargo *p) const;
    /// @brief Get real amount of expenses per km.
    virtual Currency get_E(Distance D, Weight W) const;
    /// @brief Get real price.
    virtual Currency get_P(Distance D, Weight W) const;
};

/**
 * @brief Description of refrigerated cargo that a truck can transport.
 */
class CargoTransRefrigerated: public CargoTrans{
private:
    friend std::istream& input_CargoTrans (std::istream &is,       CargoTrans *&c);
    friend std::ostream& output_CargoTrans(std::ostream &os, const CargoTrans *c);
    static const Currency P_B_;
    static const Temperature T0_;
    double E_T_;
    TemperatureRange Tr_;
protected:
    /**
     * @brief Input from \a std::istream to current object.
     * @param   is  Input stream to read from
     * @return      Same as \p is
     */
    virtual std::istream& input (std::istream &is);
    /**
     * @brief Output to \a std::ostream from current object.
     * @param   os  Output stream to write to
     * @return      Same as \p os
     */
    virtual std::ostream& output(std::ostream &os) const;
public:
    /// @brief Empty constructor.
    CargoTransRefrigerated();
    /**
     * @brief Get cargo type.
     * @return Cargo::Type::Refrigerated
     */
    virtual Cargo::Type get_type() const;
    /// @brief Get temperature range.
    const TemperatureRange& get_Tr() const;
    virtual const Currency& get_P_B() const;
    /// @brief Get reference temperature.
    const Temperature& get_T0() const;
    /// @brief Get temperature factor.
    const double& get_E_T() const;

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);
    /// @brief Return true if this cargo description can carry a given cargo
    virtual bool can_carry(const Cargo *p) const;
    /// @brief Get real amount of expenses.
    virtual Currency get_E(Distance D, Weight W, TemperatureRange Tr) const;
    /// @brief Get real price.
    virtual Currency get_P(Distance D, Weight W, TemperatureRange Tr) const;
};

/**
 * @brief Description of dangerous that a truck can transport.
 */
class CargoTransDangerous: public CargoTrans{
    friend std::istream& input_CargoTrans (std::istream &is,       CargoTrans *&c);
    friend std::ostream& output_CargoTrans(std::ostream &os, const CargoTrans *c);
private:
    static const Currency P_B_;
    DangerLevel danger_level_;
protected:
    /**
     * @brief Input from \a std::istream to current object.
     * @param   is  Input stream to read from
     * @return      Same as \p is
     */
    virtual std::istream& input (std::istream &is);
    /**
     * @brief Output to \a std::ostream from current object.
     * @param   os  Output stream to write to
     * @return      Same as \p os
     */
    virtual std::ostream& output(std::ostream &os) const;
public:
    /// @brief Empty constructor.
    CargoTransDangerous();

    /**
     * @brief Get cargo type.
     * @return Cargo::Type::Dangerous
     */
    virtual Cargo::Type get_type() const;
    /// @brief Get base price of cargo.
    virtual const Currency& get_P_B    () const;
    /// @brief Get danger level
    const Cargo::DangerLevel& get_dangerlevel() const;

    /**
     * @brief Allows input field by field with descriptive messages.
     * @param is Input stream
     * @param os Output stream
     * @return If the input was sucessful
     */
    virtual bool in(std::istream &is, std::ostream &os);

    /**
     * @brief Allows edition of property specified.
     * @param property Property to be changed
     * @param is Input stream
     * @param os Output stream
     * @return If the edit was sucessful
     */
    virtual bool edit(int property, std::istream&is, std::ostream &os);
    /// @brief Return true if this cargo description can carry a given cargo
    virtual bool can_carry(const Cargo *p) const;
    /// @brief Get real amount of expenses per km.
    virtual Currency get_E(Distance D, Weight W) const;
    /// @brief Get real price.
    virtual Currency get_P(Distance D, Weight W) const;
};

#endif // CARGO_H_INCLUDED
