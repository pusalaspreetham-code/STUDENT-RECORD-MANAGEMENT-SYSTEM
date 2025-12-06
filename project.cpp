#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cctype>
using namespace std;

#define STUD_FILE  "students.txt"
#define TICK_FILE  "tickets.txt"
#define LOGIN_FILE "credentials.txt"

//UI Helper
void line() { cout << "-------------------------------------------------------------\n"; }

bool isNumber(string s) {
    int dot = 0;
    for (char c : s) {
        if (c == '.') dot++;
        else if (!isdigit(c)) return false;
        if (dot > 1) return false;
    }
    return true;
}

class Student {
private:
    string id, name;
    int sem, year;
    char sec;
    float gpa;

public:

    static string generateID() {
        ifstream in(STUD_FILE);
        int last = 0;

        string tid, nm;
        int ts, ty; 
        char tc; 
        float tg;

        if (!in.good())
            return "STU00001";

        while (in >> tid >> nm >> ts >> ty >> tc >> tg) {
            int n = stoi(tid.substr(3));
            if (n > last) last = n;
        }
        in.close();

        last++;
        string x = to_string(last);
        return "STU" + string(5 - x.length(), '0') + x;
    }

    void addStudent() {
        id = generateID();
        cout << "\nGenerated ID: " << id << "\n";

        cin.ignore();
        cout << "Name: ";
        getline(cin, name);
        if (name.length() < 2) {
            cout << "Invalid name.\n";
            return;
        }

        string s;
        cout << "Semester (1-8): ";
        cin >> s;
        if (!isNumber(s)) { cout << "Invalid sem.\n"; return; }
        sem = stoi(s);
        if (sem < 1 || sem > 8) { cout << "Invalid sem.\n"; return; }

        year = (sem + 1) / 2;

        string secStr;
        cout << "Section (A-Z): ";
        cin >> secStr;
        if (secStr.length() != 1 || !isalpha(secStr[0])) {
            cout << "Invalid section.\n";
            return;
        }
        sec = toupper(secStr[0]);

        string g;
        cout << "GPA (0–10): ";
        cin >> g;
        if (!isNumber(g)) { cout << "Invalid GPA.\n"; return; }
        gpa = stof(g);
        if (gpa < 0 || gpa > 10) { cout << "Invalid GPA.\n"; return; }

        ofstream out(STUD_FILE, ios::app);
        out << id << " " << name << " " << sem << " "
            << year << " " << sec << " " << gpa << "\n";

        cout << " Student Added Successfully\n";
    }

    static void viewAll() {
        ifstream in(STUD_FILE);
        if (!in.good()) {
            cout << "No student records.\n";
            return;
        }

        string id,nm;
        int sm,yr;
        char sc;
        float gp;

        cout << "\n================ STUDENT LIST ================\n";
        cout << left << setw(12) << "ID"
             << setw(15) << "NAME"
             << setw(6)  << "SEM"
             << setw(6)  << "YEAR"
             << setw(6)  << "SEC"
             << "GPA\n";
        line();

        while (in >> id >> nm >> sm >> yr >> sc >> gp)
            cout << left << setw(12) << id
                 << setw(15) << nm
                 << setw(6)  << sm
                 << setw(6)  << yr
                 << setw(6)  << sc
                 << fixed << setprecision(2) << gp << "\n";
    }

    static void searchStudent() {
        string sid;
        cout << "Enter Student ID: ";
        cin >> sid;

        ifstream in(STUD_FILE);
        if (!in.good()) {
            cout << "No student records.\n";
            return;
        }

        string id,nm;
        int sm,yr;
        char sc;
        float gp;
        bool ok = false;

        while (in >> id >> nm >> sm >> yr >> sc >> gp) {
            if (id == sid) {
                ok = true;

                cout << "\n=================================================\n";
                cout << "            STUDENT INFORMATION\n";
                cout << "=================================================\n";

                cout << left;
                cout << setw(15) << "Student ID" << ": " << id << "\n";
                cout << setw(15) << "Name"       << ": " << nm << "\n";
                cout << setw(15) << "Semester"   << ": " << sm << "\n";
                cout << setw(15) << "Year"       << ": " << yr << "\n";
                cout << setw(15) << "Section"    << ": " << sc << "\n";
                cout << setw(15) << "GPA"        << ": " << fixed << setprecision(2) << gp << "\n";

                cout << "=================================================\n";

                if (gp >= 8.5) cout << " Excellent Performance!\n";
                else if (gp >= 7.0) cout << " Good Performance.\n";
                else cout << " Needs Improvement.\n";

                cout << "=================================================\n";

                return;
            }
        }
        if (!ok) cout << " Student Not Found.\n";
    }
};

class Ticket {
public:
    string id, msg;
    int type;

    void raiseTicket() {
        cout << "Your ID: ";
        cin >> id;

        cout << "1.Name  2.Semester  3.Section  4.GPA\nChoose field: ";
        cin >> type;

        if (type < 1 || type > 4) {
            cout << "Invalid Option.\n";
            return;
        }

        cout << "Describe the issue: ";
        cin.ignore();
        getline(cin, msg);

        ofstream out(TICK_FILE, ios::app);
        out << id << " " << type << " " << msg << "\n";

        cout << " Ticket Submitted\n";
    }

    static void viewTickets() {
        ifstream in(TICK_FILE);
        if (!in.good()) {
            cout << "No tickets.\n";
            return;
        }

        string id,text;
        int type;

        cout << "\n================= TICKET LIST =================\n";
        cout << "ID        FIELD       ISSUE\n";
        line();

        while (in >> id >> type) {
            in.get();
            getline(in, text);

            string field =
                (type==1? "NAME" :
                 type==2? "SEMESTER" :
                 type==3? "SECTION" : "GPA");

            cout << left << setw(10) << id
                 << setw(12) << field
                 << text << "\n";
        }
    }

    static void resolveTicket() {
        viewTickets();

        string sid;
        cout << "\nEnter Student ID to resolve ticket: ";
        cin >> sid;

        ifstream rt(TICK_FILE);
        if (!rt.good()) {
            cout << "No tickets to resolve.\n";
            return;
        }

        string tid,text;
        int type;
        bool found = false;

        while (rt >> tid >> type) {
            rt.get();
            getline(rt, text);
            if (tid == sid) { found = true; break; }
        }
        rt.close();

        if (!found) {
            cout << "No ticket found for this ID.\n";
            return;
        }

        ifstream in(STUD_FILE);
        ofstream tmp("temp.txt");

        string id,nm;
        int sm,yr;
        char sc;
        float gp;

        while (in >> id >> nm >> sm >> yr >> sc >> gp) {
            if (id == sid) {
                if (type == 1) {
                    cin.ignore();
                    cout << "Enter Correct Name: ";
                    getline(cin, nm);
                }
                else if (type == 2) {
                    string s;
                    cout << "Enter Correct Semester: ";
                    cin >> s;
                    if (!isNumber(s)) { cout<<"Invalid.\n"; return; }
                    sm = stoi(s);
                    yr = (sm+1)/2;
                }
                else if (type == 3) {
                    cout << "Enter Correct Section: ";
                    cin >> sc;
                    sc = toupper(sc);
                }
                else if (type == 4) {
                    string s;
                    cout << "Enter Correct GPA: ";
                    cin >> s;
                    if (!isNumber(s)) { cout<<"Invalid.\n"; return; }
                    gp = stof(s);
                }
            }

            tmp << id << " " << nm << " "
                << sm << " " << yr << " "
                << sc << " " << gp << "\n";
        }

        in.close();
        tmp.close();

        remove(STUD_FILE);
        rename("temp.txt", STUD_FILE);

        ifstream rin(TICK_FILE);
        ofstream nt("temp2.txt");

        while (rin >> tid >> type) {
            rin.get();
            getline(rin, text);
            if (tid != sid)
                nt << tid << " " << type << " " << text << "\n";
        }

        rin.close();
        nt.close();

        remove(TICK_FILE);
        rename("temp2.txt", TICK_FILE);

        cout << " Ticket Resolved Successfully\n";
    }
};

class Menu {
public:
    static bool login() {
        string u,p,fu,fp,r;

        cout << "Username: ";
        cin >> u;
        cout << "Password: ";
        cin >> p;

        ifstream in(LOGIN_FILE);
        if (!in.good()) {
            cout << "credentials.txt missing!\n";
            return false;
        }

        while (in >> fu >> fp >> r)
            if (u==fu && p==fp && r=="admin")
                return true;

        return false;
    }

    static void adminMenu() {
        int ch;
        while (true) {
            cout << "\n================ ADMIN MENU ================\n";
            cout << "1.Add Student\n2.View Students\n3.Search Student\n";
            cout << "4.View Tickets\n5.Resolve Ticket\n6.Logout\n";
            line();
            cout << "Enter choice: ";
            cin >> ch;

            if (ch == 1) { Student s; s.addStudent(); }
            else if (ch == 2) Student::viewAll();
            else if (ch == 3) Student::searchStudent();
            else if (ch == 4) Ticket::viewTickets();
            else if (ch == 5) Ticket::resolveTicket();
            else return;
        }
    }

    static void studentMenu() {
        int ch;
        while (true) {
            cout << "\n================ STUDENT MENU ================\n";
            cout << "1.My Details\n2.Raise Ticket\n3.Back\n";
            line();
            cout << "Enter choice: ";
            cin >> ch;

            if (ch == 1) Student::searchStudent();
            else if (ch == 2) { Ticket t; t.raiseTicket(); }
            else return;
        }
    }

    static void mainMenu() {
        int ch;
        while (true) {
            cout << "\n================ MAIN MENU ================\n";
            cout << "1.Admin Login\n2.Student Portal\n3.Exit\n";
            line();
            cout << "Enter choice: ";
            cin >> ch;

            if (ch == 1) {
                if (login()) adminMenu();
                else cout << "Invalid login.\n";
            }
            else if (ch == 2) studentMenu();
            else break;
        }
    }
};

int main() {
    Menu::mainMenu();
    return 0;
}
