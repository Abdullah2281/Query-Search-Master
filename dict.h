// Do NOT add any other includes
#include <string> 
#include <vector>
#include<fstream>
#include <iostream>
using namespace std;

struct AVLNode {
    string id;
    int count;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(const std::string& key) : id(key), count(1), height(0), left(nullptr), right(nullptr) {}
};

class Dict {
private:
    AVLNode* root;
    vector<AVLNode*> dictionary;
    string output_file;
    void add_word(string id);
    int hash(string id);
    void insertUtil(const std::string& id, AVLNode* &t);
    int getWordCountUtil(const std::string& id, AVLNode* t) const;

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};