#include <cstdio>
#include <readline/readline.h>
#include <readline/history.h>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

void print_help();
std::vector<std::string> splitAndRemoveQuotes(const std::string& input);
char* c_file = nullptr;

int main() {
    std::cout << "Welcome!" << std::endl;
    print_help();
    sf::Music music;
    while (1) { 
        char* command = readline(">> ");
        // char* c_file = nullptr;
        if (!command) {
            std::cout << std::endl;
            break;
        }

        if (command && *command) {
            add_history(command);
        }

        std::vector<std::string> tokens = splitAndRemoveQuotes(command);

        if (tokens.empty()) {
            free(command);
            continue;
        }

        if (tokens[0] == "help") {
            print_help();
        } else if (tokens[0] == "exit" || tokens[0] == "quit") {
            break;
        } else if (tokens[0] == "load") {
            if (tokens.size() < 2) {
                std::cout << "Usage: load <FILE>" << std::endl;
            } else {
                if (music.openFromFile(tokens[1])) {
                    c_file = strdup(tokens[1].c_str());
                    std::cout << "Loaded " << tokens[1] << std::endl;
                } else {
                    std::cout << "Failed to load " << tokens[1] << std::endl;
                }
            }
        } else if (tokens[0] == "unload") {
            music.stop();
            if (c_file != nullptr) {
                free(c_file);
                c_file = nullptr;
            }
            std::cout << "Unloaded" << std::endl;
        } else if (tokens[0] == "play" || tokens[0] == "unpause") {
            if (music.getStatus() == sf::Music::Status::Stopped) {
                music.play();
            } else if (music.getStatus() == sf::Music::Status::Paused) {
                music.play();
            }
        } else if (tokens[0] == "pause") {
            if (music.getStatus() == sf::Music::Status::Playing) {
                music.pause();
            }
        } else if (tokens[0] == "resume") {
            if (music.getStatus() == sf::Music::Status::Paused) {
                music.play();
            }
        } else if (tokens[0] == "stop") {
            music.stop();
        } else if (tokens[0] == "status") {
            if (music.getStatus() == sf::Music::Status::Playing || music.getStatus() == sf::Music::Status::Paused) {
                if (c_file != nullptr) {
                    std::string filename = c_file;
                    sf::Time currentTime = music.getPlayingOffset();
                    int minutes = currentTime.asSeconds() / 60;
                    int seconds = (int)currentTime.asSeconds() % 60;
                    std::cout << "<" << filename << "> " << minutes << ":" << std::setw(2) << std::setfill('0') << seconds;
                    if (music.getStatus() == sf::Music::Status::Playing) {
                        std::cout << ", Playing";
                    } else {
                        std::cout << ", Paused";
                    }
                    std::cout << std::endl;
                } else {
                    std::cout << "No file loaded" << std::endl;
                }
            } else {
                std::cout << "No file loaded" << std::endl;
            }
        } else {
            std::cout << "Unknown command: " << tokens[0] << std::endl;
        }
        free(command);
    }
    return 0;
}

void print_help() {
    std::cout << "Here are the commands you can use:" << std::endl;
    std::cout << "help\t\tPrints this message" << std::endl;
    std::cout << "load <FILE>\tLoads an audio file" << std::endl;
    std::cout << "unload\t\tUnloads the currently loaded audio file" << std::endl;
    std::cout << "play\t\tPlays theloaded audio file" << std::endl;
    std::cout << "pause\t\tPauses the loaded audio file" << std::endl;
    std::cout << "resume\t\tResumes the loaded audio file" << std::endl;
    std::cout << "stop\t\tStops the loaded audio file" << std::endl;
    std::cout << "status\t\tPrints the status of the loaded audio file" << std::endl;
    std::cout << "exit/quit\tQuits the program" << std::endl << std::endl;
}

std::vector<std::string> splitAndRemoveQuotes(const std::string& input) {
    std::vector<std::string> tokens;
    std::string token;

    std::stringstream ss(input);
    while (ss >> std::quoted(token)) {
        if (!token.empty() && (token.front() == '"' || token.front() == '\'') &&
            token.front() == token.back()) {
            token = token.substr(1, token.size() - 2);
        }
        tokens.push_back(token);
    }

    return tokens;
}