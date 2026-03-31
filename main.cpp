/*
 * ============================================================
 *         FILE MANAGEMENT TOOL — C++ Application
 *   Demonstrates: Read, Write, Append & Advanced File Ops
 * ============================================================
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <iomanip>
#include <ctime>

// ─────────────────────────────────────────────
//  UTILITY: Get current timestamp as string
// ─────────────────────────────────────────────
std::string getCurrentTimestamp() {
    std::time_t now = std::time(nullptr);
    char buf[64];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buf);
}

// ─────────────────────────────────────────────
//  UTILITY: Print a styled section header
// ─────────────────────────────────────────────
void printHeader(const std::string& title) {
    std::cout << "\n" << std::string(55, '=') << "\n";
    std::cout << "  " << title << "\n";
    std::cout << std::string(55, '=') << "\n";
}

// ─────────────────────────────────────────────
//  FEATURE 1: WRITE to a file (overwrites)
// ─────────────────────────────────────────────
bool writeFile(const std::string& filename, const std::string& content) {
    std::ofstream outFile(filename);           // std::ios::out by default (overwrites)
    if (!outFile.is_open()) {
        std::cerr << "  [ERROR] Cannot open file for writing: " << filename << "\n";
        return false;
    }
    outFile << content;
    outFile.close();
    std::cout << "  [SUCCESS] Data written to \"" << filename << "\"\n";
    return true;
}

// ─────────────────────────────────────────────
//  FEATURE 2: READ from a file (full content)
// ─────────────────────────────────────────────
bool readFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "  [ERROR] Cannot open file for reading: " << filename << "\n";
        return false;
    }

    std::cout << "  [CONTENT of \"" << filename << "\"]\n";
    std::cout << "  " << std::string(50, '-') << "\n";

    std::string line;
    int lineNum = 1;
    while (std::getline(inFile, line)) {
        std::cout << "  " << std::setw(3) << lineNum++ << " | " << line << "\n";
    }

    std::cout << "  " << std::string(50, '-') << "\n";
    inFile.close();
    return true;
}

// ─────────────────────────────────────────────
//  FEATURE 3: APPEND data to a file
// ─────────────────────────────────────────────
bool appendFile(const std::string& filename, const std::string& content) {
    std::ofstream outFile(filename, std::ios::app);   // Open in append mode
    if (!outFile.is_open()) {
        std::cerr << "  [ERROR] Cannot open file for appending: " << filename << "\n";
        return false;
    }
    outFile << content;
    outFile.close();
    std::cout << "  [SUCCESS] Data appended to \"" << filename << "\"\n";
    return true;
}

// ─────────────────────────────────────────────
//  FEATURE 4: READ file line-by-line into vector
// ─────────────────────────────────────────────
std::vector<std::string> readLines(const std::string& filename) {
    std::vector<std::string> lines;
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "  [ERROR] Cannot open file: " << filename << "\n";
        return lines;
    }
    std::string line;
    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }
    inFile.close();
    return lines;
}

// ─────────────────────────────────────────────
//  FEATURE 5: SEARCH for a keyword in a file
// ─────────────────────────────────────────────
void searchInFile(const std::string& filename, const std::string& keyword) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "  [ERROR] Cannot open file: " << filename << "\n";
        return;
    }

    std::cout << "  Searching for \"" << keyword << "\" in \"" << filename << "\"...\n";
    std::string line;
    int lineNum = 1, found = 0;
    while (std::getline(inFile, line)) {
        if (line.find(keyword) != std::string::npos) {
            std::cout << "  [FOUND] Line " << lineNum << ": " << line << "\n";
            found++;
        }
        lineNum++;
    }
    if (found == 0)
        std::cout << "  [INFO] Keyword not found.\n";
    else
        std::cout << "  [TOTAL] " << found << " match(es) found.\n";

    inFile.close();
}

// ─────────────────────────────────────────────
//  FEATURE 6: COUNT lines, words, characters
// ─────────────────────────────────────────────
void fileStats(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile.is_open()) {
        std::cerr << "  [ERROR] Cannot open file: " << filename << "\n";
        return;
    }

    int lines = 0, words = 0, chars = 0;
    std::string line;
    while (std::getline(inFile, line)) {
        lines++;
        chars += (int)line.length() + 1;   // +1 for newline
        std::istringstream iss(line);
        std::string word;
        while (iss >> word) words++;
    }
    inFile.close();

    std::cout << "  [STATS for \"" << filename << "\"]\n";
    std::cout << "    Lines      : " << lines << "\n";
    std::cout << "    Words      : " << words << "\n";
    std::cout << "    Characters : " << chars << "\n";
}

// ─────────────────────────────────────────────
//  FEATURE 7: COPY one file to another
// ─────────────────────────────────────────────
bool copyFile(const std::string& src, const std::string& dest) {
    std::ifstream inFile(src, std::ios::binary);
    std::ofstream outFile(dest, std::ios::binary);

    if (!inFile.is_open()) {
        std::cerr << "  [ERROR] Cannot open source file: " << src << "\n";
        return false;
    }
    if (!outFile.is_open()) {
        std::cerr << "  [ERROR] Cannot open destination file: " << dest << "\n";
        return false;
    }

    outFile << inFile.rdbuf();   // Stream buffer copy (efficient)
    std::cout << "  [SUCCESS] \"" << src << "\" copied to \"" << dest << "\"\n";
    return true;
}

// ─────────────────────────────────────────────
//  FEATURE 8: Structured STUDENT RECORD logger
// ─────────────────────────────────────────────
struct Student {
    std::string name;
    int         rollNo;
    float       gpa;
};

void writeStudentRecords(const std::string& filename, const std::vector<Student>& students) {
    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "  [ERROR] Cannot open file: " << filename << "\n";
        return;
    }
    outFile << std::left
            << std::setw(20) << "Name"
            << std::setw(10) << "Roll No"
            << std::setw(8)  << "GPA"
            << "\n";
    outFile << std::string(38, '-') << "\n";

    for (const auto& s : students) {
        outFile << std::left
                << std::setw(20) << s.name
                << std::setw(10) << s.rollNo
                << std::setw(8)  << std::fixed << std::setprecision(2) << s.gpa
                << "\n";
    }
    outFile.close();
    std::cout << "  [SUCCESS] Student records saved to \"" << filename << "\"\n";
}

// ─────────────────────────────────────────────
//  INTERACTIVE MENU
// ─────────────────────────────────────────────
void showMenu() {
    std::cout << "\n" << std::string(55, '*') << "\n";
    std::cout << "         FILE MANAGEMENT TOOL — MAIN MENU\n";
    std::cout << std::string(55, '*') << "\n";
    std::cout << "  1. Write to a file\n";
    std::cout << "  2. Read a file\n";
    std::cout << "  3. Append to a file\n";
    std::cout << "  4. Search keyword in file\n";
    std::cout << "  5. Show file statistics\n";
    std::cout << "  6. Copy a file\n";
    std::cout << "  7. Exit\n";
    std::cout << std::string(55, '*') << "\n";
    std::cout << "  Enter your choice: ";
}

void runInteractiveMode() {
    int choice;
    std::string filename, content, keyword, dest;

    while (true) {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                std::cout << "  Filename: "; std::getline(std::cin, filename);
                std::cout << "  Enter content (end with a line containing just '###'):\n";
                content.clear();
                while (true) {
                    std::string ln;
                    std::getline(std::cin, ln);
                    if (ln == "###") break;
                    content += ln + "\n";
                }
                writeFile(filename, content);
                break;

            case 2:
                std::cout << "  Filename: "; std::getline(std::cin, filename);
                readFile(filename);
                break;

            case 3:
                std::cout << "  Filename: "; std::getline(std::cin, filename);
                std::cout << "  Text to append: "; std::getline(std::cin, content);
                appendFile(filename, content + "\n");
                break;

            case 4:
                std::cout << "  Filename: "; std::getline(std::cin, filename);
                std::cout << "  Keyword : "; std::getline(std::cin, keyword);
                searchInFile(filename, keyword);
                break;

            case 5:
                std::cout << "  Filename: "; std::getline(std::cin, filename);
                fileStats(filename);
                break;

            case 6:
                std::cout << "  Source file     : "; std::getline(std::cin, filename);
                std::cout << "  Destination file: "; std::getline(std::cin, dest);
                copyFile(filename, dest);
                break;

            case 7:
                std::cout << "\n  Goodbye! All files have been saved.\n\n";
                return;

            default:
                std::cout << "  [WARN] Invalid choice. Try again.\n";
        }
    }
}

// ─────────────────────────────────────────────
//  DEMO MODE (runs automatically on launch)
// ─────────────────────────────────────────────
void runDemo() {
    const std::string demoFile    = "demo_notes.txt";
    const std::string logFile     = "activity_log.txt";
    const std::string studentFile = "students.txt";
    const std::string backupFile  = "demo_notes_backup.txt";

    // ── WRITE ──────────────────────────────────
    printHeader("DEMO 1: WRITE FILE");
    std::string noteContent =
        "File Management Tool — Demo\n"
        "============================\n"
        "Date   : " + getCurrentTimestamp() + "\n"
        "Author : C++ File Handler\n\n"
        "This file was created using std::ofstream.\n"
        "C++ provides powerful file I/O through the <fstream> library.\n";
    writeFile(demoFile, noteContent);

    // ── READ ───────────────────────────────────
    printHeader("DEMO 2: READ FILE");
    readFile(demoFile);

    // ── APPEND ─────────────────────────────────
    printHeader("DEMO 3: APPEND TO FILE");
    std::string appendContent =
        "\n[APPENDED @ " + getCurrentTimestamp() + "]\n"
        "This line was added using std::ios::app flag.\n"
        "Appending never overwrites existing content!\n";
    appendFile(demoFile, appendContent);
    readFile(demoFile);

    // ── SEARCH ─────────────────────────────────
    printHeader("DEMO 4: SEARCH KEYWORD");
    searchInFile(demoFile, "append");

    // ── STATS ──────────────────────────────────
    printHeader("DEMO 5: FILE STATISTICS");
    fileStats(demoFile);

    // ── COPY ───────────────────────────────────
    printHeader("DEMO 6: COPY FILE");
    copyFile(demoFile, backupFile);

    // ── ACTIVITY LOG ───────────────────────────
    printHeader("DEMO 7: ACTIVITY LOG (Timestamped Append)");
    std::vector<std::string> events = {
        "Application started",
        "File 'demo_notes.txt' created",
        "Data appended to 'demo_notes.txt'",
        "Keyword search completed",
        "File statistics generated",
        "Backup created: 'demo_notes_backup.txt'"
    };
    writeFile(logFile, "[ACTIVITY LOG]\n");
    for (const auto& e : events) {
        appendFile(logFile, "[" + getCurrentTimestamp() + "] " + e + "\n");
    }
    readFile(logFile);

    // ── STUDENT RECORDS ────────────────────────
    printHeader("DEMO 8: STRUCTURED STUDENT RECORDS");
    std::vector<Student> students = {
        {"Alice Johnson",  101, 3.95f},
        {"Bob Martinez",   102, 3.72f},
        {"Carol Williams", 103, 3.88f},
        {"David Lee",      104, 3.61f},
        {"Eva Chen",       105, 4.00f}
    };
    writeStudentRecords(studentFile, students);
    readFile(studentFile);

    std::cout << "\n  [DEMO COMPLETE] Files created: "
              << demoFile << ", " << logFile << ", "
              << studentFile << ", " << backupFile << "\n";
}

// ─────────────────────────────────────────────
//  MAIN ENTRY POINT
// ─────────────────────────────────────────────
int main() {
    std::cout << "\n";
    std::cout << "  ╔═══════════════════════════════════════════════════╗\n";
    std::cout << "  ║         C++ FILE MANAGEMENT TOOL v1.0             ║\n";
    std::cout << "  ║   Read | Write | Append | Search | Copy | Stats   ║\n";
    std::cout << "  ╚═══════════════════════════════════════════════════╝\n";

    std::cout << "\n  Choose mode:\n";
    std::cout << "    [1] Run Automated Demo\n";
    std::cout << "    [2] Interactive Mode\n";
    std::cout << "  Enter choice: ";

    int mode;
    std::cin >> mode;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (mode == 1) {
        runDemo();
    } else if (mode == 2) {
        runInteractiveMode();
    } else {
        std::cout << "  Invalid choice. Running demo by default...\n";
        runDemo();
    }

    return 0;
}
