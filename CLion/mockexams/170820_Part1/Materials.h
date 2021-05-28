//
// Created by Thomas Therkelsen on 27-05-2021.
//

#ifndef INC_170820_PART1_MATERIALS_H
#define INC_170820_PART1_MATERIALS_H

#include "TimeAndMaterials.h"

class Materials : public TimeAndMaterials {
public:
    Materials();
    Materials(const std::string& description, double price);

    double getPrice() const override;

    std::string getText() const override;

    void setDescription(const std::string &description);

    void setPrice(double price);
private:
    double _price;
    std::string _description;
};


#endif //INC_170820_PART1_MATERIALS_H
