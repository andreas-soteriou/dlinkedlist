#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../include/dllist.h" 

#define CHECK_LIST_EMPTY(head) \
	if (head == NULL) { \
		printf("List is empty\n"); \
		return FALSE; \
	}

struct node{
	void *element; /* Node element*/
	struct node *next; /* Pointer to the next element of the list */
	struct node *prev; /*Pointer to the prev element of the list */
};

static enum boolean{FALSE, TRUE}boolean;

static struct node *init_node(void *element, size_t element_size);

void init_list(struct list **list, print_fptr pfptr, comp_fptr cfptr){
	if (*list != NULL){
		/* List already initialized */
		printf("List already initialized. STOP\n");
		return;
	}
	*list = malloc(sizeof(struct list));
	if (*list == NULL){
		printf("Error allocating memory.\n");
		return;
	}
	(*list)->head = NULL;
	(*list)->tail = NULL;
	(*list)->length = 0;

	/* Assign the print and compare function pointers */
	(*list)->print = pfptr;
	(*list)->compare = cfptr;
}
void insert(struct list *list, void *element, size_t element_size){
	/* Check if list is initialized. If not call init_list */
	if (list == NULL){
		printf("Error: List is not initialized. Call 'init_list()' first.\n");
		return;
	}
	struct node *new_node = init_node(element, element_size); 
	
	/* Check if list is empty */
	if (list->head == NULL){
		list->head = new_node; /* Make the head be the new node */
		list->tail = list->head; /* Make the tail be the new node */
	}else{
		/* Insert at the end of the list */
		list->tail->next = new_node; /* Make the current tail point to the new node */
		new_node->prev = list->tail; /* Make the new node's prev point to the current tail */
		list->tail = new_node; /* Make the new tail be the new node */
	}	
	list->length++;
}
int clear(struct list *list){
	
	if (list == NULL){
		printf("List is NULL.\n");
		return FALSE;
	}
	//CHECK_LIST_EMPTY(list->head);
	
	if (list->head == NULL || list->length == 0){
		return FALSE;
	}
	struct node *current = list->head;
	
	while(list->head != NULL){
		current = list->head;
		list->head = list->head->next;
		free(current->element);
		free(current);
		list->length--;
	}
	list->tail = NULL;
	return TRUE;
}

void delete_list(struct list **list){
	if (*list == NULL){
		printf("List is NULL.\n");
		return;
	}
	
	clear(*list);
	free(*list);
	*list = NULL;
}

void print(struct list *list){
	if (list == NULL){
		printf("List is NULL.\n");
		return;
	}
	struct node *current = list->head;
	if (current == NULL){
		printf("List is empty.\n");
		return;
	}
	printf("[");
	while (current != NULL){
		if (current->next == NULL){
			/*Tail node*/ 
			list->print(current->element);
			break;
		}
		list->print(current->element);
		current = current->next;
	}
	printf("]\n");
} 

unsigned int llength(struct list *list){
	if (list == NULL){
		return 0;
	}
	return list->length;
}

int remove_element(struct list *list, void *element){
	
	if (list == NULL){
		printf("List is NULL.\n");
		return FALSE;
	}
	CHECK_LIST_EMPTY(list->head);

	struct node *current = list->head;

	/* Check if the value to delete is existing on the head */
	if (list->compare(list->head->element, element)){
		/* Make the head jump to the next node */
		list->head = list->head->next;
		/* 
		 * Important Notice:
		 * 1) If L > 1 : Then after the jump list->head is not NULL, so make the new prev node point to NULL
		 * 2) If L == 1: Then list->head is NULL so don't make the prev node point to NULL, otherwise
		 * SEGMENTATION FAULT will occur, because list->head->prev is trying to access the previous node from a NUL* L pointer
		 * */
		if (list->head != NULL){
			list->head->prev = NULL; /*New head neds the prev node to point to NULL */
		}else{
			list->tail = NULL;
		}
		free(current->element);
		free(current);
		list->length--;
		return TRUE;
	}
	struct node *prev = NULL;

	while(current != NULL){
		if (list->compare(current->element, element) && current == list->tail){
			prev->next = NULL; /* Equivalent to saying: prev->next = current->next */ 
			list->tail = prev;
			free(current->element);
			free(current);
			list->length--;
			return TRUE;
		}
		/* Not tail */
		if(list->compare(current->element, element)){
			prev->next = current->next; /* Make the prev node's next pointer point to the next node */
			current->next->prev = prev; /* Make the the next node's previous pointer point to the prev node */
			free(current->element);
			free(current);
			list->length--;
			return TRUE;
		}		
		prev = current;
		current = current->next;
	}
	return FALSE;
}

int replace(struct list *list, void *dest_element, void *src_element, size_t src_size){
	struct node *current = list->head;

	CHECK_LIST_EMPTY(list->head);
	
	while (current != NULL){
		if (list->compare(current->element, dest_element)){
			/* Reallocate the memory to the newly size */
			void *new_element = calloc(1, src_size);
			if (new_element == NULL){
				printf("Error allocating memory.\n");
				return FALSE;
			}
			memcpy(new_element, src_element, src_size);
			free(current->element);
			current->element = new_element;
			return TRUE;
		}
		current = current->next;
	}
	/* Element not found in the list */
	return FALSE;
}

void print_reverse(struct list *list){
	if (list == NULL){
		printf("List is NULL.\n");
		return;
	}
	struct node *tail = list->tail;
	
	printf("[");
	while (tail != NULL){
		if (tail->prev == NULL){
			/*Tail node */
			list->print(tail->element);
			break;
		}
		list->print(tail->element);
		tail = tail->prev;
	}
	printf("]\n");
}
void reverse(struct list *list){
	if (list == NULL){
		printf("List is NULL.\n");
		return;
	}
	
	struct node *head = list->head;
	struct node *tail = list->tail;

	while (head != NULL){
		void *temp = head->element;

		head->element = tail->element;
		tail->element = temp;

		/* For even list length && For odd list length*/
		if (head->next == tail->prev || head->next == tail){
			break;
		}
		head = head->next;
		tail = tail->prev;
	}
}

static struct node *init_node(void *element, size_t element_size){
	struct node *new_node = malloc(sizeof(struct node));
	if (new_node == NULL){
		fprintf(stderr, "Error allocating memory.\n");
		return NULL;
	}
	
	/* Allocate memory for the element itself */
	new_node->element = malloc(element_size);
	if (new_node->element == NULL){
		fprintf(stderr, "Error allocating memory.\n");
		free(new_node);
		return NULL;
	}
	/* Use memcpy to copy the memory of the new element */
	memcpy(new_node->element, element, element_size);
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}

void *get_element(struct list *list, int index) {
	if (list == NULL){
		printf("List is NULL.\n");
		return NULL;
	}
	if (list->head == NULL || index >= list->length || index < 0){
		return NULL;	
	}
	struct node *current = list->head;
	for (int i=0; i<index; i++){
		current = current->next;
	}

	return current->element;
}
