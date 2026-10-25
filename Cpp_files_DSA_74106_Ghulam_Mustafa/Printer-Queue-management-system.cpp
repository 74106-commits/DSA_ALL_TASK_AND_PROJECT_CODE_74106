#include <iostream>
using namespace std;

class PrinterQueue {
    struct Node {
        int jobId;
        Node* next;
    };

    Node* front;
    Node* rear;
    int count;

public:
    PrinterQueue() : front(nullptr), rear(nullptr), count(0) {}

    ~PrinterQueue() {
        while (front) {
            Node* t = front;
            front = front->next;
            delete t;
        }
    }

    void addJob(int id) {
        Node* n = new Node{id, nullptr};
        if (!rear) front = rear = n;
        else {
            rear->next = n;
            rear = n;
        }
        count++;
        cout << "Added Job ID: " << id << endl;
    }

    void processJob() {
        if (isEmpty()) {
            cout << "No jobs to process." << endl;
            return;
        }
        Node* t = front;
        cout << "Processing Job ID: " << t->jobId << endl;
        front = front->next;
        if (!front) rear = nullptr;
        delete t;
        count--;
    }

    int peek() {
        if (isEmpty()) return -1;
        return front->jobId;
    }

    bool isEmpty() {
        return count == 0;
    }

    int size() {
        return count;
    }

    void display() {
        cout << "--- Pending Jobs (Front to Rear) ---" << endl;
        for (Node* c = front; c; c = c->next)
            cout << c->jobId << " ";
        cout << endl;
    }
};

int main() {
    PrinterQueue pq;

    cout << "========== PRINTER QUEUE MANAGEMENT ==========" << endl << endl;

    pq.addJob(101);
    pq.addJob(102);
    pq.addJob(103);
    pq.addJob(104);

    cout << endl;
    pq.display();

    cout << endl;
    pq.processJob();
    pq.processJob();

    cout << endl;
    pq.display();

    cout << endl;
    cout << "Front Job: " << pq.peek() << endl;
    cout << "Queue Size: " << pq.size() << endl;

    cout << endl;
    while (!pq.isEmpty())
        pq.processJob();

    cout << endl << "Queue is now empty." << endl;

    cout << endl;
    cout << "============================================================" << endl;
    cout << "All memory released successfully." << endl;
    cout << "============================================================" << endl;

    return 0;
}