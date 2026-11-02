#ifndef CAR_H
#define CAR_H

#include <iostream>
#include <string>
#include <vector>
#include <exception>

class CarException : public std::exception {
protected:
    std::string message;
public:
    explicit CarException(const std::string& msg) : message(msg) {}
    const char* what() const noexcept override { return message.c_str(); }
};

class ValueRangeException : public CarException {
public:
    explicit ValueRangeException(const std::string& msg) : CarException(msg) {}
};

class NotInitializedException : public CarException {
public:
    explicit NotInitializedException(const std::string& msg) : CarException(msg) {}
};

class Car {
private:
    std::string brand; 
    std::string color; 
    int    power;   
    double engineVolume;

public:
    static const int    MAX_POWER; 
    static const double MAX_VOLUME; 

    Car();
    Car(const std::string& brand, const std::string& color);
    Car(const std::string& brand, const std::string& color, int power, double engineVolume);

   
    void setPower(int p);            
    void setEngineVolume(double v);    
    int    getPower() const;
    double getEngineVolume() const;     

    void setBrand(const std::string& b)  { brand = b; }
    void setColor(const std::string& c)  { color = c; }
    const std::string& getBrand() const  { return brand; }
    const std::string& getColor() const  { return color; }

    Car& operator+=(int extraPower);                     
    friend std::istream& operator>>(std::istream& in, Car& c);       
    friend std::ostream& operator<<(std::ostream& out, const Car& c);

    static std::vector<int> find(const std::vector<Car>& cars, const std::string& brand);
    static std::vector<int> find(const std::vector<Car>& cars, const std::string& brand,
                                 const std::string& color);
    static std::vector<int> find(const std::vector<Car>& cars, int minPower, int maxPower);
    static std::vector<int> find(const std::vector<Car>& cars, double minVolume, double maxVolume);
};

#endif 
