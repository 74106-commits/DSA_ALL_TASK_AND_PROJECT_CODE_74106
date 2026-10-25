#include <iostream>
#include <string>
using namespace std;

struct Product {
    int id;
    string name;
    double price;
    int quantity;
    Product* next;
};

class Inventory {
    Product* head;
public:
    Inventory() : head(nullptr) {}
    ~Inventory() {
        while (head) {
            Product* t = head;
            head = head->next;
            delete t;
        }
    }

    Product* find(int id) {
        Product* c = head;
        while (c) {
            if (c->id == id) return c;
            c = c->next;
        }
        return nullptr;
    }

    bool addProduct(int id, string name, double price, int qty) {
        if (find(id)) {
            cout << "Product ID already exists!\n";
            return false;
        }
        Product* p = new Product{id, name, price, qty, nullptr};
        if (!head) head = p;
        else {
            Product* c = head;
            while (c->next) c = c->next;
            c->next = p;
        }
        cout << "Product added successfully.\n";
        return true;
    }

    void display() {
        if (!head) { cout << "Inventory is empty.\n"; return; }
        cout << "\nID\tName\t\tPrice\tQty\n";
        cout << "------------------------------------------\n";
        for (Product* c = head; c; c = c->next)
            cout << c->id << "\t" << c->name << "\t\t" << c->price << "\t" << c->quantity << "\n";
    }

    void search(int id) {
        Product* p = find(id);
        if (!p) { cout << "Product not found.\n"; return; }
        cout << "Found -> ID: " << p->id << ", Name: " << p->name
             << ", Price: " << p->price << ", Qty: " << p->quantity << "\n";
    }

    void updateStock(int id, int qty) {
        Product* p = find(id);
        if (!p) { cout << "Product not found.\n"; return; }
        p->quantity = qty;
        cout << "Stock updated.\n";
    }

    void deleteProduct(int id) {
        Product *c = head, *prev = nullptr;
        while (c && c->id != id) { prev = c; c = c->next; }
        if (!c) { cout << "Product not found.\n"; return; }
        if (!prev) head = c->next;
        else prev->next = c->next;
        delete c;
        cout << "Product deleted.\n";
    }

    void lowStock() {
        bool any = false;
        cout << "\n--- Low Stock Products (Qty < 10) ---\n";
        for (Product* c = head; c; c = c->next) {
            if (c->quantity < 10) {
                cout << c->id << "\t" << c->name << "\t" << c->quantity << "\n";
                any = true;
            }
        }
        if (!any) cout << "No low-stock products.\n";
    }
};

// ---------- Stack (LIFO) ----------
class Stack {
    struct SNode { int id; SNode* next; };
    SNode* top;
public:
    Stack() : top(nullptr) {}
    ~Stack() { while (top) { SNode* t = top; top = top->next; delete t; } }

    void push(int id) {
        top = new SNode{id, top};
        cout << "Operation for Product ID " << id << " added to stack.\n";
    }
    void pop() {
        if (!top) { cout << "Stack is empty.\n"; return; }
        SNode* t = top;
        cout << "Removed last operation: Product ID " << t->id << "\n";
        top = top->next;
        delete t;
    }
    void display() {
        if (!top) { cout << "Stack is empty.\n"; return; }
        cout << "Stack (Top to Bottom): ";
        for (SNode* c = top; c; c = c->next) cout << c->id << " ";
        cout << "\n";
    }
};

// ---------- Queue (FIFO) ----------
class Queue {
    struct QNode { int orderId; QNode* next; };
    QNode *front, *rear;
public:
    Queue() : front(nullptr), rear(nullptr) {}
    ~Queue() { while (front) { QNode* t = front; front = front->next; delete t; } }

    void enqueue(int id) {
        QNode* n = new QNode{id, nullptr};
        if (!rear) front = rear = n;
        else { rear->next = n; rear = n; }
        cout << "Order " << id << " added to queue.\n";
    }
    void process() {
        if (!front) { cout << "No pending orders.\n"; return; }
        QNode* t = front;
        cout << "Processing Order: " << t->orderId << "\n";
        front = front->next;
        if (!front) rear = nullptr;
        delete t;
    }
    void display() {
        if (!front) { cout << "Queue is empty.\n"; return; }
        cout << "Pending Orders (Front to Rear): ";
        for (QNode* c = front; c; c = c->next) cout << c->orderId << " ";
        cout << "\n";
    }
};

// ---------- Array demo ----------
void demonstrateArray() {
    Product arr[5] = {
        {1, "Rice", 250.0, 50, nullptr},
        {2, "Sugar", 140.5, 8, nullptr},
        {3, "Tea", 600.0, 25, nullptr},
        {4, "Milk", 220.0, 5, nullptr},
        {5, "Oil", 480.0, 30, nullptr}
    };
    cout << "\n--- Array of 5 Products ---\n";
    cout << "ID\tName\t\tPrice\tQty\n";
    for (int i = 0; i < 5; i++)
        cout << arr[i].id << "\t" << arr[i].name << "\t\t" << arr[i].price << "\t" << arr[i].quantity << "\n";
}

void showMenu() {
    cout << "\n==============================================\n";
    cout << "        INVENTORY MANAGEMENT SYSTEM\n";
    cout << "==============================================\n";
    cout << "1.  Add Product\n";
    cout << "2.  Display Products\n";
    cout << "3.  Search Product\n";
    cout << "4.  Update Stock\n";
    cout << "5.  Delete Product\n";
    cout << "6.  Display Low-Stock Products\n";
    cout << "7.  Add Stock Operation to Stack\n";
    cout << "8.  Remove Last Stack Operation\n";
    cout << "9.  Display Stack\n";
    cout << "10. Add Order to Queue\n";
    cout << "11. Process Order\n";
    cout << "12. Display Queue\n";
    cout << "13. Demonstrate Array\n";
    cout << "14. Exit\n\n";
    cout << "Enter your choice: ";
}

int main() {
    Inventory inv;
    Stack st;
    Queue q;
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            int id, qty;
            string name;
            double price;
            cout << "Enter ID: "; cin >> id;
            cout << "Enter Name: "; cin.ignore(); getline(cin, name);
            cout << "Enter Price: "; cin >> price;
            cout << "Enter Quantity: "; cin >> qty;
            inv.addProduct(id, name, price, qty);
            break;
        }
        case 2:
            inv.display();
            break;
        case 3: {
            int id;
            cout << "Enter Product ID: "; cin >> id;
            inv.search(id);
            break;
        }
        case 4: {
            int id, qty;
            cout << "Enter Product ID: "; cin >> id;
            cout << "Enter new Quantity: "; cin >> qty;
            inv.updateStock(id, qty);
            break;
        }
        case 5: {
            int id;
            cout << "Enter Product ID to delete: "; cin >> id;
            inv.deleteProduct(id);
            break;
        }
        case 6:
            inv.lowStock();
            break;
        case 7: {
            int id;
            cout << "Enter Product ID: "; cin >> id;
            st.push(id);
            break;
        }
        case 8:
            st.pop();
            break;
        case 9:
            st.display();
            break;
        case 10: {
            int id;
            cout << "Enter Order ID: "; cin >> id;
            q.enqueue(id);
            break;
        }
        case 11:
            q.process();
            break;
        case 12:
            q.display();
            break;
        case 13:
            demonstrateArray();
            break;
        case 14:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 14);

    return 0;
}