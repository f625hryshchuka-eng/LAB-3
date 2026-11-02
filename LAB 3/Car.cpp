#include "Car.h"
#include <sstream>

const int    Car::MAX_POWER  = 2000;
const double Car::MAX_VOLUME = 10.0;

Car::Car() : brand(""), color(""), power(0), engineVolume(0.0) {}

Car::Car(const std::string& b, const std::string& c)
    : brand(b), color(c), power(0), engineVolume(0.0) {}

Car::Car(const std::string& b, const std::string& c, int p, double v)
    : brand(b), color(c), power(0), engineVolume(0.0) {
    setPower(p);  
    setEngineVolume(v); 
}

void Car::setPower(int p) {
    if (p <= 0 || p > MAX_POWER) {
        std::ostringstream os;
        os << "Потужність має бути в межах 1.." << MAX_POWER << " к.с., отримано: " << p;
        throw ValueRangeException(os.str());
    }
    power = p;
}

void Car::setEngineVolume(double v) {
    if (v <= 0.0 || v > MAX_VOLUME) {
        std::ostringstream os;
        os << "Об'єм двигуна має бути в межах 0.1.." << MAX_VOLUME << " л, отримано: " << v;
        throw ValueRangeException(os.str());
    }
    engineVolume = v;
}

int Car::getPower() const {
    if (power == 0)
        throw NotInitializedException("Потужність автомобіля ще не встановлена");
    return power;
}

double Car::getEngineVolume() const {
    if (engineVolume == 0.0)
        throw NotInitializedException("Об'єм двигуна автомобіля ще не встановлений");
    return engineVolume;
}

Car& Car::operator+=(int extra) {
    if (power == 0)
        throw NotInitializedException("Неможливо наростити потужність: початкове значення не встановлене");
    if (extra < 0)
        throw ValueRangeException("Приріст потужності не може бути від'ємним");
    if (power + extra > MAX_POWER) 
        throw ValueRangeException("Потужність після нарощування перевищить допустиму межу");
    power += extra;
    return *this;
}

std::istream& operator>>(std::istream& in, Car& c) {
    std::string b, col;
    int p;
    double v;
    if (!(in >> b >> col >> p >> v)) {
        if (!in.eof()) in.clear(std::ios::failbit); 
        throw CarException("Помилка введення: очікується 'марка колір потужність об'єм'");
    }
    Car tmp(b, col, p, v); 
    c = tmp;            
    return in;
}

std::ostream& operator<<(std::ostream& out, const Car& c) {
    out << c.brand << ", " << c.color << ", ";
    if (c.power == 0) out << "потужність: н/в"; else out << c.power << " к.с.";
    out << ", ";
    if (c.engineVolume == 0.0) out << "об'єм: н/в"; else out << c.engineVolume << " л";
    return out;
}

std::vector<int> Car::find(const std::vector<Car>& cars, const std::string& brand) {
    std::vector<int> res;
    for (size_t i = 0; i < cars.size(); ++i)
        if (cars[i].brand == brand) res.push_back((int)i);
    return res;
}

std::vector<int> Car::find(const std::vector<Car>& cars, const std::string& brand,
                           const std::string& color) {
    std::vector<int> res;
    for (size_t i = 0; i < cars.size(); ++i)
        if (cars[i].brand == brand && cars[i].color == color) res.push_back((int)i);
    return res;
}

std::vector<int> Car::find(const std::vector<Car>& cars, int minP, int maxP) {
    if (minP > maxP) throw ValueRangeException("Нижня межа потужності більша за верхню");
    std::vector<int> res;
    for (size_t i = 0; i < cars.size(); ++i)
        if (cars[i].power >= minP && cars[i].power <= maxP && cars[i].power != 0)
            res.push_back((int)i);
    return res;
}

std::vector<int> Car::find(const std::vector<Car>& cars, double minV, double maxV) {
    if (minV > maxV) throw ValueRangeException("Нижня межа об'єму більша за верхню");
    std::vector<int> res;
    for (size_t i = 0; i < cars.size(); ++i)
        if (cars[i].engineVolume >= minV && cars[i].engineVolume <= maxV && cars[i].engineVolume != 0.0)
            res.push_back((int)i);
    return res;
}
