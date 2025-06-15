# SnakeMonGame 🎲🐍🏦

A creative and interactive C++ game that blends the classic "Snakes & Ladders" board game with the strategic elements of "Monopoly." Developed as part of the CMPG102 Programming Techniques course at Cairo University – Faculty of Engineering.

## 📽 Overview

**SnakeMonGame** allows users to design a customizable game grid and then play through it with 4 players. The grid includes:
- 🪜 Ladders and 🐍 Snakes (in the same column)
- 🃏 Special Cards (13 types)
- 💰 Station ownership and player wallets
- 🎮 Two modes: Design Mode and Play Mode

Design Mode lets players create and configure the game board. Play Mode simulates a full game experience with turns, dice rolls, and special mechanics like buying stations or skipping turns.

## ✨ Features

- 🎨 GUI-based interaction (no console I/O)
- 🧠 Built using OOP principles: encapsulation, inheritance, polymorphism
- 🔁 Mode switching (Design <=> Play)
- 🧩 Cards with unique behaviors, such as:
  - Wallet effects
  - Teleportation
  - Turn manipulation
  - Real estate (buyable stations)
- 📂 Save/Open game state to text files
- 💡 Easily extendable architecture

## 🧠 Skills Gained

- Object-Oriented Design
- GUI Development with graphics library
- Game State Management
- Team Collaboration using Visual Studio
- Polymorphism and Dynamic Memory Handling

## 👨‍💻 Team

- **Mostafa Mohammed** – Logic design, code integration, GUI enhancements, and project documentation  
- **Mariam Sameh** – Game mechanics, player interactions, and Play Mode logic  
- **Mariam Mohamed** – Card implementation, I/O logic, and validations  

## 📷 Screenshots

> Add your screenshots here (e.g., `images/grid_sample.png`, `images/play_mode.png`)

## 🗃 File Structure

```
Phase2_Code/
├── Actions/           # All user-triggered actions
├── Cards/             # All card logic (CardOne to CardThirteen)
├── Grid/              # Grid and Cell classes
├── GameObjects/       # Ladder, Snake, Card (base)
├── Player/            # Player class and movement logic
├── GUI/               # Input & Output classes
├── Resources/         # Toolbar images, icons
└── main.cpp           # Entry point
```

## 💾 Sample Grids

You can find sample grid saves inside the `/SavedGrids/` folder:
- `sample1.txt` – Simple test grid with ladders and snakes
- `sample2.txt` – Includes advanced cards and stations
- `sample3.txt` – Fully playable grid with all features

Each sample is accompanied by a `.png` screenshot.

## 🚀 Getting Started

### Prerequisites

- Visual Studio (recommended)
- C++ compiler
- Project uses an open-source graphics library included in `/GUI/`

### How to Run

1. Clone the repo
2. Open the solution in Visual Studio
3. Build and Run

## 📁 Save File Format

```
[Number_of_Ladders]
[start_cell] [end_cell]
...
[Number_of_Snakes]
[start_cell] [end_cell]
...
[Number_of_Cards]
[type] [cell] [param1] [param2] ...
```

Refer to Phase 2 document for full specs.

## 📌 Course Info

**Course**: CMPG102 – Programming Techniques  
**University**: Cairo University, Faculty of Engineering  
**Semester**: Fall 2024  

## 📜 License

This project is academic work for CMPG102. Redistribution or reuse outside this context is not allowed without permission.

## 🔗 Related

- [LinkedIn Project Post](https://www.linkedin.com/in/mostafamohammed2005)  
- [CV Summary](#)

## 🏁 Final Notes

This was our first full OOP-based game project, and we’re proud of the creativity, logic, and teamwork that went into it. Special thanks to our teammates and instructors for their support!
