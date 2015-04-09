#ifndef SETTINGS_H
#define SETTINGS_H

#include <iostream>
#include <fstream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

class no_such_param : public std::runtime_error {
public:
    no_such_param(std::string const &name);
};

class cant_convert_to : public std::runtime_error {
public:
    cant_convert_to(std::string const &name, std::string const &type);
};

class incompatible_operands : public std::runtime_error {
public:
    incompatible_operands(std::string const &name, std::string const &op, std::string const &type);
};

class settings {

private:
    std::map<std::string, std::string> sett;
    std::string path;
    void deserialize();
    void serialize();

    class param {
        friend class settings;
    private:
        param(param const &);
        param(std::string nam, std::string  val, settings *par);
        std::string value;
        std::string name;
        std::stringstream conv;
        settings *parent;
    public:
        operator std::string() const;
        operator int() const;
        operator bool() const;
        operator double() const;

        param & operator=(param const &param) {
            value = param.value;
            return *this;
        }

        param & operator=(std::string const &);
        param & operator=(int);
        param & operator=(bool);
        param & operator=(double);

        param & operator+=(std::string const &);
        param & operator+=(int);
        param & operator+=(double);

        param & operator-=(int);
        param & operator-=(double);

        param & operator*=(int);
        param & operator*=(double);

        param & operator/=(int);
        param & operator/=(double);

        param & operator|=(bool param);

        param & operator&=(bool param);

        bool is_empty() const;
    };
public:
    // Main functions

    /**
         * Construct settings store
         * and load data from file (if exists)
         * \param filename Path to file with settings
         */
    settings(std::string const & filename);
    /**
         * Get setting value
         * \param name Setting unique identifier
         * \param def Default setting value
         * \return Stored value for given name or default value
         */
    std::string const get(std::string const & name,
                            std::string const & def = "") const;
    /**
         * Set or replace setting value and save changes to file
         * \param name Setting unique identifier
         * \param value New setting value
         */
    void set(std::string const & name,
             std::string const & value);
    /**
         * Reset all settings
         */
    void reset();
    /**
         * Reload all settings from file
         */
    void reload();

    // Advanced funсtions

    /**
         * Get constant setting wrapper
         * \param name Setting unique identifier
         */
    const param operator[](std::string const & name) const;
    /**
         * Get constant setting wrapper
         * \param name Setting unique identifier
         */
    param operator[](std::string const & name);
};

#endif // SETTINGS_H
