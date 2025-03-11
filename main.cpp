#include <iostream>
#include"Resolve.h"
#include"Event.h"
#include"Date.h"

//Configurations
const auto FIRST_WEEK_MONDAY = Date{2025, 2, 17};
const std::string TIME_ZONE = "Asia/Shanghai:";
const std::string CLASS_TIME_TABLE[23] = {
        "00000000",//index 0 means nothing
        "08000000", "08450000", "08550000", "09400000",
        "10100000", "10550000", "11050000", "11500000",
        "13450000", "14300000", "14400000", "15250000",
        "15550000", "16400000", "16500000", "17350000",
        "18450000", "19300000", "19400000", "20250000",
        "20350000", "21200000"
};


int main() {
    auto data = resolve();
    std::cout << "[INFO]\t Data Size: " << data.size() << std::endl;
    std::string result;
    //Header
    result += "BEGIN:VCALENDAR\n";
    result += "VERSION:2.0\n";
    result += "PRODID:-//NAME//EN\n";
    result += "CALSCALE:GREGORIAN\n";

    for (auto &row: data) {
        auto event = Event{};
        event.UID = row.course_uid + "@class.com";
        std::vector<std::vector<int>> routines;
        //start,end,all/odd/even(0/1/2)
        {
            auto routine = row.course_routine;

            std::vector<std::string> single_routine;
            {
                std::string temp;
                for (const auto &c: routine) {
                    if (c == ',') {
                        single_routine.push_back(temp);
                        temp.clear();
                    }
                    temp += c;
                }
                single_routine.push_back(temp);
            }

            for (const auto &s: single_routine) {
                int start = -1;
                int end = -1;
                int all_odd_even = 0;
                std::string temp;

                auto pos = s.find("单");
                if (pos != std::string::npos) {
                    all_odd_even = 1;
                }
                pos = s.find("双");
                if (pos != std::string::npos) {
                    all_odd_even = 2;
                }

                //X-X周(X),->
                for (auto c: s) {
                    if (c <= '9' && c >= '0')temp += c;
                    else {
                        if (start == -1) {
                            start = std::stoi(temp);
                            temp.clear();
                        } else if (end == -1) {
                            end = std::stoi(temp);
                            temp.clear();
                        }
                    }
                }

                routines.push_back({start, end, all_odd_even});
            }
        }

        int day_of_week = -1;
        {
            auto pos = row.course_date.find("一");
            if (pos != std::string::npos) {
                day_of_week = 1;
            }
            pos = row.course_date.find("二");
            if (pos != std::string::npos) {
                day_of_week = 2;
            }
            pos = row.course_date.find("三");
            if (pos != std::string::npos) {
                day_of_week = 3;
            }
            pos = row.course_date.find("四");
            if (pos != std::string::npos) {
                day_of_week = 4;
            }
            pos = row.course_date.find("五");
            if (pos != std::string::npos) {
                day_of_week = 5;
            }
            pos = row.course_date.find("六");
            if (pos != std::string::npos) {
                day_of_week = 6;
            }
            pos = row.course_date.find("日");
            if (pos != std::string::npos) {
                day_of_week = 7;
            }
        }

        int start_time = -1;
        {
            std::string temp;
            for (auto c: row.course_start_time) {
                if (c <= '9' && c >= '0') {
                    temp += c;
                }
            }
            start_time = std::stoi(temp);
        }

        int end_time = -1;
        {
            std::string temp;
            for (auto c: row.course_end_time) {
                if (c <= '9' && c >= '0') {
                    temp += c;
                }
            }
            end_time = std::stoi(temp);
        }

        auto teachers = row.course_teachers;

        auto location = row.course_location;

        bool is_lab_course = static_cast<bool>(std::stoi(row.bool_if_lab_course));

        //All data is ready, now we can generate events
        for (const auto &routine: routines) {
            for (int i = routine[0]; i <= routine[1]; ++i) {
                if (routine[2] == 1 && i % 2 == 0)continue;
                if (routine[2] == 2 && i % 2 == 1)continue;

                auto date = FIRST_WEEK_MONDAY;
                date.add_day((i - 1) * 7);
                date.add_day(day_of_week - 1);

                auto start_time_index = start_time;
                auto end_time_index = end_time;

                auto start_TIMESTAMP = TIME_ZONE + date.toTIMESTAMP() + "T" + CLASS_TIME_TABLE[start_time_index];
                auto end_TIMESTAMP = TIME_ZONE + date.toTIMESTAMP() + "T" + CLASS_TIME_TABLE[end_time_index];

                //Construct event
                event.DTSTART = start_TIMESTAMP;
                event.DTEND = end_TIMESTAMP;
                event.SUMMARY = row.course_name;
                event.DESCRIPTION = "Teachers: " + teachers;
                event.LOCATION = location;
                event.CATEGORY = is_lab_course ? "Lab" : "Lecture";

                result += event.serialize();

                //Finish
            }
        }
    }

    //Footer
    result += "END:VCALENDAR\n";

    std::ofstream file("output.ics");
    file << result;
    file.close();
    return 0;
}
