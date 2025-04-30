#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

string encrypt(const string& text, int key) {
    string result;
    for (char c : text) {
        result += static_cast<char>((unsigned char)c + key);
    }
    return result;
}

string decrypt(const string& text, int key) {
    string result;
    for (char c : text) {
        result += static_cast<char>((unsigned char)c - key);
    }
    return result;
}

void write_to_files(const string& encrypted, int key) {
    const size_t frame_size = 100;
    size_t total_length = encrypted.size();
    int num_files = static_cast<int>(ceil((double)(total_length + 2) / frame_size));

    unsigned char files_encoded = static_cast<unsigned char>(num_files + 2 * key);
    unsigned char length_encoded = static_cast<unsigned char>(total_length + key);

    size_t written = 0;
    for (int i = 0; i < num_files; ++i) {
        string filename = "data_part_" + to_string(i + 1) + ".bin";
        ofstream out(filename, ios::binary);

        if (i == 0) {
            out.write(reinterpret_cast<char*>(&files_encoded), sizeof(files_encoded));
            out.write(reinterpret_cast<char*>(&length_encoded), sizeof(length_encoded));

            size_t to_write = min(frame_size - 2, total_length - written);
            out.write(encrypted.data() + written, to_write);
            written += to_write;
        } else {
            size_t to_write = min(frame_size, total_length - written);
            out.write(encrypted.data() + written, to_write);
            written += to_write;
        }

        size_t current_size = static_cast<size_t>(out.tellp());
        while (current_size < frame_size) {
            char zero = 0;
            out.write(&zero, 1);
            current_size++;
        }

        out.close();
    }

    cout << "Saved " << num_files << " file(s) of 100 bytes each." << endl;
}

int main() {
    string input_text;
    int key;

    cout << "Enter text to encrypt: ";
    getline(cin, input_text);

    cout << "Enter encryption key: ";
    cin >> key;

    string encrypted = encrypt(input_text, key);
    write_to_files(encrypted, key);

    return 0;
}
