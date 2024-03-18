#include <iostream>
#include <fstream>
#include <string>

const int MAX_WORDS = 1000;

class TranslatorDictionary {
private:
    std::string englishWords[MAX_WORDS];
    std::string russianWords[MAX_WORDS];
    int wordCount;

public:
    TranslatorDictionary() : wordCount(0) {}

    ~TranslatorDictionary() {}

    void addWord(const std::string& english, const std::string& russian) {
        if (wordCount < MAX_WORDS) {
            englishWords[wordCount] = english;
            russianWords[wordCount] = russian;
            wordCount++;
        }
    }

    void editTranslation(const std::string& english, const std::string& newRussian) {
        for (int i = 0; i < wordCount; ++i) {
            if (englishWords[i] == english) {
                russianWords[i] = newRussian;
                return;
            }
        }
    }

    std::string getTranslation(const std::string& english) {
        for (int i = 0; i < wordCount; ++i) {
            if (englishWords[i] == english) {
                return russianWords[i];
            }
        }
        return "Translation not found";
    }

    bool containsWord(const std::string& english) {
        for (int i = 0; i < wordCount; ++i) {
            if (englishWords[i] == english) {
                return true;
            }
        }
        return false;
    }

    int getWordCount() {
        return wordCount;
    }

    void saveToFile(const std::string& filename) {
        std::ofstream file(filename);
        if (file.is_open()) {
            for (int i = 0; i < wordCount; ++i) {
                file << englishWords[i] << " : " << russianWords[i] << std::endl;
            }
            file.close();
        }
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (file.is_open()) {
            std::string english, russian;
            while (file >> english >> russian && wordCount < MAX_WORDS) {
                addWord(english, russian);
            }
            file.close();
        }
    }
};

int main() {
    TranslatorDictionary dictionary;

    dictionary.addWord("apple", "€блоко");
    dictionary.addWord("orange", "апельсин");
    dictionary.addWord("banana", "банан");

    std::cout << "Translation of 'orange': " << dictionary.getTranslation("orange") << std::endl;

    dictionary.editTranslation("orange", "оранжевый");

    std::cout << "'orange' is " << (dictionary.containsWord("orange") ? "present" : "not present") << " in the dictionary." << std::endl;

    std::cout << "Number of words in dictionary: " << dictionary.getWordCount() << std::endl;

    dictionary.saveToFile("dictionary.txt");

    dictionary.loadFromFile("dictionary.txt");

    return 0;
}