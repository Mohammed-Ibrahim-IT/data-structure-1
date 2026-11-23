# Test plan (updated version)

| Test | Steps | Expected result |
|---|---|---|
| Empty structures | 12, 2, 13, 14, 15, 6 with unknown ID | All empty/error operations safely handled |
| Register | 1 -> ID 20, Bolts, 5 | Queue and BST size become 1 |
| Duplicate ID | Register ID 20 again | Duplicate rejected |
| FIFO integration | Register ID 10 then receive next | ID 20 received first, location assigned; scan and stock updated |
| BST traversal | 7 then 8 | Inorder sorted by ID, preorder root-first |
| Linear search | 11 -> Bolts | Received stock match displayed |
| Update received | 9 -> ID 20, new name and quantity | BST and stock reflect changes; scan history unchanged |
| Update waiting | 9 -> ID 10, new name and quantity | BST and queue reflect changes |
| Delete waiting | 10 -> ID 10 | Removed from BST and queue |
| Delete received | 10 -> ID 20 | Removed from BST and stock, scan history retained |
| Stack peek/pop | 14 then 15 | Most recent scan displayed then removed |
| Invalid input | Enter nonnumeric menu choice; enter 99 | Prompt recovers; invalid choice reported |
| Single-node BST | Register only one shipment then delete | Root deletion works |
| Two-child BST | Register IDs 20,10,30; delete 20 | BST remains searchable and inorder sorted |

Run actual tests on your final environment and capture screenshots for the report. The provided sample output is an actual scripted run, not proof of all edge cases.
