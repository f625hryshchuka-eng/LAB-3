#include "Car.h"
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

void printResult(const vector<Car>& cars, const vector<int>& idx) {
    if (idx.empty()) { cout << "  Нічого не знайдено\n"; return; }
    for (int i : idx) cout << "  [" << i << "] " << cars[i] << endl;
}

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    vector<Car> cars;

    cout << "=== 1. Введення (operator>>) ===\n";
    istringstream data("Toyota red 150 1.8\n"
        "BMW black 249 3.0\n"
        "Skoda white 110 1.6\n"
        "BMW white 184 2.0\n");
    for (int i = 0; i < 4; ++i) {
        Car c;
        try { data >> c; cars.push_back(c); }
        catch (const CarException& e) { cout << "Помилка: " << e.what() << endl; }
    }
    for (const Car& c : cars) cout << c << endl;

    cout << "\n=== 2. Нарощування потужності (+=) ===\n";
    try {
        cars[0] += 20;
        cout << "Після Toyota += 20: " << cars[0] << endl;
        cars[1] += 5000; 
    }
    catch (const ValueRangeException& e) { cout << "[ValueRange] " << e.what() << endl; }
    catch (const NotInitializedException& e) { cout << "[NotInit] " << e.what() << endl; }
    catch (const CarException& e) { cout << "[Car] " << e.what() << endl; }


    cout << "\n=== 3. Пошук ===\n";
    cout << "За маркою BMW:\n";                 printResult(cars, Car::find(cars, "BMW"));
    cout << "За маркою BMW і кольором white:\n"; printResult(cars, Car::find(cars, "BMW", "white"));
    cout << "За потужністю 100..160 к.с.:\n";    printResult(cars, Car::find(cars, 100, 160));
    cout << "За об'ємом 1.5..2.0 л:\n";          printResult(cars, Car::find(cars, 1.5, 2.0));

    cout << "\n=== 4. Виняткові ситуації ===\n";
    try {
        Car c("Audi", "grey");
        c.setPower(-50);
    }
    catch (const ValueRangeException& e) { cout << "[ValueRange] " << e.what() << endl; }

    try { 
        Car c("Audi", "grey");
        cout << c.getPower() << endl;
    }
    catch (const NotInitializedException& e) { cout << "[NotInit] " << e.what() << endl; }

    try {
        Car c("Fiat", "blue", 100, 25.0);
    }
    catch (const CarException& e) { cout << "[Car] " << e.what() << endl; }

    try { 
        istringstream bad("Opel green abc 1.4");
        Car c; bad >> c;
    }
    catch (const CarException& e) { cout << "[Car] " << e.what() << endl; }

    try {    
        try { Car::find(cars, 300, 100); }
        catch (const CarException& e) {
            cout << "[внутрішній обробник] " << e.what() << endl;
            throw;
        }
    }
    catch (const exception& e) { cout << "[зовнішній обробник] " << e.what() << endl; }

    cout << "\n=== 5. Введіть авто (марка колір потужність об'єм): ";
    Car user;
    try {
        if (cin >> user) { cars.push_back(user); cout << "Додано: " << user << endl; }
    }
    catch (const CarException& e) { cout << "Помилка: " << e.what() << endl; }

    return 0;
}
