#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
// -------------------------------------- Node structure
struct Node
{
    int data;
    Node* link;
};
// -------------------------------------- CreateNode()
Node* CreateNode()
{
    Node* newNode;
    newNode = new Node;
    cout << "\nEnter the number to add : ";
    cin >> newNode->data;
    newNode->link = NULL;
    return newNode;
}
// -------------------------------------- AddLast()
Node* AddLast(Node* head)
{
    Node* ped, * cur;
    if (!head) head = CreateNode();
    else {
        ped = CreateNode();
        cur = head;
        while (cur->link != NULL)
        {
            cur = cur->link;
        }
        cur->link = ped;
    }
    return head;
}
// -------------------------------------- DeleteFirst()
Node* DeleteFirst(Node* head) {
    Node* cur;
    if (head) {
        cur = head->link;
        delete head;
        cout << "\nSUCESS: Head deleted!" << endl;
        system("pause>null");
        return cur;
    }
    else {
        cout << "\nERROR: Head was not deleted!" << endl;
        system("pause>null");
        return NULL;
    }
}
// -------------------------------------- PrintList()
void PrintList(Node* head)
{
    Node* cur;
    cout << "List elements:\n";
    cur = head;    //1
    while (cur != NULL)
    {
        cout << cur->data << " ";  //2
        cur = cur->link;
    }
}
// -------------------------------------- NodeNumber()
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
// -------------------------------------- DeleteAll()
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
    cout << "All elements deleted!\n";
}
// -------------------------------------- main()
int main()
{
    Node* head = NULL;
    int darbiba;
    do {
        // ------------------------------ Command list
        system("cls");
        cout << "**RINDA**" << endl;
        cout << "1) AddLast" << endl;
        cout << "2) DeleteFirst" << endl;
        cout << "3) PrintList" << endl;
        cout << "4) NodeNumber" << endl;
        cout << "5) DeleteAll" << endl;
        cout << "0) Exit" << endl;
        cout << "Enter command : ";
        cin >> darbiba;
        // ------------------------------ Switch Case
        switch (darbiba) {
        case 1:
            head = AddLast(head);
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

        case 0:
            cout << "Programma ir pabeigta\n";
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