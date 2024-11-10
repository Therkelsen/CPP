#include <iostream>
#include <unordered_map>
#include <sstream>
#include <algorithm>
#include <string>
#include <utility>

std::pair<std::string, int> most_frequently_occurring_word(const std::string& str) {
    std::istringstream ss{str};
    std::string line;
    std::unordered_map<std::string, int> map;

    while (ss >> line) {
        // Remove trailing punctuation if present
        if (line.back() == ',' || line.back() == '.') {
            line.pop_back();
        }
        
        // Convert to lowercase
        std::transform(line.begin(), line.end(), line.begin(), ::tolower);

        // Update frequency map
        map[line]++;
    }

    // Find the word with the highest frequency
    std::string most_frequently_occurring_word;
    int maximum_frequency = 0;
    for (const auto& pair : map) {
        if (pair.second > maximum_frequency) {
            maximum_frequency = pair.second;
            most_frequently_occurring_word = pair.first;
        }
    }

    return {most_frequently_occurring_word, maximum_frequency};
}

int main() {
    std::string str = "The cattle were running back and forth, but there was no wolf to be seen, heard, or smelled, "
                      "so the shepherd decided to take a little nap in a bed of grass and early summer flowers. "
                      "Soon he was awakened by a sound he had never heard before.";

    std::pair<std::string, int> res = most_frequently_occurring_word(str);

    std::cout << "The most common word in the string:\n" << str << "\nIs \""
    << res.first << "\" which appears " << res.second << " times." << std::endl;
}
