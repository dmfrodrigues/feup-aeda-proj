/**
 * @file Time.h
 */

#ifndef TIME_H_INCLUDED
#define TIME_H_INCLUDED

#include <string>
#include <stdexcept>
#include <ctime>

/**
 * @brief Encapsulate time in a simple class with a few methods
 */
class Time {
private:
    std::tm t_;
public:
    /**
     * @brief Default date format for input from files
     */
    static const std::string DEFAULT_FORMAT;
    /**
     * @brief Default full date format for input by user
     */
    static const std::string DEFAULT_TIME_REGEX;
    /**
     * @brief Default hour format for input by user
     */
    static const std::string DEFAULT_DATE_REGEX;
    /**
     * @brief Default time/date if none is set
     */
    static const std::string DEFAULT_TIME;
    /**
     * @brief Constructor accepting date in @ref DEFAULT_FORMAT.
     */
    Time(const std::string &s = DEFAULT_TIME);

    /**
     * @brief Format date with format string.
     * @param   fmt Format string
     * @return  string with formatted date
     */
    std::string format(const std::string &fmt = Time::DEFAULT_FORMAT) const;

    /**
     * @brief Allows input of time in a friendly user way.
     * Default format for time is: YYYY-mm-dd HH:MM:SS.
     * @param time String containing input from user
     * @throws Time::InvalidTimeFormat If input doesn't follow format rules, Time::InvalidTime if input is invalid time
     */
    void input_time(const std::string &time);
    /**
     * @brief Allows input of date in a friendly user way.
     * Default format for time is: YYYY-mm-dd.
     * The hours, minutes and seconds will be set to the 00:00:00.
     * @param hour String containing input from user
     * @throws Time::InvalidTimeFormat If input doesn't follow format rules, Time::InvalidTime if input is invalid time
     */
    void input_date(const std::string &date);

    bool operator==(const Time &t) const;
    bool operator!=(const Time &t) const;
    bool operator< (const Time &t) const;
    bool operator> (const Time &t) const;
    bool operator<=(const Time &t) const;
    bool operator>=(const Time &t) const;

    /** @brief   Overload of <em> operator>> </em>. Expects input in @ref Time::DEFAULT_FORMAT. */
    friend std::istream& operator>>(std::istream &is,       Time &t);
    /** @brief   Overload of <em> operator<< </em>. Prints in @ref Time::DEFAULT_FORMAT. */
    friend std::ostream& operator<<(std::ostream &os, const Time &t);

    /**
     * @brief   Class for denoting an invalid time format
     */
    class InvalidTimeFormat: public std::invalid_argument{
    private:
        std::string fmt_;
    public:
        /**
         * @brief Constructor accepting the time format that caused the exception.
         *
         * Also sets the string returned by <em> std::exception::what() </em>.
         * @param   fmt     Time format
         */
        InvalidTimeFormat(const std::string &fmt);
        /**
         * @brief   Get time format from which the exception was constructed.
         * @return  Time format
         */
        const std::string& get_format() const;
    };

    /**
     * @brief   Class for denoting an invalid date
     */
    class InvalidTime: public std::invalid_argument {
    private:
        std::string date_;
    public:
        /**
         * @brief Constructor accepting the time format that caused the exception.
         *
         * Also sets the string returned by <em> std::exception::what() </em>.
         * @param   fmt     Time format
         */
        InvalidTime(const std::string &date);
        /**
         * @brief   Get date from which the exception was constructed.
         * @return  Date
         */
        const std::string& get_date() const;
    };
};

#endif //TIME_H_INCLUDED
