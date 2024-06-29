#ifndef A2_SIMPLENAVIGATOR_SRC_S21_DICTIONARY_H_
#define A2_SIMPLENAVIGATOR_SRC_S21_DICTIONARY_H_

#include <fstream>
#include <string>
#include <unordered_map>

#include "libs/nlohmann/json.hpp"

namespace s21 {

class Dictionary {
 public:
  Dictionary(const std::string& language) { LoadLanguage(language); }

  void LoadLanguage(const std::string& language) {
    std::ifstream file("language/" + language + ".json");
    if (file.is_open()) {
      messages_.clear();
      nlohmann::json j;
      file >> j;
      for (auto& [key, value] : j.items()) {
        messages_[key] = value;
      }
    }
  }

  std::string GetMessage(const std::string& key) const {
    auto it = messages_.find(key);
    if (it != messages_.end()) {
      return it->second;
    }
    return "Unknown message... / Неизвестное сообщение...";
  }

 private:
  std::unordered_map<std::string, std::string> messages_;
};

}  // namespace s21

#endif  // A2_SIMPLENAVIGATOR_SRC_S21_DICTIONARY_H_
