#include <iostream>
#include <vector>
#include <ctime>
#include <bitset>
using namespace std;

/* Question:
Given a set of poker cards. Figure out if a straight flush exists (incl. royal flush) in the set the poker cards given.
*/

//#define RAND_CARDS

const int number_of_suits = 4;
const int number_of_rand_cards = 30;
const int number_of_cards = 13;

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

class Poker {
	vector<suit_t> suits;
	vector<rank_t> ranks;

private:
	void inc_count(const bitset<number_of_cards> &bs, int count[number_of_suits], suit_t suit, int index) {
		if (bs.test(index)) {
			count[suit]++;
		}
		else {
			count[suit] = 0;
		}
	}

	bool detect_street(const bitset<number_of_cards> &spade_bs, const bitset<number_of_cards> &club_bs,
		const bitset<number_of_cards> &diamond_bs, const bitset<number_of_cards> &heart_bs) {
		int count[number_of_suits] = { 0 };
		int index = 1;

		for (int i = 0; i < number_of_cards; i++) {
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
			index = index % number_of_cards;
		}

		return false;
	}

public:
	void add_card(const suit_t &s, const rank_t &r) {
		suits.push_back(s);
		ranks.push_back(r);
	}

	bool detect_straight_flush() {
		// used space are 16 bytes -> O(1)
		// could be reduced to bitsets<13*4> -> are 8 bytes
		bitset<number_of_cards> spade_bs;
		bitset<number_of_cards> club_bs;
		bitset<number_of_cards> diamond_bs;
		bitset<number_of_cards> heart_bs;

		// O(n)
		for (int i = 0; i < suits.size(); i++) {
			switch (suits[i]) {
			case spade:	spade_bs.set(ranks[i] - 1);
				break;

			case club: club_bs.set(ranks[i] - 1);
				break;

			case diamond: diamond_bs.set(ranks[i] - 1);
				break;

			case heart: heart_bs.set(ranks[i] - 1);
				break;

			default:
				break;
			}
		}

		// O(1)
		return detect_street(spade_bs, club_bs, diamond_bs, heart_bs);
	}
};

int main() {
	// your code goes here

	Poker p;

#ifdef RAND_CARDS

	srand(time(0));

	for (int i = 0; i < number_of_rand_cards; i++) {
		int suite_rand = rand() % (number_of_suits - 1);
		int rank_rand = 1 + rand() % (number_of_cards - 1);

		p.add_card(static_cast<suit_t>(suite_rand), static_cast<rank_t>(rank_rand));
	}

#else

	p.add_card(heart, ten);
	p.add_card(heart, king);
	p.add_card(heart, ace);
	p.add_card(heart, queen);
	p.add_card(heart, jack);

#endif

	cout << p.detect_straight_flush() << endl;

	return 0;
}