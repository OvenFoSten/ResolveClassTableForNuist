#include <iostream>
#include"Resolve.h"

int main() {
    auto data = resolve();
    for (const auto &i : data) {
        std::cout << i.course_name << std::endl;
        std::cout << i.course_collage << std::endl;
        std::cout << i.course_credits << std::endl;
        std::cout << i.course_routine << std::endl;
        std::cout << i.course_date << std::endl;
        std::cout << i.course_start_time << std::endl;
        std::cout << i.course_end_time << std::endl;
        std::cout << i.course_teachers << std::endl;
        std::cout << i.course_location << std::endl;
        std::cout << i.bool_if_lab_course << std::endl;
        std::cout << "----------------------" << std::endl;
    }
}
