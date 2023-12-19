#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;



class CaesarCipher {

private:
    int shift;

public:
    CaesarCipher(int shiftValue) : shift(shiftValue) {}

    string encrypt(const string& text, bool decrypt=false) {
        string result = "";

        for (char ch : text) {
            if (isalpha(ch)) {
                char base = (isupper(ch)) ? 'A' : 'a';
                if (decrypt)
                    result += static_cast<char>((ch - base + (26-shift)) % 26 + base);
                else
                    result += static_cast<char>((ch - base + shift) % 26 + base);
            }
            else {
                result += ch;
            }
        }

        return result;
    }

    string decrypt(const string& text) {
        return encrypt(text, true); // Umkehrung der Verschiebung für Entschlüsselung
    }

};


class VigenereCipher {

private:
    string key;

public:
    VigenereCipher(const string& keyWord) : key(keyWord) {}

    string encrypt(const string& text) {
        string result = "";
        int keyIndex = 0;

        for (char ch : text) {
            if (isalpha(ch)) {
                char base = (isupper(ch)) ? 'A' : 'a';
                char offset = toupper(key[keyIndex]) - 'A';
                result += static_cast<char>((ch - base + offset) % 26 + base);

                keyIndex = (keyIndex + 1) % key.length();
            }
            else {
                result += ch;
            }
        }

        return result;
    }

    string decrypt(const string& text) {
        string result = "";
        int keyIndex = 0;

        for (char ch : text) {
            if (isalpha(ch)) {
                char base = (isupper(ch)) ? 'A' : 'a';
                char offset = toupper(key[keyIndex]) - 'A';
                result += static_cast<char>((ch - base - offset + 26) % 26 + base);

                keyIndex = (keyIndex + 1) % key.length();
            }
            else {
                result += ch;
            }
        }

        return result;
    }
};


class PlayfairCipher {

private:
    string key;

    // Funktion zur Erzeugung der Playfair-Matrix
    string generateMatrix() {
        string matrix = key + "ABCDEFGHIKLMNOPQRSTUVWXYZ"; // ohne J

        // Entferne doppelte Buchstaben
        matrix.erase(remove_if(matrix.begin(), matrix.end(),
            [](char c) { return !isalpha(c); }), matrix.end());

        // Entferne doppelte Buchstaben
        string::iterator end_pos = unique(matrix.begin(), matrix.end());
        matrix.erase(end_pos, matrix.end());

        return matrix;
    }

public:
    PlayfairCipher(const string& keyword) : key(keyword) {}

    string encrypt(const string& text) {
        string matrix = generateMatrix();
        string result = "";
        // Implementiere die Verschlüsselung hier

        return result;
    }

    string decrypt(const string& text) {
        string matrix = generateMatrix();
        string result = "";
        // Implementiere die Entschlüsselung hier

        return result;
    }
};



int main()
{
    locale::global(locale("German_Austria.UTF-8"));

    int shift;
    string key, message;

    cout << "Willkommen zum Cipher Kryptographie-Tool!" << endl;

    while (true) {
        cout << "\nWählen Sie eine Option:\n"
            << "1. Caesar-Verschlüsselung\n"
            << "2. Caesar-Entschlüsselung\n"
            << "3. Vigenère-Verschlüsselung\n"
            << "4. Vigenère-Entschlüsselung\n"
            << "5. Playfair-Verschlüsselung\n"
            << "6. Playfair-Entschlüsselung\n"
            << "7. Beenden\nIhr Wahl: ";

        int choice;
        while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Ungültige Eingabe. Bitte wählen Sie 1 bis 7: ";
        }


        if (choice == 1) { // Caesar-Verschlüsselung
            cout << "Geben Sie den zu verschlüsselnden Text ein: ";
            cin.ignore();
            getline(cin, message);

            cout << "Geben Sie die Verschiebung (Schlüssel) für Caesar-Verschlüsselung ein: ";
            cin >> shift;

            CaesarCipher caesar(shift);
            string encryptedCaesar = caesar.encrypt(message);
            cout << "\nVerschlüsselter Text (Caesar): " << encryptedCaesar << endl;
        }
        else if (choice == 2) { // Caesar-Entschlüsselung
            cout << "Geben Sie den zu entschlüsselnden Text ein: ";
            cin.ignore();
            getline(cin, message);

            cout << "Geben Sie die Verschiebung (Schlüssel) für Caesar-Entschlüsselung ein: ";
            cin >> shift;

            CaesarCipher caesar(shift);
            string decryptedCaesar = caesar.decrypt(message);
            cout << "\nEntschlüsselter Text (Caesar): " << decryptedCaesar << endl;
        }
        else if (choice == 3) { // Vigenère-Verschlüsselung
            cout << "Geben Sie den zu verschlüsselnden Text ein: ";
            cin.ignore();
            getline(cin, message);

            cout << "Geben Sie das Schlüsselwort ein: ";
            getline(cin, key);

            VigenereCipher vigenere(key);
            string encrypted = vigenere.encrypt(message);
            cout << "\nVerschlüsselter Text (Vigenère): " << encrypted << endl;
        }
        else if (choice == 4) { // Vigenère-Entschlüsselung
            cout << "Geben Sie den zu entschlüsselnden Text ein: ";
            cin.ignore();
            getline(cin, message);

            cout << "Geben Sie das Schlüsselwort ein: ";
            getline(cin, key);

            VigenereCipher vigenere(key);
            string decrypted = vigenere.decrypt(message);
            cout << "\nEntschlüsselter Text (Vigenère): " << decrypted << endl;
        }
        else if (choice == 5) {
            cout << "Geben Sie den zu verschlüsselnden Text ein: ";
            cin.ignore();
            getline(cin, message);

            cout << "Geben Sie das Schlüsselwort für die Playfair-Verschlüsselung ein: ";
            getline(cin, key);

            PlayfairCipher playfair(key);
            string encryptedPlayfair = playfair.encrypt(message);
            cout << "\nVerschlüsselter Text (Playfair): " << encryptedPlayfair << endl;
        }
        else if (choice == 6) {
            cout << "Geben Sie den zu entschlüsselnden Text ein: ";
            cin.ignore();
            getline(cin, message);

            cout << "Geben Sie das Schlüsselwort für die Playfair-Entschlüsselung ein: ";
            getline(cin, key);

            PlayfairCipher playfair(key);
            string decryptedPlayfair = playfair.decrypt(message);
            cout << "\nEntschlüsselter Text (Playfair): " << decryptedPlayfair << endl;
        }
        else if (choice == 7) {
            cout << "Programm wird beendet. Auf Wiedersehen!" << endl;
            break;
        }
        else {
            cout << "Ungültige Eingabe. Bitte wählen Sie 1 bis 7." << endl;
        }

        //cin.clear();
        //cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        //fflush(stdin);
    }

    return 0;
}