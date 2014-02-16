#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

/* Question:
You are given a deck containing N cards.  While holding the deck:

1. Take the top card off the deck and set it on the table
2. Take the next card off the top and put it on the bottom of the deck
in your hand.
3. Continue steps 1 and 2 until all cards are on the table.  This is a
round.
4. Pick up the deck from the table and repeat steps 1-3 until the deck
is in the original order.

Write a program to determine how many rounds it will take to put a
deck back into the original order.  This will involve creating a data
structure to represent the order of the cards. Do not use an array.
This program should be written in C only. It should take a number of
cards in the deck as a command line argument and write the result to
stdout.
*/

typedef struct card {
	int number;
	struct card_t *next;
}card_t;

typedef struct list {
	card_t *front;
	card_t *back;
}list_t;

card_t *new_card(int number) {
	card_t *node = (card_t*)malloc(sizeof(card_t));
	node->number = number;
	node->next = NULL;
	return node;
}

list_t *create_empty_list() {
	list_t *l = (list_t*)malloc(sizeof(list_t));
	l->front = NULL;
	l->back = NULL;

	return l;
}

void delete_list(list_t **l) {
	card_t *curr = (*l)->front;

	while (curr) {
		card_t *to_del = curr;
		curr = curr->next;
		free(to_del);
	}

	free(*l);
	*l = NULL;
}

card_t *dequeue_front(list_t *l) {
	card_t *front = l->front;

	if (l->front) {
		l->front = l->front->next;
	}

	return front;
}

void enqueue_front(list_t *l, card_t *c) {
	c->next = NULL;

	if (l->front == NULL) {
		l->front = c;
		l->back = c;
	}
	else {
		c->next = l->front;
		l->front = c;
	}
}

void enqueue_back(list_t *l, card_t *c) {
	c->next = NULL;

	if (l->front == NULL) {
		l->front = c;
		l->back = c;
	}
	else {
		l->back->next = c;
		l->back = c;
	}
}

void insert_back(list_t *l, int value) {
	card_t *c = new_card(value);

	if (l->front == NULL) {
		l->front = c;
		l->back = c;
	}
	else {
		l->back->next = c;
		l->back = c;
	}
}

void print(list_t *l) {
	card_t *curr = l->front;

	while (curr != NULL) {
		printf("%d ", curr->number);
		curr = curr->next;
	}
	printf("\n");
}

void init_cards(list_t *hand, unsigned int number_of_cards) {
	unsigned int i = 0;

	for (i = 0; i < number_of_cards; i++) {
		insert_back(hand, i+1);
	}
}

bool is_sorted(list_t *hand, int number_of_cards) {
	card_t *curr = hand->front;

	for (int num = 1; num <= number_of_cards; num++) {
		if (curr->number != num) {
			return false;
		}

		curr = curr->next;
	}

	return true;
}

void next_round(list_t *hand, list_t *table) {
	while (hand->front) {
		card_t *top_card = NULL;

		// Take the top card off the hand and set it on the table
		top_card = dequeue_front(hand);
		enqueue_front(table, top_card);

		if (!top_card) {
			break;
		}

		// Take the next card off the top and put it on the bottom of the hand in your hand
		top_card = dequeue_front(hand);
		if (!top_card) {
			break;
		}
		enqueue_back(hand, top_card);
	}
}

void pickup_hand(list_t **hand, list_t **table) {
	list_t *tmp = *hand;
	*hand = *table;
	*table = tmp;
}

unsigned int get_number_of_rounds(unsigned int number_of_cards) {
	if (number_of_cards <= 2) {
		return number_of_cards;
	}

	list_t *hand = create_empty_list();
	list_t *table = create_empty_list();
	bool is_equal = false;
	unsigned int rounds = 0;

	init_cards(hand, number_of_cards);

	do {
		rounds++;
		next_round(hand, table);
		pickup_hand(&hand, &table);
		//print(hand);
		is_equal = is_sorted(hand, number_of_cards);
	} while (!is_equal);

	delete_list(&hand);
	delete_list(&table);

	return rounds;
}

int main() {
	int i = 0;

	for(i = 0; i <= 10; i++) {
		printf("number of cards: %d, rounds: %d\n", i, get_number_of_rounds(i));
		printf("\n");
	}

	return 0;
}
