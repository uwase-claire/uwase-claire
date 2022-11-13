
#include <cstdlib>
#include <unordered_map>
#include <list>
#include <fstream>
#include <iostream>
using namespace std;
typedef list<string> str_list;
typedef unordered_map<string, str_list> adj_list;
typedef unordered_map<string, string> visited;

adj_list* load(string file_name = "data.txt") {
    adj_list *word_map = new adj_list;
    string word;
    ifstream file(file_name.c_str());
    while (getline(file, word)) {
        word_map->insert(pair<string, str_list>(word, list<string>()));
    };
    file.close();
    return word_map;
}

void preprocess(adj_list* word_map, string file_name = "data.txt") {
    ifstream file(file_name.c_str());
    string word;
    string other_word;
    int per = 0;
    int b = 0;
    while (getline(file, word)) {
        for (int i = 0; i < word.size(); i++) {
            other_word = word;
            for (int j = 97; j <= 122; j++) {
                other_word[i] = static_cast<char> (j);
                if (word_map->count(other_word) > 0 && other_word != word) {
                    word_map->at(word).push_back(other_word);
                }
            }
        }
        per++;
    }
    file.close();
};

void print_adj(string word, adj_list* word_map) {

    str_list::iterator i;
    for (i = word_map->at(word).begin(); i != word_map->at(word).end(); i++) {
        cout << *i << "  ";
    }
};

void print_path(str_list& p) {
    str_list::iterator i;
    while (!p.empty()) {
        cout << p.back() << endl;
        p.pop_back();
    }

};

bool BFS(string start, string end, adj_list* word_map) {
    if (word_map->count(start) <= 0 ||
            word_map->count(end) <= 0)
        return 0;
    visited visited_nodes;
    str_list word_queue;
    str_list path;
    string word;
    str_list::iterator i;
    visited_nodes.insert(pair<string, string>(start, start));
    word_queue.push_back(start);
    while (!word_queue.empty()) {
        word = word_queue.front();

        word_queue.pop_front();
        if (word == end) {
            while (word != start) {
                path.push_back(word);
                word = visited_nodes.at(word);
            }
            path.push_back(word);
            print_path(path);
            return 1;
        }
        for (i = word_map->at(word).begin(); i != word_map->at(word).end(); i++) {
            if (visited_nodes.count(*i) <= 0) {
                visited_nodes.insert(pair<string, string>(*i, word));
                word_queue.push_back(*i);
            }
        }
    }
    return 0;
};

int main() {
    cout << "loading dictionary into Hash Table..." << endl;
    adj_list* word_map = load();
    preprocess(word_map);
    string start, end;
    while (1) {
        cout << "Type the first word: ";
        cin >> start;
        cout << "Type the second word: ";
        cin >> end;
        if (!BFS(start, end, word_map)) {
            cout << start << " is either not in the dictionary or cannot be transformed into any other word.";
        };
        cout << endl;
    }
    return 0;
}