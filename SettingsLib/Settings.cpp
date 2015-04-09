#include "Settings.h"
no_such_param::no_such_param(const std::string &name)
    :std::runtime_error("No such param: \"" + name + "\"\n") {
}

cant_convert_to::cant_convert_to(const std::string &name, const std::string &type)
    :std::runtime_error("Can't convert param: \"" + name + "\" to type: \"" + type + "\"\n") {
}

incompatible_operands::incompatible_operands(const std::string &name, const std::string &op, const std::string &type)
    :std::runtime_error("Can't apply operation: \"" + op + "\" on param: \"" + name +
                        "\"\nparam: " + name + "\" cannot be converted to type: \"" + type + "\"\n") {
}

settings::param::param(std::string nam, std::string val, settings *par) {
    name = nam;
    value = val;
    parent = par;
}

settings::param::operator std::string() const {
    return value;
}

settings::param::operator int() const {
    try {
        return stoi(value);
    } catch(...) {
        throw cant_convert_to(name, "int");
    }
}

settings::param::operator double() const {
    try {
        return stod(value);
    } catch(...) {
        throw cant_convert_to(name, "double");
    }
}

settings::param::operator bool() const {
    if(value!="true" && value!="false") {
        throw cant_convert_to(name, "bool");
    }
    return (value == "true");
}

settings::param & settings::param::operator=(std::string const &param) {
    value = param;
    parent->set(name, value);
    return *this;
}

settings::param & settings::param::operator=(int param) {
    value = std::to_string(param);
    parent->set(name, value);
    return *this;
}

settings::param & settings::param::operator=(bool param) {
    if(param) {
        value = "true";
    } else {
        value = "false";
    }
    parent->set(name, value);
    return *this;
}

settings::param & settings::param::operator=(double param) {
    value = std::to_string(param);
    parent->set(name, value);
    return *this;
}

settings::param & settings::param::operator+=(std::string const & param) {
    value += param;
    parent->set(name, value);
    return *this;
}

settings::param & settings::param::operator+=(int param){
    try {
        value = std::to_string(std::stoi(value) + param);
        parent->set(name, value);
        return *this;
    } catch (...) {
        throw incompatible_operands(name, "+", "int");
    }
}

settings::param & settings::param::operator+=(double param) {
    try {
        value = std::to_string(std::stod(value) + param);
        parent->set(name, value);
        return *this;
    } catch(...) {
        throw incompatible_operands(name, "+", "double");
    }
}

settings::param & settings::param::operator-=(int param) {
    try {
        value = std::to_string(std::stoi(value) - param);
        parent->set(name, value);
        return *this;
    } catch(...) {
        throw incompatible_operands(name, "-", "int");
    }
}

settings::param & settings::param::operator-=(double param) {
    try {
        value = std::to_string(std::stod(value) - param);
        parent->set(name, value);
        return *this;
    } catch(...) {
        throw incompatible_operands(name, "-", "double");
    }
}

settings::param & settings::param::operator*=(int param) {
    try {
        value = std::to_string(std::stoi(value) * param);
        parent->set(name, value);
        return *this;
    } catch(...) {
        throw incompatible_operands(name, "*", "int");
    }
}
settings::param & settings::param::operator*=(double param) {
    try {
        value = std::to_string(std::stod(value) * param);
        parent->set(name, value);
        return *this;
    } catch(...) {
        throw incompatible_operands(name, "*", "double");
    }
}

settings::param & settings::param::operator/=(int param) {
    try {
        value = std::to_string(std::stoi(value) / param);
        parent->set(name, value);
        return *this;
    } catch(...) {
        throw incompatible_operands(name, "/", "int");
    }
}
settings::param & settings::param::operator/=(double param) {
    try {
        value = std::to_string(std::stod(value) / param);
        parent->set(name, value);
        return *this;
    } catch(...) {
        throw incompatible_operands(name, "+", "double");
    }
}

settings::param & settings::param::operator|=(bool param) {
    if(value != "true" && value != "false") {
        throw incompatible_operands(name, "|", "bool");
    }
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
    parent->set(name, value);
    return *this;
}

settings::param & settings::param::operator&=(bool param) {
    if(value != "true" && value!="false") {
        throw incompatible_operands(name, "&", "bool");
    }
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
    parent->set(name, value);
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
        sett[key] = val;
    }
    in.close();
}

void settings::serialize() {
    std::ofstream out(path);
    for(std::map<std::string, std::string>::iterator i = sett.begin(); i!=sett.end(); i++) {
        out << i->first << ":" << i->second << ";";
    }
    out.close();
}

void settings::reset() {
    std::ofstream out(path, std::ofstream::trunc);
    out.close();
    sett.clear();
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
    sett[name] = value;
    serialize();
}

const settings::param settings::operator[](std::string const & name) const {
    try {
        return param(name, sett.at(name), const_cast<settings*>(this));
    } catch(...) {
        throw no_such_param(name);
    }
}

settings::param settings::operator[](std::string const & name) {
    try {
        return param(name, sett.at(name), this);
    } catch (...) {
        throw no_such_param(name);
    }
}
