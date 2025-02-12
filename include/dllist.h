#ifndef DLLIST_H 
#define DLLIST_H 

/* This is the list node.
 * Do not use this structure to create your list insta* nce
 * */
struct node;

/*
 * List strucure
 * Use this list structure to create your list instanc* e
 */
struct list{
	struct node *head;
	struct node *tail;
	unsigned int length;
};

/* Initialize list 
 * Please don't forget to call this function before using the list
 * */
void init_list(struct list **list);

/* Insert a new element to the list */
void insert(struct list *list, int value);

/* Clear the list 
 * Does not mean that the list has been deleted
 * */
int clear(struct list *list);

/*
 * Delete the list / Deallocates the list
 * */
void delete_list(struct list **list);

/* Prints the list */
void print(struct list *list);

/* Calculates the length of the list */
unsigned int llength(struct list *list);

/* Removes the first occurence of value if exists
 * @return 1 in successfull removal, 0 in unsuccessfull
 * */
int remove_element(struct list *list, int value);

/* Replace the first occurence of el with value 
 * @returns 1 in success, 0 in failure
 * */
int replace(struct list *list, int el, int value);

/* Print list in reverse */
void print_reverse(struct list *list);

/* Print list in reverse using recursion */
void print_reverse_recur(struct node *head);

/* Reverse the list */
void reverse(struct list *list);

/* Retrieves the element at index */ 
int get_element(struct list *list, int index);
#endif /* DLLIST_H*/

