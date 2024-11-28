#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
// -------------------------------------------- Node struct
struct Node
{
    int data;
    Node* link;
};
// -------------------------------------------- CreateNode()
Node* CreateNode()
{
    Node* newNode;
    newNode = new Node;
    cout << "\nIevadiet skaitli, kuru pievienot:  ";
    cin >> newNode->data;
    newNode->link = NULL;
    return newNode;
}
// -------------------------------------------- AddFirst()
Node* AddFirst(Node* head) {
    Node* create;
    create = CreateNode();
    create->link = head;
    head = create;
    return head;
}
// -------------------------------------------- AddLast()
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
// -------------------------------------------- DeleteFirst()
Node* DeleteFirst(Node* head) {
    Node* cur;
    if (head) {
        cur = head->link;
        delete head;
        cout << "\nHaed nodzests!" << endl;
        system("pause>null");
        return cur;
    }
    else {
        cout << "\nHead nav atrasts!" << endl;
        system("pause>null");
        return NULL;
    }
}
// -------------------------------------------- DeleteLast()
void DeleteLast(Node* head) {
    if (head == NULL) {
        cout << "Pedejais nav atrasts!" << endl;
        system("pause>null");
        return;
    }

    Node* cur = head;
    Node* prev = NULL;

    if (head->link == NULL) {
        head = DeleteFirst(head);
    }
    else {
        while (cur->link != NULL) {
            prev = cur;
            cur = cur->link;
        }
        prev->link = NULL;
        delete cur;
        cout << "Pedejais nodzests!" << endl;
        system("pause>null");
    }
}
// -------------------------------------------- PrintList()
void PrintList(Node* head)
{
    Node* cur;
    cout << "Saraksta elementi:\n";
    cur = head;
    while (cur != NULL)
    {
        cout << cur->data << " ";
        cur = cur->link;
    }
}
// -------------------------------------------- NodeNumber()
void NodeNumber(Node* head)
{
    Node* cur;
    cout << "Kopejais elementu skaits:\n";
    cur = head;
    int number = 0;
    while (cur != NULL)
    {
        cur = cur->link;
        number++;
    }
    cout << number;
}
// -------------------------------------------- DeleteAll()
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
    cout << "Visi elementi tika nodzesti\n";
}
// -------------------------------------------- main()
int main()
{
    Node* head = NULL;
    int darbiba;
    do {
        // ------------------------------------ command list
        system("cls");
        cout << "1) AddFirst" << endl;
        cout << "2) AddLast" << endl;
        cout << "3) DeleteFirst" << endl;
        cout << "4) DeleteLast" << endl;
        cout << "5) PrintList" << endl;
        cout << "6) NodeNumber" << endl;
        cout << "7) DeleteAll" << endl;
        cout << "0) Exit" << endl;
        cout << "Enter command : ";
        cin >> darbiba;
        system("cls");
        // ------------------------------------ switch case
        switch (darbiba) {

        case 0: cout << "Goodbye!\n";
            break;

        case 1:
            head = AddFirst(head);
            break;

        case 2:head = AddLast(head);
            break;

        case 3: head = DeleteFirst(head);
            break;

        case 4: DeleteLast(head);
            break;

        case 5:PrintList(head);
            system("pause>nul");
            break;

        case 6: NodeNumber(head);
            system("pause>null");
            break;

        case 7:  DeleteAll(head);
            system("pause>null");
            break;

        default:cout << "ERROR: Wrong command!" << endl;
            system("pause>nul");
            break;
        }
    } while (darbiba != 0);

    system("pause>nul");
    return 0;
}
