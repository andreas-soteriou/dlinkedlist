# Linked List API
This is a guide on how to use the linked list CRUD api

## This API provides
* Insertion
* Deletion
* Update
* Print List 
* Print in reverse
* Recursive print in reverse
* Reverse List
* Empty List 
* List deallocation / deletion

## Build
1. Modify Makefile according to your main program. See also Makefile's description for more details.

2. Build the executable file by running the below command
```
make
```
3. Use the below command to remove the object files and the executable file.
```
make clean
```

## How to use the list structure 

1. Please take the moment and read the comments for each operation in the include/myllist.h.
2. Initialize list before calling any CRUD operations
3. Delete the list at the end of it's use, to prevent memory leaks.
5. Example code given:
    ``` c
    #include <stdio.h>
    #include "include/myllist.h"

    int main(){
        struct list *list =  NULL;
        // Initialize the list before any CRUD Operations
        init_list(&list);
        
        /* CRUD Operations */
        for (int i=0; i<=9; i++){
            insert(list, i);
        }
        print(list);

        remove_element(list, 5);
        print(list);
        
        replace(list, 3, -3);
        reverse(list);
        print(list);

        clear(list);
        print(list);
        // Deallocate the list at the end
        delete_list(&list);
        print(list);

        return 0;
    }
    ```
## Example Result
![Doubly Linked List Demo](testcases/ddlist-test.png)

## Ideas for the future
1. Allow storing any data type
2. Implement file stream api to store list in disk.
3. Sort list 
4. Retrieve element
5. Apply filtering or mapping 

## Disclaimer
This is by no means the perfect Linked list data structure, and we are open for any improvements, as we ourselves are also improving it day by day.

