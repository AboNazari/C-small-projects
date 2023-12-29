#include <bits/stdc++.h>

struct HuffmanNode {
    std::shared_ptr<HuffmanNode> left;
    std::shared_ptr<HuffmanNode> right;
    std::shared_ptr<HuffmanNode> parent;
    int data;
    char symbol;

    explicit HuffmanNode(int data, char symbol) {
        this->symbol = symbol;
        this->data = data;
    }

    HuffmanNode(const std::shared_ptr<HuffmanNode> &left, const std::shared_ptr<HuffmanNode> &right) {
        this->left = left;
        this->right = right;
        this->data = left->data + right->data;
        symbol = '\0';
    }


    bool operator<(const HuffmanNode &other) const {
        return data < other.data;
    }
};

struct CompareNode {
    bool operator()(const std::shared_ptr<HuffmanNode> &a, const std::shared_ptr<HuffmanNode> &b) const {
        return a->data < b->data || (a->data == b->data && a < b);
    }
};

std::string read_file(const std::string &path) {
    std::ifstream file(path);
    std::string line;
    std::string file_content;
    while (std::getline(file, line)) {
        file_content += line + "\n";
    }
    return file_content;
}


std::map<char, int> count_freqs(const std::string &file) {
    std::map<char, int> freq_map;
    for (char c: file) {
        freq_map[c]++;
    }
    return freq_map;
}

std::set<std::shared_ptr<HuffmanNode>, CompareNode> created_initial_nodes(const std::map<char, int> &freq_map) {
    std::set<std::shared_ptr<HuffmanNode>, CompareNode> nodes;
    for (auto &it: freq_map) {
        nodes.insert(std::make_shared<HuffmanNode>(it.second, it.first));
    }
    return nodes;
}

template<typename A, typename B, template<class, class, class...> class M, class... Args>
void debug_print_map(const M<A, B, Args...> &map) {
    for (auto it = map.begin(); it != map.end(); it++) {
        std::cout << it->first << " : " << it->second << std::endl;
    }
}

std::shared_ptr<HuffmanNode>
construct_huffman_tree(std::set<std::shared_ptr<HuffmanNode>, CompareNode> &all_letter_nodes) {
    while (all_letter_nodes.size() > 1) {
        auto first = all_letter_nodes.begin();
        auto second = all_letter_nodes.begin();
        second++;
        auto new_node = std::make_shared<HuffmanNode>(*first, *second);
        all_letter_nodes.erase(first);
        all_letter_nodes.erase(second);
        all_letter_nodes.insert(new_node);
    }
    return *all_letter_nodes.begin();
}


void
generate_codes_helper(const std::shared_ptr<HuffmanNode> &node, std::string code, std::map<char, std::string> &codes) {
    if (!node) return;

    // When a leaf node is reached, add its symbol and the corresponding code to the map
    if (!node->left && !node->right) {
        codes[node->symbol] = code;
    }

    // Traverse left and right subtrees, adding '0' for left and '1' for right
    generate_codes_helper(node->left, code + "0", codes);
    generate_codes_helper(node->right, code + "1", codes);
}


std::map<char, std::string> generate_codes(const std::shared_ptr<HuffmanNode> &tree) {
    std::map<char, std::string> codes;
    generate_codes_helper(tree, "", codes);
    return codes;
}


std::string encode(const std::string &file, const std::map<char, std::string> &codes) {
    std::string encodedMessage;
    for (char c: file) {
        encodedMessage += codes.at(c);
    }
    return encodedMessage;
}

void output_bin(const std::string &encoded_message, const std::string &path) {
    std::ofstream out_file(path, std::ios::binary);
    std::string buffer;
    for (char bit: encoded_message) {
        buffer += bit;
        while (buffer.length() >= 8) { // Write bytes (8 bits) at a time
            char byte = 0;
            for (int i = 0; i < 8; i++) {
                byte = (byte << 1) | (buffer[i] - '0'); // Convert '0'/'1' to binary
            }
            out_file.put(byte);
            buffer.erase(0, 8); // Remove the written bits
        }
    }

    // Write any remaining bits (less than 8) as a last byte
    if (!buffer.empty()) {
        while (buffer.length() < 8) {
            buffer += '0'; // Pad with zeros if needed
        }
        char byte = 0;
        for (int i = 0; i < 8; i++) {
            byte = (byte << 1) | (buffer[i] - '0'); // Convert '0'/'1' to binary
        }
        out_file.put(byte);
    }
}


void output_codes(const std::map<char, std::string> &codes, const std::string &path) {
    std::ofstream out_file(path);
    for (auto &code: codes) {
        out_file << code.second << ":" << code.first << std::endl;
    }
}

int main() {
    std::string file = read_file("./ex_text.txt");
    std::map<char, int> freq_map = count_freqs(file); // Specify the template arguments <char, int>
    auto all_letter_nodes = created_initial_nodes(freq_map);
    auto tree = construct_huffman_tree(all_letter_nodes);
    std::map<char, std::string> codes = generate_codes(tree);
    //debug_print_map(codes);
    std::string encoded_message = encode(file, codes);
    output_bin(encoded_message, "./encoded_text.bin");
    output_codes(codes, "./encoded_pairs.txt");
}
