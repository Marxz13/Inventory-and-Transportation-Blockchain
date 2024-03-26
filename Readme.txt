# Inventory and Transport Management System using Blockchain

This C++ application utilizes blockchain technology for secure and transparent management of inventory and transport logistics. It is designed to ensure data integrity and security, providing a straightforward method for managing and tracking inventory and transport data.

## Features

- **Adding New Blocks**: Users can add new blocks by either manually entering data or importing from a formatted file.
- **Block Search**: Search for blocks using the first two and the last four characters in the block's hash.
- **Save Blockchain**: Save the current blockchain state in memory to a file for persistence.
- **View Blockchain**: Users can view the current blockchain stored in memory or select a saved blockchain file to view.

## Getting Started

To use this application, you'll need a C++ compiler set up on your system.

### Prerequisites

- C++ compiler (GCC, Clang, MSVC)
- Basic knowledge of terminal or command prompt commands

### Compilation

Compile the source files using your C++ compiler. For example, if you are using GCC, you can compile the application with the following command:

```bash
g++ -o blockchain_app main.cpp Blockchain.cpp Block.cpp FileOperations.cpp -std=c++11
Running the Application
After compilation, you can run the application using:

bash
Copy code
./blockchain_app
Or on Windows:

cmd
Copy code
blockchain_app.exe
Usage
Upon launching the application, you'll be prompted to log in.

## Login Details
Username: admin
Password: admin
After logging in, follow the on-screen instructions to interact with the application.

## Acknowledgments
Created by Marzallan
Inspired by the principles of blockchain technology and its applications in inventory and transport management.
