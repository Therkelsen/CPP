#include <iostream>
#include <unordered_map>
#include <sstream>
#include <utility>

std::pair<std::string, int> mostFreqWord(std::string str){
    std::istringstream ss{str};
    std::string line;

    std::unordered_map<std::string, int> map;

    while(std::getline(ss, line, ' ')){
        if(line.at(line.size()-1) == ',' || line.at(line.size()-1) == '.'){
            line.pop_back();
        }
        map[line]++;
    }

    std::string key;
    int value = 0;
    for(const auto& pair: map) {
        if(pair.second > value){
            value = pair.second;
            key = pair.first;
        }
    }

    return {key, value};
}

int main() {
    std::string str = "The cattle were running back and forth, but there was no wolf to be seen, heard, or smelled, "
                      "so the shepherd decided to take a little nap in a bed of grass and early summer flowers. "
                      "Soon he was awakened by a sound he had never heard before.";

    std::pair<std::string, int> res = mostFreqWord(str);

    std::cout << "The most common word in the string:\n" << str << "\nIs \""
    << res.first << "\" which appears " << res.second << " times." << std::endl;
}
