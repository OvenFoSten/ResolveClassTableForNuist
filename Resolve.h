//
// Created by OvenFoSten on 25-3-10.
//

#ifndef RESOLVECLASSTABLE_RESOLVE_H
#define RESOLVECLASSTABLE_RESOLVE_H

#include<string>
#include<vector>
#include<fstream>
#include<sstream>

const int RowDataMembers = 17;
struct RowData {
    std::string course_name;
    [[maybe_unused]]std::string course_uid;
    [[maybe_unused]]std::string course_id;
    std::string course_collage;
    std::string course_credits;
    std::string course_routine;
    std::string course_date;
    std::string course_start_time;
    std::string course_end_time;
    std::string course_teachers;
    std::string course_location;
    [[maybe_unused]]std::string course_type_1;
    [[maybe_unused]]std::string course_type_2;
    [[maybe_unused]]std::string unknown;
    std::string bool_if_lab_course;
    [[maybe_unused]]std::string SFBKK;
    [[maybe_unused]]std::string KCXMMC;
};

std::vector<RowData> resolve() {
    auto file_name = "raw.txt";
    //Read the whole file
    std::ifstream file(file_name);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    std::ostringstream buffer;
    buffer << file.rdbuf();
    std::string data = buffer.str();

    const char *key = "span title=\"";
    size_t key_length = strlen(key);
    std::vector<std::string> row;
    //Suppose data's size less than 2.15GB
    int data_length = static_cast<int>(data.length());
    std::vector<RowData> result;
    for (int s = 0; s < data_length; ++s) {
        bool matched = true;
        for (int i = s; i < data_length && i < s + key_length; ++i) {
            if (data[i] != key[i - s]) {
                matched = false;
                break;
            }
        }
        if (matched) {
            std::string temp;
            for (size_t i = s + key_length; i < data_length; ++i) {
                if (data[i] == '\"')break;
                temp += data[i];
            }
            row.push_back(temp);
            if (row.size() == RowDataMembers) {
                RowData rowData;
                rowData.course_name = row[0];
                rowData.course_uid = row[1];
                rowData.course_id = row[2];
                rowData.course_collage = row[3];
                rowData.course_credits = row[4];
                rowData.course_routine = row[5];
                rowData.course_date = row[6];
                rowData.course_start_time = row[7];
                rowData.course_end_time = row[8];
                rowData.course_teachers = row[9];
                rowData.course_location = row[10];
                rowData.course_type_1 = row[11];
                rowData.course_type_2 = row[12];
                rowData.unknown = row[13];
                rowData.bool_if_lab_course = row[14];
                rowData.SFBKK = row[15];
                rowData.KCXMMC = row[16];
                result.push_back(rowData);
                row.clear();
            }
        }
    }

    return result;
}

#endif //RESOLVECLASSTABLE_RESOLVE_H
