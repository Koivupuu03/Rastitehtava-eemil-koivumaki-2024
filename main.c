CREATE DATABASE bookstore;

USE bookstore;

CREATE TABLE book (
  id_book INT PRIMARY KEY AUTO_INCREMENT,
  name VARCHAR(255),
  author VARCHAR(255),
  isbn VARCHAR(20)
);

CREATE TABLE user (
  id_user INT PRIMARY KEY AUTO_INCREMENT,
  username VARCHAR(20) UNIQUE,
  password VARCHAR(255)
);

CREATE TABLE car (
  id_car INT PRIMARY KEY AUTO_INCREMENT,
  branch VARCHAR(255),
  model VARCHAR(255)
);

const express = require('express');
const mysql = require('mysql');
const bcrypt = require('bcrypt');
const bodyParser = require('body-parser');

const app = express();
const port = 3000;

// MySQL connection
const connection = mysql.createConnection({
  host: 'localhost',
  user: 'your_mysql_user',
  password: 'your_mysql_password',
  database: 'bookstore'
});

// Middleware
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

// CRUD operations for the book table

// Get all books
app.get('/books', (req, res) => {
  connection.query('SELECT * FROM book', (error, results) => {
    if (error) throw error;
    res.send(results);
  });
});

// Get a book by id
app.get('/books/:id', (req, res) => {
  const bookId = req.params.id;
  connection.query('SELECT * FROM book WHERE id_book = ?', [bookId], (error, results) => {
    if (error) throw error;
    res.send(results[0]);
  });
});

// Create a new book
app.post('/books', (req, res) => {
  const { name, author, isbn } = req.body;
  connection.query('INSERT INTO book (name, author, isbn) VALUES (?, ?, ?)', [name, author, isbn], (error, results) => {
    if (error) throw error;
    res.send('Book added successfully');
  });
});

// Update a book
app.put('/books/:id', (req, res) => {
  const bookId = req.params.id;
  const { name, author, isbn } = req.body;
  connection.query('UPDATE book SET name = ?, author = ?, isbn = ? WHERE id_book = ?', [name, author, isbn, bookId], (error, results) => {
    if (error) throw error;
    res.send('Book updated successfully');
  });
});

// Delete a book
app.delete('/books/:id', (req, res) => {
  const bookId = req.params.id;
  connection.query('DELETE FROM book WHERE id_book = ?', [bookId], (error, results) => {
    if (error) throw error;
    res.send('Book deleted successfully');
  });
});

// Get all cars
app.get('/cars', (req, res) => {
  connection.query('SELECT * FROM car', (error, results) => {
    if (error) throw error;
    res.send(results);
  });
});

// Get a car by id
app.get('/cars/:id', (req, res) => {
  const carId = req.params.id;
  connection.query('SELECT * FROM car WHERE id_car = ?', [carId], (error, results) => {
    if (error) throw error;
    res.send(results[0]);
  });
});

// Create a new car
app.post('/cars', (req, res) => {
  const { branch, model } = req.body;
  connection.query('INSERT INTO car (branch, model) VALUES (?, ?)', [branch, model], (error, results) => {
    if (error) throw error;
    res.send('Car added successfully');
  });
});

// Update a car
app.put('/cars/:id', (req, res) => {
  const carId = req.params.id;
  const { branch, model } = req.body;
  connection.query('UPDATE car SET branch = ?, model = ? WHERE id_car = ?', [branch, model, carId], (error, results) => {
    if (error) throw error;
    res.send('Car updated successfully');
  });
});

// Delete a car
app.delete('/cars/:id', (req, res) => {
  const carId = req.params.id;
  connection.query('DELETE FROM car WHERE id_car = ?', [carId], (error, results) => {
    if (error) throw error;
    res.send('Car deleted successfully');
  });
});

// Start the server
app.listen(port, () => {
  console.log(`Server is running on port ${port}`);
});

