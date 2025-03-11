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
        std::string result = "BEGIN:VEVENT\n";
        result += "UID:" + UID + "\n";
        result += "DTSTAMP:19900101T000000Z\n";
        result += "DTSTART;" + DTSTART + "\n";
        result += "DTEND;" + DTEND + "\n";
        result += "SUMMARY:" + SUMMARY + "\n";
        result += "DESCRIPTION:" + DESCRIPTION + "\n";
        result += "LOCATION:" + LOCATION + "\n";
        result += "CATEGORIES:" + CATEGORY + "\n";
        result += "END:VEVENT\n";
        return result;
    }
};

#endif //RESOLVECLASSTABLE_EVENT_H
