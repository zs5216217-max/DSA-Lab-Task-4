#include <iostream>
#include <string>
using namespace std;

struct BloodRequestNode
{
    int requestID;
    string patientName;
    string bloodGroup;
    int units;
    int priority;
    BloodRequestNode* next;
};

class BloodPriorityQueue
{
private:
    BloodRequestNode* front;
    BloodRequestNode* rear;

public:
    BloodPriorityQueue()
    {
        front = NULL;
        rear = NULL;
    }

    void Add(BloodRequestNode* request)
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
            BloodRequestNode* current = front;

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
    }

    BloodRequestNode* Remove()
    {
        if (front == NULL)
        {
            return NULL;
        }

        BloodRequestNode* request = front;
        front = front->next;

        if (front == NULL)
        {
            rear = NULL;
        }

        request->next = NULL;
        return request;
    }

    bool IsEmpty()
    {
        return front == NULL;
    }

    void Display()
    {
        if (IsEmpty())
        {
            cout << "No blood requests available.\n";
            return;
        }

        BloodRequestNode* current = front;

        while (current != NULL)
        {
            cout << "\nRequest ID: " << current->requestID << endl;
            cout << "Patient Name: " << current->patientName << endl;
            cout << "Blood Group: " << current->bloodGroup << endl;
            cout << "Units Required: " << current->units << endl;
            cout << "Priority: " << current->priority << endl;
            cout << "-----------------------------\n";

            current = current->next;
        }
    }

    ~BloodPriorityQueue()
    {
        while (front != NULL)
        {
            BloodRequestNode* temp = front;
            front = front->next;
            delete temp;
        }

        rear = NULL;
    }
};

int main()
{
    BloodPriorityQueue requests;
    int choice;

    do
    {
        cout << "\n===== Blood Donation Management System =====\n";
        cout << "1. Add Blood Request\n";
        cout << "2. Process Highest Priority Request\n";
        cout << "3. Display All Requests\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            BloodRequestNode* request = new BloodRequestNode;

            cout << "Enter Request ID: ";
            cin >> request->requestID;
            cin.ignore(1000, '\n');

            cout << "Enter Patient Name: ";
            getline(cin, request->patientName);

            cout << "Enter Blood Group: ";
            getline(cin, request->bloodGroup);

            cout << "Enter Units Required: ";
            cin >> request->units;

            cout << "Enter Priority (1, 2, or 3): ";
            cin >> request->priority;

            if (request->priority < 1 || request->priority > 3 ||
                request->units <= 0)
            {
                cout << "Invalid priority or number of units.\n";
                delete request;
            }
            else
            {
                request->next = NULL;
                requests.Add(request);
                cout << "Blood request added successfully.\n";
            }
        }
        else if (choice == 2)
        {
            BloodRequestNode* processed = requests.Remove();

            if (processed == NULL)
            {
                cout << "No blood requests to process.\n";
            }
            else
            {
                cout << "\n===== Highest Priority Request =====\n";
                cout << "Patient Name: " << processed->patientName << endl;
                cout << "Blood Group: " << processed->bloodGroup << endl;
                cout << "Units Required: " << processed->units << endl;
                cout << "Priority: " << processed->priority << endl;

                delete processed;
            }
        }
        else if (choice == 3)
        {
            cout << "\n===== Pending Blood Requests =====\n";
            requests.Display();
        }
        else if (choice == 4)
        {
            cout << "Exiting the program.\n";
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}

