# Student Record Management System (C++)

This project is a simple and efficient **Student Record Management System** implemented in **C++** using Object-Oriented Programming and file handling. It provides a console-based interface for students and administrators to manage academic records and submit/resolve correction tickets.

## Features

### Admin
- Secure login using `credentials.txt`
- Add new students with auto-generated unique IDs (STU00001, STU00002, …)
- View all student records in a formatted table
- Search for a specific student
- View all raised tickets
- Resolve tickets by updating only the requested field

### Student
- View own student record
- Raise a correction ticket with an issue type:
  - Name
  - Semester
  - Section
  - GPA

### System Highlights
- Uses file handling for persistent storage (`students.txt`, `tickets.txt`)
- Auto-generates unique student IDs by reading the last ID from file
- Input validation and error handling for all major fields
- Clean UI for student detail view and ticket display
- Modular design using:
  - `Student` class
  - `Ticket` class
  - `Menu` class (static menu handlers)

## File Structure
```
project.cpp
students.txt
tickets.txt
credentials.txt
README.md
```

## How to Compile & Run

### Using g++
```
g++ project.cpp -o project
./project
```

### Required Files
- **credentials.txt**
```
admin admin123 admin
```

## Future Enhancements
- Color-based console UI
- CSV export or database support
- Password encryption
- Sorting and filtering student records
