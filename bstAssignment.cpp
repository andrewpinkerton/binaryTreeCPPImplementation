#include <iostream>
#include <string>

using namespace std;

struct Contact {
    string name;
    int phone;
    Contact* left;
    Contact* right;

    Contact(string n, int p)
        : name(n), phone(p), left(nullptr), right(nullptr) {}
};

class ContactBST {
private:
    Contact* root;
    // Insert contact
    Contact* insert(Contact* node, string name, int phone) {
        if (node == NULL)
        {
            return new Contact(name, phone);
        }

        if (name < node->name)
        {
            node->left = insert(node->left, name, phone);
        }
        else if (name > node->name)
        {
            node->right = insert(node->right, name, phone);
        }

        return node;

    }

    // Search for a contact by name
    Contact* search(Contact* node, string name) {
        if (node == nullptr || node->name == name)
        {
            return node;
        }

        if (name < node->name)
        {
            return search(node->left, name);
        }
        else if (name > node->name)
        {
            return search(node->right, name);
        }
    }

    // Find the minimum node (for deletion)
    Contact* findMin(Contact* node) {
        while (node && node->left != nullptr)
        {
            node = (node->left);
        }

        return node;
    }

    // Delete a contact by name
    Contact* deleteContact(Contact* node, string name) {
        if (node == nullptr)
        {
            return node;
        }

        if (node->name > name)
        {
            node->left = deleteContact(node->left, name);
        }
        else if (node->name < name)
        {
            node->right = deleteContact(node->right, name);
        }
        else {
            if (node->left == nullptr) // when root has 0 children or only right child
            {
                Contact* temp = node->right;
                delete node;
                return temp;
            }
            if (node->right == nullptr) // when root has only left child
            {
                Contact* temp = node->left;
                delete node;
                return temp;
            }

            //both children
            Contact* temp = findMin(node->right);
            node->name = temp->name;
            node->phone = temp->phone;
            node->right = deleteContact(node->right, temp->name);
        }
        return node;
    }

     // Inorder traversal
    void inorder(Contact* node) {
        if (node != nullptr)
        {
            inorder(node->left);
            cout << node->name << " ";
            inorder(node->right);
        }
    }

    public:
    ContactBST() : root(nullptr) {}

    void insertContact(string name, int phone) {
        root = insert(root, name, phone);
    }

    void searchContact(string name) {
        Contact* result = search(root, name);
        if (result == nullptr) {
            cout << "Contact not found!" << endl;
        } else {
            cout << "Found: " << result->name << " - " << result->phone << endl;
        }
    }

    void deleteContact(string name) {
        root = deleteContact(root, name);
    }

    void listContacts() {
        inorder(root);
    }
};

int main() {
    ContactBST contacts;
    contacts.insertContact("Alice", 12345);
    contacts.insertContact("Bob", 67890);
    contacts.insertContact("Charlie", 54321);

    cout << "All Contacts (Inorder Traversal): " << endl;
    contacts.listContacts();

    cout << endl << "\nSearching for 'Bob':" << endl;
    contacts.searchContact("Bob");

    cout << "\nDeleting 'Bob':" << endl;
    contacts.deleteContact("Bob");


    cout << "\nAll Contacts After Deletion: " << endl;
    contacts.listContacts();

    cout << endl << endl;

    return 0;
}