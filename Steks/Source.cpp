#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
// ------------------------------------- Node Structure
struct Node
{
    int data;
    Node* link;
};
// ------------------------------------- CreateNode()
Node* CreateNode()
{
    Node* newNode;
    newNode = new Node;
    cout << "Enter the number to add to the stack: ";
    cin >> newNode->data;
    newNode->link = NULL;
    return newNode;
}
// ------------------------------------- AddFirts()
Node* AddFirst(Node* head) {
    Node* create;
    create = CreateNode();
    create->link = head;
    head = create;
    return head;
}
// ------------------------------------- DeleteFirst()
Node* DeleteFirst(Node* head) {
    Node* cur;
    if (head) {
        cur = head->link;
        delete head;
        cout << "SUCESS: Head deleted!" << endl;
        system("pause>null");
        return cur;
    }
    else {
        cout << "ERROR: Head not founded!" << endl;
        system("pause>null");
        return NULL;
    }
}
// ------------------------------------- PrintList()
void PrintList(Node* head)
{
    Node* cur;
    cout << "Steck elements:\n";
    cur = head;
    while (cur != NULL)
    {
        cout << cur->data << " ";
        cur = cur->link;
    }
}
// ------------------------------------- NodeNumber()
void NodeNumber(Node* head)
{
    Node* cur;
    cout << "Total number of elements:\n";
    cur = head;
    int number = 0;
    while (cur != NULL)
    {
        cur = cur->link;
        number++;
    }
    cout << number;
}
// ------------------------------------- DeleteAll()
void DeleteAll(Node*& head)
{
    Node* cur = head;
    Node* next;
    while (cur != NULL)
    {
        next = cur->link;
        delete cur;
        cur = next;
    }
    head = NULL;
    cout << "SUCESS: All the elements was deleted!\n";
}
// ------------------------------------- main()
int main()
{
    Node* head = NULL;
    int darbiba;
    do {
        // ----------------------------- Command List
        system("cls");
        cout << "**STECK**" << endl;
        cout << "1) AddFirst" << endl;
        cout << "2) DeleteFirst" << endl;
        cout << "3) PrintList" << endl;
        cout << "4) NodeNumber" << endl;
        cout << "5) DeleteAll" << endl;
        cout << "0) Exit" << endl;
        cout << "Ievadiet kamandu : ";
        cin >> darbiba;
        system("cls");
        // ------------------------------ Switch Case
        switch (darbiba) {
        case 0:
            cout << "Goodbye!\n";
            break;

        case 1:
            head = AddFirst(head);
            break;

        case 2:
            head = DeleteFirst(head);
            break;

        case 3:
            PrintList(head);
            system("pause>nul");
            break;

        case 4:
            NodeNumber(head);
            system("pause>null");
            break;

        case 5:
            DeleteAll(head);
            system("pause>null");
            break;

        default:
            cout << "ERROR: Wrong command number!" << endl;
            system("pause>nul");
            break;
        }

    } while (darbiba != 0);

    system("pause>nul");
    return 0;
}