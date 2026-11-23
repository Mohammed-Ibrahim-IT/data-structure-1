# CS212 – Warehouse Receiving Dock

## Overview
A C++17 console application for warehouse receiving. Register a shipment in a manually implemented BST and FIFO queue; receive the oldest pallet into a manually implemented stock linked list; record the completed scan in a manually implemented LIFO stack. The BST, waiting queue and stock list remain synchronized when current shipment fields change or shipments are deleted. The scan stack is intentionally historical: old scans are not rewritten or deleted when current shipment records change.

## Compile and run
Linux/macOS: `g++ -std=c++17 -Wall -Wextra -pedantic Source_Code/Warehouse_Receiving_Dock.cpp -o warehouse && ./warehouse`

Windows (MinGW): `g++ -std=c++17 -Wall -Wextra -pedantic Source_Code/Warehouse_Receiving_Dock.cpp -o warehouse.exe` then `warehouse.exe`.

No external dependencies. Data is held in memory and resets when the program exits.

## Menu
1 Register incoming pallet; 2 Receive next pallet; 3 Show queue; 4 Show completed scan history; 5 Show stock; 6 BST search by ID; 7 BST inorder; 8 BST preorder; 9 Update name and quantity; 10 Delete shipment; 11 Linear search received stock by exact name; 12 Sizes and empty states; 13 Queue front; 14 Stack peek; 15 Stack pop; 0 Exit.

## Required data structures and operations
- Linked-node Stack: push, pop, peek, isEmpty, size, display. Completed scans are immutable historical snapshots.
- Linked-node Queue: enqueue, dequeue, front, isEmpty, size, display; also remove/update to keep current records synchronized.
- Singly Linked List: insert, delete, search, update, traverse, size, isEmpty. Received stock locations.
- Unbalanced BST: insert, delete (including two-child case), search by unique ID, inorder, preorder, size, isEmpty.
- Explicit course algorithm: **Linear Search** by exact product name over received stock (O(n)); this is separate from BST search.

## Integration scenarios
A: Register two pallets, then receive one: FIFO queue shrinks; stock, BST location and scan history update.
B: Update a pending shipment and a received shipment: active queue/stock and BST show the new name/quantity. Delete a pending or received shipment: it disappears from active records and BST, while old scan history remains for audit.

## Complexity (n = number of elements in the relevant structure)
Stack push/pop/peek: O(1); Queue enqueue/dequeue/front: O(1); Queue update/remove: O(n); Linked List insert at head: O(1), search/update/delete/traverse: O(n); BST insert/search/delete: average O(log n), worst O(n) when unbalanced; inorder/preorder: O(n); Linear Search: O(n).

## Known limitations
The BST is not self-balancing, and all data is lost on exit. Product-name linear search is exact and case-sensitive. Scan-history pop removes a historical entry only; it does not undo a physical receiving transaction.

## Before submission
1. Add your own PDF/DOCX report to `Report/` (the folder is deliberately left empty except for a placeholder).
2. Add real screenshots of the final executable to `Screenshots/`.
3. Review and add team test evidence to `Tests/`.
4. Complete each student's individual TXT template and replace the URL placeholder after uploading the shared folder to GitHub or OneDrive.
5. Every member submits their own TXT to eLearning. Follow your instructor's AI acknowledgement policy.
