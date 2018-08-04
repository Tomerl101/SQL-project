#include "manager.h"

void get_books() {
	int n = 0;
	while (1)
	{
		QUERY("SELECT * FROM book LIMIT 5 OFFSET ?");
		pstmt->setInt(1, n); 
		ResultSet *res = pstmt->executeQuery();

		if (!res->next() && n>0)                            //if there is no next
		{
			cout << endl << "there is no next data!" << endl;
			n -= 5;
			delete res;
			delete pstmt;
			continue;
		}
		res->beforeFirst();
		while (res->next())
		{
			cout << "book id: " << res->getString("book_id") << endl << "title: " << res->getString("title") << endl << "price: " << res->getString("price") << endl << "quantity: " << res->getString("quantity") << endl<<endl;
		}
		n = pagination(n);
		if(n == -1)
			return;
		DEL_CON;
	}
}

void get_open_orders() {
	int n = 0;
	while (1)
	{
		QUERY("SELECT * FROM orders WHERE status = 0 LIMIT 5 OFFSET ?");
		pstmt->setInt(1, n);
		ResultSet *res = pstmt->executeQuery();

		if (!res->next() && n>0)                            //if there is no next
		{
			cout << endl << "there is no next data!" << endl;
			n -= 5;
			delete res;
			delete pstmt;
			continue;
		}
		res->beforeFirst();
		while (res->next())
		{
			cout << "order id: " << res->getString("order_id") << endl << "order date: " << res->getString("order_date") << endl << endl;
		}
		n = pagination(n);
		if (n == -1)
			return;
		DEL_CON;
	}
}

void get_customers() {
	int n = 0;
	while (1)
	{
		QUERY("SELECT * FROM customers LIMIT 5 OFFSET ?");
		pstmt->setInt(1, n);
		ResultSet *res = pstmt->executeQuery();

		if (!res->next() && n>0)                            //if there is no next
		{
			cout << endl << "there is no next data!" << endl;
			n -= 5;
			delete res;
			delete pstmt;
			continue;
		}
		res->beforeFirst();
		while (res->next())
		{
			cout << "customer id: " << res->getString("customer_id") << endl << "first name: " << res->getString("first_name") << endl;
			cout << "last name: " << res->getString("last_name") << endl << "Phone: " << res->getString("phone") << endl<<endl;
		}
		n = pagination(n);
		if (n == -1)
			return;
		DEL_CON;
	}
};

void get_suppliers() 
{
	int n = 0;
	int i = 1;

	while (1)
	{
		QUERY("SELECT * FROM supplier LIMIT 5 OFFSET ?");
		pstmt->setInt(1, n);
		ResultSet *res = pstmt->executeQuery();

		if (!res->next() && n>0)                            //if there is no next
		{
			cout << endl << "there is no next data!" << endl;
			n -= 5;
			delete res;
			delete pstmt;
			continue;
		}
		res->beforeFirst();
		i = n;
		while (res->next())
		{
			cout << "supplier id: " << res->getString("supplier_id") << endl << "name: " << res->getString("name") << endl << endl;
		}
		n = pagination(n);
		if (n == -1)
			return;
		DEL_CON;
	}
};

void get_order_between(const string &date1, const string &date2) 
{
	int n = 0;
	while (1)
	{
		QUERY("SELECT * FROM orders WHERE order_date BETWEEN ? AND ? LIMIT 5 OFFSET ?");
		pstmt->setString(1, date1);
		pstmt->setString(2, date2);
		pstmt->setInt(3, n);
		ResultSet *res = pstmt->executeQuery();

		if (!res->next() && n>0)                            //if there is no next
		{
			cout << endl << "there is no next data!" << endl;
			n -= 5;
			delete res;
			delete pstmt;
			continue;
		}
		res->beforeFirst();
		while (res->next())
		{
			cout << "order id: " << res->getString("order_id") << endl << "order date: " << res->getString("order_date") << endl<<endl;
		}
		n = pagination(n);
		if (n == -1)
			return;
		DEL_CON;
	}
};

void isDiscount() 
{
	int n = 0;
	while (1)
	{
		QUERY("SELECT * FROM book WHERE isDiscount=1 LIMIT 5 OFFSET ?");
		pstmt->setInt(1, n);
		ResultSet *res = pstmt->executeQuery();

		if (!res->next() && n>0)                            //if there is no next
		{
			cout << endl << "there is no next data!" << endl;
			n -= 5;
			delete res;
			delete pstmt;
			continue;
		}
		res->beforeFirst();
		while (res->next())
		{
			cout << "book id: " << res->getString("book_id") << endl<<"title: " << res->getString("title") <<endl<< "price: " << res->getString("price") <<endl<< endl;
		}
		n = pagination(n);
		if (n == -1)
			return;
		DEL_CON;
	}
};

void get_book(string checkStock) 
{
	while (1)
	{
		QUERY("SELECT * FROM book WHERE title=? AND quantity>0 ");
		pstmt->setString(1, checkStock);
		ResultSet *res = pstmt->executeQuery();

		if (!res->next())                            //if there is no next
		{
			cout << endl << "Book is out of stock..." << endl;
			DEL_CON;
			return;
		}
		res->beforeFirst();
		while (res->next())
		{
			cout << "book id: " << res->getString("book_id") <<endl<< "title: " << res->getString("title") <<endl<< "quantity: " << res->getString("quantity") <<endl<< endl;
		}
		DEL_CON;
		return;
	}
};

void get_book_suppliers(string book) 
{
	int n = 0;
	while (1)
	{
		QUERY("SELECT sb.supplier_id, s.name, sb.book_id FROM supplier_books AS sb, Book AS b, supplier AS s WHERE b.title=? AND b.book_id = sb.book_id AND s.supplier_id = sb.supplier_id LIMIT 5 OFFSET ?");
		pstmt->setString(1, book);
		pstmt->setInt(2, n);
		ResultSet *res = pstmt->executeQuery();

		if (!res->next() && n>0)                            //if there is no next
		{
			cout << endl << "there is no next data!" << endl;
			n -= 5;
			delete res;
			delete pstmt;
			continue;
		}
		res->beforeFirst();
		while (res->next())
		{
			cout << "supplier id: " << res->getString("supplier_id") <<endl<< "name: " << res->getString("name") <<endl<< "book id: " << res->getString("book_id") <<endl<< endl;;
		}
		n = pagination(n);
		if (n == -1)
			return;
		DEL_CON;
	}
};

void sales_of_book(string book, string date) 
{
	while (1)
	{
		QUERY("SELECT SUM(od.quantity) AS quantity FROM orders AS o JOIN( book AS b JOIN orderdetails AS od ON b.book_id = od.book_id AND b.title = ?) ON o.order_id = od.order_id WHERE o.order_date >= ?");
		pstmt->setString(1, book);
		pstmt->setString(2, date);
		ResultSet *res = pstmt->executeQuery();

		if (!res->next())                            //if there is no next
		{
			cout << endl << "there is no next data!" << endl;
			DEL_CON;
			return;
		}
		res->beforeFirst();
		while (res->next())
		{
			cout << "book quantity: " << res->getString("quantity")<<endl<<endl;
		}
		DEL_CON;
		return;
	}
};

void customer_books(string customer, string date) 
{
	while (1)
	{
		QUERY("SELECT SUM(od.quantity) AS total FROM orderdetails AS od JOIN(customers AS c JOIN orders AS o ON o.customer_id = c.customer_id) ON o.order_id = od.order_id AND c.customer_id = ? WHERE o.order_date > ? ");
		pstmt->setString(1, customer);
		pstmt->setString(2, date);
		ResultSet *res = pstmt->executeQuery();

		if (!res->next() )                            //if there is no next
		{
			cout << endl << "there is no next data!" << endl;
			DEL_CON;
			return;
		}
		res->beforeFirst();
		while (res->next())
		{
			cout << "customer total books order: " << res->getString("total") << endl<<endl;
		}
		DEL_CON;
		return;
	}
};

void top_customer(string date) 
{
	while (1)
	{
		QUERY("SELECT c.first_name, c.last_name FROM customers AS c JOIN (SELECT o.customer_id, SUM(od.quantity) AS pay FROM orderdetails AS od, orders AS o WHERE o.order_id = od.order_id AND o.order_date >= ? GROUP BY o.customer_id) AS x WHERE c.customer_id = x.customer_id ORDER BY x.pay DESC LIMIT 1");
		pstmt->setString(1, date);
		ResultSet *res = pstmt->executeQuery();

		if (!res->next())                            //if there is no next
		{
			cout << endl << "there is no next data!" << endl;
			DEL_CON;
			return;
		}
		res->beforeFirst();
		while (res->next())
		{
			cout << "TOP customer name: " << res->getString("first_name") << " " << res->getString("last_name") << endl<<endl;
		}
		DEL_CON;
		return;
	}
};

void top_supplier(string date) 
{
	while (1)
	{
		QUERY("SELECT s.supplier_id, s.name, x.cost FROM supplier AS s JOIN (SELECT p.supplier_id, SUM(p.quantity) AS cost FROM purchase AS p WHERE p.purchase_date >= ? GROUP BY p.supplier_id) AS x ON s.supplier_id = x.supplier_id ORDER BY x.cost DESC LIMIT 1");
		pstmt->setString(1, date);
		ResultSet *res = pstmt->executeQuery();

		if (!res->next())                            //if there is no next
		{
			cout << endl << "there is no next data!" << endl;
			DEL_CON;
			return;
		}
		res->beforeFirst();
		while (res->next())
		{
			cout << "TOP supplier: " << res->getString("name") <<endl<< "total purchase: " << res->getString("cost") <<endl<< endl;
		}
		DEL_CON;
		return;
	}
};

void purchase_between(string date1, string date2) 
{
	int n = 0;
	while (1)
	{
		QUERY("SELECT book.title, COUNT(purchase.book_id) FROM purchase, book WHERE book.book_id = purchase.book_id AND purchase_date BETWEEN ? AND ? GROUP BY purchase.book_id LIMIT 5 OFFSET ?");
		pstmt->setString(1, date1);
		pstmt->setString(2, date2);
		pstmt->setInt(3, n);
		ResultSet *res = pstmt->executeQuery();

		if (!res->next() && n>0)                            //if there is no next
		{
			cout << endl << "there is no next data!" << endl;
			n -= 5;
			delete res;
			delete pstmt;
			continue;
		}
		res->beforeFirst();
		while (res->next())
		{
			cout << "book title: " << res->getString("title") <<endl<< "number of purchase: " << res->getString("COUNT(purchase.book_id)") <<endl<< endl;
		}
		n = pagination(n);
		if (n == -1)
			return;
		DEL_CON;
	}
};

void close_orders(string date1, string date2) 
{
	while (1)
	{
		QUERY("SELECT COUNT(status) FROM orders WHERE status = 1 AND order_date BETWEEN ? AND ?");
		pstmt->setString(1, date1);
		pstmt->setString(2, date2);
		ResultSet *res = pstmt->executeQuery();

		if (!res->next())                            //if there is no next
		{
			cout << endl << "there is no next data!" << endl;
			DEL_CON;
			return;
		}
		res->beforeFirst();
		while (res->next())
		{
			cout << "close orders: " << res->getString("COUNT(status)") << endl<<endl ;
		}
		DEL_CON;
		return;
	}
};

void customer_discount(string customer_id, string date)
{
	while (1)
	{
		QUERY("SELECT total , IF(total>1000,total*0.1,'no discount') AS discount FROM (SELECT SUM(x.total) AS total FROM orders AS o JOIN (SELECT od.order_id, SUM(b.price * od.quantity) AS total FROM book AS b, orderDetails AS od WHERE od.book_id = b.book_id GROUP BY od.order_id) AS x ON o.order_id = x.order_id WHERE o.customer_id = ? AND o.order_date >= ? GROUP BY o.customer_id) as t; ");
		pstmt->setString(1, customer_id);
		pstmt->setString(2, date);
		ResultSet *res = pstmt->executeQuery();

		if (!res->next())                            //if there is no next
		{
			cout << endl << "there is no next data!" << endl;
			DEL_CON;
			return;
		}
		res->beforeFirst();
		while (res->next())
		{
			cout << "Total order price: " << res->getString("total") <<endl<< " discount: " << res->getString("discount") << endl<<endl;
		}
		DEL_CON;
		return;
	}
}

void quarter_revenue() 
{
	while (1)
	{
		QUERY("SELECT QUARTER(o.order_date) AS quarter, SUM(x.total) AS total FROM orders AS o JOIN (SELECT od.order_id, SUM(b.price * od.quantity) AS total FROM book AS b, orderdetails AS od WHERE b.book_id = od.book_id GROUP BY od.order_id) AS x WHERE o.order_id = x.order_id GROUP BY quarter");
		ResultSet *res = pstmt->executeQuery();

		if (!res->next())                            //if there is no next
		{
			cout << endl << "there is no next data!" << endl;
			DEL_CON;
			return;
		}
		res->beforeFirst();
		while (res->next())
		{
			cout << "Q" << res->getString("quarter") <<" "<<"total:"<<res->getString("total")<< endl;
		}
		DEL_CON;
		return;
	}
};

void new_customers(string join_date) 
{
	while (1)
	{
		QUERY("SELECT COUNT(c.customer_id) AS join_customers FROM customers AS c WHERE c.join_date > ?");
		pstmt->setString(1, join_date);
		ResultSet *res = pstmt->executeQuery();

		if (!res->next())                            //if there is no next
		{
			cout << endl << "there is no next data!" << endl;
			DEL_CON;
			return;
		}
		res->beforeFirst();
		while (res->next())
		{
			cout << "new customers: " << res->getString("join_customers")<<endl<<endl;
		}
		DEL_CON;
		return;
	}
};

void supplier_total_purchase(string supplier_id) 
{
	while (1)
	{
		QUERY("SELECT SUM(p.quantity * sb.price) AS total, p.supplier_id FROM purchase AS p, supplier_books AS sb WHERE p.supplier_id = sb.supplier_id AND sb.book_id = p.book_id AND p.supplier_id = ?");
		pstmt->setString(1, supplier_id);
		ResultSet *res = pstmt->executeQuery();

		if (!res->next())                            //if there is no next
		{
			cout << endl << "there is no next data!" << endl;
			DEL_CON;
			return;
		}
		res->beforeFirst();
		while (res->next())
		{
			cout << "purchase from supplier:"<< supplier_id<<endl<<"total: "<< res->getString("total") << endl;
		}
		DEL_CON;
		return;
	}
};

void employee_sum(string emp_id,string date1, string date2) 
{
	while (1)
	{
		QUERY("SELECT SUM(x.total) AS total FROM orders AS o JOIN (SELECT od.order_id, SUM(b.price * od.quantity) AS total FROM book AS b, orderDetails AS od WHERE od.book_id = b.book_id GROUP BY od.order_id) AS x ON o.order_id = x.order_id WHERE o.employee_id = ? AND o.order_date  BETWEEN ? AND ? GROUP BY o.employee_id");
		pstmt->setString(1, emp_id);
		pstmt->setString(2, date1);
		pstmt->setString(3, date2);
		ResultSet *res = pstmt->executeQuery();

		if (!res->next())                            //if there is no next
		{
			cout << endl << "there is no next data!" << endl;
			DEL_CON;
			return;
		}
		res->beforeFirst();
		while (res->next())
		{
			cout << "Sales from employee:" << emp_id << endl<<"total: "<< res->getString("total") << endl;
		}
		DEL_CON;
		return;
	}
};

void top_10(string date1, string date2) 
{
	int n = 0;
	int i = 1;

	while (1)
	{
		QUERY("SELECT b.title, sum_quantity FROM book AS b JOIN (SELECT od.book_id, SUM(od.quantity) AS sum_quantity FROM orders AS o, orderDetails AS od WHERE o.order_id = od.order_id AND o.order_date BETWEEN ? AND ? GROUP BY od.book_id LIMIT 10) AS x WHERE x.book_id = b.book_id ORDER BY x.sum_quantity DESC LIMIT 5 OFFSET ?");
		pstmt->setString(1, date1);
		pstmt->setString(2, date2);
		pstmt->setInt(3, n);
		ResultSet *res = pstmt->executeQuery();

		if (!res->next() && n>0)                            //if there is no next
		{
			cout << endl << "there is no next data!" << endl;
			n -= 5;
			delete res;
			delete pstmt;
			continue;
		}
		res->beforeFirst();
		i = n;
		while (res->next())
		{
			cout << "#" <<i<<endl<<"title: " <<res->getString("title") <<endl<< "sold: " <<  res->getString("sum_quantity") <<endl<< endl;
			i++;
		}
		n = pagination(n);
		if (n == -1)
			return;
		DEL_CON;
	}
};

int& pagination(int &index)
{
	cout << endl << endl << "1.next" << endl << "2.prev" << endl << "other number to main menu" << endl;

	int choose;
	cin >> choose;
	switch (choose) {
	case 1:
	{
		index += 5;
		break;
	}
	case 2:
	{
		index = index < 5 ? 0 : (index - 5);
		cout << endl << "there is no prev data!" << endl;
		break;
	}
	default:
		index = -1;
		return index;
	}
	return index;
}

void menu()
{
	cout <<endl << " WELCOME TO OUR BOOKSTORE" << endl
		<< "=================================" << endl << endl
		<< "1.books in stock" << endl 
		<< "2.show open orders" << endl 
		<< "3.show customers" << endl 
		<< "4.show suppliers" << endl 
		<< "5.show orders between dates" << endl 
		<< "6.show books with discount" << endl 
		<< "7.check book stock quantity" << endl 
		<< "8.show suppliers of book" << endl 
		<< "9.show copies of book from date" << endl 
		<< "10.show total customer books orders" << endl 
		<< "11.show TOP customer" << endl 
		<< "12.show TOP supplier" << endl 
		<< "13.show purchase between dates" << endl 
		<< "14.show number of closed sales" << endl 
		<< "15.show customer discount since date" << endl 
		<< "16.show QUARTER revenues" << endl 
		<< "17.show new customers between dates" << endl 
		<< "18.show total purchase from supplier between dates" << endl 
		<< "19.show total orders of employee between dates" << endl 
		<< "20.show TOP10 books between dates" << endl;
}