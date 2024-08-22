#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QJsonDocument>

-- Create book table
CREATE TABLE book (
    id_book INT PRIMARY KEY AUTO_INCREMENT,
    name VARCHAR(255),
    author VARCHAR(255),
    isbn VARCHAR(20)
);

-- Create user table
CREATE TABLE user (
    id_user INT PRIMARY KEY AUTO_INCREMENT,
    username VARCHAR(20) UNIQUE,
    password VARCHAR(255)
);

-- Create car table
CREATE TABLE car (
    id_car INT PRIMARY KEY AUTO_INCREMENT,
    branch VARCHAR(255),
    model VARCHAR(255)
    
);

const express = require('express');
const mysql = require('mysql2');
const bcrypt = require('bcrypt');
const bodyParser = require('body-parser');

const app = express();
const port = 3000;

// Middleware
app.use(bodyParser.json());

// MySQL Connection
const db = mysql.createConnection({
    host: 'localhost',
    user: 'your_username',
    password: 'your_password',
    database: 'your_database_name'
});

// Connect to MySQL
db.connect((err) => {
    if (err) {
        throw err;
    }
    console.log('Connected to MySQL database');
});

// 1. Get all cars
app.get('/cars', (req, res) => {
    db.query('SELECT * FROM car', (err, results) => {
        if (err) {
            console.log(err);
            res.status(500).send('Error retrieving cars from database');
        } else {
            res.json(results);
        }
    });
});

// API endpoints for CRUD operations on 'book' table
// 1. Get all books
app.get('/books', (req, res) => {
    db.query('SELECT * FROM book', (err, results) => {
        if (err) {
            console.log(err);
            res.status(500).send('Error retrieving books from database');
        } else {
            res.json(results);
        }
    });
});

// 2. Get a specific book by id
app.get('/books/:id', (req, res) => {
    const bookId = req.params.id;
    db.query('SELECT * FROM book WHERE id_book = ?', [bookId], (err, results) => {
        if (err) {
            console.log(err);
            res.status(500).send(`Error retrieving book with id ${bookId} from database`);
        } else if (results.length === 0) {
            res.status(404).send(`Book with id ${bookId} not found`);
        } else {
            res.json(results[0]);
        }
    });
});

// 3. Create a new book
app.post('/books', (req, res) => {
    const { name, author, isbn } = req.body;
    db.query('INSERT INTO book (name, author, isbn) VALUES (?, ?, ?)', [name, author, isbn], (err, result) => {
        if (err) {
            console.log(err);
            res.status(500).send('Error saving book to database');
        } else {
            res.status(201).send('Book added to database');
        }
    });
});

// 4. Update an existing book
app.put('/books/:id', (req, res) => {
    const bookId = req.params.id;
    const { name, author, isbn } = req.body;
    db.query('UPDATE book SET name = ?, author = ?, isbn = ? WHERE id_book = ?', [name, author, isbn, bookId], (err, result) => {
        if (err) {
            console.log(err);
            res.status(500).send(`Error updating book with id ${bookId}`);
        } else if (result.affectedRows === 0) {
            res.status(404).send(`Book with id ${bookId} not found`);
        } else {
            res.send(`Book with id ${bookId} updated`);
        }
    });
});

// 5. Delete a book
app.delete('/books/:id', (req, res) => {
    const bookId = req.params.id;
    db.query('DELETE FROM book WHERE id_book = ?', [bookId], (err, result) => {
        if (err) {
            console.log(err);
            res.status(500).send(`Error deleting book with id ${bookId}`);
        } else if (result.affectedRows === 0) {
            res.status(404).send(`Book with id ${bookId} not found`);
        } else {
            res.send(`Book with id ${bookId} deleted`);
        }
    });
});

// Dummy endpoint for user authentication
// This should be secured and use HTTPS in a real application
app.post('/login', async (req, res) => {
    const { username, password } = req.body;
    try {
        const hashedPassword = await bcrypt.hash(password, 10);
        // Here you would typically compare hashedPassword with the one stored in your database for the given username
        // Example:
        // const user = await db.query('SELECT * FROM user WHERE username = ?', [username]);
        // const storedHashedPassword = user[0].password;
        // const match = await bcrypt.compare(password, storedHashedPassword);
        // if (match) {
        //     res.send('Login successful');
        // } else {
        //     res.status(401).send('Authentication failed');
        // }
        res.send('Dummy login endpoint');
    } catch (error) {
        console.log(error);
        res.status(500).send('Error authenticating user');
    }
});

// Start the server
app.listen(port, () => {
    console.log(`Server running on port ${port}`);
});
