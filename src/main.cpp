#include <stdlib.h>
#include <iostream>
#include "Database.h"
#include "manager.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <boost/tokenizer.hpp>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
	int choose;
	while (1)
	{
		cout << endl << endl << endl << endl << endl << endl << endl;
		menu();
		cin >> choose;
		switch (choose) {
		case 1:
		{
			cout << endl << endl << endl << endl << endl << endl << endl;
			get_books();
			break;
		}
		case 2:
		{
			get_open_orders();
			break;
		}
		case 3:
		{
			get_customers();
			break;
		}
		case 4:
		{
			get_suppliers();
			break;
		}
		case 5:
		{
			string date1;
			string date2;
			cout << "enter start date : ";
			cin >> date1;
			cout << "enter end date : ";
			cin >> date2;
			get_order_between(date1, date2);
			break;
		}
		case 6:
		{
			isDiscount();
			break;
		}
		case 7:
		{
			string checkStock;
			cout << "enter book name: ";
			cin >> checkStock;
			get_book(checkStock);
			break;
		}
		case 8:
		{
			string book;
			cout << "enter book name : ";
			cin >> book;
			get_book_suppliers(book);
			break;
		}
		case 9:
		{
			string book;
			string date;
			cout << "enter book name : ";
			cin >> book;
			cout << "enter start date : ";
			cin >> date;
			sales_of_book(book,date);
			break;
		}
		case 10:
		{
			string customer;
			string date;
			cout << "enter customer name: ";
			cin >> customer;
			cout << "enter start date : ";
			cin >> date;
			customer_books(customer, date);
			break;
		}

		case 11:
		{
			string date;
			cout << "enter start date : ";
			cin >> date;
			top_customer(date);
			break;
		}
		case 12:
		{
			string date;
			cout << "enter start date : ";
			cin >> date;
			top_supplier(date);
			break;
		}
		case 13:
		{
			string date1;
			string date2;
			cout << "enter start date : ";
			cin >> date1;
			cout << "enter end date : ";
			cin >> date2;
			purchase_between(date1, date2);
			break;
		}
		case 14:
		{
			string date1;
			string date2;
			cout << "enter start date : ";
			cin >> date1;
			cout << "enter end date : ";
			cin >> date2;
			close_orders(date1,date2);
			break;
		}

		case 15:
		{
			string customer_id;
			string date;
			cout << "enter customer id: ";
			cin >> customer_id;
			cout << "enter start date : ";
			cin >> date;
			customer_discount(customer_id, date);
			break;
		}
		case 16:
		{
			quarter_revenue();
			break;
		}
		case 17:
		{
			string join_date;
			cout << "enter date: ";
			cin >> join_date;
			new_customers(join_date);
			break;
		}
		case 18:
		{
			string supplier_id;
			cout << "enter supplier id: ";
			cin >> supplier_id;
			supplier_total_purchase(supplier_id);
			break;
		}
		case 19:
		{
			string emp_id;
			string date1;
			string date2;
			cout << "enter employee id: ";
			cin >> emp_id;
			cout << "enter start date : ";
			cin >> date1;
			cout << "enter end date : ";
			cin >> date2;
			employee_sum(emp_id,date1, date2);
			break;
		}
		case 20:
		{
			string date1;
			string date2;
			cout << "enter start date : ";
			cin >> date1;
			cout << "enter end date : ";
			cin >> date2;
			top_10(date1, date2);
			break;
		}

		default:
		{
			return 0;
			break;
		}
		}
	}

	return 0;
}
