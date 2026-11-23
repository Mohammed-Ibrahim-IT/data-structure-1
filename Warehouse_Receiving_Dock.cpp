#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct Shipment { int id; string name; int quantity; string location; };
void printShipment(const Shipment& s) { cout << "ID: " << s.id << " | Name: " << s.name << " | Quantity: " << s.quantity << " | Location: " << s.location << '\n'; }

struct StackNode { Shipment data; StackNode* next; };
class ScanStack {
    StackNode* topNode = nullptr; int count = 0;
public:
    ~ScanStack() { Shipment s; while (pop(s)) {} }
    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
    void push(const Shipment& s) { topNode = new StackNode{s, topNode}; ++count; }
    bool pop(Shipment& s) { if (isEmpty()) return false; StackNode* old = topNode; s = old->data; topNode = old->next; delete old; --count; return true; }
    bool peek(Shipment& s) const { if (isEmpty()) return false; s = topNode->data; return true; }
    void show() const { if (isEmpty()) cout << "No completed scans.\n"; for (StackNode* p = topNode; p; p = p->next) printShipment(p->data); }
};

struct QueueNode { Shipment data; QueueNode* next; };
class PalletQueue {
    QueueNode *first = nullptr, *last = nullptr; int count = 0;
public:
    ~PalletQueue() { Shipment s; while (dequeue(s)) {} }
    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
    void enqueue(const Shipment& s) { QueueNode* n = new QueueNode{s, nullptr}; if (last) last->next = n; else first = n; last = n; ++count; }
    bool front(Shipment& s) const { if (isEmpty()) return false; s = first->data; return true; }
    bool dequeue(Shipment& s) { if (isEmpty()) return false; QueueNode* n = first; s = n->data; first = n->next; if (!first) last = nullptr; delete n; --count; return true; }
    bool remove(int id) { QueueNode *p = first, *prev = nullptr; while (p && p->data.id != id) { prev = p; p = p->next; } if (!p) return false; if (prev) prev->next = p->next; else first = p->next; if (last == p) last = prev; delete p; --count; return true; }
    bool update(const Shipment& s) { for (QueueNode* p = first; p; p = p->next) if (p->data.id == s.id) { p->data = s; return true; } return false; }
    void show() const { if (isEmpty()) cout << "No pallets waiting.\n"; for (QueueNode* p = first; p; p = p->next) printShipment(p->data); }
};

struct ListNode { Shipment data; ListNode* next; };
class StockList {
    ListNode* head = nullptr; int count = 0;
public:
    ~StockList() { while (head) { ListNode* n = head; head = head->next; delete n; } }
    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
    void insert(const Shipment& s) { head = new ListNode{s, head}; ++count; }
    Shipment* search(int id) { for (ListNode* p = head; p; p = p->next) if (p->data.id == id) return &p->data; return nullptr; }
    bool update(const Shipment& s) { Shipment* p = search(s.id); if (!p) return false; *p = s; return true; }
    bool remove(int id) { ListNode *p = head, *prev = nullptr; while (p && p->data.id != id) { prev = p; p = p->next; } if (!p) return false; if (prev) prev->next = p->next; else head = p->next; delete p; --count; return true; }
    void show() const { if (isEmpty()) cout << "No stock records.\n"; for (ListNode* p = head; p; p = p->next) printShipment(p->data); }
    void linearSearchByName(const string& name) const { int matches = 0; for (ListNode* p = head; p; p = p->next) if (p->data.name == name) { printShipment(p->data); ++matches; } if (!matches) cout << "No matching stock records.\n"; cout << "Matches: " << matches << '\n'; }
};

struct TreeNode { Shipment data; TreeNode *left, *right; };
class ShipmentBST {
    TreeNode* root = nullptr; int count = 0;
    static TreeNode* insertNode(TreeNode* n, const Shipment& s) { if (!n) return new TreeNode{s, nullptr, nullptr}; if (s.id < n->data.id) n->left = insertNode(n->left, s); else if (s.id > n->data.id) n->right = insertNode(n->right, s); return n; }
    static TreeNode* eraseNode(TreeNode* n, int id) { if (!n) return nullptr; if (id < n->data.id) n->left = eraseNode(n->left, id); else if (id > n->data.id) n->right = eraseNode(n->right, id); else { if (!n->left) { TreeNode* r = n->right; delete n; return r; } if (!n->right) { TreeNode* l = n->left; delete n; return l; } TreeNode* successor = n->right; while (successor->left) successor = successor->left; n->data = successor->data; n->right = eraseNode(n->right, successor->data.id); } return n; }
    static void inorder(TreeNode* n) { if (!n) return; inorder(n->left); printShipment(n->data); inorder(n->right); }
    static void preorder(TreeNode* n) { if (!n) return; printShipment(n->data); preorder(n->left); preorder(n->right); }
    static void clear(TreeNode* n) { if (!n) return; clear(n->left); clear(n->right); delete n; }
public:
    ~ShipmentBST() { clear(root); }
    bool isEmpty() const { return count == 0; }
    int size() const { return count; }
    Shipment* search(int id) const { TreeNode* p = root; while (p) { if (p->data.id == id) return &p->data; p = id < p->data.id ? p->left : p->right; } return nullptr; }
    bool insert(const Shipment& s) { if (search(s.id)) return false; root = insertNode(root, s); ++count; return true; }
    bool remove(int id) { if (!search(id)) return false; root = eraseNode(root, id); --count; return true; }
    void showInorder() const { if (isEmpty()) cout << "No shipments registered.\n"; else inorder(root); }
    void showPreorder() const { if (isEmpty()) cout << "No shipments registered.\n"; else preorder(root); }
};

int readInt(const string& prompt, int minimum) { int x; while (true) { cout << prompt; if (cin >> x && x >= minimum) { cin.ignore(numeric_limits<streamsize>::max(), '\n'); return x; } cout << "Invalid number. Try again.\n"; cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); } }
string readText(const string& prompt) { string x; do { cout << prompt; getline(cin, x); if (x.find_first_not_of(" \t") == string::npos) { cout << "This field cannot be empty.\n"; x.clear(); } } while (x.empty()); return x; }

int main() {
    ScanStack scans; PalletQueue waiting; StockList stock; ShipmentBST shipments;
    while (true) {
        cout << "\n===== Warehouse Receiving Dock =====\n"
             << "1. Register incoming pallet\n2. Receive next pallet\n3. Show waiting queue\n"
             << "4. Show completed scans (Stack)\n5. Show stock (Linked List)\n"
             << "6. Search shipment by ID (BST)\n7. Show shipments inorder (BST)\n"
             << "8. Show shipments preorder (BST)\n9. Update shipment name/quantity\n"
             << "10. Delete shipment\n11. Search received stock by name (Linear Search)\n"
             << "12. Show counts and empty states\n13. Peek next waiting pallet\n"
             << "14. Peek most recent scan\n15. Pop most recent scan from history\n0. Exit\n";
        int choice = readInt("Choose: ", 0);
        if (choice == 0) break;
        if (choice == 1) {
            Shipment s; s.id = readInt("Shipment ID: ", 1);
            if (shipments.search(s.id)) { cout << "This ID already exists.\n"; continue; }
            s.name = readText("Product name: "); s.quantity = readInt("Quantity: ", 1); s.location = "Not assigned";
            shipments.insert(s); waiting.enqueue(s); cout << "Pallet registered and queued.\n";
        } else if (choice == 2) {
            Shipment s;
            if (!waiting.front(s)) { cout << "No pallets to receive.\n"; continue; }
            string location = readText("Storage location: ");
            waiting.dequeue(s); s.location = location; stock.insert(s); scans.push(s);
            Shipment* indexed = shipments.search(s.id); if (indexed) *indexed = s;
            cout << "Pallet received, stock updated, and scan recorded.\n";
        } else if (choice == 3) waiting.show();
        else if (choice == 4) scans.show();
        else if (choice == 5) stock.show();
        else if (choice == 6) { int id = readInt("Shipment ID: ", 1); Shipment* p = shipments.search(id); if (p) printShipment(*p); else cout << "Shipment not found.\n"; }
        else if (choice == 7) shipments.showInorder();
        else if (choice == 8) shipments.showPreorder();
        else if (choice == 9) {
            int id = readInt("Shipment ID to update: ", 1); Shipment* p = shipments.search(id);
            if (!p) { cout << "Shipment not found.\n"; continue; }
            Shipment updated = *p; updated.name = readText("New product name: "); updated.quantity = readInt("New quantity: ", 1);
            *p = updated; waiting.update(updated); stock.update(updated);
            cout << "Current shipment record updated. Completed scan history remains a historical snapshot.\n";
        } else if (choice == 10) {
            int id = readInt("Shipment ID to delete: ", 1);
            if (!shipments.remove(id)) { cout << "Shipment not found.\n"; continue; }
            waiting.remove(id); stock.remove(id);
            cout << "Shipment removed from index and active queue/stock. Historical scans are retained.\n";
        } else if (choice == 11) stock.linearSearchByName(readText("Exact product name: "));
        else if (choice == 12) {
            cout << "Waiting queue: " << waiting.size() << " (empty: " << (waiting.isEmpty() ? "yes" : "no") << ")\n";
            cout << "Stock list: " << stock.size() << " (empty: " << (stock.isEmpty() ? "yes" : "no") << ")\n";
            cout << "Shipment BST: " << shipments.size() << " (empty: " << (shipments.isEmpty() ? "yes" : "no") << ")\n";
            cout << "Scan history: " << scans.size() << " (empty: " << (scans.isEmpty() ? "yes" : "no") << ")\n";
        } else if (choice == 13) { Shipment s; if (waiting.front(s)) printShipment(s); else cout << "Queue is empty.\n"; }
        else if (choice == 14) { Shipment s; if (scans.peek(s)) printShipment(s); else cout << "Stack is empty.\n"; }
        else if (choice == 15) { Shipment s; if (scans.pop(s)) { cout << "Removed historical scan: "; printShipment(s); } else cout << "Stack is empty.\n"; }
        else cout << "Invalid choice.\n";
    }
    return 0;
}
