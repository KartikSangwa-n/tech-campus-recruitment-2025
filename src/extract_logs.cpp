#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>  // To run curl
#include <sys/stat.h> // To check if a file exists

using namespace std;

// To check if a file exists
bool fileExists(const string &filename) {
    struct stat buffer;
    return (stat(filename.c_str(), &buffer) == 0);
}

// To download the log file if it's not already present
void downloadLogFile(const string &url, const string &outputFile) {
    if (fileExists(outputFile)) {
        cout << "Log file already exists. Skipping download." << endl;
        return;
    }

    cout << "Downloading log file..." << endl;
    string command = "curl -L -o " + outputFile + " \"" + url + "\"";
    int result = system(command.c_str());

    if (result != 0) {
        cerr << "Error: Failed to download log file!" << endl;
        exit(1);
    }
    cout << "Log file downloaded successfully!" << endl;
}

// It is to extract logs for a given date
void extractLogs(const string &logFile, const string &date, const string &outputFile) {
    ifstream infile(logFile);
    ofstream outfile(outputFile);

    if (!infile) {
        cerr << "Error: Unable to open log file: " << logFile << endl;
        return;
    }
    if (!outfile) {
        cerr << "Error: Unable to create output file: " << outputFile << endl;
        return;
    }

    string line;
    size_t count = 0;  // Count no. of extracted lines
    while (getline(infile, line)) {
        if (line.find(date) == 0) {  // Checks if the line starts with the given date
            outfile << line << "\n";
            count++;
        }
    }

    if (count > 0) {
        cout << "Logs for " << date << " extracted successfully (" << count << " lines)." << endl;
    } else {
        cout << "No logs found for " << date << "." << endl;
    }

    infile.close();
    outfile.close();
}

int main(int argc, char *argv[]) {
    // Validate input
    if (argc != 2) {
        cerr << "Usage: ./extract_logs YYYY-MM-DD" << endl;
        return 1;
    }

    string date = argv[1];
    string logFile = "test_logs.log";
    string outputFile = "output/output_" + date + ".txt";
    string downloadURL = "https://limewire.com/d/90794bb3-6831-4e02-8a59-ffc7f3b8b2a3";

    
    system("mkdir -p output");

    
    downloadLogFile(downloadURL, logFile);

   
    extractLogs(logFile, date, outputFile);

    return 0;
}
