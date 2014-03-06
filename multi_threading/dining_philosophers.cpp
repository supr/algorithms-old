/* Question:
Five introspective and introverted philisophers are sitting at a circular table. In front of each
philosopher is a plate of food. A fork (or a chopstick) lies between each philosopher, one by the
philosopher's left hand and one by the right hand. A philosopher cannot each until he or she has
both forks in hand. Forks are picked up at one at a time. If a fork is unavailable, the philosopher
simply waits for the fork to be freed. When a philosopher has to forks, he or she eats bites and then
returns freed. When a philospher has two forks, he or she eats bites and then returns both forks to
the table. If a philosopher cannot obtain both forks for a long time, he or she will strave. Is there
an algorithm that will ensure that no philosopher strave?
*/

#define N 5 // number of philosophers
#define LEFT (i+N-1)%N // number of is left beighbor
#define RIGHT (i+1)%N
#define THINKING 0
#define HUNGRY 1
#define EATING 2

mutex lock[N]; // 1 mutex per philosopher
mutex m;

void philosoper(int i) { // i: philospher number, from 0 to 4
	while (true) {
		think();  // philisopher is thinking
		take_fork(i); // take left fork
		take_for((i + 1) % N); // take right fork; % is modulo operator
		eat(); // yum-yum, spaghetti
		put_fork(i); // put left fork back on the table
		put_fork((i + 1) % N); // put right fork back on the table
	}
}

void take_forks(int i) {
	m.lock();
	state[i] = HUNGRY; // record fact that philosopher i is hungry
	test(i); // try to aquire 2 forks
	m.unlock();

	lock[i].lock(); // block if forks were not acquired
}

void put_forks(int i) {
	m.lock();
	state[i] = THINKING; // philosopher has finished eating
	test(LEFT); // see if left neighbor can now eat
	test(RIGHT); // see if right neighbor can now eat
	m.unlock();
}

void test(i) {
	if (state[i] == HUNGRY && state[LEFT] != EATING) {
		state[i] = EATING;
		m.lock();
	}
}
