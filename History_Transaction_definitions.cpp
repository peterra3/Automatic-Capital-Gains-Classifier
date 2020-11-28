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

	if (buy_sell_trans == true) {
		this->trans_type = "Buy";
	}
	else {
		this->trans_type = "Sell";
	}
	this->shares = number_shares;
	this->amount = trans_amount;
	this->trans_id = assigned_trans_id;
	++assigned_trans_id;

	// These private members have to be populated so for now put placeholder values on them
	this->acb = 0;
	this->acb_per_share = 0;

	this->share_balance = 0;
	this->cgl = 0;


	this->p_next = nullptr;
}


Transaction::~Transaction() {
	//no dynamic allocation in transaction class
}


// Overloaded < operator.
//
bool Transaction::operator<(Transaction const& other) {
	//compares dates or variables for each class
	//return true if one transaction is bigger than other
	//false if it smaller
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
	
			return false;
		

	}
}



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


// Member functions to set values.
//
void Transaction::set_acb(double acb_value) { acb = acb_value; }
void Transaction::set_acb_per_share(double acb_share_value) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance(unsigned int bal) { share_balance = bal; }
void Transaction::set_cgl(double value) { cgl = value; }
void Transaction::set_next(Transaction* p_new_next) { p_next = p_new_next; }


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


History::History() {


	p_head = nullptr;
}


History::~History() {


	Transaction* temp = nullptr;

	while (p_head != nullptr) {

		temp = p_head->get_next();

		delete p_head;
		p_head = nullptr;
		p_head = temp;
		temp = nullptr;
	}
}


// Read the transaction history from file.
//
void History::read_history() {

	ece150::open_file();

	while (ece150::next_trans_entry()) {
		std::string symbol{ ece150::get_trans_symbol() };
		unsigned int trans_day{ ece150::get_trans_day() };
		unsigned int trans_month{ ece150::get_trans_month() };
		unsigned int trans_year{ ece150::get_trans_year() };

		bool trans_type{ ece150::get_trans_type() };
		unsigned int trans_shares{ ece150::get_trans_shares() };
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
	//step 2: Create handlding pointers (p_sorted, p_temp1, p_temp2)
	//step 3: moved the first node
	//Step 3a: move p_head to second node
	//step 3b: Disconnect firt node from p_head list
	//step 3c: Point p_sorted to first node
	//step 4: break off the next node
	//step 4a: move p_temp1 back to p_head, and move p_head to next node, and disconnect first node
	//step 5: insert the node into p_sorted list
		//case 1 - transferred node goes at front of new list
		//case 2 - transferred node goes somewhere other than front

	//rebuild the list as sorted in p_sorted
	Transaction* p_temp1{ p_head };
	Transaction* p_temp2{ nullptr };
	Transaction* p_sorted{ nullptr };

	if ((p_head == nullptr) || (p_head->get_next() == nullptr)) {

	}
	else {


		//p_temp1 and 2 
		p_sorted = p_head;
		p_head = p_head->get_next();
		p_sorted->set_next(nullptr);

		//the start of a new linked list	


		while (p_head != nullptr) {

			p_temp1 = p_head;
			p_head = p_head->get_next();
			p_temp1->set_next(nullptr);
			//at this point, three seperate linked lists

			if (*p_temp1 < *p_sorted) {
				p_temp1->set_next(p_sorted);
				//here you are moving the head p_sort to point at the beginning of the sorted linked list again
				p_sorted = p_temp1;

			}
			else {
				p_temp2 = p_sorted;
				while ((p_temp2->get_next() != nullptr) && !(*p_temp1 < *(p_temp2->get_next()))) {
					p_temp2 = p_temp2->get_next();
				}

		
				//now p_temp1 node get next is pointing to the node with greater value
				p_temp1->set_next(p_temp2->get_next());

				//now connect p_temp2's node in the address to this new node 
				p_temp2->set_next(p_temp1);
			}
		}
		p_head = p_sorted;
		p_temp1 = nullptr;
		p_temp2 = nullptr;
		p_sorted = nullptr;
	}
	p_temp1 = nullptr;
}



// Update the acb members in the linked list.
//
void History::update_acb_cgl() {
	Transaction* p_temp{ p_head };
	double acb_value{ 0.0 };
	double acb_share{ 0.0 };
	int share_balance{ 0 };
	double cgl{ 0.0 };

	while (p_temp != nullptr) {

		//share balance
		if (p_temp->get_trans_type() == true) {
			share_balance += p_temp->get_shares();
		}
		else {
				share_balance -= p_temp->get_shares();
			
		}
		p_temp->set_share_balance(share_balance);


		//acb
		if (p_temp->get_trans_type() == true) {

			acb_value += p_temp->get_amount();
			p_temp->set_acb(acb_value);

			//acb per share
			// *NOTE ACB Share only changes with purchases
			acb_share = acb_value / share_balance;
			p_temp->set_acb_per_share(acb_share);

		}
		else {
			p_temp->set_acb_per_share(acb_share);
			acb_value -= ((p_temp->get_shares()) * acb_share);
			p_temp->set_acb(acb_value);

			//cgl
			cgl = p_temp->get_amount() - ((p_temp->get_shares()) * acb_share);
			p_temp->set_cgl(cgl);
		}
		p_temp = p_temp->get_next();
	}
	p_temp = nullptr;
}



// Compute the ACB, and CGL.
//
double History::compute_cgl(unsigned int year) {
	Transaction* p_temp{ p_head };
	double cgl_year{ 0.0 };

	while (p_temp != nullptr) {
		while ((p_temp->get_year()) == year) {
			cgl_year += (p_temp->get_cgl());
			break;
		}
		p_temp = p_temp->get_next();
	}
	p_temp = nullptr;
	return cgl_year;
}



// Print the transaction history.
//

void History::print() {
	std::cout << "========== BEGIN TRANSACTION HISTORY ============" << std::endl;
	Transaction* p_temp{ p_head };
	while (p_temp != nullptr) {
		p_temp->print();
		p_temp = p_temp->get_next();

	}
	std::cout << "========== END TRANSACTION HISTORY ============" << std::endl;
	p_temp = nullptr;
}

Transaction* History::get_p_head() { return p_head; }

#endif
