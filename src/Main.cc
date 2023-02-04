#include <iostream>
#include <fstream>
#include <list>
using namespace std;
class Task {
    public:
        string name;
        list<string> doOnExec;
};
bool StartsWith(string a, string b) {
    bool res = true;
    if (a.size() < b.size()) return false;
    for (size_t i = 0; i < b.size(); i++) if (a[i] != b[i]) return false; 
    return res;
}
string StringFromStringButSkipCharsWithIDs(string in, list<size_t> ids) {
    string out;
    for (size_t id : ids) if (id >= in.size()) return "";
    for (size_t i = 0; i < in.size(); i++) for (size_t id : ids) if (id != i) out += in[i]; 
    return out;
}
list<Task> ParseTasks(string content) {
    list<Task> tasks;
    bool stop = false;
    for (size_t i = 0; i < content.size(); i++) {
        if (stop) break;
        if (content[i] == ':') {
            string taskName;
            i++; while (content[i] != '~') { taskName += content[i]; i++; } i++;
            Task task; task.name = taskName;
            list<string> doOnExec; string cache;
            while (content[i] != '}') { if (content[i] == '|') { doOnExec.push_back(cache); cache.clear(); i++; continue; } cache += content[i]; i++; }
            task.doOnExec = doOnExec;
            tasks.push_back(task);
        }
    }
    return tasks;
}
void ExecTask(list<Task> tasks, string name) {
    for (Task task : tasks) {
        if (task.name == name) {
            for (string fn : task.doOnExec) {
                if (StartsWith(fn, "task:")) ExecTask(tasks, StringFromStringButSkipCharsWithIDs(fn, { 0, 1, 2, 3, 4 }));
                else {
                    int res = system(fn.c_str());
                    if (res != 0) { cout << "Function \"" << fn << "\" finished with code " << res << "!" << endl; exit(res); }
                }
            }
        }
    }
}
int main(int argc, char **argv) {
    string arg = "help";
    if (argc > 1) arg = argv[1];
    if (arg == "version" || arg == "v") cout << "RecipeManager version: v1.0-fOS" << endl;
    else if (arg == "run" || arg == "r") {
        ifstream f ("./Recipe");
        bool exists = f.good();
        if (!exists) cout << "No recipe file found in your directory!" << endl;
        else {
            string content; while (f) content += f.get();
            list<Task> tasks = ParseTasks(content);
            ExecTask(tasks, "run");
        }
        f.close();
    } else if (arg == "build" || arg == "b") {
        ifstream f ("./Recipe");
        bool exists = f.good();
        if (!exists) cout << "No recipe file found in your directory!" << endl;
        else {
            string content; while (f) content += f.get();
            list<Task> tasks = ParseTasks(content);
            ExecTask(tasks, "build");
        }
        f.close();
    } else if (arg == "test" || arg == "t") {
        ifstream f ("./Recipe");
        bool exists = f.good();
        if (!exists) cout << "No recipe file found in your directory!" << endl;
        else {
            string content; while (f) content += f.get();
            list<Task> tasks = ParseTasks(content);
            ExecTask(tasks, "test");
        }
        f.close();
    } else if (arg == "tasks" || arg == "ts") {
        ifstream f ("./Recipe");
        bool exists = f.good();
        if (!exists) cout << "No recipe file found in your directory!" << endl;
        else {
            string content; while (f) content += f.get();
            list<Task> tasks = ParseTasks(content);
            for (Task task : tasks) {
                cout << task.name << endl;
                for (string doOn : task.doOnExec) cout << "  " << doOn << endl;
            }
        }
        f.close();
    } else if (arg == "help" || arg == "h") {
        cout << "Usage:" << endl << endl;
        cout << "     help, h                  Print help" << endl;
        cout << "     version, v               Print version" << endl;
        cout << "     run, r                   Run recipe" << endl;
        cout << "     build, b                 Build with recipe" << endl;
        cout << "     test, t                  Test with recipe" << endl;
        cout << "     tasks, ts                View tasks from recipe" << endl;
        cout << "     <task name>              Run <task name> from recipe" << endl;
    } else {
        ifstream f ("./Recipe");
        bool exists = f.good();
        if (!exists) cout << "No recipe file found in your directory!" << endl;
        else {
            string content; while (f) content += f.get();
            list<Task> tasks = ParseTasks(content);
            ExecTask(tasks, arg);
        }
        f.close();
    }
    return 0;
}
