#include <iostream>
#include "History.hpp"
#include "Transaction.hpp"


#ifndef MARMOSET_TESTING
unsigned int Transaction::assigned_trans_id = 0;
int main() {
	Transaction first = Transaction("VGRO", 1, 05, 2018, true, 150, 10300.14);
	Transaction second = Transaction("VGRO", 1, 05, 2018, true, 150, 10300.14);

	if (first < second) {
		std::cout << "The first transaciton occurs before th esecond transaction" << std::endl;
	}
	else {
		std::cout << "The second transaction occurs before the first transaction" << std::endl;
	}


	History trans_history{};
	trans_history.read_history();
  return 0;
}
#endif
