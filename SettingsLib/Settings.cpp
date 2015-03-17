#include "Settings.h"
settings::param::param() {

}

settings::param::param(std::string val) {
    value = val;
}

settings::param::operator std::string() const {
    return value;
}

settings::param::operator int() const {
    return stoi(value);
}

settings::param::operator double() const {
    return stod(value);
}

settings::param::operator bool() const {
    return (value == "true");
}

settings::param & settings::param::operator|=(bool param) {
        bool tmp;
        conv << std::boolalpha << value;
        conv >> std::boolalpha >> tmp;
        tmp |= param;
        conv << std::boolalpha << tmp;
        conv >> std::boolalpha >> value;
        return *this;
}

settings::param & settings::param::operator&=(bool param) {
        bool tmp;
        conv << std::boolalpha << value;
        conv >> std::boolalpha >> tmp;
        tmp &= param;
        conv << std::boolalpha << tmp;
        conv >> std::boolalpha >> value;
        return *this;
}

settings::settings(std::string const & filename)
{
    path = filename;
}

void settings::deserialize() {
    std::ifstream in(path);
    std::string key, val;
    while((std::getline(in, key, ':'), std::getline(in, val, ';'))) {
        sett[key] = settings::param(val);
    }
    in.close();
}

void settings::serialize() {
    std::ofstream out(path);
    for(std::map<std::string, settings::param>::iterator i = sett.begin(); i!=sett.end(); i++) {
        out << i->first << ":" << (std::string)i->second << ";";
    }
    out.close();
}
