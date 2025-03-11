//
// Created by OvenFoSten on 25-3-10.
//

#ifndef RESOLVECLASSTABLE_EVENT_H
#define RESOLVECLASSTABLE_EVENT_H

#include<string>


struct Event{
    std::string UID;
    std::string DTSTART;
    std::string DTEND;
    std::string SUMMARY;
    std::string DESCRIPTION;
    std::string LOCATION;
    std::string CATEGORY;

    std::string serialize() const {
        std::string result = "BEGIN:VEVENT\r\n";
        result += "UID:" + UID + "\r\n";
        result += "DTSTAMP:19900101T000000Z\r\n";
        result += "DTSTART;" + DTSTART + "\r\n";
        result += "DTEND;" + DTEND + "\r\n";
        result += "SUMMARY:" + SUMMARY + "\r\n";
        result += "DESCRIPTION:" + DESCRIPTION + "\r\n";
        result += "LOCATION:" + LOCATION + "\r\n";
        result += "CATEGORIES:" + CATEGORY + "\r\n";
        result += "END:VEVENT\r\n";
        return result;
    }
};

#endif //RESOLVECLASSTABLE_EVENT_H
