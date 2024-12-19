#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;

// ------------------------------- Node структура
struct Node
{
    int data;
    Node* left, * right;
};
// ------------------------------- CreateNode()
Node* CreateNode()
{
    Node* newNode;
    newNode = new Node;
    cout << "\nType number which do you want to add :  ";
    cin >> newNode->data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
// ------------------------------- PrintTree()
void PrintTree(Node* cur)
{//LVR
    if (!cur) return;
    PrintTree(cur->left);
    cout << cur->data << " ";
    PrintTree(cur->right);
}
// ------------------------------- AddNode()
Node* AddNode(Node* root) {
    Node* newNode;
    Node* cur = root;

    if (!root) {
        root = CreateNode();
    }
    else {
        newNode = CreateNode();

        while ((newNode->data <= cur->data && cur->left != NULL) || (newNode->data > cur->data && cur->right != NULL)) {
            // Значение нового узла меньше текущего - ВЛЕВО!
            while (newNode->data <= cur->data && cur->left != NULL) {
                cur = cur->left;
            }
            // Значение нового узла больше текущего - ВПРАВО!
            while (newNode->data > cur->data && cur->right != NULL) {
                cur = cur->right;
            }
        }
        // Оппа, нашли место для нового узла:
        if (newNode->data <= cur->data) {
            cur->left = newNode;  // Если значение нового узла меньше текущего - ВЛЕВО!
        }
        else {
            cur->right = newNode;  // Если значение нового узла больше текущего - ВПРАВО!
        }
    }
    return root;
}
// ------------------------------- FindNode()
void FindNode(Node* root)
{
    Node* cur;
    int x;
    cout << "Type searching number : ";
    cin >> x;
    cur = root;

    while (cur != NULL) {
        if (cur->data == x) {
            cout << "SUCESS: Founded!\n";
            return;
        }
        if (x < cur->data)
            cur = cur->left;
        else
            cur = cur->right;
    }

    cout << "FAILED: Not founded!\n";
}
// ------------------------------- FindMin()
Node* FindMin(Node* root)
{
    while (root && root->left)
    {
        root = root->left;
    }
    return root;
}
// ------------------------------- DeleteNode()
Node* DeleteNode(Node* root, int x) {
    if (root == NULL) return NULL; // Узел не был найден

    // Влево, если x меньше
    if (x < root->data) {
        root->left = DeleteNode(root->left, x);
    }
    // Вправо, если x больше
    else if (x > root->data) {
        root->right = DeleteNode(root->right, x);
    }

    // Тут мы нашли узел для удаления:
    else {

        // 1: У узла 0 или 1 потомок
        if (root->left == NULL || root->right == NULL) {
            Node* child = (root->left != NULL) ? root->left : root->right;
            delete root;
            return child;
        }

        // 2: У узла 2 потомка
        Node* successor = FindMin(root->right); // Ура, вот он, минимальный узел поддерева
        root->data = successor->data; // Заменяем данные
        root->right = DeleteNode(root->right, successor->data); // В помойку successor, старый минимальный узел
    }
    return root; // Возвращаем обновленное дерево
}

// ====================================================
// ------------------------------- PreOrder()
void PreOrder(Node* cur) { // VLR, берёт первых встречных
    if (!cur) return;
    cout << cur->data << " ";
    PreOrder(cur->left);
    PreOrder(cur->right);
}
// ------------------------------- InOrder()
void InOrder(Node* cur) { // LVR, берёт те, с которыми "прощаемся" или встречаем второй раз
    if (!cur) return;
    InOrder(cur->left);
    cout << cur->data << " ";
    InOrder(cur->right);
}
// ------------------------------- PostOrder()
void PostOrder(Node* cur) { // LRV, берёт те, к которым больше не вернётся
    if (!cur) return;
    PostOrder(cur->left);
    PostOrder(cur->right);
    cout << cur->data << " ";
}
// ====================================================

// ------------------------------- CountNodes()
int CountNodes(Node* root) {
    if (!root) return 0;
    return 1 + CountNodes(root->left) + CountNodes(root->right);
}
// ------------------------------- main()
int main() {
    Node* root = NULL;
    int darbiba;
    do {
        // ------------------------------- Список команд
        system("cls");
        cout << "**BINARY TREE**" << endl;
        cout << "1.  Create Head" << endl;
        cout << "2.  Show Head" << endl;
        cout << "3.  Print List" << endl;
        cout << "4.  Add Node" << endl;
        cout << "6.  Find Node" << endl;
        cout << "7.  Delete Node" << endl;
        cout << "8.  PreOrder / InOrder / PostOrder" << endl;
        cout << "9.  Number of elements" << endl;
        cout << "10. Tree rotation (NOT WORKING!)" << endl;
        cout << "11. Info" << endl;
        cout << "0.  Exit (You may enter 0 or any letter)" << endl;
        cout << "\nType command number : ";
        cin >> darbiba;
        system("cls");
        // ------------------------------- switch/case
        switch (darbiba) {
        case 0:
            cout << "**Exit**" << endl;
            cout << "Goodbye!" << endl;
            break;

        case 1:
            cout << "**Create Head**" << endl;
            if (!root) root = CreateNode();
            else cout << "ERROR: Head already created!" << endl;
            system("pause>nul");
            break;

        case 2:
            cout << "**Show Head**" << endl;
            if (root) cout << "\nRoot value: " << root->data << endl;
            else cout << "\nWARNING: Root not created!";
            system("pause>nul");
            break;

        case 3:
            cout << "**Print List**" << endl;
            PrintTree(root);
            cout << "\n";
            system("pause>nul");
            break;

        case 4:
            cout << "**Add Node**" << endl;
            root = AddNode(root);
            system("pause>nul");
            break;

        case 6:
            cout << "**Find Node**" << endl;
            if (root) FindNode(root);
            else cout << "WARNING: Tree is empty!" << endl;
            system("pause>nul");
            break;

        case 7:
            cout << "**Delete Node**" << endl;
            if (root) {
                int x;
                cout << "Enter the number of the node to be deleted: ";
                cin >> x;
                root = DeleteNode(root, x);
            }
            else cout << "ERROR: Tree is empty!" << endl;
            system("pause>nul");
            break;

        case 8:
            cout << "**Pre/In/Postorder**" << endl;
            if (root) {
                cout << "Preorder: "; PreOrder(root); cout << endl;
                cout << "Inorder: "; InOrder(root); cout << endl;
                cout << "Postorder: "; PostOrder(root); cout << endl;
            }
            else cout << "ERROR: Tree is empty!" << endl;
            system("pause>nul");
            break;

        case 9:
            cout << "**Number of Elements**" << endl;
            cout << "Number of elements :" << CountNodes(root) << endl;
            system("pause>nul");
            break;

        case 10:
            cout << "**Tree Rotation**" << endl;
            cout << "ERROR: This part doesn`t work!" << endl;
            system("pause>nul");
            break;

        case 11:
            cout << "**Info**" << endl;
            cout << "Developed by Vladislav Andreev, 16.12.2024" << endl;
            system("pause>nul");
            break;

        default:
            cout << "ERROR: Wrong command!" << endl;
            system("pause>nul");
        }

    } while (darbiba != 0);

    system("pause>nul");
    return 0;
}