#ifndef settings_H
#define settings_H

#include <fstream>
#include <map>
#include <sstream>
#include <string>

class settings {
public:
    class param {
    private:
        param(param const &);
        std::string value;
        std::stringstream conv;
    public:
        param();
        param(std::string val);
        operator std::string() const;
        operator int() const;
        operator bool() const;
        operator double() const;

        param & operator=(param const &param) {
            value = param.value;
            return *this;
        }

        template <typename T>
        param & operator=(T const &param) {
            conv << std::boolalpha << param;
            conv >> std::boolalpha >> value;
            return *this;
        }

        template <typename T>
        param & operator+=(T const &param) {
            T tmp;
            conv << std::boolalpha << value;
            conv >> std::boolalpha >> tmp;
            tmp += param;
            conv << std::boolalpha << tmp;
            conv >> std::boolalpha >> value;
            return *this;
        }

        template <typename T>
        param & operator-=(T param) {
            T tmp;
            conv << std::boolalpha << value;
            conv >> std::boolalpha >> tmp;
            tmp -= param;
            conv << std::boolalpha << tmp;
            conv >> std::boolalpha >> value;
            return *this;
        }

        template <typename T>
        param & operator*=(T param) {
            T tmp;
            conv << std::boolalpha << value;
            conv >> std::boolalpha >> tmp;
            tmp *= param;
            conv << std::boolalpha << tmp;
            conv >> std::boolalpha >> value;
            return *this;
        }

        template <typename T>
        param & operator/=(T param) {
            T tmp;
            conv << std::boolalpha << value;
            conv >> std::boolalpha >> tmp;
            tmp /= param;
            conv << std::boolalpha << tmp;
            conv >> std::boolalpha >> value;
            return *this;
        }

        param & operator|=(bool param);

        param & operator&=(bool param);

        bool is_empty() const;
    };

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
    std::string const & get(std::string const & name,
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

private:
    std::map<std::string, param> sett;
    std::string path;
    void deserialize();
    void serialize();
};

#endif // settings_H
