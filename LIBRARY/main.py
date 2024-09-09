import mysql.connector


def connect_to_db():
    try:
        connection = mysql.connector.connect(
            host="localhost",
            user="root",
            password="12345",
            database="book_store"
        )
        return connection
    except Exception as e:
        print("Database connection failed. Please check your settings.")
        return None


def show_menu():
    while True:
        print("\n--- Welcome to the Book Store Management System ---")
        print("1. Browse Available Books")
        print("2. Sign Up")
        print("3. Manager Access")
        print("4. Exit")

        selection = input("Choose an option (1-4): ")

        if selection == '1':
            browse_books()
        elif selection == '2':
            sign_up()
        elif selection == '3':
            Manager_login()
        elif selection == '4':
            print("Goodbye! Thanks for visiting the bookstore.")
            break
        else:
            print("Invalid input. Please enter a number between 1 and 4.")


def browse_books():
    connection = connect_to_db()
    if not connection:
        return

    cursor = connection.cursor()

    try:
        cursor.execute("SELECT * FROM books WHERE stock > 0")
        books = cursor.fetchall()

        if books:
            print("\n--- Available Books ---")
            for book in books:
                print(f"ID: {book[0]}, Title: {book[1]}, Author: {book[2]}, Price: ${book[3]}, Stock: {book[4]}")
            
            book_id = input("Enter the ID of the book you'd like to purchase, or 'Q' to quit: ")

            if book_id.lower() != 'q':
                purchase_book(connection, book_id)
        else:
            print("No books are currently available.")
    except Exception as e:
        print("Unable to retrieve books. Please try again later.")
    finally:
        connection.close()


def purchase_book(connection, book_id):
    cursor = connection.cursor()

    try:
        cursor.execute("SELECT stock, price FROM books WHERE book_id = %s", (book_id,))
        result = cursor.fetchone()

        if result and result[0] > 0:
            stock, price = result
            print(f"The price of this book is ${price}.")
            confirm = input("Would you like to proceed with the purchase? (yes/no): ").lower()

            if confirm == 'yes':
                cursor.execute("UPDATE books SET stock = stock - 1 WHERE book_id = %s", (book_id,))
                connection.commit()
                print("Purchase successful! Enjoy your book.")
            else:
                print("Purchase cancelled.")
        else:
            print("The selected book is out of stock or invalid.")
    except Exception as e:
        print("There was an error processing your purchase.")
    finally:
        cursor.close()


def sign_up():
    connection = connect_to_db()
    if not connection:
        return

    cursor = connection.cursor()

    try:
        username = input("Create a username: ")
        password = input("Create a password: ")

        cursor.execute("INSERT INTO users (username, password) VALUES (%s, %s)", (username, password))
        connection.commit()

        print("Your account has been created. You can now log in and make purchases.")
    except Exception as e:
        print("Sign-up failed. Please try again.")
    finally:
        connection.close()


def Manager_login():
    Manager_user = "Manager"
    Manager_pass = "Managerpass"

    username = input("Manager Username: ")
    password = input("Manager Password: ")

    if username == Manager_user and password == Manager_pass:
        Manager_tasks()
    else:
        print("Invalid credentials. Access denied.")


def Manager_tasks():
    while True:
        print("\n--- Manager Panel ---")
        print("1. Add New Book")
        print("2. Remove Book")
        print("3. Log Out")

        choice = input("Choose an action (1-3): ")

        if choice == '1':
            add_book()
        elif choice == '2':
            remove_book()
        elif choice == '3':
            print("Logging out from Manager panel.")
            break
        else:
            print("Invalid option. Please choose again.")


def add_book():
    connection = connect_to_db()
    if not connection:
        return

    cursor = connection.cursor()

    try:
        title = input("Enter book title: ")
        author = input("Enter book author: ")
        price = float(input("Enter book price: "))
        stock = int(input("Enter stock quantity: "))

        cursor.execute("""
            INSERT INTO books (title, author, price, stock)
            VALUES (%s, %s, %s, %s)
        """, (title, author, price, stock))

        connection.commit()
        print("Book successfully added to the inventory.")
    except Exception as e:
        print("Error adding book. Ensure all data is correct.")
    finally:
        connection.close()


def remove_book():
    book_id = input("Enter the ID of the book you wish to remove: ")

    connection = connect_to_db()
    if not connection:
        return

    cursor = connection.cursor()

    try:
        cursor.execute("DELETE FROM books WHERE book_id = %s", (book_id,))
        connection.commit()
        print("Book removed from the inventory.")
    except Exception as e:
        print("Error removing book. Please try again.")
    finally:
        connection.close()


if __name__ == "__main__":
    show_menu()
