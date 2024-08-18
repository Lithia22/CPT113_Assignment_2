#include <iostream>
#include <fstream>

using namespace std;

// Node structure for the linked list
struct NodeType {
    char info;
    NodeType* link;
};

// Linked List Stack implementation
class linkedListStack {
private:
    NodeType* stackTop;

public:
    linkedListStack();
    ~linkedListStack();
    void push(char item);  // Function to push an item onto the stack
    char top();  // Function to return the top element of the stack
    void pop();  // Function to pop an element from the stack
    bool isEmpty();  // Function to check if the stack is empty
};

linkedListStack::linkedListStack() {
    stackTop = nullptr;
}

linkedListStack::~linkedListStack() {
    while (!isEmpty()) {
        pop();
    }
}

void linkedListStack::push(char item) {
    NodeType* newNode = new NodeType;
    newNode->info = item;
    newNode->link = stackTop;
    stackTop = newNode;
}

char linkedListStack::top() {
    if (!isEmpty()) {
        return stackTop->info;
    } else {
        cerr << "Error: Stack is empty" << endl;
        return char();
    }
}

void linkedListStack::pop() {
    if (!isEmpty()) {
        NodeType* temp = stackTop;
        stackTop = stackTop->link;
        delete temp;
    } else {
        cerr << "Error: Stack is empty" << endl;
    }
}

bool linkedListStack::isEmpty() {
    return stackTop == nullptr;
}

// Linked List Queue implementation
class linkedListQueue {
private:
    NodeType* queueFront;
    NodeType* queueRear;

public:
    linkedListQueue();
    ~linkedListQueue();
    void addQueue(char item);  // Function to add an item to the queue
    char front();  // Function to return the front element of the queue
    void deleteQueue();  // Function to delete the front element of the queue
    bool isEmpty();  // Function to check if the queue is empty
};

linkedListQueue::linkedListQueue() {
    queueFront = queueRear = nullptr;
}

linkedListQueue::~linkedListQueue() {
    while (!isEmpty()) {
        deleteQueue();
    }
}

void linkedListQueue::addQueue(char item) {
    NodeType* newNode = new NodeType;
    newNode->info = item;
    newNode->link = nullptr;

    if (isEmpty()) {
        queueFront = queueRear = newNode;
    } else {
        queueRear->link = newNode;
        queueRear = newNode;
    }
}

char linkedListQueue::front() {
    if (!isEmpty()) {
        return queueFront->info;
    } else {
        cerr << "Error: Queue is empty" << endl;
        return char();
    }
}

void linkedListQueue::deleteQueue() {
    if (!isEmpty()) {
        NodeType* temp = queueFront;
        if (queueFront == queueRear) {
            queueFront = queueRear = nullptr;
        } else {
            queueFront = queueFront->link;
        }
        delete temp;
    } else {
        cerr << "Error: Queue is empty" << endl;
    }
}

bool linkedListQueue::isEmpty() {
    return queueFront == nullptr;
}

class InforXApp {
private:
    string ogText;
    linkedListStack s1; 
    linkedListQueue q1;  

public:
    bool AlphaChecker(char c);  // Function to check if a character is an alphabet

    void reversedWords();  // Function to reverse the characters in words
    void replacedVowels();  // Function to replace vowels with symbols

    bool readInputFromFile(const string& filename);  // Function to read input from a file
    void saveOutputToFile(const string& filename, const string& output);  // Function to save output to a file

    void encrypt();  // Function to perform encryption
    void decrypt();  // Function to perform decryption
};

bool InforXApp::AlphaChecker(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void InforXApp::reversedWords() {
    for (size_t i = 0; i < ogText.size(); ++i) {
        s1.push(ogText[i]);
    }

    ogText.clear();
    while (!s1.isEmpty()) {
        ogText += s1.top();
        s1.pop();
    }
}

void InforXApp::replacedVowels() {
    for (size_t i = 0; i < ogText.size(); ++i) {
        char& c = ogText[i];
        switch (c) {
            case 'a': case 'A': q1.addQueue('*'); break;
            case 'e': case 'E': q1.addQueue('@'); break;
            case 'i': case 'I': q1.addQueue('#'); break;
            case 'o': case 'O': q1.addQueue('$'); break;
            case 'u': case 'U': q1.addQueue('&'); break;
            default: q1.addQueue(c); break;
        }
    }

    ogText.clear();
    while (!q1.isEmpty()) {
        ogText += q1.front();
        q1.deleteQueue();
    }
}

bool InforXApp::readInputFromFile(const string& filename) {
    ifstream inputFile(filename);
    if (inputFile.is_open()) {
        ogText = "";  // Clear previous content
        string line;
        while (getline(inputFile, line)) {
            ogText += line;
            if (!inputFile.eof()) {
                ogText += "\n";  // Add a newline only if it's not the last line
            }
        }
        inputFile.close();
        return true;  // Successfully read the file
    } else {
        cerr << "Error: Unable to open file '" << filename << "'. Please enter a valid filename." << endl;
        return false;  // Unable to open the file
    }
}


void InforXApp::saveOutputToFile(const string& filename, const string& output) {
    ofstream outputFile(filename);
    if (outputFile.is_open()) {
        outputFile << output;
        outputFile.close();
        cout << "Output saved to '" << filename << "'" << endl;
    } else {
        cerr << "Error: Unable to open file '" << filename << "' for saving output" << endl;
    }
}

void InforXApp::encrypt() {
    ogText = "";
    cout << "\nEncryption Tool:" << endl;

    string inputFilename;

    do {
        cout << "Enter the filename to be encrypted with the extension of (.txt): ";
        cin >> inputFilename;
    } while (!readInputFromFile(inputFilename));

    reversedWords();
    replacedVowels();

    system("cls");  // Clear the console screen

    cout << "\nEncrypted text:\n------------------------------------------------------\n" << ogText << "\n------------------------------------------------------\n" << endl;
    // Save the output only if the input file was successfully read
    saveOutputToFile("encrypt_output.txt", ogText);

    cout << "Press Enter to return to the menu...";
    cin.ignore();
    cin.get();
    system("cls");  // Clear the console screen before returning to the menu
}

void InforXApp::decrypt() {
    ogText = "";
    cout << "\nDecryption Tool:" << endl;

    string inputFilename;

    do {
        cout << "Enter the filename to be decrypted or use 'encrypt_output.txt': ";
        cin >> inputFilename;
    } while (!readInputFromFile(inputFilename));

    // Reversing the replacement of vowels
    for (size_t i = 0; i < ogText.size(); ++i) {
        char& c = ogText[i];
        switch (c) {
            case '*': c = 'a'; break;
            case '@': c = 'e'; break;
            case '#': c = 'i'; break;
            case '$': c = 'o'; break;
            case '&': c = 'u'; break;
        }
    }
    // Reversing the reversal of characters in words
    reversedWords();

    system("cls");  // Clear the console screen

    cout << "\nDecrypted text:\n------------------------------------------------------\n" << ogText << "\n------------------------------------------------------\n" << endl;
    // Save the output only if the input file was successfully read
    saveOutputToFile("decrypt_output.txt", ogText);

    cout << "Press Enter to return to the menu...";
    cin.ignore();
    cin.get();
    system("cls");  // Clear the console screen before returning to the menu
}


int getChoice() {
    int choice;
    cout << "Enter your choice: ";

    while (!(cin >> choice) || choice < 1 || choice > 3) {
        cout << "Invalid input. Please enter a valid number (1-3): ";
        cin.clear();
        cin.ignore(256, '\n');  // Clear the input buffer
    }

    return choice;
}

int main() {
    InforXApp inforXApp;
    int choice;

	//Displaying menu
    do {
        cout << "************* InforXApp *************" << endl;
        cout << "1. Encrypt" << endl;
        cout << "2. Decrypt" << endl;
        cout << "3. Exit" << endl;
        cout << "*************************************\n" << endl;
        choice = getChoice();
		
        switch (choice) {
            case 1:
            	cout << "\nInstruction: Make sure the file is in assign2_163850 folder\n" << endl;
                inforXApp.encrypt();
                break;

            case 2:
            	cout << "\nInstruction: Make sure the file is in assign2_163850 folder\n" << endl;
                inforXApp.decrypt();
                break;

            case 3:
                cout << "Exiting program.\n" << endl;
                break;

            default:
                cerr << "Invalid choice. Please enter a valid option.\n" << endl;
        }
    } while (choice != 3);

    return 0;
}

