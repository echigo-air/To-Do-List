#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

struct Task
{
    string text;
    bool marked;
};

vector<Task> tasks;
const string TO_DO_LIST = "todolist.txt";

// ========= UTILITY =========
void Pause()
{
    cout << "\nPress ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// ========= FILE I/O =========
void LoadTList()
{
    ifstream file(TO_DO_LIST);
    if (!file) return;

    tasks.clear();

    string line;
    while (getline(file, line))
    {
        if (line.size() < 3) continue;

        Task t;
        t.marked = (line[0] == '1');
        t.text = line.substr(2);
        tasks.push_back(t);
    }
}

void SaveTasks()
{
    ofstream file(TO_DO_LIST);
    if (!file)
    {
        cout << "Failed to save file.\n";
        return;
    }

    for (const auto& t : tasks)
    {
        file << (t.marked ? "1|" : "0|") << t.text << "\n";
    }
}

// ========= FEATURES =========
void ViewTasks()
{
    system("clear");
    cout << "===== TO DO LIST =====\n";

    if (tasks.empty())
    {
        cout << "No To Do List found.\n";
        Pause();
        return;
    }

    for (size_t i = 0; i < tasks.size(); i++)
    {
        cout << i + 1 << ". "
             << (tasks[i].marked ? "[x] " : "[ ] ")
             << tasks[i].text << "\n";
    }

    Pause();
}

void AddTask()
{
    system("clear");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string text;
    cout << "New Task: ";
    getline(cin, text);

    if (text.empty())
    {
        cout << "Task cannot be empty.\n";
        Pause();
        return;
    }

    tasks.push_back({text, false});
    SaveTasks();

    cout << "Task added successfully.\n";
    Pause();
}

void MarkDone()
{
    system("clear");
    ViewTasks();

    if (tasks.empty()) return;

    int index;
    cout << "\nMark task number as done: ";
    cin >> index;

    if (index < 1 || index > (int)tasks.size())
    {
        cout << "Invalid task number.\n";
        Pause();
        return;
    }

    tasks[index - 1].marked = true;
    SaveTasks();

    cout << "Task marked as done.\n";
    Pause();
}

void DeleteTask()
{
    system("clear");
    ViewTasks();

    if (tasks.empty()) return;

    int index;
    cout << "\nDelete task number: ";
    cin >> index;

    if (index < 1 || index > (int)tasks.size())
    {
        cout << "Invalid task number.\n";
        Pause();
        return;
    }

    tasks.erase(tasks.begin() + index - 1);
    SaveTasks();

    cout << "Task deleted.\n";
    Pause();
}

// ========= MAIN =========
int main()
{
    LoadTList();

    bool ExitState = false;

    while (!ExitState)
    {
        system("clear");
        cout << "===== TO DO LIST APP =====\n";
        cout << "1. Add Task\n";
        cout << "2. View Tasks\n";
        cout << "3. Delete Task\n";
        cout << "4. Mark Task as Done\n";
        cout << "5. Exit\n";
        cout << "> ";

        int choice;
        cin >> choice;

        switch (choice)
        {
            case 1: AddTask(); break;
            case 2: ViewTasks(); break;
            case 3: DeleteTask(); break;
            case 4: MarkDone(); break;
            case 5: ExitState = true; break;
            default:
                cout << "Invalid choice.\n";
                Pause();
                break;
        }
    }

    return 0;
}