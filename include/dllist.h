#ifndef DLLIST_H 
#define DLLIST_H 

#include <stddef.h>

/* This is the list node.
 * Do not use this structure to create your list insta* nce
 * */
struct node;

typedef void (*print_fptr)(void *element); /*The user is responsible to create a print function that displays the element*/
typedef int (*comp_fptr)(void *element1, void *element2); /*The user is responsible to create a comparable function that compares two elements based on the user's criteria*/

/*
 * List strucure
 * Use this list structure to create your list instanc* e
 */
struct list{
	struct node *head;
	struct node *tail;
	unsigned int length;
	print_fptr print; /*The user is responsible to create a print function that displays the element*/ 
	comp_fptr compare; /*The user is responsible to create a comparable function that compares two elements based on the user's criteria. This should return 1 in success, non zero in failure*/
;
};

/* Initialize list 
 * Please don't forget to call this function before using the list
 * */
void init_list(struct list **list, print_fptr pfptr, comp_fptr cfptr);

/* Insert a new element to the list */
void insert(struct list *list, void *element, size_t element_size);

/* Clear the list 
 * Does not mean that the list has been deleted
 * */
int clear(struct list *list);

/*
 * Delete the list / Deallocates the list
 * */
void delete_list(struct list **list);

/* Prints the list
 * This function calls the print element function that the user creates
 * */
void print(struct list *list);

/* Calculates the length of the list */
unsigned int llength(struct list *list);

/* Removes the first occurence of value if exists
 * This function calls the comparable function that the user  creates
 * @return 1 in successfull removal, 0 in unsuccessfull
 * */
int remove_element(struct list *list, void *element);

/* Replace the first occurence of dest_element with  src_element
 * This function calls the comparable function that the user creates
 * @returns 1 in success, 0 in failure
 * */
int replace(struct list *list, void *dest_element, void *src_element, size_t src_size);

/* Print list in reverse */
void print_reverse(struct list *list);

/* Print list in reverse using recursion */
void print_reverse_recur(struct node *head);

/* Reverse the list */
void reverse(struct list *list);

/* Retrieves the element at index */ 
void *get_element(struct list *list, int index);
#endif /* DLLIST_H*/

