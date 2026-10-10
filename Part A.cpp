#include <iostream>
#include <string>
using namespace std;

struct BookRequestNode
{
    int studentID;
    string studentName;
    int bookID;
    string bookTitle;
    int priority;
    BookRequestNode* next;
};

class PriorityQueue
{
private:
    BookRequestNode* front;
    BookRequestNode* rear;
    int count;

public:
    PriorityQueue()
    {
        front = NULL;
        rear = NULL;
        count = 0;
    }

    void Add(BookRequestNode* request)
    {
        request->next = NULL;

        if (front == NULL)
        {
            front = request;
            rear = request;
        }
        else if (request->priority < front->priority)
        {
            request->next = front;
            front = request;
        }
        else
        {
            BookRequestNode* current = front;

            while (current->next != NULL &&
                   current->next->priority <= request->priority)
            {
                current = current->next;
            }

            request->next = current->next;
            current->next = request;

            if (request->next == NULL)
            {
                rear = request;
            }
        }

        count++;
    }

    BookRequestNode* Remove()
    {
        if (front == NULL)
        {
            return NULL;
        }

        BookRequestNode* request = front;
        front = front->next;

        if (front == NULL)
        {
            rear = NULL;
        }

        request->next = NULL;
        count--;

        return request;
    }

    bool IsEmpty()
    {
        return front == NULL;
    }

    bool IsNotEmpty()
    {
        return front != NULL;
    }

    void PrintQueue()
    {
        if (IsEmpty())
        {
            cout << "No book requests available." << endl;
            return;
        }

        BookRequestNode* current = front;

        while (current != NULL)
        {
            cout << "\nStudent ID: " << current->studentID << endl;
            cout << "Student Name: " << current->studentName << endl;
            cout << "Book ID: " << current->bookID << endl;
            cout << "Book Title: " << current->bookTitle << endl;
            cout << "Priority: " << current->priority << endl;
            cout << "-----------------------------" << endl;

            current = current->next;
        }
    }

    ~PriorityQueue()
    {
        while (front != NULL)
        {
            BookRequestNode* temp = front;
            front = front->next;
            delete temp;
        }

        rear = NULL;
        count = 0;
    }
};

int main()
{
    PriorityQueue requests;
    int choice;

    do
    {
        cout << "\n===== Library Book Request System =====" << endl;
        cout << "1. Add Book Request" << endl;
        cout << "2. Process Highest Priority Request" << endl;
        cout << "3. Display All Requests" << endl;
        cout << "4. Check Queue Status" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";

        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number." << endl;
            continue;
        }

        if (choice == 1)
        {
            BookRequestNode* request = new BookRequestNode;

            cout << "Enter Student ID: ";
            if (!(cin >> request->studentID))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                delete request;
                cout << "Invalid Student ID." << endl;
                continue;
            }

            cin.ignore(1000, '\n');

            cout << "Enter Student Name: ";
            getline(cin, request->studentName);

            cout << "Enter Book ID: ";
            if (!(cin >> request->bookID))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                delete request;
                cout << "Invalid Book ID." << endl;
                continue;
            }

            cin.ignore(1000, '\n');

            cout << "Enter Book Title: ";
            getline(cin, request->bookTitle);

            cout << "Enter Priority (1, 2, or 3): ";
            if (!(cin >> request->priority))
            {
                cin.clear();
                cin.ignore(1000, '\n');
                delete request;
                cout << "Invalid priority." << endl;
                continue;
            }

            if (request->studentName.empty() ||
                request->bookTitle.empty() ||
                request->priority < 1 ||
                request->priority > 3)
            {
                cout << "Invalid details. Please try again." << endl;
                delete request;
            }
            else
            {
                request->next = NULL;
                requests.Add(request);
                cout << "Book request added successfully." << endl;
            }
        }
        else if (choice == 2)
        {
            BookRequestNode* processed = requests.Remove();

            if (processed == NULL)
            {
                cout << "No requests to process." << endl;
            }
            else
            {
                cout << "\n===== Processed Request =====" << endl;
                cout << "Student ID: " << processed->studentID << endl;
                cout << "Student Name: " << processed->studentName << endl;
                cout << "Book ID: " << processed->bookID << endl;
                cout << "Book Title: " << processed->bookTitle << endl;
                cout << "Priority: " << processed->priority << endl;

                delete processed;
            }
        }
        else if (choice == 3)
        {
            cout << "\n===== All Pending Requests =====" << endl;
            requests.PrintQueue();
        }
        else if (choice == 4)
        {
            if (requests.IsEmpty())
            {
                cout << "The queue is empty." << endl;
            }
            else if (requests.IsNotEmpty())
            {
                cout << "The queue contains pending requests." << endl;
            }
        }
        else if (choice == 5)
        {
            cout << "Exiting the program." << endl;
        }
        else
        {
            cout << "Invalid choice. Please try again." << endl;
        }

    } while (choice != 5);

    return 0;
}

