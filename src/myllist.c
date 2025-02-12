#include <stdlib.h>
#include <stdio.h>
#include "../include/myllist.h" 

#define CHECK_LIST_EMPTY(head) \
	if (head == NULL) { \
		printf("List is empty\n"); \
		return FALSE; \
	}

struct node{
	int value; /* Node value */
	struct node *next; /* Pointer to the next element of the list */
	struct node *prev; /*Pointer to the prev element of the list */
};

static enum boolean{FALSE, TRUE}boolean;

static struct node *init_node(int value);

void init_list(struct list **list){
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
}
void insert(struct list *list, int value){
	/* Check if list is initialized. If not call init_list */
	if (list == NULL){
		printf("Initializing list...\n");
		init_list(&list);
	}
	struct node *new_node = init_node(value); 
	
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
			printf("%d", current->value);
			break;
		}
		printf("%d, ", current->value);
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

int remove_element(struct list *list, int value){
	
	if (list == NULL){
		printf("List is NULL.\n");
		return FALSE;
	}
	CHECK_LIST_EMPTY(list->head);

	struct node *current = list->head;

	/* Check if the value to delete is existing on the head */
	if (list->head->value == value){
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
		free(current);
		return TRUE;
	}
	struct node *prev = NULL;

	while(current != NULL){
		if (current->value == value && current == list->tail){
			prev->next = NULL; /* Equivalent to saying: prev->next = current->next */ 
			list->tail = prev;
			free(current);
			return TRUE;
		}
		if(current->value == value){
			prev->next = current->next; /* Make the prev node's next pointer point to the next node */
			current->next->prev = prev; /* Make the the next node's previous pointer point to the prev node */
			free(current);
			return TRUE;
		}		
		prev = current;		
		current = current->next;
	}
	return FALSE;
}

int replace(struct list *list, int el, int value){
	struct node *current = list->head;

	CHECK_LIST_EMPTY(list->head);
	
	while (current != NULL){
		if (current->value == el){
			/* Found */
			current->value = value;
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
			printf("%d", tail->value);
			break;
		}
		printf("%d, ", tail->value);
		tail = tail->prev;
	}
	printf("]\n");
}
void print_reverse_recur(struct node *head){
	if (head == NULL){
		return;
	}
	print_reverse_recur(head->next);
	if (head->next == NULL){
		printf("[%d, ", head->value);
	}else if (head->prev == NULL){
		printf("%d]\n", head->value);
	}else{
		printf("%d, ", head->value);
	}

}

void reverse(struct list *list){
	if (list == NULL){
		printf("List is NULL.\n");
		return;
	}
	
	struct node *head = list->head;
	struct node *tail = list->tail;

	while (head != NULL){
		int temp = head->value;

		head->value = tail->value;
		tail->value = temp;

		/* For even list length && For odd list length*/
		if (head->next == tail->prev || head->next == tail){
			break;
		}
		head = head->next;
		tail = tail->prev;
	}
}

static struct node *init_node(int value){
	struct node *new_node = malloc(sizeof(struct node));
	if (new_node == NULL){
		fprintf(stderr, "Error allocating memory.\n");
		return NULL;
	}

	new_node->value = value;
	new_node->next = NULL;
	new_node->prev = NULL;
	return new_node;
}

int get_element(struct list *list, int index) {
	if (list == NULL){
		printf("List is NULL.\n");
		return -1;
	}
	if (list->head == NULL || index >= list->length || index < 0){
		return -1;	
	}
	struct node *current = list->head;
	for (int i=0; i<index; i++){
		current = current->next;
	}

	return current->value;
}
