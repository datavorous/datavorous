import mysql.connector
import os

def connect_to_db():
    try:
        return mysql.connector.connect(
            host="localhost",
            user="root",
            password="12345",
            database="library_management_system"
        )
    except mysql.connector.Error as err:
        print(f"Error connecting to database: {err}")
        exit()

def main_menu():
    while True:
        print("Welcome to School Library!")
        print("1. SEARCH BOOKS")
        print("2. CREATE USER ACCOUNT")
        print("3. ADMIN LOGIN")
        print("4. EXIT")

        choice = input("Please choose an option: ")

        if choice == '1':
            search_books()
        elif choice == '2':
            create_user_account()
        elif choice == '3':
            admin_login()
        elif choice == '4':
            exit()
        else:
            print("Invalid choice, please try again.")

def search_books():
    db = connect_to_db()
    cursor = db.cursor()

    try:
        cursor.execute("SELECT * FROM books WHERE is_available = TRUE")
        books = cursor.fetchall()

        if books:
            print("Available books:")
            for book in books:
                print(f"ID: {book[0]}, Title: {book[1]}, Author: {book[2]}, Genre: {book[3]}")

            book_id = input("Enter the book ID you'd like to borrow: ")

            cursor.execute("SELECT is_available FROM books WHERE book_id = %s", (book_id,))
            result = cursor.fetchone()

            if result and result[0]:
                user_name = input("Enter your name: ")
                check_user_account(db, user_name, book_id)
            else:
                print("The book is unavailable or invalid book ID.")
        else:
            print("No books are available at the moment.")
    except mysql.connector.Error as err:
        print(f"Error fetching books: {err}")
    finally:
        db.close()


def borrow_book(db, user_id, book_id):
    try:
        days = int(input("For how many days will you borrow the book? "))
        purpose = input("Purpose of borrowing: ")
        documents_provided = input("Do you have the necessary documents? (Yes/No) ").lower() == 'yes'

        cursor = db.cursor()

        cursor.execute("""
            INSERT INTO borrows (user_id, book_id, borrow_date, days, purpose, documents_provided)
            VALUES (%s, %s, CURDATE(), %s, %s, %s)
        """, (user_id, book_id, days, purpose, documents_provided))

        cursor.execute("UPDATE books SET is_available = FALSE WHERE book_id = %s", (book_id,))
        db.commit()

        print("Borrowing confirmed!")
        print("Please return the book within the due date.")
    except mysql.connector.Error as err:
        print(f"Error borrowing book: {err}")

def create_user_account():
    db = connect_to_db()
    cursor = db.cursor()

    try:
        username = input("Enter a username: ")
        password = input("Enter a password: ")

        cursor.execute("INSERT INTO users (username, password) VALUES (%s, %s)", (username, password))
        db.commit()

        print("Account created successfully!")
    except mysql.connector.Error as err:
        print(f"Error creating account: {err}")
    finally:
        db.close()

def check_user_account(db, username, book_id):
    cursor = db.cursor()

    try:
        cursor.execute("SELECT user_id FROM users WHERE username = %s", (username,))
        result = cursor.fetchone()

        if result:
            user_id = result[0]
            borrow_book(db, user_id, book_id)
        else:
            print("User not found. Please create an account first.")
            create_user_account()
    except mysql.connector.Error as err:
        print(f"Error checking user account: {err}")

def admin_login():
    ADMIN_USERNAME = "LIBRARIAN"
    ADMIN_PASSWORD = "HELLOWORLD"

    username = input("Enter admin username: ")
    password = input("Enter admin password: ")

    if username == ADMIN_USERNAME and password == ADMIN_PASSWORD:
        admin_tasks()
    else:
        print("Invalid admin credentials.")

def admin_tasks():
    while True:
        print("1. ADD BOOK")
        print("2. DELETE BOOK")
        print("3. BACK TO MAIN MENU")

        choice = input("Choose an option: ")

        if choice == '1':
            add_book()
        elif choice == '2':
            delete_book()
        elif choice == '3':
            break
        else:
            print("Invalid choice, please try again.")

def add_book():
    db = connect_to_db()
    cursor = db.cursor()

    try:
        title = input("Enter book title: ")
        author = input("Enter author: ")
        genre = input("Enter genre: ")

        cursor.execute("""
            INSERT INTO books (title, author, genre)
            VALUES (%s, %s, %s)
        """, (title, author, genre))

        db.commit()
        print("Book added successfully!")
    except mysql.connector.Error as err:
        print(f"Error adding book: {err}")
    finally:
        db.close()

def delete_book():
    book_id = input("Enter the book ID to delete: ")

    db = connect_to_db()
    cursor = db.cursor()

    try:
        cursor.execute("DELETE FROM borrows WHERE book_id = %s", (book_id,))
        db.commit()

        cursor.execute("DELETE FROM books WHERE book_id = %s", (book_id,))
        db.commit()

        print("Book deleted successfully!")
    except mysql.connector.Error as err:
        print(f"Error deleting book: {err}")
    except Exception as e:
        print(f"Unexpected error: {e}")
    finally:
        db.close()

if __name__ == "__main__":
    main_menu()
