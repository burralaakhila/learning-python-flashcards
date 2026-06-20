#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>

// Helper function to trim spaces and convert a string to lowercase
std::string cleanString(std::string str) {
    // Trim leading whitespace
    str.erase(0, str.find_first_not_of(" \t\r\n"));
    // Trim trailing whitespace
    str.erase(str.find_last_not_of(" \t\r\n") + 1);
    // Convert to lowercase
    for (char &c : str) {
        c = std::tolower(c);
    }
    return str;
}

int main() {
    // 1. Setup our flashcard data using std::map (Key: Value)
    std::map<std::string, std::string> flashcards = {
        {"What is the keyword to define a function in Python?", "def"},
        {"Which data structure is ordered and changeable (mutable)?", "list"},
        {"Which data structure stores data in key-value pairs?", "dictionary"},
        {"What built-in function returns the number of items in an object?", "len"},
        {"What data type holds True or False values?", "boolean"}
    };

    std::cout << "=== Welcome to the Python Basics Flashcard Quiz! ===\n";
    std::cout << "Type your answer and press Enter. (Answers are case-insensitive)\n\n";

    int score = 0;

    // 2. Move map items into a vector so we can shuffle them
    std::vector<std::pair<std::string, std::string>> card_list(flashcards.begin(), flashcards.end());
    
    // Seed and shuffle using a random engine
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(card_list.begin(), card_list.end(), std::default_random_engine(seed));

    // 3. Loop through each flashcard
    for (const auto& card : card_list) {
        std::string question = card.first;
        std::string correct_answer = card.second;

        std::cout << "Question: " << question << "\n";
        std::cout << "Your Answer: ";
        
        std::string user_answer;
        std::getline(std::cin, user_answer); // Using getline to catch full multi-word responses if needed

        // 4. Check the user's answer using our helper function
        if (cleanString(user_answer) == cleanString(correct_answer)) {
            std::cout << "Correct!\n\n";
            score++;
        } else {
            std::cout << "Wrong. The correct answer was: '" << correct_answer << "'\n\n";
        }
    }

    // 5. Final Score Breakdown
    double total_cards = flashcards.size();
    int success_rate = static_cast<int>((score / total_cards) * 100);

    std::cout << "=========================================\n";
    std::cout << "Quiz Complete! Your Final Score: " << score << "/" << total_cards << "\n";
    std::cout << "Success Rate: " << success_rate << "%\n";
    std::cout << "=========================================\n";

    return 0;
}
