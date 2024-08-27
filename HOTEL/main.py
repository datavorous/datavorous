import mysql.connector
import os


def connect_to_db():
    """
    Establishes a connection to the MySQL database.

    Returns:
        MySQL connection object if successful, otherwise exits the program.
    """
    try:
        return mysql.connector.connect(
            host="localhost",
            user="root",
            password="12345",
            database="hotel_booking_system"
        )
    except mysql.connector.Error as err:
        print(f"Error connecting to database: {err}")
        exit()


def main_menu():
    """
    Displays the main menu of the hotel booking system.
    This menu allows users to find rooms, create accounts, or login as admin.
    """
    while True:
        print("Welcome to Modern Hotel!")
        print("1. FIND ROOMS")
        print("2. CREATE USER ACCOUNT")
        print("3. ADMIN LOGIN")
        print("4. EXIT")

        choice = input("Please choose an option: ")

        if choice == '1':
            find_rooms()
        elif choice == '2':
            create_user_account()
        elif choice == '3':
            admin_login()
        elif choice == '4':
            exit()
        else:
            print("Invalid choice, please try again.")


def find_rooms():
    """
    Retrieves available rooms from the database and allows users to book one.
    If a room is available, the user is prompted to provide their username for booking.
    """
    db = connect_to_db()
    cursor = db.cursor()

    try:
        cursor.execute("SELECT * FROM rooms WHERE is_available = TRUE")
        rooms = cursor.fetchall()

        if rooms:
            print("Available rooms:")
            for room in rooms:
                print(f"Room Number: {room[1]}, Type: {room[2]}, Bed Type: {room[3]}, Price: {room[4]}")

            room_number = input("Enter the room number you'd like to book: ")

            cursor.execute("SELECT is_available FROM rooms WHERE room_number = %s", (room_number,))
            result = cursor.fetchone()

            if result and result[0]:  # If the room is available
                user_name = input("Enter your name: ")
                check_user_account(db, user_name, room_number)
            else:
                print("The room is unavailable or invalid room number.")
        else:
            print("No rooms are available at the moment.")
    except mysql.connector.Error as err:
        print(f"Error fetching rooms: {err}")
    finally:
        db.close()


def book_room(db, user_id, room_number):
    """
    Books a room for the user, updates the database, and calculates the total price.
    
    Parameters:
        db (MySQL connection): The database connection object.
        user_id (int): The ID of the user making the booking.
        room_number (str): The number of the room to be booked.
    """
    try:
        nights = int(input("How many nights will you stay? "))
        food_included = input("Do you want food included? (Yes/No) ").lower() == 'yes'
        purpose = input("Purpose of your stay: ")
        documents_provided = input("Do you have the necessary documents? (Yes/No) ").lower() == 'yes'

        cursor = db.cursor()
        cursor.execute("SELECT room_id, price FROM rooms WHERE room_number = %s", (room_number,))
        room = cursor.fetchone()

        if room:
            room_id, price_per_night = room
            total_price = price_per_night * nights
            if food_included:
                total_price += 200 * nights  # Example food cost

            cursor.execute("""
                INSERT INTO bookings (user_id, room_id, check_in_date, nights, food_included, purpose, documents_provided, total_price)
                VALUES (%s, %s, CURDATE(), %s, %s, %s, %s, %s)
            """, (user_id, room_id, nights, food_included, purpose, documents_provided, total_price))

            cursor.execute("UPDATE rooms SET is_available = FALSE WHERE room_number = %s", (room_number,))
            db.commit()

            print(f"Booking confirmed! Total Price: {total_price}")
            print("Please make the payment at the hotel before your departure.")
        else:
            print("Room not found.")
    except mysql.connector.Error as err:
        print(f"Error booking room: {err}")


def create_user_account():
    """
    Prompts the user to create a new account and saves the details in the database.
    """
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


def check_user_account(db, username, room_number):
    """
    Checks if the user exists in the database and proceeds to book a room if found.

    Parameters:
        db (MySQL connection): The database connection object.
        username (str): The username to be checked in the database.
        room_number (str): The number of the room to be booked if the user exists.
    """
    cursor = db.cursor()

    try:
        cursor.execute("SELECT user_id FROM users WHERE username = %s", (username,))
        result = cursor.fetchone()

        if result:
            user_id = result[0]
            book_room(db, user_id, room_number)
        else:
            print("User not found. Please create an account first.")
            create_user_account()
    except mysql.connector.Error as err:
        print(f"Error checking user account: {err}")


def admin_login():
    """
    Prompts the admin for login credentials. If successful, allows access to admin tasks.
    """
    ADMIN_USERNAME = "admin"
    ADMIN_PASSWORD = "admin123"

    username = input("Enter admin username: ")
    password = input("Enter admin password: ")

    if username == ADMIN_USERNAME and password == ADMIN_PASSWORD:
        admin_tasks()
    else:
        print("Invalid admin credentials.")


def admin_tasks():
    """
    Displays the admin task menu and allows the admin to add or delete rooms.
    """
    while True:
        print("1. ADD ROOM")
        print("2. DELETE ROOM")
        print("3. BACK TO MAIN MENU")

        choice = input("Choose an option: ")

        if choice == '1':
            add_room()
        elif choice == '2':
            delete_room()
        elif choice == '3':
            break
        else:
            print("Invalid choice, please try again.")


def add_room():
    """
    Allows the admin to add a new room to the database.
    """
    db = connect_to_db()
    cursor = db.cursor()

    try:
        room_number = input("Enter room number: ")
        room_type = input("Enter room type (AC/NON AC): ").upper()
        bed_type = input("Enter bed type (SINGLE BED/DOUBLE BED): ").upper()
        price = float(input("Enter price per night: "))

        cursor.execute("""
            INSERT INTO rooms (room_number, room_type, bed_type, price)
            VALUES (%s, %s, %s, %s)
        """, (room_number, room_type, bed_type, price))

        db.commit()
        print("Room added successfully!")
    except mysql.connector.Error as err:
        print(f"Error adding room: {err}")
    except ValueError:
        print("Invalid input. Please ensure that the price is a number.")
    finally:
        db.close()


def delete_room():
    """
    Allows the admin to delete a room from the database, ensuring any associated bookings are deleted first.
    """
    room_number = input("Enter the room number to delete: ")

    db = connect_to_db()
    cursor = db.cursor()

    try:
        # Delete any bookings associated with this room first
        cursor.execute("DELETE FROM bookings WHERE room_id = (SELECT room_id FROM rooms WHERE room_number = %s)", (room_number,))
        db.commit()

        # Now delete the room
        cursor.execute("DELETE FROM rooms WHERE room_number = %s", (room_number,))
        db.commit()

        print("Room deleted successfully!")
    except mysql.connector.Error as err:
        print(f"Error deleting room: {err}")
    except Exception as e:
        print(f"Unexpected error: {e}")
    finally:
        db.close()


if __name__ == "__main__":
    main_menu()
