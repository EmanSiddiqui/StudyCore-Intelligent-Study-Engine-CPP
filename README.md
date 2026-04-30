# StudyCore — Intelligent Study Engine 📚

## 📌 About This Project

**StudyCore** is a console-based Smart Study Planner developed in **C++** that helps
students organize their study schedule intelligently. It automatically generates a
personalized day-by-day timetable based on the number of chapters, days until exam,
and the student's weakness level in each subject.

---

## ✨ Features

- 👤 **Student Profile** — Create a personalized profile with name and ID
- ➕ **Add Subjects** — Add subjects with total chapters, exam days and weakness level
- ✏️ **Edit & Delete Subjects** — Modify or remove subjects anytime
- 📅 **Smart Timetable Generator** — Auto-generates a day-by-day study plan
- ⚠️ **Weakness Detection** — Highlights weak subjects and gives smart study tips
- 📊 **Progress Tracker** — Mark and view completed chapters per subject
- ✅ **Input Validation** — Prevents incorrect or out-of-range entries
- 🔁 **Revision Day** — Automatically assigns last day as revision

---

## 🏗️ Object Oriented Design

| Class | Role |
|-------|------|
| `Subject` | Stores all subject data with getters, setters and progress tracking |
| `Planner` | Abstract base class with pure virtual function — Strategy Interface |
| `TimetablePlanner` | Inherits Planner, implements the smart timetable algorithm |
| `StudyContext` | Strategy Context — holds and executes the planning strategy |
| `StudyFacade` | Facade Pattern — hides all complexity behind one simple interface |

---

## 🎨 Design Patterns Used

- 🔄 **Strategy Pattern** — Planner interface allows switching planning algorithms
- 🏛️ **Facade Pattern** — StudyFacade simplifies interaction with the entire system

---

## 🛠️ Tools & Technologies

| Tool | Details |
|------|---------|
| Language | C++ |
| Compiler | Dev C++ |
| Libraries | iostream, vector, string |
| Concepts | OOP, Inheritance, Abstract Classes, Design Patterns, Vectors |
| Environment | Command-Line Interface (CLI) |

---

## 📂 Repository Contents

| File | Description |
|------|-------------|
| `main.cpp` | Complete source code of the project |
| `Report` | Detailed project report |
| `Presentation` | Project presentation slides |

---

## 🚀 How to Run

1. Clone the repository:
git clone https://github.com/EmanSiddiqui/Smart-Study-Planner-CPP.git
2. Open `main.cpp` in **Dev C++** or any C++ compiler
3. Compile and run the file
4. Enter your name and ID to create your profile
5. Start managing your subjects and generating your timetable! 📖

---

## 📫 Connect With Me

- 📧 Email: emansiddiqui2781@gmail.com
- 🐙 GitHub: [EmanSiddiqui](https://github.com/EmanSiddiqui)
