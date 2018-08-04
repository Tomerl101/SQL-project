#ifndef manager_h
#define manager_h

#include <stdio.h>
#include <iostream>
#include "Database.h"

#include "mysql_connection.h"

using namespace std;

void get_books();
void get_open_orders();
void get_customers();
void get_suppliers();
void get_order_between(const string &date1, const string &date2);
void isDiscount();
void get_book(string checkStock);
void get_book_suppliers(string book);
void sales_of_book(string book, string date);
void customer_books(string customer, string date);
void top_customer(string date);
void top_supplier(string date);
void purchase_between(string date1, string date2);
void close_orders(string date1, string date2);
void customer_discount(string customer, string date);
void quarter_revenue();
void new_customers(string join_date);
void supplier_total_purchase(string supplier_id);
void employee_sum(string emp_id,string date1, string date2);
void top_10(string date1, string date2);

int& pagination(int &index);
void menu();

#endif 

