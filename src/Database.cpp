#include "Database.h"

Database *Database::instance = 0;

Database::Database() : driver(get_driver_instance()) {
	connection_properties["hostName"] = DB_HOST;
	connection_properties["port"] = DB_PORT;
	connection_properties["userName"] = DB_USER;
	connection_properties["password"] = DB_PASS;
	connection_properties["OPT_RECONNECT"] = true;
	
	// use database
	try {
		Connection *con = driver->connect(connection_properties);
		try {
			con->setSchema("bookstore2");
		}
		catch (SQLException &e) {
			Statement *stmt = con->createStatement();
			stmt->execute(
				"CREATE DATABASE IF NOT EXISTS bookstore2");
			con->setSchema("bookstore2"); // switch database
			stmt->execute("CREATE TABLE IF NOT EXISTS book ( "
				"book_id int(11) NOT NULL AUTO_INCREMENT,"
				"title varchar(30) NOT NULL,"
				"price int(10) NOT NULL,"
				"quantity int(10) NOT NULL,"
				"isDiscount tinyint(1) NOT NULL,"
				"PRIMARY KEY(book_id)"
				")");
			stmt->execute("CREATE TABLE IF NOT EXISTS customers("
				"customer_id int(11) NOT NULL AUTO_INCREMENT,"
				"first_name varchar(20) NOT NULL,"
				"last_name varchar(20) NOT NULL,"
				"phone varchar(20) NOT NULL,"
				"join_date date NOT NULL,"
				"PRIMARY KEY(customer_id)"
				")");
			stmt->execute("CREATE TABLE IF NOT EXISTS employee ( "
				"employee_id int(11) NOT NULL AUTO_INCREMENT,"
				"name varchar(20) NOT NULL,"
				"PRIMARY KEY(employee_id)"
				")");
			stmt->execute("CREATE TABLE IF NOT EXISTS orders ("
				"order_id int(11) NOT NULL,"
				"customer_id int(11) NOT NULL,"
				"employee_id int(11) NOT NULL,"
				"order_date date NOT NULL,"
				"status tinyint(1) NOT NULL,"
				"PRIMARY KEY(order_id),"
				"FOREIGN KEY(customer_id) REFERENCES customers(customer_id),"
				"FOREIGN KEY(employee_id) REFERENCES employee(employee_id)"
				")");
			stmt->execute("CREATE TABLE IF NOT EXISTS orderdetails ( "
				"orderDetails_id int(11) NOT NULL AUTO_INCREMENT,"
				"order_id int(11) NOT NULL,"
				"book_id int(11) NOT NULL,"
				"quantity int(11) NOT NULL,"
				"PRIMARY KEY(orderDetails_id),"
				"FOREIGN KEY(order_id) REFERENCES orders(order_id),"
				"FOREIGN KEY(book_id) REFERENCES book(book_id)"
				")");
			stmt->execute("CREATE TABLE IF NOT EXISTS supplier ( "
				"supplier_id int(11) NOT NULL AUTO_INCREMENT,"
				"name varchar(20) NOT NULL,"
				"PRIMARY KEY(supplier_id)"
				")");
			stmt->execute("CREATE TABLE IF NOT EXISTS purchase ( "
				"purchase_id int(11) NOT NULL AUTO_INCREMENT,"
				"supplier_id int(11) NOT NULL,"
				"book_id int(11) NOT NULL,"
				"quantity int(11) NOT NULL,"
				"purchase_date date NOT NULL,"
				"PRIMARY KEY(purchase_id),"
				"FOREIGN KEY(supplier_id) REFERENCES supplier(supplier_id),"
				"FOREIGN KEY(book_id) REFERENCES book(book_id)"
				")");
			stmt->execute("CREATE TABLE IF NOT EXISTS supplier_books ( "
				"supplier_id int(11) NOT NULL,"
				"book_id int(11) NOT NULL,"
				"price int(11) NOT NULL,"
				"FOREIGN KEY(book_id) REFERENCES book(book_id),"
				"FOREIGN KEY(supplier_id) REFERENCES supplier(supplier_id)"
				")");

			stmt->execute("INSERT INTO `book` (`book_id`, `title`, `price`, `quantity`, `isDiscount`) VALUES"
					"(1, 'book1', 39, 5, 0),"
					"(2, 'book2', 19, 3, 1),"
					"(3, 'book3', 79, 1, 1),"
					"(4, 'book4', 47, 2, 1),"
					"(5, 'book5', 12, 9, 0),"
					"(6, 'book6', 82, 2, 0),"
					"(7, 'book7', 22, 1, 1),"
					"(8, 'book8', 16, 6, 1),"
					"(9, 'book9', 109, 3, 0),"
					"(10, 'book10', 29, 1, 1),"
					"(11, 'book11', 36, 0, 0)");

			stmt->execute("INSERT INTO `customers` (`customer_id`, `first_name`, `last_name`, `phone`, `join_date`) VALUES"
				"(1, 'tomer', 'lotan', '053454778', '2018-07-22'),"
				"(2, 'customer2', 'customer2', '123123', '2018-07-23'),"
				"(3, 'customer3', 'customer', '1111111', '2018-05-15'),"
				"(4, 'customer4', 'customer4', '222222', '2018-02-14'),"
				"(5, 'customer5', 'customer5', '6666666', '2018-06-14'),"
				"(6, 'customer6', 'customer6', '7777777', '2018-04-20'),"
				"(7, 'customer7', 'customer7', '454545454', '2018-07-20'),"
				"(8, 'customer8', 'customer8', '98989898', '2018-02-06'),"
				"(9, 'customer9', 'customer9', '9999999', '2018-01-10'),"
				"(10, 'customer10', 'customer10', '10101010', '2018-03-16')");

			stmt->execute("INSERT INTO `employee` (`employee_id`, `name`) VALUES"
				"(1, 'employee1'),"
				"(2, 'employee2'),"
				"(3, 'employee3'),"
				"(4, 'employee4'),"
				"(5, 'employee5'),"
				"(6, 'employee6'),"
				"(7, 'employee7'),"
				"(8, 'employee8'),"
				"(9, 'employee9'),"
				"(10, 'employee10')");

			stmt->execute("INSERT INTO `orders` (`order_id`, `customer_id`, `employee_id`, `order_date`, `status`) VALUES"
				"(1021, 1, 10, '2018-06-07', 0),"
				"(1023, 7, 3, '2018-03-14', 0),"
				"(1024, 1, 4, '2018-05-10', 1),"
				"(1028, 5, 7, '2018-07-12', 1),"
				"(1029, 8, 8, '2018-05-16', 1),"
				"(1030, 5, 4, '2018-08-22', 0),"
				"(1031, 9, 9, '2018-10-11', 1),"
				"(1032, 2, 1, '2018-07-27', 1),"
				"(1033, 3, 3, '2018-11-14', 0),"
				"(1034, 9, 1, '2018-12-26', 1)");

			stmt->execute("INSERT INTO `orderdetails` (`orderDetails_id`, `order_id`, `book_id`, `quantity`) VALUES"
				"(1, 1021, 1, 3),"
				"(2, 1021, 5, 4),"
				"(3, 1023, 7, 1),"
				"(4, 1024, 2, 2),"
				"(5, 1028, 3, 3),"
				"(6, 1029, 6, 1),"
				"(7, 1030, 8, 4),"
				"(8, 1031, 9, 2),"
				"(9, 1032, 4, 1),"
				"(10, 1033, 5, 2),"
				"(11, 1033, 1, 1),"
				"(12, 1034, 9, 1),"
				"(13, 1034, 8, 3)");

			stmt->execute("INSERT INTO `supplier` (`supplier_id`, `name`) VALUES"
				"(1, 'supplier1'),"
				"(2, 'supplier2'),"
				"(3, 'supplier3'),"
				"(4, 'supplier4'),"
				"(5, 'supplier5'),"
				"(6, 'supplier6'),"
				"(7, 'supplier7'),"
				"(8, 'supplier8'),"
				"(9, 'supplier9'),"
				"(10, 'supplier10')");

			stmt->execute("INSERT INTO `purchase` (`purchase_id`, `supplier_id`, `book_id`, `quantity`, `purchase_date`) VALUES"
				"(1, 1, 5, 15, '2018-07-16'),"
				"(2, 6, 8, 10, '2018-04-11'),"
				"(3, 3, 3, 7, '2018-10-17'),"
				"(4, 4, 4, 5, '2018-11-15'),"
				"(5, 5, 9, 13, '2018-02-14'),"
				"(6, 2, 5, 6, '2018-07-03'),"
				"(7, 1, 5, 76, '2018-07-25'),"
				"(8, 3, 10, 4, '2018-07-13'),"
				"(9, 7, 7, 17, '2018-07-28'),"
				"(10, 5, 6, 21, '2018-07-29')");

			stmt->execute("INSERT INTO `supplier_books` (`supplier_id`, `book_id`, `price`) VALUES"
				"(1, 1, 30),"
				"(1, 5, 9),"
				"(2, 2, 12),"
				"(2, 7, 17),"
				"(3, 3, 70),"
				"(3, 4, 42),"
				"(4, 4, 35),"
				"(4, 1, 31),"
				"(5, 5, 7),"
				"(5, 9, 101),"
				"(6, 6, 76),"
				"(6, 8, 11),"
				"(7, 7, 17),"
				"(7, 3, 72),"
				"(8, 8, 14),"
				"(8, 10, 17),"
				"(9, 9, 105),"
				"(9, 6, 73),"
				"(10, 10, 21),"
				"(10, 1, 29),"
				"(3, 10, 60)");


			delete stmt;
		}

		delete con;
	}
	catch (SQLException &e) {
		cout << e.getErrorCode() << " " << e.what() << " " << e.getSQLState();
	}
}

Database & Database::getInstance() {
	if (Database::instance == 0) {
		instance = new Database();
	}
	return *instance;
}

Connection * Database::getConnection() {
	try {
		Connection *con = driver->connect(connection_properties);
		con->setSchema(DB_NAME);
		return con;
	} catch (SQLException &e) {
		cout << e.what();
	}
	return 0;
}
