#include <bits/stdc++.h>

std::map<std::string, char> read_codes(const std::string &path) {
    std::ifstream file(path);
    std::string line;
    std::map<std::string, char> codes;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        //format of the line <code>:<symbol>
        std::string code = line.substr(0, line.find(':'));
        std::string symbol_str = line.substr(line.find(':') + 1);
        char symbol;
        if (symbol_str.empty()) {
            symbol = '\n';
        } else {
            symbol = symbol_str[0];
        }

        codes[code] = symbol;
    }

    return codes;
}

std::string decode(std::map<std::string, char> &codes, const std::string &path) {
    std::ifstream file(path, std::ios::binary);
    std::string binaryString;
    char byte;

    // Read each byte and convert it to a binary string
    while (file.read(reinterpret_cast<char *>(&byte), 1)) {
        for (int i = 7; i >= 0; --i) {
            binaryString.push_back((byte & (1 << i)) ? '1' : '0');
        }
    }

    std::string res;
    std::string currentCode;
    for (char bit: binaryString) {
        currentCode += bit;
        auto it = codes.find(currentCode);
        if (it != codes.end()) {
            res += it->second;
            currentCode.clear();
        }
    }

    return res;
}


std::string read_file(const std::string &path) {
    std::ifstream file(path);
    std::string line;
    std::string file_content;
    while (std::getline(file, line)) {
        file_content += line + "\n";
    }
    return file_content;
}


int main() {
    auto codes = read_codes("./encoded_pairs.txt");
    std::string res = decode(codes, "./encoded_text.bin");
    std::string example = read_file("./text.txt");
    std::ofstream out_file("./decoded_text.txt");
    out_file << res;
}