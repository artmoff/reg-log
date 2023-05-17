#include <iostream>
#include <fstream>
#include <string>


const std::string USERS_FILE = "users.txt";

// Есть ли пользователь в бд
bool doesUserExist(const std::string& username) {
    std::ifstream file(USERS_FILE);
    std::string line;
    while (getline(file, line)) {
        if (line.substr(0, line.find(',')) == username) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// Регистрация
void registerUser() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;

    // Есть ли такое имя пользователя
    if (doesUserExist(username)) {
        std::cout << "Username already exists. Registration failed." << std::endl;
        return;
    }

    std::cout << "Enter password: ";
    std::cin >> password;

    // Запись пользователя в файл
    std::ofstream file(USERS_FILE, std::ios::app);
    file << username << "," << password << std::endl;
    file.close();

    std::cout << "Registration successful!" << std::endl;
}

// Вход
void loginUser() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;

    // Проверка сходства имени и пароля
    std::ifstream file(USERS_FILE);
    std::string line;
    while (getline(file, line)) {
        std::string storedUsername = line.substr(0, line.find(','));
        std::string storedPassword = line.substr(line.find(',') + 1);
        if (storedUsername == username && storedPassword == password) {
            file.close();
            std::cout << "Login successful!" << std::endl;
            return;
        }
    }
    file.close();

    std::cout << "Invalid username or password. Login failed." << std::endl;
}

int main() {
    int choice;
    bool exitProgram = false;

    while (!exitProgram) {
        std::cout << "1. Register" << std::endl;
        std::cout << "2. Login" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            registerUser();
            break;
        case 2:
            loginUser();
            break;
        case 3:
            exitProgram = true;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
        std::cout << std::endl;
    }

    return 0;
}