//
// Created by Thomas Therkelsen on 28-05-2021.
//

#ifndef INC_170820_PART1_TIMESHEET_H
#define INC_170820_PART1_TIMESHEET_H

#include "TimeAndMaterials.h"
#include <vector>
class TimeSheet : public TimeAndMaterials {
public:
    TimeSheet();
    virtual ~TimeSheet();
    void addTimeAndMaterial(TimeAndMaterials* tm);
    void sortByType();
    friend std::ostream& operator<<(std::ostream& ost, const TimeAndMaterials& tam);
private:
    std::vector<TimeAndMaterials*> mItems;

    double getPrice() const;

    std::string getText() const;
};

std::ostream& operator<<(std::ostream& ost, const TimeAndMaterials& tam);

#endif //INC_170820_PART1_TIMESHEET_H
