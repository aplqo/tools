/*
Sync file between phone and computer
os: windows
 */
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
const string push = "adb push ";
const string pull = "adb pull ";
string temp;
string* path1;
string* path2;
bool clear = true, fs = true, root = false, kill = true;
//fs=true phone->computer
bool del = true;
string ip, port = "";
unsigned int n = 0;
int main()
{
    //read from file
    {
        ifstream file;
        file.open("filepath.txt", ios::in);
        if (!file.is_open())
        {
            cout << "Can't find filepath.txt" << endl;
            cout << "Press enter to exit" << endl;
            cin.get();
            exit(0);
        }
        string a;
        for (unsigned int i = 0; i < 10; i++)
        {
            file >> a;
            if (a == "ip:")
            {
                file >> ip;
                continue;
            }
            if (a == "port:")
            {
                file >> port;
                continue;
            }
            if (a == "clear:")
            {
                file.setf(ios_base::boolalpha);
                file >> clear;
                file.unsetf(ios_base::boolalpha);
                continue;
            }
            if (a == "kill:")
            {
                file.setf(ios_base::boolalpha);
                file >> kill;
                file.unsetf(ios_base::boolalpha);
                continue;
            }
            if (a == "root:")
            {
                file.setf(ios_base::boolalpha);
                file >> root;
                file.unsetf(ios_base::boolalpha);
                continue;
            }
            if (a == "del:")
            {
                file.setf(ios_base::boolalpha);
                file >> del;
                file.unsetf(ios_base::boolalpha);
                continue;
            }
            if (a == "fs:")
            {
                file.setf(ios_base::boolalpha);
                file >> fs;
                file.unsetf(ios_base::boolalpha);
                continue;
            }
            if (a == "num:")
            {
                file >> n;
                const unsigned int b = n;
                path1 = new string[b];
                path2 = new string[b];
                continue;
            }
            if (a == "input:")
            {
                if (n != 0)
                {
                    for (unsigned int j = 0; j < n; j++)
                    {
                        file >> path1[j];
                    }
                }
                else
                {
                    cout << "File error:" << a << endl;
                    cout << "Press enter to exit" << endl;
                    cin.get();
                }
                continue;
            }
            if (a == "output:")
            {
                if (n != 0)
                {
                    for (unsigned int j = 0; j < n; j++)
                    {
                        file >> path2[j];
                    }
                }
                else
                {
                    cout << "File error:" << a << endl;
                    cout << "Press enter to exit" << endl;
                    cin.get();
                }
            }
            continue;
        }
        file.close();
    }
    system("adb start-server");
    //connect
    cout << "adb connect" << endl;
    temp = "adb connect " + ip;
    if (port != "")
    {
        temp = temp + " :" + port;
    }
    system(temp.c_str());
    system("adb wait-for-device");
    system("adb devices");
    //root
    if (root)
    {
        cout << "adb root" << endl;
        system("adb root");
    }
    //push/pull
    cout << "adb push /pull" << endl;
    {
        string fir, sec;
        if (fs)
        {
            fir = pull;
            sec = push;
        }
        else
        {
            fir = push;
            sec = pull;
        }
        for (unsigned int i = 0; i < n; i++)
        {
            temp = fir + path1[i] + " " + path2[i];
            system(temp.c_str());
        }
        cout << "Press enter to sync" << endl;
        cin.get();
        for (unsigned int i = 0; i < n; i++)
        {
            temp = sec + path2[i] + " " + path1[i];
            system(temp.c_str());
        }
    }
    if (!del)
        goto no;
    //delete
    if (fs)
    {
        cout << "del" << endl;
        for (unsigned int i = 0; i < n; i++)
        {
            temp = "del " + path2[i];
            system(temp.c_str());
        }
    }
    else
    {
        cout << "adb command rm" << endl;
        for (unsigned int i = 0; i < n; i++)
        {
            temp = "adb command rm " + path2[i];
            system(temp.c_str());
        }
    }
no:;
    //kill-server
    if (kill)
    {
        cout << "adb kill-server" << endl;
        system("adb kill-server");
    }
    //clear the file
    if (clear)
    {
        ofstream file;
        file.open("filepath.txt", ios::out);
        file << "ip: " << endl;
        file << "port: " << endl;
        file << "fs: " << endl;
        file << "root: " << endl;
        file << "num: " << endl;
        file << "input: " << endl;
        file << "output: " << endl;
        file << "del: " << endl;
        file << "kill: " << endl;
        file << "clear: " << endl;
        file << "Remember: 'num' must be in front of 'input' and 'output'" << endl;
        file.close();
    }
    cout << "Press enter to exit" << endl;
    cin.get();
    delete[] path1;
    delete[] path2;
    return 0;
}
