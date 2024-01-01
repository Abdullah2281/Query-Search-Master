// Do NOT add any other includes
#include "dict.h"

Dict::Dict(){
    dictionary.resize(2500000);
    root = NULL; 
}

void baldevDestroyer(AVLNode* root) {
    if (root == NULL) {
        return;
    }
    baldevDestroyer(root->left);
    baldevDestroyer(root->right);
    delete root;
}

Dict::~Dict() {
    for(auto i:dictionary){
        baldevDestroyer(i);
    }
}

int height(AVLNode* node) {
    if (node == NULL) {
        return -1;
    }
    return node->height;
}

int getBalance(AVLNode* node) {
    if (node == NULL) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

void updateHeight(AVLNode* node) {
    if (node != NULL) {
        node->height = 1 + std::max(height(node->left), height(node->right));
    }
}

AVLNode* rotateWithLeftChild(AVLNode* k2) {
    AVLNode* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    // updateHeight(k2);
    // updateHeight(k1);
    k2->height = 1 + std::max(height(k2->left), height(k2->right));
    k1->height = 1 + std::max(height(k1->left), height(k1->right));
    return k1;
}

AVLNode* rotateWithRightChild(AVLNode* k1) {
    AVLNode* k2 = k1->right;
    k1->right = k2->left;
    k2->left = k1;
    // updateHeight(k1);
    // updateHeight(k2);
    k1->height = 1 + std::max(height(k1->left), height(k1->right));
    k2->height = 1 + std::max(height(k2->left), height(k2->right));
    return k2;
}

AVLNode* doubleWithLeftChild(AVLNode* k3) {
    k3->left = rotateWithRightChild(k3->left);
    return rotateWithLeftChild(k3);
}

AVLNode* doubleWithRightChild(AVLNode* k3) {
    k3->right = rotateWithLeftChild(k3->right);
    return rotateWithRightChild(k3);
}

void Dict::insertUtil(const std::string& id, AVLNode* &t) {
    if (t == NULL) {
        t = new AVLNode(id);
    } 
    else if(t->id == id) {
        t->count++;
    }
    else if (id < t->id) {
        insertUtil(id, t->left);
    } 
    else if (t->id < id) {
        insertUtil(id, t->right);
    }

    //balance the tree
    if (t == NULL) return;
    int balance = getBalance(t);
    if (balance > 1) {
        if (getBalance(t->left) > 0) {
            t = rotateWithLeftChild(t);
        } else {
            // t = doubleWithLeftChild(t);
            t->left = rotateWithRightChild(t->left);
            t = rotateWithLeftChild(t);
        }
    } else if (balance < -1) {
        if (getBalance(t->right) < 0) {
            t = rotateWithRightChild(t);
        } else {
            // t = doubleWithRightChild(t);
            t->right = rotateWithLeftChild(t->right);
            t = rotateWithRightChild(t);
        }
    }
    // updateHeight(t);
    t->height = 1 + std::max(height(t->left), height(t->right));
}

int Dict::getWordCountUtil(const std::string& id, AVLNode* t) const {
    if (t == NULL) {
        return 0;
    }
    if (id == t->id) {
        return t->count;
    } 
    else if (id < t->id) {
        return getWordCountUtil(id, t->left);
    } 
    else {
        return getWordCountUtil(id, t->right);
    }
}

void Dict::add_word(string id) {
    int i = hash(id);
    insertUtil(id, dictionary[i]);
}


int Dict::hash(string id) {
    const int prime = 31;
    int hashValue = 0;

    for (char c : id) {
        hashValue = (hashValue * prime) + static_cast<int>(c);
    }
    if (hashValue < 0) {
        hashValue = -hashValue;
    }
    return hashValue%2500000;
}

bool isSeparator(char c) {
    // Define your separator characters here
    const std::string separators = " .,-:!\"'()?—[]“”‘’˙;@";
    return separators.find(c) != std::string::npos;
}

//niche unke functions hai

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    string temp;
    for (char c : sentence) {
        if (isSeparator(c) || c == ' ') {
            if (!temp.empty()) {
                // Convert to lowercase and add to the words vector
                for (char& character : temp) {
                    if (character >= 'A' && character <= 'Z') {
                        character = character - 'A' + 'a';
                    }
                }
                int i = hash(temp);
                insertUtil(temp, dictionary[i]);
                temp = "";
            }
        } else {
            temp += c;
        }
    }
    if (!temp.empty()) {
        // Convert the last word to lowercase and add it
        for (char& character : temp) {
            if (character >= 'A' && character <= 'Z') {
                character = character - 'A' + 'a';
            }
        }
        int i = hash(temp);
        insertUtil(temp, dictionary[i]);
    }
    return;
}

int Dict::get_word_count(string word){
    int i = hash(word);
    return getWordCountUtil(word, dictionary[i]);
    return 0;
}

void write_to_file(vector<string> &commands, string &filename) {
    ofstream outputFile;
    outputFile.open(filename,ios::app);
    // Check if opened
    if (!outputFile.is_open()) {
        return;
    }
        for (const std::string& line : commands) {
            outputFile << line << std::endl;
        }
    outputFile.close();
}

void inOrderDump(AVLNode* node, std::vector<std::string>& data) {
    if (node == NULL) {
        return;
    }
    inOrderDump(node->left, data);
    std::string temp = node->id + ", " + std::to_string(node->count);
    data.push_back(temp);
    inOrderDump(node->right, data);
}

void Dict::dump_dictionary(string filename){
    output_file = filename;
    ofstream rp(output_file.c_str());
    vector<string> write;
    for (int i = 0; i < dictionary.size(); i++) {
        inOrderDump(dictionary[i], write);
    }
    write_to_file(write, output_file);
    return;
}