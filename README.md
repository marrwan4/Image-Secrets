# Image Steganography Program

This C++ program implements image steganography, allowing users to embed and extract hidden messages within images using basic pixel manipulation. The console interface is inspired by "Harry Potter" for a themed user experience.

## Features
- **Embed (Encrypt) Text**: Hide a message within an image by adjusting pixel values.
- **Extract (Decrypt) Text**: Retrieve hidden messages from modified images.
- **File Handling**: Load, modify, and save images with options to save as a new file or overwrite.
- **Console Interface**: User-friendly prompts guide you through image loading, encryption, and decryption steps.

## Code Overview

### Global Variables
- `img_in`: Stores the original image.
- `img_filter`: Holds the image copy for editing.
- `imginput`: Tracks the loaded image filename.
- `saveindicator`: Tracks whether the image is saved (`"Y"` for yes, `"N"` for no).

### Key Functions

1. **`charToBinary`**: Converts a character to binary format.
2. **`str_to_binary`**: Converts a string to binary, adding a null terminator.
3. **`binary_to_char`**: Converts binary to a character.
4. **`encrypt_image`**: Embeds a binary message within image pixels.
5. **`decrypt_image`**: Extracts binary message from pixels and converts to readable text.
6. **`insert`**: Loads an image file.
7. **`save`**: Saves the modified image.
8. **`filters_menu`**: Provides encryption and decryption options.
9. **`main`**: Runs the program’s main loop, managing user input and coordinating function calls.

## Program Flow

1. **Insert Image**: Loads the image for editing.
2. **Chamber of Secrets**: Accesses the encryption or decryption feature.
3. **Save Image**: Saves modified images.
4. **Exit**: Optionally saves changes before closing.

## Usage

- Clone the repository and compile the program.
- Follow prompts to load an image, hide a message, extract a message, and save changes.

## Potential Improvements

- **Error Handling**: Enhance checks for non-image files.
- **Extended Formats**: Add support for more image formats.
- **GUI**: Consider a graphical interface for improved usability.

## Known Issues

- Limited for **.BMP, .PNG, .TGA** formats.

---

> **Note**: This project is for educational purposes and is not optimized for secure steganography in sensitive contexts.
