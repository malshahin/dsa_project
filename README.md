# 🚌 Bus Ticket Booking System (C Project)

A terminal-based bus ticket reservation system built in C for educational and demonstration purposes.

## 💡 Features

- Register buses with unique IDs and seat capacity
- Book seats for passengers
- Manage waiting list using queues
- Cancel bookings with automatic reallocation from waiting list
- Show bus details with available/occupied seat status
- Clear cross-platform terminal screen using macros

## 📁 Project Structure

- `project.c`: Main source file
- `Makefile`: (Optional) For building the project (you can add one if needed)

## 🔧 Compilation

On Linux:
```bash
gcc project.c -o bus_booking
./bus_booking
```
On Windows:
```bash
gcc project.c -o bus_booking.exe
bus_booking.exe
```
