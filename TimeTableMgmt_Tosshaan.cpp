#include <iostream.h>
#include <conio.h>
#include <iomanip.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <fstream.h>


char* SubjectForCode(char code)  //returns name of subject for code 
{
    switch (code)
    {
	case 'E': return "English";
	case 'M': return "Maths";
	case 'P': return "Physics:";
	case 'C': return "Computers";
	case 'H': return "Chemistry";
	case 'O': return "Economics";
	case 'A': return "Accounts";
	case 'B': return "Business Studies";
	case 'F': return "Fine Arts";
	case 'S': return "Psychology";
	case 'L': return "Library";
	case 'V': return "Physical Education";
	case 'U': return "SUPW";

	default: return "Unknown";
    }
}


char* ShortForCode(char code)  //returns shortf-form for code
{
    switch (code)
    {
	case 'E': return "Eng";
	case 'M': return "Mat";
	case 'P': return "Phy";
	case 'C': return "Com";
	case 'H': return "Che";
	case 'O': return "Eco";
	case 'A': return "Acc";
	case 'B': return "B.S";
	case 'F': return "Art";
	case 'S': return "Psy";
	case 'L': return "Lib";
	case 'V': return "P.E";
	case 'U': return "SUP";

	default: return "N.A";
    }
}

int clamp(int x, int lo, int hi) //checks if the given argument lies between the limits
{
    return x >= lo && x <= hi;
}


char days[6][10] = {"", "Mon", "Tue", "Wed", "Thu", "Fri"};
const int cellTop = 10, cellLeft = 12, cellBottom = 23;


void clearLine()
{
	gotoxy(cellLeft, cellBottom);
	cout << "                                                                    ";
	gotoxy(cellLeft, cellBottom);
}

char tempTeacherList[20][50];
int tempTeacherCount;

class TimeTable // time table class
{
    char table[6][10];
    char subjects[20];
    char class_sec[4];

public:
    void printLayout() // prints layout
    {
		gotoxy(cellLeft - 2, cellTop - 1);
		int p, day;
		for (p = 1; p <= 9; p++)
		    cout << setw(6) << p;

		for (day = 1; day <= 5; day++)
		{
		    gotoxy(cellLeft - 4, cellTop + 2 * day - 1);
		    cout << days[day];
		}

		gotoxy(cellLeft, cellTop);
		cout << "|";
		for (p = 1; p <= 9; p++)
		    cout << "------";
		cout << "|";

		for (day = 1; day <= 5; day++)
		{
		    gotoxy(cellLeft, cellTop + 2 * day);
		    cout << "|";
		    for (p = 1; p <= 9; p++)
			cout << "------";
		    cout << "|";
		    gotoxy(cellLeft, cellTop + 2 * day - 1);
		    for (p = 1; p <= 9; p++)
			cout << "|     ";
		    cout << " |";
		}
	}

    TimeTable () //constructor
    {
		strcpy(class_sec, "");
		for (int i = 0; i < 20; i++) subjects[i] = 0;
		for (int day = 1; day <= 5; day++)
		    for (int p = 1; p <= 9; p++)
			table[day][p] = 0;
    }

    char GetSubject (int id) //returns subject name for id
	{
		return subjects[id];
	}

    char GetClasses (int day, int p) //returns class if valid day and period are entered
	{
		if (clamp(day, 1, 5) && clamp(p, 1, 9))
			return table[day][p];
		return 0;
	}

    char* GetClassSec () //returns section
	{
		return class_sec;
	}

    void Enter() //to get data
    {
		clrscr();
		cout << "\t\t\t\tTIME TABLE CREATOR\n";
		cout << "\n   KEY: M (Math), E (Eng), P (Phy), C (Comp), H (Chem), O (Eco)";
		cout << ", A (Accounts)\n\tB (Business), F (Fine Arts), S (Psychology)";
		cout << "L (Library)\n\tV (Physical Ed.), U(SUPW), Q (Quit)";
		cout << "\n\n\tEnter your Time Table:\n ";

		char tempTable[6][10];
		int day, p;
		printLayout();
		for (day = 1; day <= 5; day++)
		{
		    for (p = 1; p <= 9; p++)
		    {
			 char code;
			 while (1)
			 {
				clearLine();
				cout << "Enter code for " << days[day] << ", Per " << p;
				cout << ":  ";
				gotoxy(cellLeft + 27, cellBottom);
				cin >> code;
				code = toupper(code);
				if (code == 'Q')
				    return;
				if (strcmp("N.A", ShortForCode(code)))
				    break;
			 }
			 table[day][p] = code;
			 tempTable[day][p] = code;
			 gotoxy(cellLeft + p * 6 - 4, cellTop + 2 * day - 1);
			 cout << ShortForCode(code);
		    }
		}

		clrscr();
		cout << "\t\t\t\tTEACHER LIST\n\n";
		for (int i = 0; i < tempTeacherCount; i++)
		{
			cout << "\t\tID " << setw(2) << i << " : " << tempTeacherList[i] << endl;
		}

		cout << "\n\n";
		for (day = 1; day <= 5; day++)
		{
		    for (p = 1; p <= 9; p++)
		    {
				if (tempTable[day][p] > 0)
				{
					char code = tempTable[day][p];
					for (int D = 1; D <= 5; D++)
						for (int P = 1; P <= 9; P++)
							if (tempTable[D][P] == code)
								tempTable[D][P] = 0;
					int id = 20;
					while (!clamp(id, 0, tempTeacherCount - 1))
					{
						clearLine();
						cout << "Enter teacher for " << SubjectForCode(code) << " : ";
						cin >> id;
						subjects[id] = code;
					}
				}
			}
		}

		clearLine();
		cout << "Do you want to save your time table to a file? (y/n)";
		char reply;
		cin >> reply;
		if (tolower(reply) == 'y')
		    WriteToFile();
    }

    void Display()// to display table 
    {
		clrscr();
		gotoxy(0,0);
		cout << "\n\t\t\t\tYOUR TIMETABLE";
		printLayout();
		for (int day = 1; day <= 5; day++)
		{
		    for (int p = 1; p <= 9; p++)
		    {
			 gotoxy(cellLeft + p * 6 - 4, cellTop + 2 * day - 1);
			 cout << ShortForCode(table[day][p]);
		    }
		}

    }

    void WriteToFile()// to write to the file and store
    {
		Display();
		gotoxy(cellLeft, cellBottom);

		if (strlen(class_sec) == 0)
		{
		    cout << "Enter the name of the TimeTable: ";
		    gets(class_sec);
		}
		fstream file(class_sec, ios::out);

		cout << "Writing to file...";
		for (int day = 1; day <= 5; day++)
		    for (int p = 1; p <= 9; p++)
			file << table[day][p];
		file.close();
		getch();
    }

    void ReadFromFile()// to read from txt file
    {
		clrscr();
		cout << "\n\tEnter the name of the file: ";
		gets(class_sec);
		fstream fil(class_sec, ios::in);
		if (fil.eof())
		{
		    cout << "The file you requested does not exist. Lol";
		    getch();
		    return;
		}
		for (int day = 1; day <= 5; day++)
		    for (int p = 1; p <= 9; p++)
			fil >> table[day][p];
		Display();
		gotoxy(cellLeft, cellBottom);
		cout << "Time Table : " << class_sec;
		getch();
    }

    void Modify()// to modify the contents of the file
    {
		clrscr();
		cout << "\t\t\t\tTIME TABLE EDITOR\n";
		cout << "\n  KEY: M (Math), E (Eng), P (Phy), C (Comp), H (Chem), O (Eco)";
		cout << ", A (Accounts)\n\tB (Business), F (Fine Arts), S (Psychology), Q (Quit)";
		cout << "L (Library)\n\tV (Physical Ed.), U(SUPW), Q (Quit)";
		cout << "\n\n\tEnter your Time Table:\n ";
		char code;
		printLayout();
		int p;
		for (int day = 1; day <= 5; day++)
		{
		    for (p = 1; p <= 9; p++)
		    {
			 gotoxy(cellLeft + p * 6 - 4, cellTop + 2 * day - 1);
			 cout << ShortForCode(table[day][p]);
		    }
		}
		char reply = 'y';
		do
		{
		    while (1)
		    {
			clearLine();
			cout << "Enter the day (1-5) and period (1-9) which you want to change: ";
			cin >> day >> p;
			if (clamp(day, 1, 5) && clamp(p, 1, 9))
			    break;
		    }
		    while (1)
		    {
			clearLine();
			cout << "Enter the subject for " << days[day] << " Period " << p << ": ";
			cin >> code;
			if (strcmp("N.A", ShortForCode(code)))
			    break;
		    }

		    table[day][p] = code;
		    gotoxy(cellLeft + p * 6 - 4, cellTop + 2 * day - 1);
		    cout << ShortForCode(table[day][p]);
		    clearLine();
		    cout << "Do you want to change any other period?: (y/n)";
		    cin >> reply;
		    reply = tolower(reply);
		} while (reply == 'y');
		clearLine();
		cout << "Do you want to save the file (y/n)?";
		cin >> reply;
		if (tolower(reply) == 'y')
		    WriteToFile();
    }

    void Search()// to search  for a specific subject's period
    {
		clrscr();
		cout << "\t\t\t\tTIME TABLE EDITOR\n";
		cout << "\n  KEY: M (Math), E (Eng), P (Phy), C (Comp), H (Chem), O (Eco)";
		cout << ", A (Accounts)\n\tB (Business), F (Fine Arts), S (Psychology), Q (Quit)";
		cout << "L (Library)\n\tV (Physical Ed.), U(SUPW), Q (Quit)";

		gotoxy(cellLeft, cellBottom);
		char code = 0;
		while (!code)
		{
		    cout << "Enter the subject code to search for: ";
		    cin >> code;
		    if (strcmp("N.A", ShortForCode(code)))
			break;
		}

		printLayout();
		int p;
		for (int day = 1; day <= 5; day++)
		{
		    for (p = 1; p <= 9; p++)
		    {
				gotoxy(cellLeft + p * 6 - 4, cellTop + 2 * day - 1);
				if (code == table[day][p])
				{
				cout << ShortForCode(table[day][p]);
				}
		    }
		}
    }

    int Loaded()// checks if tables are filled
    {
		if (strlen(class_sec) == 0 && table[1][1] == 0)
		    return 0;
		else
		    return 1;
    }

    char* Name()// returns name of the table for a section
    {
		if (!Loaded())
		    return "---";
		else if (strlen(class_sec) == 0)
		    return "N.A";
		else
		    return class_sec;
    }
};

void tableMenu(TimeTable &T);

class Manager // class for manager
{
	TimeTable tables[20];
	int numTeachers, numTables;
	char teachers[20][50];

	int getIDForTeacher (char name[50])// gets id for teacher mentioned
	{
		for (int t = 0; t < numTeachers; t++)
			if (strcmp(teachers[t], name) == 0)
				return t;
		return -1;
	}

public:
	Manager()// constructor
	{
		numTeachers = 0;
		numTables = 0;
	}

	char* GetName (int id)// returns name of teacher for id
	{
		if (clamp(id, 0, numTeachers - 1))
			return teachers[id];
		else
			return "";
	}

	void AddTimeTable ()//to add time table
	{
		SetGlobalTeachers();
		TimeTable t;
		t.Enter();
		if (numTables < 20)
		{
			tables[numTables] = t;
			numTables++;
		}
		else
		{
			clearLine();
			cout << "Max. Time table limit reached.";
		}
	}

	void SetGlobalTeachers()
	{
		tempTeacherCount = numTeachers;
		for (int i = 0; i < numTeachers; i++)
			strcpy(tempTeacherList[i], teachers[i]);
	}

	void AddTeacher ()// to add teachers
	{
		DisplayTeachers();
		if (numTeachers >= 20)
		{
			clearLine();
			cout << "Max. Teacher limit reached.";
			return;
		}
		clearLine();
		cout << "Enter the name of Teacher (ID " << numTeachers << "): ";
		gets(teachers[numTeachers]);

		numTeachers++;
	}

	void DisplayTeachers()// tp display name of teachers
	{
		clrscr();
		cout << "\n\t\t\t\tTEACHER LIST\n\n";
		for (int i = 0; i < numTeachers; i++)
		{
			cout << "\t\t\tID " << setw(2) << i << " : " << teachers[i] << endl;
		}
	}

	void PrintTableForTeacher ()// prints table for teachers
	{
		if (numTeachers == 0)
		{
			clearLine();
			cout << "No teachers found";
		}
		DisplayTeachers();
		int id = 20;
		while (!clamp(id, 0, numTeachers - 1))
		{
			clearLine();
			cout << "Enter ID for teacher (0-" << numTeachers - 1 << ") : ";
			cin >> id;
		}
		clrscr();
		char table[6][10][4];
		for (int t1 = 0; t1 < 6; t1++)
		    for (int t2 = 0; t2 < 10; t2++)
		    {
			strcpy(table[t1][t2], "   ");

		    }
		for (int tt = 0; tt < numTables; tt++)
		{
			if (tables[tt].GetSubject(id) == 0)
				continue;
			for (int day = 1; day <= 5; day++)
				for (int p = 1; p <= 9; p++)
					if (tables[tt].GetSubject(id) == tables[tt].GetClasses(day, p))
						strcpy(table[day][p], tables[tt].Name());
		}
		TimeTable t;
		t.printLayout();
		for (int day = 1; day <= 5; day++)
		{
		    for (int p = 1; p <= 9; p++)
		    {
				gotoxy(cellLeft + p * 6 - 4, cellTop + 2 * day - 1);
				cout << table[day][p];
		    }
		}
		gotoxy(cellLeft + 5, cellTop - 3);
		cout << "ID " << setw(2) << id << " : " << teachers[id] << endl;
		getch();
	}

	void Substitution ()// to check for substitutions and assign
	{
		if (numTeachers == 0)
		{
		    clearLine();
		    cout << "No teachers exist.";
		    return;
		}
		clrscr();
		DisplayTeachers();

		int teacher = 20;
		while (!clamp(teacher, 0, numTeachers - 1))
		{
		    clearLine();
		    cout << "Enter ID of teacher who is absent (0-";
		    cout << numTeachers - 1 << ") : ";
		    cin >> teacher;
		}

		int table[6][10];
		for (int day = 1; day <= 5; day++)
			for (int p = 1; p <= 9; p++)
				table[day][p] = -1;
		for (int tt = 0; tt < numTables; tt++)
		{
			for (int day = 1; day <= 5; day++)
				for (int p = 1; p <= 9; p++)
					if (tables[tt].GetSubject(teacher) == tables[tt].GetClasses(day, p))
						table[day][p] = teacher;
		}

		for (int t = 0; t < numTeachers; t++)
		{
			int temp[6][10] = {{0}};
			if (t == teacher) continue;
			for (int tt = 0; tt < numTables; tt++)
				for (int day = 1; day <= 5; day++)
					for (int p = 1; p <= 9; p++)
						if (tables[tt].GetSubject(t) == tables[tt].GetClasses(day, p))
							temp[day][p] = 1;
			for (day = 1; day <= 5; day++)
				for (p = 1; p <= 9; p++)
					if (temp[day][p] == 0 && table[day][p] == teacher)
						table[day][p] = t;
		}

		TimeTable timt;
		timt.printLayout();
		for (day = 1; day <= 5; day++)
		{
		    for (p = 1; p <= 9; p++)
		    {
				gotoxy(cellLeft + p * 6 - 4, cellTop + 2 * day - 1);
				if (table[day][p] != -1)
					cout << " " << table[day][p];
		    }
		}
		getch();
	}

	void ManageTimeTable ()// to manage time tables
	{
		SetGlobalTeachers();
		clearLine();
		if (numTables == 0)
		{
			cout << "No table exists. Bye.\n";
			return;
		}
		int id;
		cout << "Enter ID of time table to open (0-" << numTables - 1 << ") : ";
		cin >> id;
		tableMenu(tables[id]);
	}

} manager;

void SaveManager ()// to save managers object in the file
{
	fstream fil("manager.dat", ios::binary | ios::out);
	fil.write((char *)&manager, sizeof(manager));
	fil.close();
}

void LoadManager () ///to read from manager file
{
	fstream fil("manager.dat", ios::binary | ios::in);
	if (fil.eof())
		manager = Manager();
	else
		fil.read((char *)&manager, sizeof(manager));
	fil.close();
}

void tableMenu(TimeTable &T)// to print menu for editing
{
    clrscr();

    while (1)
    {
		int choice = 0;
		while (!clamp(choice, 1, 6))
		{
		    clrscr();
		    int open = T.Loaded();
		    cout << "\t\t\t\tTIME TABLE PROGRAM\n";
		    cout << "\t\tTable Name: " << T.Name()<<"\n";
		    cout << "\t\tChoose an option from the following (1-6):\n";
		    cout << "\t\t\t1. Enter a new Time Table\n";
		    cout << (open ? "\t\t\t2. Change Time Table\n" : "\t\t\t2. NA\n");
		    cout << "\t\t\t3. Open Time Table\n";
		    cout << (open ? "\t\t\t4. Save Time Table\n" : "\t\t\t4. NA\n");
		    cout << (open ? "\t\t\t5. Search for Subject\n" : "\t\t\t5. NA\n");
		    cout << "\t\t\t6. Go Back\n";
		    cout << "\n\n\t\tEnter your choice: ";
		    cin >> choice;
		    if (!open)
		    {
			if (choice == 2 || choice == 4 || choice == 5)
			    continue;
		    }
		}

		if (choice == 6)
		    break;

		switch (choice)
		{
		    case 1:
				T.Enter();
				break;

		    case 2:
				T.Modify();
				break;

		    case 3:
				T.ReadFromFile();
				break;

		    case 4:
				T.WriteToFile();
				break;

		    case 5:
				T.Search();
				break;

		    default:
				return;
		}
    }
}

void main()
{
	clrscr();
	LoadManager();
    while (1)
    {
		int choice = 0;
		while (!clamp(choice, 1, 8))
		{
		    clrscr();
		    cout << "\t\t\t\tTIME TABLE MANAGER\n";
		    cout << "\t\tChoose an option from the following (1-6):\n";
		    cout << "\t\t\t1. Add a new Time Table\n";
		    cout << "\t\t\t2. Manage Time Table for Class\n";
		    cout << "\t\t\t3. Add Teacher\n";
		    cout << "\t\t\t4. View Teachers\n";
		    cout << "\t\t\t5. Print Time Table for Teacher\n";
		    cout << "\t\t\t6. Add substitution for Teacher\n";
		    cout << "\t\t\t7. Reset Manager\n";
		    cout << "\t\t\t8. Quit\n";
		    cout << "\n\n\t\tEnter your choice: ";
		    cin >> choice;
		}

		if (choice == 8)
		    break;

		switch (choice)
		{
		    case 1:
				manager.AddTimeTable();
				break;

		    case 2:
				manager.ManageTimeTable();
				break;

			case 3:
				manager.AddTeacher();
				break;

			case 4:
				manager.DisplayTeachers();
				break;

		    case 5:
				manager.PrintTableForTeacher();
				break;

		    case 6:
				manager.Substitution();
				break;

		    case 7:
				manager = Manager();
				break;

		    default:
				return;
		}

		SaveManager();
    }

}
