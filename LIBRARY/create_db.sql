CREATE DATABASE library_management_system;
USE library_management_system;

CREATE TABLE books (
    book_id INT PRIMARY KEY AUTO_INCREMENT,
    title VARCHAR(100),
    author VARCHAR(100),
    genre VARCHAR(50),
    is_available BOOLEAN DEFAULT TRUE
);

CREATE TABLE users (
    user_id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(50) UNIQUE,
    password VARCHAR(255),
    is_admin BOOLEAN DEFAULT FALSE
);

CREATE TABLE borrows (
    borrow_id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT,
    book_id INT,
    borrow_date DATE,
    days INT,
    purpose VARCHAR(255),
    documents_provided BOOLEAN,
    FOREIGN KEY (user_id) REFERENCES users(user_id),
    FOREIGN KEY (book_id) REFERENCES books(book_id)
);
