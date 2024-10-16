#include <iostream>
#include <algorithm>
#include <string>
#include <cmath>
#include <bitset>
#include <unistd.h>
#include <ctime>
#include "header/Image_Class.h"

using namespace std;

// Global variables
Image img_in; // Original image
Image img_filter; // Image to apply filters on
string imginput = "NULL"; // Input image name
string saveindicator = "N"; // Indicator to check if the image is saved

// Function to convert a character to its binary representation
string charToBinary(char c) {
    bitset<8> binary(c);
    return binary.to_string();
}

// Function to convert a string to its binary representation
string str_to_binary() {
    string str, binary = "";
    while (true) {
        cout << "Enter a string: ";
        getline(cin, str);
        // Check if the string length exceeds the limit
        if (str.length() > floor(img_filter.width * img_filter.height * 3 / 8) - 1) {
            cout << "uh-oh seems like we got a limit Harry, hmmm let me see... " << endl;
            sleep(1);
            cout << "we can write up to " << floor(img_filter.width * img_filter.height * 3 / 8) - 1 << " characters." << endl;
            continue;
        } else {
            break;
        }
    }
    // Convert each character to binary and append to the binary string
    for (int i = 0; i < str.length(); i++) {
        binary += charToBinary(str[i]);
    }
    return binary;
}

// Function to convert a binary string to a character
char binary_to_char(const std::string& binary_str) {
    char result = 0;
    for (size_t i = 0; i < 8; i++) {
        result <<= 1;
        result |= binary_str[i] - '0';
    }
    return result;
}

// Function to encrypt a message into the image
void encrypt_image() {
    cout << "Oh you littel devil wizard, you want to encrypt a message in the image? \n";
    cout << "let's do it! \n";
    string binary;
    binary = str_to_binary();
    binary += "00000000"; // Append end marker
    int count = 0;
    int mod, binary_cahr;
    // Iterate through each pixel and channel of the image
    for (int j = 0; j < img_filter.height; j++) {
        for (int i = 0; i < img_filter.width; i++) {
            for (int k = 0; k < 3; k++) {
                binary_cahr = stoi(string(1, binary[count]));
                mod = img_filter(i, j, k) % 10;
                // Adjust the pixel value to embed the binary character
                if (mod <= 5) {
                    img_filter(i, j, k) = img_filter(i, j, k) - mod;
                } else {
                    img_filter(i, j, k) = min(250, img_filter(i, j, k) + (10 - mod));
                }
                img_filter(i, j, k) = img_filter(i, j, k) + binary_cahr;
                count++;
                // Check if the entire binary message is embedded
                if (count == binary.length()) {
                    cout << "Now you have your secret.\n";
                    return;
                }
            }
        }
    }
}

// Function to decrypt a message from the image
string decrypt_image() {
    cout << "Oh you littel devil wizard, you want to decrypt a message from the image? \n";
    cout << "let's do it! \n";
    int binary_bit;
    string binary = "";
    string temp = "";
    char character;
    string final_string = "";
    // Iterate through each pixel and channel of the image
    for (int j = 0; j < img_filter.height; j++) {
        for (int i = 0; i < img_filter.width; i++) {
            for (int k = 0; k < 3; k++) {
                // Check if there is no message to decrypt
                if ((img_filter(i,j,k)%10 > 1 || img_filter(i,j,k)%10 < 0)  && (binary == "" || binary.length() < 8)) {
                    return "Oh looks like there is nothing to decrypt here.";
                }
                binary_bit = img_filter(i, j, k) % 2;
                binary += to_string(binary_bit);
            }
        }
    }
    // Convert the binary string to the original message
    for (size_t i = 0; i < binary.length(); i++) {
        temp += binary[i];
        if (temp.length() == 8) {
            if (temp == "00000000") {
                return final_string;
            } else {
                character = binary_to_char(temp);
                final_string += character;
                temp = "";
            }
        }
    }
    return final_string;
}

// Function to prompt the user to enter an image name with its extension and load the image
int insert() {
    while (true) { // Loop until a valid image is loaded
        cout << "Please enter image name with its extension: ";
        getline(cin,imginput); // Read image name from user input
        try {
            img_in.loadNewImage(imginput); // Attempt to load the image
            break;
        } catch (invalid_argument) { // Catch exception if image loading fails
            continue;
        }
    }
    img_filter = img_in; // Set the filter image to the loaded image
    return 0;
}

// Function to provide options for saving an image
int save(Image img_save) {
    string savechoice;
    while (true) {
        cout << "\n*** How do you want to save your image? ***\n";
        cout << "===========================================\n";
        cout << "A) Save as a new image\n";
        cout << "B) Replace the existing image\n";
        cout << "C) Exit this menu\n";
        cout << "===========================================\n";
        cout << "Enter your choice: ";
        getline(cin, savechoice); // Read user's save choice
        if (savechoice.size() != 1) {
            cout << "Please enter a valid choice" << endl;
            continue;
        }
        transform(savechoice.begin(), savechoice.end(), savechoice.begin(), ::toupper);
        // Process user's save choice
        if (savechoice == "A") {
            string outimg;
            while (true) { // Loop until a valid output image name is provided
                try {
                    cout << "\nPlease enter image name with its extension: ";
                    getline(cin, outimg); // Read output image name from user input
                    img_save.saveImage(outimg); // Save the image with the provided name
                    break;
                } catch (invalid_argument) { // Catch exception if saving fails
                    continue;
                }
            }
            cout << "Image Saved!" << endl;
            return 0;
        } else if (savechoice == "B") {
            while (true) {
                try {
                    img_save.saveImage(imginput); // Replace the existing image with the same name
                    break;
                } catch (invalid_argument) { // Catch exception if saving fails
                    continue;
                }
            }
            cout << "Image Saved!" << endl;
            return 0;
        } else if (savechoice == "C") {
            return 0;
        } else {
            cout << "Please enter a valid choice" << endl;
        }
    }
}

// Function to provide options for applying filters to the image
int filters_menu() {
    string filterschoice;
    while (true) {
        cout << "\n*** Chamber of secrets ***\n";
        cout << "==============================\n";
        cout << "A) Encrypt\n";
        cout << "B) Decrypt\n";
        cout << "==============================\n";
        cout << "Enter your choice: ";
        getline(cin, filterschoice);
        if (filterschoice.size() != 1) {
            cout << "Please enter a valid choice" << endl;
            continue;
        }
        transform(filterschoice.begin(), filterschoice.end(), filterschoice.begin(), ::toupper); // Convert filter choice to uppercase
        if (filterschoice == "A") {
            encrypt_image(); // Call function to encrypt the image
            saveindicator = "N"; // Set save indicator to 'N' after encryption
            return 1;
        }
        if (filterschoice == "B") {
            string decrypted_message = decrypt_image(); // Call function to decrypt the image
            cout << decrypted_message << endl; // Display the decrypted message
            saveindicator = "N"; // Set save indicator to 'N' after decryption
            return 1;
        }
    }
}

// Main function of the program
int main() {
    cout <<  "Hello Mr.Harry potter. \n";
    cout <<  "Welcome to the chamber of secrets. \n";
    string choice; 
    while (true) {
        cout << "\n*** Main Menu ***\n";
        cout << "===================\n";
        cout << "A) Insert image\n";
        cout << "B) The Chamber of secrets\n";
        cout << "C) Save image\n";
        cout << "D) Exit the program\n";
        cout << "===================\n";
        cout << "Enter your choice: ";
        getline(cin, choice);
        if (choice.size() != 1) {
            cout << "Please enter a valid choice" << endl;
            continue;
        }
        transform(choice.begin(), choice.end(), choice.begin(), ::toupper); 
        if (choice == "A") {
            insert(); // Call function to insert an image
            saveindicator = "N"; // Set save indicator to 'N' after inserting an image
            cout << "Image Inserted!" << endl;
        } else if (choice == "B") {
            if (imginput == "NULL") {
                cout << "Please insert an image first! Use option A." << endl;
                continue;
            } else {
                if (filters_menu() == 0) {
                    return 0;
                }
            }
        } else if (choice == "C") {
            if (imginput == "NULL") {
                cout << "Please insert an image first! Use option A." << endl;
                continue;
            } else {
                save(img_filter); // Call function to save the image
                saveindicator = "Y"; // Set save indicator to 'Y' after saving the image
            }
        } else if (choice == "D") {
            string exit_choice;
            if (imginput == "NULL") {
                return 0;
            } else if (saveindicator == "N") {
                while (true) {
                    cout << "Do you want to save current image before exiting? (Y / N): ";
                    getline(cin, exit_choice);
                    if (exit_choice.size() != 1) {
                        cout << "Please enter a valid choice" << endl;
                        continue;
                    }
                    transform(exit_choice.begin(), exit_choice.end(), exit_choice.begin(), ::toupper);
                    if (exit_choice == "Y") {
                        save(img_filter); // Call function to save the image before exiting
                        return 0;
                    } else if (exit_choice == "N" ) {
                        return 0;
                    } else {
                        cout << "Please enter a valid choice" << endl;
                        continue;
                    }
                }
            } else if (saveindicator == "Y") {
                return 0;
            }
        } else {
            cout << "Please enter a valid choice" << endl;
        }
    }
}