//
// Created by OvenFoSten on 25-3-10.
//

#ifndef RESOLVECLASSTABLE_DATE_H
#define RESOLVECLASSTABLE_DATE_H

#include<string>

const int month_days[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

struct Date {
    int year;
    int month;
    int day;

    bool is_leap_year(int year) {
        return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    }

    void add_day(int n) {
        day += n;
        auto current_days = month_days[month];
        while (day > current_days) {
            if (month == 2 && is_leap_year(year)) {
                current_days = 29;
            }
            day -= current_days;
            month++;
            if (month > 12) {
                month = 1;
                year++;
            }
            current_days = month_days[month];
        }
    }

    std::string toTIMESTAMP() {
        std::string result;
        result += std::to_string(year);
        result += month < 10 ? "0" + std::to_string(month) : std::to_string(month);
        result += day < 10 ? "0" + std::to_string(day) : std::to_string(day);
        return result;
    }
};

#endif //RESOLVECLASSTABLE_DATE_H
