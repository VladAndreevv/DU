#include <iostream>
#include <cstdlib>
#include <string>
using namespace std;
//----------------------------- Структура Узла
struct Node
{
    int data;
    Node* link;
};
//----------------------------- Создать новый узел
Node* CreateNode()
{
    Node* newNode;     //1
    newNode = new Node;  //2
    cout << "\nType number to add it:  ";
    cin >> newNode->data;  //3
    newNode->link = NULL;  //4
    return newNode;    //5
}
//----------------------------- Создать узел в начале списка
Node* AddFirst(Node* head) {
    Node* create;
    create = CreateNode();
    create->link = head;
    head = create;
    return head;
}
//----------------------------- Созать узел в конце списка
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
//------------------------------ Ищет узел с заданным значением data и возвращает указатель на этот узел.
Node* FindNode(Node* head, int x)
{
    Node* cur;
    cur = head;
    while (cur && cur->data != x) cur = cur->link;
    return cur;
}
//------------------------------- Ищет узел с заданным значением data, но возвращает указатель на предыдущий узел(тот, который идёт перед найденным узлом).
Node* FindNode2(Node* head, int x)
{
    Node* cur, * prev;
    cur = head;
    prev = NULL;
    while (cur && cur->data != x)
    {
        prev = cur;
        cur = cur->link;
    }
    return prev;
}
//-------------------------------
//void AddAfter2(Node *head)
//{
//  Node* newNode, * cur;
//  int x;
//  cout << "Pec kura pievienot" << endl;
//  cin >> x;
//  cur=FindNode(head, x);
//  if (!cur)  {
//    newNode = CreateNode();
//    newNode->link = cur->link;
//    cur->link = newNode;
//  }
//  else cout << "Tada skaitla nav" << endl;
//}
//------------------------------- Добавить новый узел сразу после узла, который укажет пользователь
Node* AddAfter(Node* head)
{
    Node* cur, * pec;
    int cipars;
    cout << "Enter 'x', the number AFTER which to add a new element : ";
    cin >> cipars;

    if (!head) {
        cout << "ERROR: Head not found!" << endl;
        return head;
    }
    else {
        cur = head;
        while (cur->link != NULL && cur->data != cipars)
        {
            cur = cur->link;
        }
    }
    pec = CreateNode();
    pec->link = cur->link;
    cur->link = pec;
    return head;
}
//------------------------------- Добавить новый узел сразу перед узлом, который укажет пользователь
Node* Addbefore(Node* head)
{
    Node* newNode, * prev;
    int x;
    cout << "Enter 'x', the number BEFORE which to add a new element : ";
    cin >> x;

    if (!head) {
        cout << "ERROR: Head not found!" << endl;
        return head;
    }
    prev = FindNode2(head, x);
    if (!prev) {
        cout << "ERROR: Node not found!\n";
        return head;
    }
    newNode = CreateNode();
    newNode->link = prev->link;
    prev->link = newNode;
    return head;
}
//------------------------------- Удалить первый узел в списке
Node* DeleteFirst(Node* head) {
    Node* cur;
    if (head) {
        cur = head->link;
        delete head;
        cout << "\nSucess! First deleted!" << endl;
        system("pause>null");
        return cur;
    }
    else {
        cout << "\nERROR: First not found!" << endl;
        system("pause>null");
        return NULL;
    }
}
//------------------------------- Удалить последний узел в списке
void DeleteLast(Node* head) {
    if (head == NULL) {
        cout << "ERROR: Last not found!" << endl;
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
        cout << "Last deleted!" << endl;
        system("pause>null");
    }
}
//------------------------------- Удалить узел, который будет идти сразу ПОСЛЕ указанного узла
void DeleteAfter(Node* head)
{
    int x;
    Node* y, * cur;
    cout << "Enter 'x', the node number, the node AFTER the node you want to delete :" << endl;
    cin >> x;
    y = FindNode(head, x);
    if (y)
    {
        if (y->link != NULL)
        {
            cur = y->link;
            y->link = cur->link;
            delete cur;
            cout << "Sucess! Node after '" << x << "' deleted!\n";

        }
        else {
            cout << "ERROR: There is no node that can be deleted!\n";
        }
    }
    else {
        cout << "ERROR: That number doesn't exist!\n";
    }
}
//------------------------------- Удалить узел, который будет идти сразу ПЕРЕД указанным узлом (1)
//Node* DeleteBefore(Node *head)
 //{
  // int x;
  // Node* prev, * cur, *y;
  // cout << "Pirms kura skaitla dzest?" << endl;
  // cin >> x;
  // y = FindNode(head, x);
  // cur= FindNode2(head, x);
  // if (cur != head)
  // {
  //   prev = FindNode2(head, cur->data);
  //   prev->link = y;
  //   delete cur;
  //   cout << "Mezgls ir nodzests\n";
  // }
  // else
  // {
  //   delete head;
  //   head = y;
  //   cout << "Mezgls ir nodzests\n";
  // }
  // return head;
 //}
//------------------------------- Удалить узел, который будет идти сразу ПЕРЕД указанным узлом (2)
void DeleteBefore(Node*& head)
{
    int x;
    cout << "Enter 'x', the node number, the node BEFORE the node you want to delete :";
    cin >> x;

    if (!head || !head->link) {
        cout << "ERROR: There is no node that can be deleted before!\n";
        return;
    }
    Node* cur = FindNode(head, x);
    if (!cur) {
        cout << "ERROR: Node '" << x << "' not found on the list!\n";
        return;
    }
    Node* y = FindNode2(head, x);
    if (!y) {
        cout << "ERROR: There is no node that can be deleted!\n";
        return;
    }

    if (y == head) {
        head = head->link;
        delete y;
    }
    else {
        Node* prev = FindNode2(head, cur->data);
        prev->link = y;
        delete y;
    }
    cout << "Sucess! Node before '" << x << "' deleted!\n";
}
//------------------------------- Вывести список всех существующих узлов
void PrintList(Node* head)
{
    if (head == NULL) {
        cout << "WARNING: List is empty!" << endl;
        return;
    }

    Node* cur;
    cout << "List Elements:\n";
    cur = head;    //1
    while (cur != NULL)
    {
        cout << cur->data << " ";  //2
        cur = cur->link;
    }
}
//------------------------------- info
void info() {
    cout << "**Info**" << endl;
    cout << "\nDeveloped by Vladislav Andreev, 2nd cource IT\n";
    system("pause>nul");
}

//------------------------------- main()
int main()
{
    Node* head = NULL, * cur;
    int darbiba;
    int x;

    do {
        //------------------------------- Меню
        system("cls");
        cout << "**MAIN MENU**" << endl;
        cout << endl;

        // ВЫВОД:
        cout << "1.Print list;" << endl;
        cout << "2.Search node;" << endl;
        cout << "3.Show Head;" << endl;
        cout << endl;
        // ДОБАВЛЕНИЕ:
        cout << "4.Add Head;" << endl;
        cout << "5.Add first node;" << endl;
        cout << "6.Add last node;" << endl;
        cout << "7.Add after 'x' node;" << endl;
        cout << "8.Add before 'x' node;" << endl;
        cout << endl;
        // УДАЛЕНИЕ:
        cout << "10.Delete first node;" << endl;
        cout << "11.Delete last node;" << endl;
        cout << "12.Delete after 'x';" << endl;
        cout << "13.Delete before 'x';" << endl;
        cout << endl;
        // ВЫХОД:
        cout << "14.Info" << endl;
        cout << "0.Exit;" << endl;
        cout << endl;

        cout << "Choose command! Enter current number : ";
        cin >> darbiba;
        system("cls");

        //------------------------------- Функции
            switch (darbiba) {
            case 0: // Выход из программы, поскольку "darbiba = 0"
                cout << "**Exit**\n" << endl;
                cout << "Goodbye!" << endl;
                break;

            case 1: // Вывод списка созданных узлов
                cout << "**Print list**\n" << endl;
                PrintList(head);
                system("pause>nul");
                break;

            case 2: // Поиск конкретного узла в списке
                cout << "**Find node**\n" << endl;
                cout << "Enter node number : "; cin >> x;
                cur = FindNode(head, x);
                if (!cur) {
                    cout << "\nFAILED: Not found!" << endl;
                }
                else {
                    cout << "\nSUCESS: Found!" << endl;
                }
                system("pause>nul");
                break;

            case 3: // Вывести "Голову"
                cout << "**Show Head**\n" << endl;
                if (head) {
                    cout << "head= " << head->data << endl;
                }
                else {
                    cout << "ERROR: List is empty!" << endl;
                }
                system("pause>nul");
                break;

            case 4: // Создать "Голову"
                cout << "**Add Head**\n" << endl;
                if (!head)head = CreateNode();
                else {
                    cout << "ERROR: Head already created!" << endl;
                    system("pause>nul");
                }
                break;

            case 5: // Создать новый узел в начале списка
                cout << "**Add first**\n" << endl;
                head = AddFirst(head);
                break;

            case 6: // Создать новый узел в конце списка
                cout << "**Add last**\n" << endl;
                head = AddLast(head);
                break;

            case 7: // Создать новый узел ПОСЛЕ узла, который введёт пользователь
                cout << "**Add after**\n" << endl;
                head = AddAfter(head);
                break;

            case 8: // Создать новый узел ПЕРЕД узлом, который введёт пользователь
                cout << "**Add before**\n" << endl;
                head = Addbefore(head);
                break;

            case 10: // Удалить первый узел в списке
                cout << "**Delete first**\n" << endl;
                head = DeleteFirst(head);
                break;

            case 11: // Удалить последний узел в списке
                cout << "**Delete last**\n" << endl;
                DeleteLast(head);
                break;

            case 12: // Удалить узел ПОСЛЕ узла, номер которого введёт пользователь
                cout << "**Delete after**\n" << endl;
                if (head) {
                    DeleteAfter(head);
                }
                else {
                    cout << "ERROR: Head doesn't exist!\n";
                }
                system("pause>null");
                break;

            case 13: // Удалить узел ПЕРЕД узлом, номер которого введёт пользователь
                cout << "**Delete before**\n" << endl;
                if (head) {
                    DeleteBefore(head);
                }
                else {
                    cout << "ERROR: Head doesn't exist!\n";
                }
                system("pause>null");
                break;

            case 14:
                info();
                break;

            default: // Если пользователь ввёл неверную цифру при выборе команды
                cout << "ERROR: Wrong command number!" << endl;
                system("pause>nul");
                break;
            }
        } while (darbiba != 0);
        system("pause>nul");
        return 0;
}