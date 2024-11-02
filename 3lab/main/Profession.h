#pragma once
#include <string>
#include <vector>


class Profession {
private:
    std::string profession_name;
    std::string profession_info;
    int salary;
public:
    std::string getProfessionName() const {
        return  this->profession_name;
    }
    void setProfessionName(const std::string& name) {
       this-> profession_name = name;
    }
    std::string getProfessionInfo() const {
        return  this->profession_info;
    }
    void setProfessionInfo(const std::string& info) {
        this->profession_info = info;
    }
    void setProfessionSalary(int salary) {
        this->salary = salary;
    }
    int getProfessionSalary() {
        return this->salary;
    }
};