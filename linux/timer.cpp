/*
Count down timer
os: linux
compile: -pthread
 */
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <mutex>
#include <stdlib.h>
#include <thread>
#include <unistd.h>
/*----------using----------*/
//-----input and output
using std::cerr;
using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::ios;
//-----thread
using std::mutex;
using std::thread;
//-----time
using std::chrono::duration;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::steady_clock;
using std::chrono::time_point;
/*----------variables----------*/
fstream file;
mutex m;
steady_clock::duration need, use;
steady_clock::time_point start, last;
bool run = false, clear = false;
/*----------funcations----------*/
inline void out(const steady_clock::duration& a)
{
    seconds b = duration_cast<seconds>(a);
    time_t tmp = static_cast<time_t>(b.count());
    tm* l = gmtime(&tmp);
    cerr << "\033[K";
    cout << l->tm_mon << " " << l->tm_mday - 1 << " " << l->tm_hour << ":" << l->tm_min << ":" << l->tm_sec << endl;
}
void info(bool first)
{
    if (!m.try_lock())
        return;
    if (!first)
    {
        if (clear | run)
        {
            if (!run)
            {
                clear = false;
                cerr << "\033[1A\033[K";
                cerr << "\033[1A\033[K";
            }
            else
            {
                cerr << "\033[1A";
            }
        }
        cerr << "\033[4A";
    }
    cout.setf(ios::boolalpha);
    cout << "\033[Krun:" << run;
    cout.unsetf(ios::boolalpha);
    cout << endl;
    if (run)
    {
        steady_clock::time_point n = steady_clock::now();
        steady_clock::duration s = n - last;
        need -= s;
        use += s;
        cout << "\033[Kthis:";
        out(n - start);
        last = n;
    }
    cout << "\033[Kneed:";
    out(need);
    cout << "\033[Kuse:";
    out(use);
    steady_clock::duration all = use + need;
    cout << "\033[Kprocess:" << static_cast<double>(use.count()) / static_cast<double>(all.count()) * 100.0 << "%" << endl;
    m.unlock();
}
void* get(void*)
{
    char input = 0;
    while (1)
    {
        if (!m.try_lock())
        {
            continue;
        }
        else
        {
            m.unlock();
        }
        cin.clear();
        cin >> input;
        m.lock();
        switch (input)
        {
        case 'q':
            if (run)
            {
                cout << "\033[Kclock is running,stop it first" << endl;
                cerr << "\033[2A";
            }
            else
            {
                cerr << "\033[2B";
                exit(0);
            }
            break;
        case 's':
            if (!run)
            {
                cout << "\033[Kclock started" << endl;
                cerr << "\033[1A";
                run = true;
                clear = true;
                start = steady_clock::now();
                last = steady_clock::now();
            }
            else
            {
                cout << "\033[Kclock is running" << endl;
                cerr << "\033[2A";
            }
            break;
        case 'p':
            if (run)
            {
                steady_clock::time_point n = steady_clock::now();
                steady_clock::duration th;
                th = n - last;
                need = need - th;
                use = use + th;
                run = false;
                cout << "\033[Kclock stopped" << endl;
                file.open("time", ios::out);
                file << need.count();
                file << " ";
                file << use.count();
                file.close();
                cerr << "\033[1A";
            }
            else
            {
                cout << "\033[Kclock isn't running";
                cerr << "\033[1A";
            }
            break;
        case 0:
            break;
        default:
            cout << "\033[Kinput error" << endl;
            cerr << "\033[2A";
            break;
        }
        input = 0;
        m.unlock();
        info(false);
    }
    return nullptr;
}
int main()
{
    file.open("time", ios::in);
    if (!file.is_open())
    {
        cout << "can't open file" << endl;
        return 0;
    }
    {
        int64_t temp;
        file >> temp;
        need = steady_clock::duration(temp);
        file >> temp;
        use = steady_clock::duration(temp);
    }
    file.close();
    info(true);
    thread i(get, nullptr);
    while (1)
    {
        info(false);
        sleep(1);
    }
    return 0;
}
