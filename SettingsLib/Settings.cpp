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

settings::param & settings::param::operator=(std::string const &param) {
    value = param;
    return *this;
}

settings::param & settings::param::operator=(int param) {
    value = std::to_string(param);
    return *this;
}

settings::param & settings::param::operator=(bool param) {
    if(param) {
        value = "true";
    } else {
        value = "false";
    }
    return *this;
}

settings::param & settings::param::operator=(double param) {
    value = std::to_string(param);
    return *this;
}

settings::param & settings::param::operator+=(std::string const & param) {
    value += param;
    return *this;
}

settings::param & settings::param::operator+=(int param){
    value = std::to_string(std::stoi(value) + param);
    return *this;
}

settings::param & settings::param::operator+=(double param) {
    value = std::to_string(std::stod(value) + param);
    return *this;
}

settings::param & settings::param::operator-=(int param) {
    value = std::to_string(std::stoi(value) - param);
    return *this;
}

settings::param & settings::param::operator-=(double param) {
    value = std::to_string(std::stod(value) - param);
    return *this;
}

settings::param & settings::param::operator*=(int param) {
    value = std::to_string(std::stoi(value) * param);
    return *this;
}
settings::param & settings::param::operator*=(double param) {
    value = std::to_string(std::stod(value) * param);
    return *this;
}

settings::param & settings::param::operator/=(int param) {
    value = std::to_string(std::stoi(value) / param);
    return *this;
}
settings::param & settings::param::operator/=(double param) {
    value = std::to_string(std::stod(value) / param);
    return *this;
}

settings::param & settings::param::operator|=(bool param) {
    if(value == "true") {
        param |= true;
    } else {
        param |= false;
    }
    if(param) {
       value = "true";
    } else {
       value = "false";
    }
    return *this;
}

settings::param & settings::param::operator&=(bool param) {
    if(value == "true") {
        param &= true;
    } else {
        param &= false;
    }
    if(param) {
        value = "true";
    } else {
        value = "false";
    }
    return *this;
}

settings::settings(std::string const & filename)
{
    path = filename;
    deserialize();
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

void settings::reset() {
    reload();
}

void settings::reload() {
    sett.clear();
    deserialize();
}

std::string const settings::get(const std::string &name, const std::string &def) const {
    try {
        return sett.at(name);
    } catch(std::out_of_range) {
        return def;
    }
}

void settings::set(const std::string &name, const std::string &value) {
    sett[name] = settings::param(value);
    serialize();
}

const settings::param & settings::operator[](std::string const & name) const {
    return sett.at(name);
}

settings::param & settings::operator[](std::string const & name) {
    return sett[name];
}
