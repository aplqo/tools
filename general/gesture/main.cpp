/*
Try android gesture
Not tested
problem: sha1
 */
#include "sha1.hpp"
#include <condition_variable>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
using hash::sha1;
using std::cin;
using std::condition_variable;
using std::cout;
using std::endl;
using std::ifstream;
using std::ios;
using std::mutex;
using std::string;
using std::thread;
struct fy
{
    unsigned int start, end;
};
condition_variable con;
mutex out, res;
bool succ = false;
unsigned int end = 0;
char* password = nullptr;
unsigned int length = 0;
string name;
inline void try_once(sha1 b, const unsigned int l, char16_t* d)
{
    sha1 sh;
    bit8* a = reinterpret_cast<bit8*>(d);
    sh.getnum(a, l * 2);
    if (sh == b)
    {
        res.lock();
        succ = true;
        password = new char[l * 2];
        for (auto i = 0u; i <= l * 2; i++)
        {
            password[i] = a[i];
        }
        length = l * 2 + 1;
        res.unlock();
        con.notify_all();
    }
}
inline void ty_r(bool* a, sha1 b, unsigned int c, char16_t* d, const char16_t* str, unsigned long& time)
{
    bit8* e = reinterpret_cast<bit8*>(d);
    {
        d[c] = str[0];
        try_once(b, c + 1, d);
        time++;
    }
    if (c == 8)
    {
        goto last;
    }
    for (auto i = 1u; i < 9; i++)
    {
        d[c] = str[i];
        if (!a[i])
            continue;
        a[i] = false;
        ty_r(a, b, c + 1, d, str, time);
        a[i] = true;
    }
    return;
last:;
    for (auto i = 1u; i < 9; i++)
    {
        d[c] = str[i];
        if (!a[i])
            continue;
        a[i] = false;
        try_once(b, c + 1, d);
        a[i] = true;
        time++;
    }
}
inline void try_fir(bool* a, sha1 b, unsigned int c, char16_t* d, const char16_t* str, unsigned long& time, thread::id e)
{
    if (c == 3)
        goto last;
    for (auto i = 1u; i < 9; i++)
    {
        if (!a[i])
            continue;
        a[i] = false;
        d[c] = str[i];
        try_fir(a, b, c + 1, d, str, time, e);
        a[i] = true;
    }
    return;
last:;
    for (auto i = 1u; i < 9; i++)
    {
        if (!a[i])
            continue;
        a[i] = false;
        d[c] = str[i];
        ty_r(a, b, c + 1, d, str, time);
        a[i] = true;
    }
    out.lock();
    cout << "Thread " << e << " has tried " << time << " times." << endl;
    cout << endl;
    out.unlock();
}
void tr(fy a, sha1 c)
{
    const char str[19] = { "000102030405060708" };
    bool allow[10] = { true, true, true, true, true, true, true, true, true, true };
    unsigned long time = 0;
    const char16_t* one = reinterpret_cast<const char16_t*>(str);
    char16_t temp[10];
    for (auto i = a.start; i < a.end; i++)
    {
        allow[i] = false;
        temp[1] = one[i];
        try_fir(allow, c, 1, temp, one, time, std::this_thread::get_id());
        allow[i] = true;
    }
    res.lock();
    end++;
    res.unlock();
}
int main()
{
    unsigned int thnum;
    thread* thr;
    sha1 ys;
    {
        cout << "Enter the file name" << endl;
        string a;
        cin >> a;
        ifstream f;
        f.open(a, ios::binary | ios::in);
        if (!f.is_open())
        {
            cout << "Can't find file" << endl;
            cout << "Press enter to exit" << endl;
            cin.get();
            exit(0);
        }
        //f.read() not sure
        f.close();
    }
    unsigned int a = thread::hardware_concurrency();
    {
        if (a >= 2)
        {
            thnum = a - 1;
            const unsigned int k = thnum;
            unsigned int* nu = new unsigned int[k];
            fy* f = new fy[k];
            unsigned int pj = 8 / thnum;
            unsigned int dy = 8 % thnum;
            for (auto i = 0u; i < k; i++)
            {
                nu[i] = pj;
            }
            for (auto i = 0u; i < dy; i++)
            {
                nu[i]++;
            }
            f[0].start = 1;
            f[0].end = 1 + nu[0] - 1;
            for (auto i = 1u; i < k; i++)
            {
                f[i].start = f[i - 1].end + 1;
                f[i].end = f[i].start + nu[i] - 1;
            }
            thr = new thread[k];
            for (auto i = 0u; i < k; i++)
            {
                thr[i] = thread::thread(tr, f[i], ys);
            }
            delete[] nu;
            delete[] f;
        }
        else
        {
            thr = nullptr;
        }
    }
    if (a > 2)
    {
        /*while(1)
		{
			con.wait();
			if(succ|(end==thnum))
			{
				break;
			}
		}*/
        //con.wait(res,succ|(end==thnum));
    }
    else
    {
        fy f = { 1, 8 };
        tr(f, ys);
    }
    if (succ)
    {
        cout << endl
             << "the password is:" << password << endl;
    }
    else
    {
        cout << endl
             << "failed" << endl;
    }
    delete[] password;
    cout << "Press enter to exit" << endl;
    cin.get();
    return 1;
}
