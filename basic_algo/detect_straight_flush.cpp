#include <iostream>
#include <vector>
#include <ctime>
#include <bitset>
using namespace std;

/* Question:
Given a set of poker cards. Figure out if a straight flush exists (incl. royal flush) in the
set the poker cards given.
*/

//#define RAND_CARDS

const int number_of_suits = 4;
const int number_of_rand_cards = 30;
const int number_of_ranks = 13;

//types of card
typedef enum suit_t {
	spade = 0,
	club,
	diamond,
	heart
}suit_t;

//value each card holds 
typedef enum rank_t {
	ace = 1,
	two,
	three,
	four,
	five,
	six,
	seven,
	eight,
	nine,
	ten,
	jack,
	king,
	queen
}rank_t;


typedef struct poker_card {
	suit_t suit;
	rank_t rank;
	poker_card(suit_t suit_, rank_t rank_) : suit(suit_), rank(rank_) {}
}poker_card;

class Poker {
	vector<poker_card> cards;

private:
	void inc_count(const bitset<number_of_ranks> &bs, int count[number_of_suits], suit_t suit, int index) {
		if (bs.test(index)) {
			count[suit]++;
		}
		else {
			count[suit] = 0;
		}
	}

	bool detect_street(const bitset<number_of_ranks> &spade_bs, const bitset<number_of_ranks> &club_bs,
		const bitset<number_of_ranks> &diamond_bs, const bitset<number_of_ranks> &heart_bs) {
		int count[number_of_suits] = { 0 };
		int index = 0; // index starts at 0, bc. the rank 'ace' is assigned to value 0

		// iterate number_of_ranks+1 times to cover case: ten, jack, king, queen, ace
		for (int i = 0; i < number_of_ranks + 1; i++) {
			inc_count(spade_bs, count, spade, index);
			inc_count(club_bs, count, club, index);
			inc_count(diamond_bs, count, diamond, index);
			inc_count(heart_bs, count, heart, index);

			if (count[spade] == 5 ||
				count[club] == 5 ||
				count[diamond] == 5 ||
				count[heart] == 5) {
				return true;
			}

			index++;
			index = index % number_of_ranks;
		}

		return false;
	}

public:
	void add_card(const poker_card &c) {
		cards.push_back(c);
	}

	bool detect_straight_flush() {
		// if cards size is less than 5, we cannot have a flush
		if (cards.size() < 5) {
			return false;
		}

		// used space are 16 bytes -> O(1)
		// could be reduced to bitsets<13*4> -> are 8 bytes
		bitset<number_of_ranks> spade_bs;
		bitset<number_of_ranks> club_bs;
		bitset<number_of_ranks> diamond_bs;
		bitset<number_of_ranks> heart_bs;

		// O(n)
		for (int i = 0; i < cards.size(); i++) {
			switch (cards[i].suit) {
			case spade:	spade_bs.set(cards[i].rank - 1);
				break;

			case club: club_bs.set(cards[i].rank - 1);
				break;

			case diamond: diamond_bs.set(cards[i].rank - 1);
				break;

			case heart: heart_bs.set(cards[i].rank - 1);
				break;

			default:
				break;
			}
		}

		// check if one bitsize field is at least 5 cards, otherwize return false
		if (spade_bs.size() < 5 &&
			club_bs.size() < 5 &&
			diamond_bs.size() < 5 &&
			heart_bs.size() < 5) {
			return false;
		}

		// O(1)
		return detect_street(spade_bs, club_bs, diamond_bs, heart_bs);
	}
};

int main() {
	// your code goes here

	Poker p1;
	Poker p2;
	Poker p3;

#ifdef RAND_CARDS

	srand(time(0));

	for (int i = 0; i < number_of_rand_cards; i++) {
		int suite_rand = rand() % number_of_suits; // generates a suit between 0 and number_of_suits - 1
		int rank_rand = 1 + rand() % number_of_cards; // generates a suite between 1 and number_of_cards - 1

		p1.add_card(poker_card(static_cast<suit_t>(suite_rand), static_cast<rank_t>(rank_rand)));
	}

	cout << p1.detect_straight_flush() << endl;

#else

	p1.add_card(poker_card(heart, ten));
	p1.add_card(poker_card(heart, king));
	p1.add_card(poker_card(heart, ace));
	p1.add_card(poker_card(heart, queen));
	p1.add_card(poker_card(heart, jack));

	p2.add_card(poker_card(heart, two));
	p2.add_card(poker_card(heart, three));
	p2.add_card(poker_card(heart, ace));
	p2.add_card(poker_card(heart, four));
	p2.add_card(poker_card(heart, five));

	p3.add_card(poker_card(heart, two));
	p3.add_card(poker_card(heart, three));
	p3.add_card(poker_card(heart, seven));
	p3.add_card(poker_card(heart, four));
	p3.add_card(poker_card(heart, five));

	cout << p1.detect_straight_flush() << endl;
	cout << p2.detect_straight_flush() << endl;
	cout << p3.detect_straight_flush() << endl;

#endif

	return 0;
}