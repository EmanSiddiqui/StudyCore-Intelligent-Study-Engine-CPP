#include <iostream>
#include <vector>
#include <string>
using namespace std;

// =========================================================================
// CLASS 1: Subject
// Represents one subject with all its data
// =========================================================================
class Subject {
private:
    string name;
    int totalChapters;
    int daysUntilExam;
    int weaknessLevel;
    int chaptersCompleted;

public:
    Subject(string n, int chapters, int days, int weakness) {
        name = n;
        totalChapters = chapters;
        daysUntilExam = days;
        weaknessLevel = weakness;
        chaptersCompleted = 0;
    }

    // Getters
    string getName()           { return name; }
    int getTotalChapters()     { return totalChapters; }
    int getDaysUntilExam()     { return daysUntilExam; }
    int getWeaknessLevel()     { return weaknessLevel; }
    int getChaptersCompleted() { return chaptersCompleted; }
    int getChaptersLeft()      { return totalChapters - chaptersCompleted; }

    // Setters
    void setName(string n)       { name = n; }
    void setTotalChapters(int c) { totalChapters = c; }
    void setDaysUntilExam(int d) { daysUntilExam = d; }
    void setWeaknessLevel(int w) { weaknessLevel = w; }

    void addProgress(int count) {
        if (getChaptersLeft() == 0) {
            cout << "\n  All chapters already completed!\n";
            return;
        }
        int remaining = totalChapters - chaptersCompleted;
        while (count < 1 || count > remaining) {
            if (count < 1)
                cout << "  Enter at least 1 chapter.\n";
            else
                cout << "  Only " << remaining << " chapters left! Enter correct number: ";
            cin >> count;
            cin.ignore();
        }
        chaptersCompleted += count;
    }

    void display() {
        cout << "  Subject         : " << name << "\n";
        cout << "  Total Chapters  : " << totalChapters << "\n";
        cout << "  Chapters Done   : " << chaptersCompleted << "\n";
        cout << "  Chapters Left   : " << getChaptersLeft() << "\n";
        cout << "  Days Until Exam : " << daysUntilExam << "\n";
        cout << "  Weakness (1-10) : " << weaknessLevel << "\n";
    }
};

// =========================================================================
// CLASS 2: Planner — Strategy Interface (Abstract Base Class)
// Defines the contract — every planner MUST implement generatePlan()
// Pure virtual function forces all child classes to override it
// =========================================================================
class Planner {
public:
    virtual void generatePlan(vector<Subject>& subjects) = 0;
    virtual ~Planner() {}
};

// =========================================================================
// CLASS 3: TimetablePlanner — Concrete Strategy
// Inherits from Planner and implements the actual timetable algorithm
// =========================================================================
class TimetablePlanner : public Planner {
public:
    void generatePlan(vector<Subject>& subjects) override {

        if (subjects.empty()) {
            cout << "\n  No subjects added yet!\n";
            cout << "  Go to Manage Subjects and add subjects first.\n";
            return;
        }

        cout << "\n  +==========================================+\n";
        cout << "  |       StudyCore -- Smart Timetable       |\n";
        cout << "  +==========================================+\n";

        // Sort subjects by soonest exam first — bubble sort
        int n = subjects.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (subjects[j].getDaysUntilExam() > subjects[j+1].getDaysUntilExam()) {
                    Subject temp  = subjects[j];
                    subjects[j]   = subjects[j+1];
                    subjects[j+1] = temp;
                }
            }
        }

        for (int i = 0; i < subjects.size(); i++) {

            int totalDays    = subjects[i].getDaysUntilExam();
            int chaptersLeft = subjects[i].getChaptersLeft();
            int done         = subjects[i].getChaptersCompleted();

            cout << "\n  ==========================================\n";
            cout << "  Subject : " << subjects[i].getName() << "\n";
            cout << "  ==========================================\n";
            cout << "  Chapters Left   : " << chaptersLeft << "\n";
            cout << "  Days Until Exam : " << totalDays << "\n";
            cout << "  ------------------------------------------\n";

            // Case 1 — all chapters done
            if (chaptersLeft <= 0) {
                cout << "  All chapters done! Revision plan:\n\n";
                for (int day = 1; day <= totalDays; day++)
                    cout << "  Day " << day << " : Revision\n";
                continue;
            }

            // Case 2 — only 1 day left
            if (totalDays == 1) {
                cout << "  Only 1 day left!\n";
                cout << "  Day 1 : Revise everything + cover what you can\n";
                continue;
            }

            // Case 3 — normal smart calculation
                
            int availableStudyDays = totalDays - 1;
            int chaptersPerDay;
			int daysNeeded;
			int extraChapters;
			
			if (chaptersLeft <= availableStudyDays) {
			daysNeeded     = chaptersLeft;
			chaptersPerDay = 1;
			extraChapters  = 0;
			} 
			
			else {
			daysNeeded     = availableStudyDays;
			chaptersPerDay = chaptersLeft / daysNeeded;
			extraChapters  = chaptersLeft % daysNeeded;
			}

int revisionDays = totalDays - daysNeeded;

            cout << "  Study Days    : " << daysNeeded << "\n";
            cout << "  Revision Days : " << revisionDays << "\n\n";

            int chapterNumber = done + 1;

            for (int day = 1; day <= totalDays; day++) {

                // last day always revision
                if (day == totalDays) {
                    cout << "  Day " << day << " : *** REVISION DAY ***\n";
                    break;
                }

                // chapters finished or past study days — revision
                if (chapterNumber > subjects[i].getTotalChapters() ||
                    day > daysNeeded) {
                    cout << "  Day " << day << " : Revision\n";
                    continue;
                }

                int todayChapters = chaptersPerDay;
                if (extraChapters > 0 && day <= extraChapters)
                    todayChapters = chaptersPerDay + 1;

                int chapterEnd = chapterNumber + todayChapters - 1;

                if (chapterEnd > subjects[i].getTotalChapters())
                    chapterEnd = subjects[i].getTotalChapters();

                cout << "  Day " << day << " : Chapter "
                     << chapterNumber << " to " << chapterEnd;

                if (subjects[i].getWeaknessLevel() >= 7)
                    cout << "  [ Weak - Focus Hard! ]";

                cout << "\n";
                chapterNumber = chapterEnd + 1;
            }

            cout << "\n";

            if (chaptersPerDay >= 4)
                cout << "  Warning : Heavy load - " << chaptersPerDay
                     << " chapters/day!\n";

            if (subjects[i].getWeaknessLevel() >= 8)
                cout << "  Tip : Weakest subject - start it first every day.\n";
            else if (subjects[i].getWeaknessLevel() >= 5)
                cout << "  Tip : Don't skip this subject.\n";
            else
                cout << "  Tip : You are strong here - stay consistent.\n";
        }

        cout << "\n  +==========================================+\n";
        cout << "  |   Timetable Ready! Stay Consistent!      |\n";
        cout << "  +==========================================+\n";
    }
};

// =========================================================================
// CLASS 4: StudyContext — Strategy Context
// Holds a pointer to a Planner strategy
// Allows switching planning algorithms without changing other code
// =========================================================================
class StudyContext {
private:
    Planner* strategy;
public:
    StudyContext() : strategy(NULL) {}

    void setPlanner(Planner* s) {
        strategy = s;
    }

    void executePlan(vector<Subject>& subjects) {
        if (strategy)
            strategy->generatePlan(subjects);
    }
};

// =========================================================================
// CLASS 5: StudyFacade — Facade Pattern
// Hides all complexity of subject management, progress tracking,
// and timetable generation behind one simple class
// main() only creates this object and calls start()
// =========================================================================
class StudyFacade {
private:
    vector<Subject>  subjects;
    TimetablePlanner planner;
    StudyContext     context;
    string           userName;
    string           userId;

public:
    StudyFacade() {
        context.setPlanner(&planner);
    }

    void start() {
        cout << "\n  +==========================================+\n";
        cout << "  |         WELCOME TO STUDYCORE             |\n";
        cout << "  |    Intelligent Study Engine v1.0         |\n";
        cout << "  +==========================================+\n";
        cout << "\n  Enter Your Name : ";
        getline(cin, userName);
        cout << "  Enter Your ID   : ";
        getline(cin, userId);
        cout << "\n  Welcome, " << userName << "! Profile created.\n";

        int choice;
        do {
            cout << "\n  +==========================================+\n";
            cout << "  |              DASHBOARD                   |\n";
            cout << "  +==========================================+\n";
            cout << "  1. View Profile\n";
            cout << "  2. Manage Subjects\n";
            cout << "  3. Generate Timetable\n";
            cout << "  4. Study Progress\n";
            cout << "  0. Exit\n";
            cout << "\n  Enter Choice: ";
            cin >> choice;
            cin.ignore();

            if (choice == 1) {
                cout << "\n  +==========================================+\n";
                cout << "  |            STUDENT PROFILE               |\n";
                cout << "  +==========================================+\n";
                cout << "  Name : " << userName << "\n";
                cout << "  ID   : " << userId   << "\n";
            }
            else if (choice == 2)
                manageSubjects();
            else if (choice == 3)
                context.executePlan(subjects);
            else if (choice == 4)
                studyProgress();
            else if (choice == 0) {
                cout << "\n  +==========================================+\n";
                cout << "  |  Goodbye, " << userName << "!\n";
                cout << "  |  Keep Studying. You Got This!\n";
                cout << "  +==========================================+\n\n";
            }
            else
                cout << "\n  Invalid choice. Please try again.\n";

        } while (choice != 0);
    }

    void manageSubjects() {
        int choice;
        do {
            cout << "\n  +==========================================+\n";
            cout << "  |           MANAGE SUBJECTS                |\n";
            cout << "  +==========================================+\n";
            cout << "  1. Add Subject\n";
            cout << "  2. Edit Subject\n";
            cout << "  3. Delete Subject\n";
            cout << "  4. View Subjects\n";
            cout << "  0. Back to Dashboard\n";
            cout << "\n  Enter Choice: ";
            cin >> choice;
            cin.ignore();

            if (choice == 1) {
                string n;
                int c, d, w;

                cout << "\n  -- Add New Subject --\n";
                cout << "  Subject Name            : ";
                getline(cin, n);

                do {
                    cout << "  Total Chapters (1-200)  : ";
                    cin >> c;
                    if (c < 1 || c > 200)
                        cout << "  Invalid! Enter between 1 and 200.\n";
                } while (c < 1 || c > 200);

                do {
                    cout << "  Days Until Exam (1-365) : ";
                    cin >> d;
                    if (d < 1 || d > 365)
                        cout << "  Invalid! Enter between 1 and 365.\n";
                } while (d < 1 || d > 365);

                do {
                    cout << "  Weakness Level (1-10)   : ";
                    cin >> w;
                    if (w < 1 || w > 10)
                        cout << "  Invalid! Enter between 1 and 10.\n";
                } while (w < 1 || w > 10);

                cin.ignore();
                subjects.push_back(Subject(n, c, d, w));
                cout << "\n  Subject added successfully!\n";
            }

            else if (choice == 2) {
                if (subjects.empty()) {
                    cout << "\n  No subjects to edit.\n";
                } else {
                    cout << "\n  -- Select Subject to Edit --\n";
                    for (int i = 0; i < subjects.size(); i++)
                        cout << "  [" << i+1 << "] " << subjects[i].getName() << "\n";

                    int idx;
                    do {
                        cout << "  Enter number: ";
                        cin >> idx;
                        if (idx < 1 || idx > subjects.size())
                            cout << "  Invalid! Enter between 1 and "
                                 << subjects.size() << ".\n";
                    } while (idx < 1 || idx > subjects.size());

                    cin.ignore();
                    idx = idx - 1;

                    string n;
                    int c, d, w;

                    cout << "  New Name                : ";
                    getline(cin, n);

                    do {
                        cout << "  New Total Chapters (1-200)  : ";
                        cin >> c;
                        if (c < 1 || c > 200)
                            cout << "  Invalid! Enter between 1 and 200.\n";
                    } while (c < 1 || c > 200);

                    do {
                        cout << "  New Days Until Exam (1-365) : ";
                        cin >> d;
                        if (d < 1 || d > 365)
                            cout << "  Invalid! Enter between 1 and 365.\n";
                    } while (d < 1 || d > 365);

                    do {
                        cout << "  New Weakness (1-10)         : ";
                        cin >> w;
                        if (w < 1 || w > 10)
                            cout << "  Invalid! Enter between 1 and 10.\n";
                    } while (w < 1 || w > 10);

                    cin.ignore();
                    subjects[idx].setName(n);
                    subjects[idx].setTotalChapters(c);
                    subjects[idx].setDaysUntilExam(d);
                    subjects[idx].setWeaknessLevel(w);
                    cout << "\n  Subject updated successfully!\n";
                }
            }

            else if (choice == 3) {
                if (subjects.empty()) {
                    cout << "\n  No subjects to delete.\n";
                } else {
                    cout << "\n  -- Select Subject to Delete --\n";
                    for (int i = 0; i < subjects.size(); i++)
                        cout << "  [" << i+1 << "] " << subjects[i].getName() << "\n";

                    int idx;
                    do {
                        cout << "  Enter number: ";
                        cin >> idx;
                        if (idx < 1 || idx > subjects.size())
                            cout << "  Invalid! Enter between 1 and "
                                 << subjects.size() << ".\n";
                    } while (idx < 1 || idx > subjects.size());

                    cin.ignore();
                    idx = idx - 1;
                    string deleted = subjects[idx].getName();
                    subjects.erase(subjects.begin() + idx);
                    cout << "\n  '" << deleted << "' deleted successfully.\n";
                }
            }

            else if (choice == 4) {
                if (subjects.empty()) {
                    cout << "\n  No subjects added yet.\n";
                } else {
                    cout << "\n  +==========================================+\n";
                    cout << "  |            ALL SUBJECTS                  |\n";
                    cout << "  +==========================================+\n";
                    for (int i = 0; i < subjects.size(); i++) {
                        cout << "\n  -- Subject " << i+1 << " --\n";
                        subjects[i].display();
                    }
                }
            }

            else if (choice != 0)
                cout << "\n  Invalid choice. Please try again.\n";

        } while (choice != 0);
    }

    void studyProgress() {
        int choice;
        do {
            cout << "\n  +==========================================+\n";
            cout << "  |            STUDY PROGRESS                |\n";
            cout << "  +==========================================+\n";
            cout << "  1. Mark Progress\n";
            cout << "  2. View Progress\n";
            cout << "  0. Back to Dashboard\n";
            cout << "\n  Enter Choice: ";
            cin >> choice;
            cin.ignore();

            if (choice == 1) {
                if (subjects.empty()) {
                    cout << "\n  No subjects added yet.\n";
                } else {
                    cout << "\n  -- Select Subject --\n";
                    for (int i = 0; i < subjects.size(); i++)
                        cout << "  [" << i+1 << "] " << subjects[i].getName() << "\n";

                    int idx;
                    do {
                        cout << "  Enter number : ";
                        cin >> idx;
                        if (idx < 1 || idx > subjects.size())
                            cout << "  Invalid! Enter between 1 and "
                                 << subjects.size() << ".\n";
                    } while (idx < 1 || idx > subjects.size());

                    cin.ignore();
                    idx = idx - 1;

                    cout << "  Chapters done today : ";
                    int count;
                    cin >> count;
                    cin.ignore();

                    subjects[idx].addProgress(count);
                    cout << "\n  Progress saved!\n";
                    cout << "  Chapters Left : "
                         << subjects[idx].getChaptersLeft() << "\n";
                }
            }

            else if (choice == 2) {
                if (subjects.empty()) {
                    cout << "\n  No subjects added yet.\n";
                } else {
                    cout << "\n  +==========================================+\n";
                    cout << "  |            STUDY PROGRESS                |\n";
                    cout << "  +==========================================+\n";
                    for (int i = 0; i < subjects.size(); i++) {
                        cout << "\n  -- " << subjects[i].getName() << " --\n";
                        cout << "  Chapters Done : "
                             << subjects[i].getChaptersCompleted() << "\n";
                        cout << "  Chapters Left : "
                             << subjects[i].getChaptersLeft() << "\n";
                        cout << "  Total         : "
                             << subjects[i].getTotalChapters() << "\n";
                    }
                }
            }

            else if (choice != 0)
                cout << "\n  Invalid choice. Please try again.\n";

        } while (choice != 0);
    }
};


int main() {
    StudyFacade app;
    app.start();
    return 0;
}
