#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

#define N 26
int numberVoca;

struct Trie {
    struct Trie *children[N];
    pair<vector<int>, vector<int>> numberAndListWords;
};

struct Trie *newNode() {
    struct Trie *pNode = new Trie;
    pNode->numberAndListWords.first.push_back(-1);
    pNode->numberAndListWords.second.push_back(numberVoca);
    for(int i = 0; i < N; i++)
        pNode->children[i] = NULL;
    return pNode;
}

void insert(struct Trie *root, string s) {
    struct Trie *tempTrie = root;

    for(int i = 0; i < s.size(); i++) {
        int index = s[i] - 'a';
        if(!tempTrie->children[index])
            tempTrie->children[index] = newNode();
        else
            tempTrie->numberAndListWords.second.push_back(numberVoca);
        tempTrie = tempTrie->children[index];
    }
    tempTrie->numberAndListWords.first[0] = numberVoca++;
}

vector<int> search(struct Trie *root, string s) {
    struct Trie *tempTrie = root;
    vector<int> check(1, -1);

    for(int i = 0; i < s.size(); i++) {
        int index = s[i] - 'a';
        if(!tempTrie->children[index])
            return check;
        tempTrie = tempTrie->children[index];
    }
    return (tempTrie->numberAndListWords.first[0] == -1 ? tempTrie->numberAndListWords.second : tempTrie->numberAndListWords.first);
}

int main() {
    ifstream fileInput, fileMeans;
    ofstream fileOutput;
    fstream file;
    vector<string> meansVoca;
    vector<string> vocabulary;

    struct Trie *root = newNode();

    fileInput.open("input.txt");
    fileMeans.open("output.txt");

    numberVoca = 0;

    while(!fileInput.eof()) {
        string voca, means;
        getline(fileInput, voca);
        insert(root, voca);
        getline(fileMeans, means);
        vocabulary.push_back(voca);
        meansVoca.push_back(means);
    }

    fileInput.close();
    fileMeans.close();

    while(1) {
        int choose;
        system("cls");
        cout << "1. Them tu moi" << endl;
        cout << "2. Sua tu" << endl;
        cout << "3. Tim kiem" << endl;
        cout << "4. Thoat" << endl;
        cout << "Nhap lua chon: ";
        cin >> choose;

        switch (choose)
        {
        case 1:
            {
                string temp;
                cin.ignore(1);
                cout << "Nhap tu: " << endl;
                getline(cin, temp);
                for(int i = 0; i < temp.size(); i++) {
                    if((int)temp[i] >= 65 && (int)temp[i] <= 90)
                        temp[i] += 32;
                }
                vector<int> isExits = search(root, temp);
                if(isExits[0] == -1) {
                    file.open("input.txt", ios::app);
                    file << temp << endl;
                    file.close();
                    insert(root, temp);
                    vocabulary.push_back(temp);
                    cout << "Nhap y nghia: " << endl;
                    getline(cin, temp);
                    file.open("output.txt", ios::app);
                    file << temp << endl;
                    meansVoca.push_back(temp);
                    file.close();
                }
                else {
                    cout << "Tu nay da ton tai!";
                    system("pause");
                }
            }
            break;
        case 2:
            {

            }
            break;
        case 3:
            {
                string temp;
                cin.ignore(1);
                cout << "Nhap tu: " << endl;
                getline(cin, temp);
                for(int i = 0; i < temp.size(); i++) {
                    if((int)temp[i] >= 65 && (int)temp[i] <= 90)
                        temp[i] += 32;
                }
                vector<int> isExits = search(root, temp);
                if(isExits[0] != -1) {
                    for(int i = 0; i < isExits.size(); i++) {
                        cout << i + 1 << ". " << vocabulary[isExits[i]] << endl;
                        cout << "Nghia la: " << meansVoca[isExits[i]] << endl;
                    }
                }
                else
                    cout << "Tu nay khong co trong tu dien" << endl;
                system("pause");
            }
            break;

        case 4: return 0;
        default:
            cout << "?? :D ??" << endl;
            system("pause");
            break;
        }
    }
    return 0;
}
