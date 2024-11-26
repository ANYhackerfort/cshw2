// WordCount.cpp

#include "WordCount.h"

using namespace std;

// Default constructor
WordCount::WordCount() {}

// Simple hash function. Do not modify.
size_t WordCount::hash(std::string word) const {
	size_t accumulator = 0;
	for (size_t i = 0; i < word.size(); i++) {
		accumulator += word.at(i);
	}
	return accumulator % CAPACITY;
}

int WordCount::getTotalWords() const {
	int totalWords = 0;
	for (size_t i = 0; i < CAPACITY; i++) {
		 for (const std::pair<std::string, int>& pair : table[i]) {
            totalWords += pair.second; 
        }
	}
	return totalWords;
}

int WordCount::getNumUniqueWords() const {
    int uniqueWords = 0;
    for (const auto& pairs : table) { 
        uniqueWords += pairs.size(); 
    }
    return uniqueWords;
}

int WordCount::getWordCount(std::string word) const {
	std::string validWord = makeValidWord(word);
	if (validWord.size() == 0) {
		return 0;
	}
	size_t bucketIndex = hash(validWord);
	for (const std::pair<std::string, int>& pair : table[bucketIndex]) {
		if (pair.first == validWord) {
			return pair.second; 
		}
	}
	return 0; 
}
	
int WordCount::incrWordCount(std::string word) {
	std::string validWord = makeValidWord(word);
	if (validWord.size() == 0) { //possible edgecase
		return 0; 
	}

	size_t arrayIndex = hash(validWord);
	for (std::pair<std::string, int>& pair: table[arrayIndex]) {
        if (pair.first == validWord) {
            pair.second += 1;   
            return pair.second;  
        }
    }

	//else not found
	table[arrayIndex].emplace_back(validWord, 1); 

	return 1;
}

int WordCount::decrWordCount(std::string word) {
	std::string validWord = makeValidWord(word);
	if (validWord.size() == 0) { //edge case
		return -1; //not found
	}

	size_t arrayIndex = hash(validWord);
    for (auto iterator = table[arrayIndex].begin(); iterator != table[arrayIndex].end(); iterator++) {
        if (iterator->first == validWord) {
            if (iterator->second > 1) {
                iterator->second -= 1;
                return iterator->second;
            } else {
                table[arrayIndex].erase(iterator); // Remove if count is 1
                return 0;
            }
        }
    }
	//else not found
	return -1;
}

bool WordCount::isWordChar(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

std::string WordCount::makeValidWord(std::string word) {
	std::string validWord; 
	int start = 0;

	if (word.size() == 0) {
		return validWord;
	}

	for (size_t i = 0; i < word.size(); i++) {
		if (isWordChar(word[i])) {
			break;
		} else {
			start++; 
		}
	} 

	int end = word.size() - 1; 
	for (int i = word.size() - 1; i >= 0; i--) {
		if (isWordChar(word[i])) {
			break;
		} else {
			end--; 
		}
	} 

	if (start > end) {
		return validWord; //no word essentially
	}

	for (int i = start; i <= end; i++) {
		if (isWordChar(word[i])) {
            validWord += std::tolower(word[i]); 
        } else if ((word[i] == '-' || word[i] == '\'') && isWordChar(word[i-1]) && isWordChar(word[i+1])) {
            validWord += word[i]; 
        }
	}
	return validWord; 
}

void WordCount::dumpWordsSortedByWord(std::ostream &out) const {
	std::vector<std::pair<std::string, int>> wordCounts;
	for (int i = 0; i < 100; i++) {
		for (std::size_t j = 0; j < table[i].size(); j++) {
			wordCounts.push_back(table[i][j]); 
		}
	}

	auto compareByWordAscending = [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.first < b.first; // Ascending order by word
    };

	std::sort(wordCounts.begin(), wordCounts.end(), compareByWordAscending);

	for (const auto &pair : wordCounts) {
        out << pair.first << "," << pair.second << "\n";
    }
}

void WordCount::dumpWordsSortedByOccurence(std::ostream &out) const {
	std::vector<std::pair<std::string, int>> wordCounts;
	for (int i = 0; i < 100; i++) {
		for (std::size_t j = 0; j < table[i].size(); j++) {
			wordCounts.push_back(table[i][j]); 
		}
	}
	
	auto compareByWordAscending = [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        if (a.second == b.second) {
            return a.first < b.first; 
        }
        return a.second < b.second; 
    };

	std::sort(wordCounts.begin(), wordCounts.end(), compareByWordAscending);

	for (const auto &pair : wordCounts) {
        out << pair.first << "," << pair.second << "\n";
    }
}

void WordCount::addAllWords(std::string text) {
	std::string addingWord;
	for (std::size_t i = 0; i < text.size(); i++) {
		if (!std::isspace(text[i])) {
			addingWord.push_back(text[i]);
		} else {
			if (!addingWord.empty()) { 
                incrWordCount(addingWord); 
                addingWord.clear();       
            }
		}
	}

	if (!addingWord.empty()) { // Edge case for last character is not a space 
        incrWordCount(addingWord);
    }
}
