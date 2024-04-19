#include <iostream>
#include <queue>
#include <omp.h>

using namespace std;

// Node structure for the binary tree
struct Node {
    int data;
    Node *left, *right;
    
    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Function to insert a new node into the binary tree
Node* insert(Node *root, int data) {
    if (root == nullptr) {
        return new Node(data);
    }
    
    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node *temp = q.front();
        q.pop();

        if (temp->left == nullptr) {
            temp->left = new Node(data);
            return root;
        } else {
            q.push(temp->left);
        }

        if (temp->right == nullptr) {
            temp->right = new Node(data);
            return root;
        } else {
            q.push(temp->right);
        }
    }

    return root;
}

// Function to perform breadth-first search traversal of the binary tree
void bfs(Node *root) {
    if (root == nullptr) {
        return;
    }

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        int levelSize = q.size();
        #pragma omp parallel for
        for (int i = 0; i < levelSize; i++) {

            #pragma omp critical{
            Node *currNode = q.front();
            q.pop();

            cout << currNode->data << " ";
            }
            #pragma omp critical{
            if (currNode->left) {
                q.push(currNode->left);
            }
            if (currNode->right) {
                q.push(currNode->right);
            }
            }
        }
    }
}

int main() {
    Node *root = nullptr;
    int data;
    char ans;

    do {
        cout << "\nEnter data for the new node: ";
        cin >> data;

        root = insert(root, data);

        cout << "Do you want to insert one more node? (y/n): ";
        cin >> ans;

    } while (ans == 'y' || ans == 'Y');

    cout << "\nBreadth-first search traversal result: ";
    bfs(root);

    return 0;
}
