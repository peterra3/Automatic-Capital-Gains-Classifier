#ifndef _HISTORY_TRANSACTION_CPP_
#define _HISTORY_TRANSACTION_CPP_

#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"




//constructor
Transaction::Transaction(std::string ticker_symbol, unsigned int day_date,
	unsigned int month_date, unsigned year_date,
	bool buy_sell_trans, unsigned int number_shares,
	double trans_amount) {

	


	

	this->symbol = ticker_symbol;
	//same for day_date, month, year, number shares, transactions

	this->day = day_date;
	this->month = month_date;
	this->year = year_date;

	//if true, then trans type is equal to something, a boolean
	if (buy_sell_trans == true) {
		this->trans_type = "Buy";
	}
	else {
		this->trans_type = "Sell";
	}



	this->shares = number_shares;
	this->amount = trans_amount;

	//static is like a saved value that is saved forever, like it doesn't change, allows us to save the value through instances of that class
	//basically global variable that only exist in this class/namespace
	this->trans_id = assigned_trans_id;
	++assigned_trans_id;

	// These private members have to be populated so for now put placeholder values on them
	this->acb = 0;
	this->acb_per_share = 0;
	//this makes it more clear that we are accessing  
	this->share_balance = 0;
	this->cgl = 0;

	
	this->p_next = nullptr;
}


Transaction::~Transaction() {
	//used to deallocate stuff from the stack but since there is no dynamic allocated memory in transaction part 1, 
	//we don't need to do anythhing as we are not d allocationg, we don't need to do anything
	//should be empty here, but won't be for history
}


// Overloaded < operator.
//
bool Transaction::operator<(Transaction const& other) {





	//if (my_first_transaction < my_second_transaction)

	if (this->year < other.year) {
		return true;
	}
	
	else if (this->year > other.year) {
		return false;
	}




	if (this->month < other.month) {
		return true;
	}

	else if (this->month > other.month) {
		return false;
	}

	if (this->day < other.day) {
		return true;
	}
	else if (this->day > other.day) {
		return false;
	}


	if (this->day == other.day) {
		if (this->trans_id > other.trans_id) {
			return true;
		}
		else {
			return false;
		}

	}
	//since we are overloading the operator func we can access all private variables directly without the object.year

//compares dates or variables for each class
//hardest part is accessing the variables

//return true if one transaction is bigger than other
//false if it smaller



}








// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true : false; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction* Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb(double acb_value) { acb = acb_value; }
void Transaction::set_acb_per_share(double acb_share_value) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance(unsigned int bal) { share_balance = bal; }
void Transaction::set_cgl(double value) { cgl = value; }
void Transaction::set_next(Transaction* p_new_next) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
	std::cout << std::fixed << std::setprecision(2);
	std::cout << std::setw(4) << get_trans_id() << " "
		<< std::setw(4) << get_symbol() << " "
		<< std::setw(4) << get_day() << " "
		<< std::setw(4) << get_month() << " "
		<< std::setw(4) << get_year() << " ";


	if (get_trans_type()) {
		std::cout << "  Buy  ";
	}
	else { std::cout << "  Sell "; }

	std::cout << std::setw(4) << get_shares() << " "
		<< std::setw(10) << get_amount() << " "
		<< std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
		<< std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
		<< std::setw(10) << std::setprecision(3) << get_cgl()
		<< std::endl;
}







//constructor
History::History() {
	//starting state of linked list

	p_head = nullptr;
}



// Destructor.
//
History::~History() {
	//what are the transactions that form from the linked list??
	//void insert(Transaction *p_new_trans); is the node function

	Transaction* temp = nullptr;

	while (p_head != nullptr) {

		temp = p_head->get_next();

		delete p_head;
		p_head = nullptr;
		p_head = temp;
		temp = nullptr;
		//maybe for member functions you don't need to use the ->
	}
}




// Read the transaction history from file.
//
void History::read_history() {
	//to call a member function on an address we use an arrow
	ece150::open_file();


	//history class contains/is/holds the first node of the linked list

	//next trans entry is like a cursor, points to the next entry, next transaciton in the file
	///returns a bool value
	


	/// RECHECK THIS SECTION MIGHT BE SKIPPING THE FIRST AND LAST ENTRIES
	while (ece150::next_trans_entry()) {
		std::string symbol{ ece150::get_trans_symbol() };
		unsigned int trans_day{ ece150::get_trans_day() };
		unsigned int trans_month{ ece150::get_trans_month() };
		unsigned int trans_year{ ece150::get_trans_year() };
		
		bool trans_type{ ece150::get_trans_type() };
		unsigned int trans_shares{ ece150::get_trans_shares()};
		double trans_amount{ ece150::get_trans_amount() };
		
		Transaction* p_history{ new Transaction{symbol, trans_day, trans_month, trans_year, trans_type, trans_shares, trans_amount} };
		insert(p_history);


		p_history = nullptr;
		//until you call next trans entry, you will be inside the same transactoin
		
	}


	


	ece150::close_file();






	//will create a transaction, dynamically allocate, then call insert and put into linked list

}




// Insert transaction in linked list.
//
void History::insert(Transaction* p_new_trans) {
	

	//added to the tail
	if (p_head == nullptr) {
		p_head = p_new_trans;
	}
	else {
		Transaction* p_temp{ p_head };
		while (p_temp->get_next() != nullptr) {
			
			p_temp = p_temp->get_next();
	

		}
		p_temp->set_next(p_new_trans);
		
	
	}
}




// Sort using insertion sort.
//
void History::sort_by_date() {
	//step 1: check if list is empty, or even a single node (would mean we are done)
	//step 2: Create halding pointers (p_sorted, p_temp1, p_temp2)
	//step 3: moved the first node
	//Step 3a: move p_head to second node
	//step 3b: Disconnect firt node from p_head list
	//step 3c: Point p_sorted to first node
	//step 4: break off the next node
	//step 4a: move p_temp1 back to p_head, and move p_head to next node, and disconnect first node
	//step 5: insert the node into p_sorted list
		//case 1 - transferred node goes at front of new list
		//case 2 - transferred node goes somewhere other than front
	Transaction* p_temp1{ p_head };
	Transaction* p_temp2{ nullptr };
	Transaction* p_sorted{ nullptr };


}




// Update the acb members in the linked list.
//
void History::update_acb_cgl() {

}




// Compute the ACB, and CGL.
//
double History::compute_cgl(unsigned int year) {
	return 0.0;
}




// Print the transaction history.
//

void History::print() {

}







// Constructor
// TASK 3
//


// Destructor
// TASK 3
//


// read_transaction(...): Read the transaction history from file.
// TASK 4
//

// insert(...): Insert transaction into linked list.
// TASK 5
//


// sort_by_date(): Sort the linked list by trade date.
// TASK 6
//


// update_acb_cgl(): Updates the ACB and CGL values.
// TASK 7
//



// compute_cgl(): )Compute the ACB, and CGL.
// TASK 8




// print() Print the transaction history.
//TASK 9
//



// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction* History::get_p_head() { return p_head; }


#endif
