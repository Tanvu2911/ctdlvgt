#include <bits/stdc++.h>
using namespace std;

class Node {
public:
    string eng;
    string vn;
    Node* left;
    Node* right;
    Node(string eng, string vn) : eng(eng), vn(vn), left(NULL), right(NULL) {
    }
};

class Tudien {
private:
    Node* root;

public:
    Tudien() : root(NULL) {
    }

    void insert(Node*& node, string eng, string vn) {
        if (node == NULL) {
            node = new Node(eng, vn);
        } else if (eng < node->eng) {
            insert(node->left, eng, vn);
        } else if (eng > node->eng) {
            insert(node->right, eng, vn);
        }
    }
	void openfile(string name){
		ifstream file(name);
		if(file.is_open()){
			cout << "mo file thanh cong.\n";
			string line;
			while(getline(file, line)){
				size_t pos = line.find(":");
				string eng = line.substr(0,pos);
				string vn = line.substr(pos + 1);
				addWord(eng,vn); 
			}
			file.close(); 
		}
		else {
			cout<<"khong mo duoc file"<<endl; 
		} 
		 
	}
    void infile(Node* node, ofstream& file) {
        if (!node) return; 
        infile(node->left, file);
        file << node->eng << ":" << node->vn << endl;
    	infile(node->right, file);
        
    }
    void printTree(Node* node) {
	    if (!node) return;
	    printTree(node->left);
	    cout << node->eng << ":" << node->vn << endl;
	    printTree(node->right);
	}
	void printTree(){
		printTree(root);
	}

    Node* search(Node* node, string eng) {
        if (node == NULL || node->eng == eng) {
            return node;
        } else if (eng < node->eng) {
            return search(node->left, eng);
        } else {
            return search(node->right, eng);
        }
    }

    Node* deletenode(Node* node, string eng) {
        if (node == NULL) return node;
        else if (eng < node->eng) {
            node->left = deletenode(node->left, eng);
        } else if (eng > node->eng) {
            node->right = deletenode(node->right, eng);
        } else {
            if (node->left == NULL) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (node->right == NULL) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            Node* temp = minValueNode(node->right);
            node->eng = temp->eng;
            node->vn = temp->vn;
            node->right = deletenode(node->right, temp->eng);
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left != NULL)
            current = current->left;
        return current;
    }

    void updateMeaning(Node* node,  string eng,  string newMeaning) {
        if (node) {
            if (node->eng == eng) {
                node->vn = newMeaning;
            } else if (eng < node->eng) {
                updateMeaning(node->left, eng, newMeaning);
            } else {
                updateMeaning(node->right, eng, newMeaning);
            }
        } else {
            cout << "Word '" << eng << "' not found for update." << endl;
        }
    }

    void saveToFile(string name) {
        ofstream file(name);
        if (file.is_open()) {
        	cout<<"mo file thanh cong"; 
            infile(root, file);
            file.close();
        } else {
            cout << "no" << endl;
        }
    }    

    void addWord( string eng, const string vn) {
        insert(root, eng, vn);
    }

    void remove(string eng) {
        root = deletenode(root, eng );
    }

    void updateWordMeaning( string eng,  string newMeaning) {
        updateMeaning(root, eng, newMeaning);
    }

    string searchWord(string eng) {
        Node* result = search(root, eng);
        return result ? result->vn : "Not found";
    }
};

int main() {
    Tudien a;
    int option;
    do {
        cout << "1. Ðoc file\n";
        cout << "2. Them tu\n";
        cout << "3. In danh sach\n";
        cout << "4. Thay doi nghia cua tu\n";
        cout << "5. Tim kiem\n";
        cout << "6. Xoa tu\n";
        cout << "7. Luu vao file\n";
        cout << "0. Thoat chuong trinh\n";
        cout << "Nhap lua chon: ";
        cin >> option;
        cin.ignore();  
        switch (option) {
            case 1: {
                string namefile;
                cout << "Nhap ten file can mo: ";
                getline(cin, namefile);
                a.openfile(namefile);
                break;
            }
            case 2: {
                string e, v;
                cout << "Nhap tu tieng Anh: ";
                getline(cin, e);
                cout << "Nhap nghia tieng Viet: ";
                getline(cin, v);
                a.addWord(e, v);
                break;
            }
            case 3:
                a.printTree();
                break;
            case 4: {
                string e, v;
                cout << "Nhap tu tieng Anh: ";
                getline(cin, e);
                cout << "Nhap nghia moi: ";
                getline(cin, v);
                a.updateWordMeaning(e, v);
                break;
            }
            case 5: {
                string e;
                cout << "Nhap tu tieng Anh can tim: ";
                getline(cin, e);
                string v = a.searchWord(e);
                cout << "Nghia cua tu '" << e << "': " << v << endl;
                break;
            }
            case 6: {
                string e;
                cout << "Nhap tu tieng Anh can xóa: ";
                getline(cin, e);
                a.remove(e);
                break;
            }
            case 7: {
                string namefile;
                cout << "Nhap ten file luu: ";
                getline(cin, namefile);
                a.saveToFile(namefile);
                break;
            }
            case 0:
                cout << "Thoat chuong trinh." << endl;
                break;
            default:
                cout << "Lua chon khong hop le!" << endl;
                break;
        }
    } while (option != 0);
}


