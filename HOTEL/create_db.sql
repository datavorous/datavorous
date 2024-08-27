-- Create database
CREATE DATABASE IF NOT EXISTS hotel_booking_system;
USE hotel_booking_system;

-- Create rooms table
CREATE TABLE IF NOT EXISTS rooms (
    room_id INT PRIMARY KEY AUTO_INCREMENT,
    room_number VARCHAR(10) UNIQUE,
    room_type ENUM('AC', 'NON AC'),
    bed_type ENUM('SINGLE BED', 'DOUBLE BED'),
    price DECIMAL(10, 2),
    is_available BOOLEAN DEFAULT TRUE
);

-- Create users table
CREATE TABLE IF NOT EXISTS users (
    user_id INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(50) UNIQUE,
    password VARCHAR(255),
    is_admin BOOLEAN DEFAULT FALSE
);

-- Create bookings table
CREATE TABLE IF NOT EXISTS bookings (
    booking_id INT PRIMARY KEY AUTO_INCREMENT,
    user_id INT,
    room_id INT,
    check_in_date DATE,
    nights INT,
    food_included BOOLEAN,
    purpose VARCHAR(255),
    documents_provided BOOLEAN,
    total_price DECIMAL(10, 2),
    FOREIGN KEY (user_id) REFERENCES users(user_id),
    FOREIGN KEY (room_id) REFERENCES rooms(room_id)
);
