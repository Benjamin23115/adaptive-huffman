#include "adaptive-huffman.h"
#include <iostream>
#include <fstream>

using namespace std;

const int maxArguments = 4;

int main(int argc, char const *argv[])
{
    // Create an instance of AdaptiveHuffman
    AdaptiveHuffman adaptiveHuffman;

    // File streams for reading and writing
    fstream alphabetFile;
    fstream textFile;

    // Strings to store the alphabet, input message, encoded message, and decoded message
    string alphabet = "";
    string message = "";
    string encoded = "";
    string decoded = "";

    // Command-line arguments
    string commandArg;  // Command argument (encode/decode)
    string alphabetArg; // Alphabet file argument
    string messageArg;  // Input message file argument (for encode)
    string encodedArg;  // Encoded message file argument (for decode)

    // Check the number of command-line arguments
    if (argc != maxArguments)
    {
        cout << "Usage: " << argv[0] << " <encode/decode> <alphabet_file> <input_file>" << endl;
        return -1;
    }

    // Extract command-line arguments
    commandArg = argv[1];
    alphabetArg = argv[2];

    // Set input file arguments based on the command
    if (commandArg == "encode")
    {
        messageArg = argv[3];
    }
    else if (commandArg == "decode")
    {
        encodedArg = argv[3];
    }

    // Print the alphabet file argument
    cout << "Alphabet: " << alphabetArg << endl;

    // Encode operation
    if (commandArg == "encode")
    {
        // Open alphabet file and read it into a string
        alphabetFile.open(alphabetArg, ios::in);
        if (alphabetFile.is_open())
        {
            getline(alphabetFile, alphabet);
        }
        else
        {
            cout << "Error: Unable to open alphabet file." << endl;
        }
        alphabetFile.close();

        // Open input message file and read it into a string
        textFile.open(messageArg, ios::in);
        if (textFile.is_open())
        {
            while (getline(textFile, message))
            {
                // Concatenate each line to the message string if needed
            }
        }
        else
        {
            cout << "Error: Unable to open input message file." << endl;
        }
        textFile.close();

        // Create an AdaptiveHuffman encoder with the specified alphabet
        AdaptiveHuffman encoder(alphabet);

        // Encode the message
        encoded = encoder.encode(message);

        // Print the encoded message
        cout << "Encoded Message: " << encoded << endl;

        // Output the encoded message to a file
        messageArg += ".encoded";
        textFile.open(messageArg, ios::out);
        if (textFile.is_open())
        {
            textFile << encoded;
        }
        textFile.close();
    }
    // Decode operation
    else if (commandArg == "decode")
    {
        // Open alphabet file and read it into a string
        alphabetFile.open(alphabetArg, ios::in);
        if (alphabetFile.is_open())
        {
            getline(alphabetFile, alphabet);
        }
        else
        {
            cout << "Error: Unable to open alphabet file." << endl;
        }
        alphabetFile.close();

        // Open encoded message file and read it into a string
        textFile.open(encodedArg, ios::in);
        if (textFile.is_open())
        {
            while (getline(textFile, message))
            {
                // Concatenate each line to the message string if needed
            }
        }
        else
        {
            cout << "Error: Unable to open encoded message file." << endl;
        }
        textFile.close();

        // Create an AdaptiveHuffman decoder with the specified alphabet
        AdaptiveHuffman decoder(alphabet);

        // Decode the message
        decoded = decoder.decode(message);

        // Print the decoded message
        cout << "Decoded Message: " << decoded << endl;

        // Output the decoded message to a file
        int extensionLen = 8;
        encodedArg.erase(encodedArg.end() - extensionLen, encodedArg.end());
        encodedArg += ".decoded";
        textFile.open(encodedArg, ios::out);
        if (textFile.is_open())
        {
            textFile << decoded;
        }
        textFile.close();
    }
    else
    {
        cout << "Invalid command. Use 'encode' or 'decode'." << endl;
        return -1;
    }

    return 0;
}
