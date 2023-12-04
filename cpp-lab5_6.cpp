#include <bits/stdc++.h>

using namespace std;

const int LNAME=255;
const int LGENDER=10;
const int LRACE=25;
const int LCOUNTRY=60;

const int MAX_COUNTRIES = 200; // Максимальное предполагаемое количество стран

class HUMAN {
    char name[LNAME]{}; // фио
    char gender[LGENDER]{}; // пол
    char race[LRACE]{}; // раса
    int age; // возраст
    char country[LCOUNTRY]{}; // страна
    int iq; // айкью

public:
    HUMAN(); // конструктор без параметров
    HUMAN(char *, char *, char *, int, char *, int); // конструктор с параметрами
    HUMAN(const HUMAN &); // конструктор копирования
    ~HUMAN() = default; // деструктор

    // функции установки поля
    void setName(const char *n) { strcpy(name, n);    }
    void setGender(const char *g) { strcpy(gender, g);    }
    void setRace(const char *r) { strcpy(race, r);    }
    void setAge(int a) { age = a;    }
    void setCountry(const char *c) { strcpy(country, c);    }
    void setIQ(int i) { iq = i;    }

    // функции получения поля
    const char* getName() const { return name; }
    const char* getGender() const { return gender; }
    const char* getRace() const { return race; }
    int getAge() const { return age; }
    const char* getCountry() const { return country; }
    int getIQ() const { return iq; }

    // функции вывода поля
    void printName() {        cout << "Name: " << name << endl;    }
    void printGender() {        cout << "Gender: " << gender << endl;    }
    void printRace() {        cout << "Race: " << race << endl;    }
    void printAge() const {        cout << "Age: " << age << endl;    }
    void printCountry() {        std::cout << "Country: " << country << endl;    }
    void printIQ() const {        cout << "IQ: " << iq << endl;    }
};

HUMAN::HUMAN() {
    strcpy(name, "");
    strcpy(gender, "");
    strcpy(race, "");
    age = 0;
    strcpy(country, "");
    iq = 0;
}

HUMAN::HUMAN(char * NAME, char * GENDER, char * RACE, int AGE, char * COUNTRY, int IQ) {
    strcpy(name,NAME);
    strcpy(gender,GENDER);
    strcpy(race,RACE);
    age=AGE;
    strcpy(country,COUNTRY);
    iq=IQ;
}

HUMAN::HUMAN(const HUMAN & other) {
    strncpy(name, other.name, LNAME);
    strncpy(gender, other.gender, LGENDER);
    strncpy(race, other.race, LRACE);
    age = other.age;
    strncpy(country, other.country, LCOUNTRY);
    iq = other.iq;
}

// среднее значение IQ для конкретной расы
double averageIQForRace(HUMAN humans[], int size, const char* race) {
    double totalIQ = 0;
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (strcmp(humans[i].getRace(), race) == 0) {
            totalIQ += humans[i].getIQ();
            count++;
        }
    }
    return count > 0 ? totalIQ / count : 0;
}


// средний возраст для порога IQ
double averageAgeForIQAbove(HUMAN humans[], int size, int threshold) {
    double totalAge = 0;
    int count = 0;
    for (int i = 0; i < size; i++) {
        if (humans[i].getIQ() > threshold) {
            totalAge += humans[i].getAge();
            count++;
        }
    }
    return count > 0 ? totalAge / count : 0;
}

// Структура для хранения данных по странам
struct CountryStats {
    char country[LCOUNTRY] = "";
    int totalIQ = 0;
    int count = 0;
    double averageIQ = 0;
// To clarify: these are called brace-or-equal-initializers (because you may also use brace initialization instead of equal sign). This is not only for aggregates: you can use this in normal class definitions. This was added in C++11.
    /*CountryStats() : totalIQ(0), count(0), averageIQ(0) {
        strcpy(country, "");
    }*/
};

// Функция для добавления информации о человеке в статистику страны
void addHumanToCountryStats(HUMAN &human, CountryStats stats[], int &numCountries) {
    for (int i = 0; i < numCountries; ++i) {
        if (strcmp(stats[i].country, human.getCountry()) == 0) {
            stats[i].totalIQ += human.getIQ();
            ++stats[i].count;
            return; // выходим
        }
    }
    // Если страна не найдена, добавляем новую запись
    strcpy(stats[numCountries].country, human.getCountry());
    stats[numCountries].totalIQ = human.getIQ();
    stats[numCountries].count = 1;
    numCountries++;
}

// Функция для вычисления среднего IQ каждой страны
void calculateAverageIQ(CountryStats stats[], int numCountries) {
    for (int i = 0; i < numCountries; ++i) {
        if (stats[i].count > 0) {
            stats[i].averageIQ = static_cast<double>(stats[i].totalIQ) / stats[i].count;
        }
    }
}

// Функция сортировки стран по среднему IQ (бабл сортировка)
void sortCountriesByAverageIQ(CountryStats stats[], int numCountries) {
    for (int i = 0; i < numCountries - 1; i++) {
        for (int j = 0; j < numCountries - i - 1; j++) {
            if (stats[j].averageIQ < stats[j + 1].averageIQ) {
                CountryStats temp = stats[j];
                stats[j] = stats[j + 1];
                stats[j + 1] = temp;
            }
        }
    }
}

int main(){
    const auto SIZE = 5;

    HUMAN humans[SIZE];
    humans[0].setName("Aliya Mintemerova");
    humans[0].setGender("Female");
    humans[0].setRace("Tatar");
    humans[0].setAge(18);
    humans[0].setCountry("Russia");
    humans[0].setIQ(177);

    humans[1].setName("John Green");
    humans[1].setGender("Male");
    humans[1].setRace("English");
    humans[1].setAge(30);
    humans[1].setCountry("Russia");
    humans[1].setIQ(140);

    humans[2].setName("Jane Smith");
    humans[2].setGender("Female");
    humans[2].setRace("English");
    humans[2].setAge(25);
    humans[2].setCountry("USA");
    humans[2].setIQ(120);

    humans[3].setName("Mohammed Ali");
    humans[3].setGender("Male");
    humans[3].setRace("Arab");
    humans[3].setAge(22);
    humans[3].setCountry("Saudi Arabia");
    humans[3].setIQ(100);

    humans[4].setName("Maria Ivaniva");
    humans[4].setGender("Female");
    humans[4].setRace("Hispanic");
    humans[4].setAge(35);
    humans[4].setCountry("Mexico");
    humans[4].setIQ(90);

    humans[4].printName();
    humans[4].printGender();
    humans[4].printRace();
    humans[4].printAge();
    humans[4].printCountry();
    humans[4].printIQ();

    char rasa[LRACE]{};
    cout << "Print the race : " << endl;
    cin.getline(rasa, LRACE);

    double avgIQ = averageIQForRace(humans, SIZE, rasa);
    cout << "Average IQ for this race: " << avgIQ << endl;

    cout << "Print N (for average age for IQ above N) : " << endl;

    int N;
    cin >> N;

    double avgAge = averageAgeForIQAbove(humans, SIZE, N);
    cout << "Average age for this threshold: " << avgAge << endl;

    CountryStats countryStats[MAX_COUNTRIES];
    int numCountries = 0;

    // Собираем данные о каждой стране
    for (int i = 0; i < SIZE; ++i) {
        addHumanToCountryStats(humans[i], countryStats, numCountries);
    }

    // Вычисляем средний IQ для каждой страны
    calculateAverageIQ(countryStats, numCountries);

    // Сортируем страны по среднему IQ
    sortCountriesByAverageIQ(countryStats, numCountries);

    // Вывод отсортированного списка стран
    for (int i = 0; i < numCountries; ++i) {
        cout << "Country: " << countryStats[i].country << ", Average IQ: " << countryStats[i].averageIQ << endl;
    }

    return 0;
}