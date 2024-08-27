# DO NOT PRINT THIS FILE PLS THIS IS JUST FOR MAKING THE DATABASE

import mysql.connector

def connect_to_db():
    try:
        return mysql.connector.connect(
            host="localhost",
            user="root",
            password="12345"
        )
    except mysql.connector.Error as err:
        print(f"Error connecting to database: {err}")
        exit()

def execute_sql_script(file_path):
    db = connect_to_db()
    cursor = db.cursor()

    try:
        with open(file_path, 'r') as file:
            sql_script = file.read()

        sql_commands = sql_script.split(';')  # Split the script by semicolon
        for command in sql_commands:
            if command.strip():  # Avoid executing empty commands
                cursor.execute(command)

        db.commit()
        print("SQL script executed successfully!")
    except mysql.connector.Error as err:
        print(f"Error executing SQL script: {err}")
    finally:
        cursor.close()
        db.close()

if __name__ == "__main__":
    # Provide the path to your SQL script file
    execute_sql_script("create_db.sql")
