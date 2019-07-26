/*
Auto change files' header and footer
std: c++17
 */
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <filesystem>

/*using*/
using std::cin;
using std::cout;
using std::endl;
using std::ios;
using std::ios_base;
using std::locale;
using std::wcout;
using std::wfstream;
using std::wifstream;
using std::wistream;
using std::wofstream;
using std::wostream;
using std::wstring;
using std::filesystem::directory_iterator;
using std::filesystem::path;

struct dat
{
	wstring str = L"";
	dat *last = nullptr, *next = nullptr;
};
class data
{
public:
	data();
	void read(wfstream &file);
	void write(wfstream &file);
	~data();
	dat *now;
	dat *fir;
};
data::data()
{
	now = new dat;
	fir = now;
	now->last = nullptr;
	now->next = nullptr;
}
void data::read(wfstream &file)
{
	while (!file.eof())
	{
		now->next = new dat{L"", now, nullptr};
		now = now->next;
		std::getline(file, now->str);
	}
}
void data::write(wfstream &file)
{
	dat *p = fir;
	while (p != nullptr)
	{
		file << (p->str) << endl;
		p = p->next;
	}
}
data::~data()
{
	while (now->last != nullptr)
	{
		now = now->last;
		delete now->next;
	}
}

/*locale*/
locale utf("en_US.UTF-8");
/*data*/
wstring *beg_dat = nullptr;
wstring *end_dat = nullptr;
unsigned int len[2] = {0, 0};
/*setting*/
wstring flag;
bool again = false;
bool select = false; //false:exclude,true:include
path *file = nullptr;
wstring location;
unsigned int l = 0;

inline void out(unsigned int id, path file, const wchar_t *stat, const wchar_t *message);
inline void read()
{
	wifstream f;
	f.imbue(utf);
	wstring tmp = L"";
	f.open("file.txt", ios::in);
	if (!f.is_open())
	{
		cout << "failed to open file file.txt" << endl;
		cout << "Press enter to exit" << endl;
		cin.get();
		exit(1);
	}
	for (unsigned int i = 0; i < 7; i++)
	{
		f >> tmp;
		if (tmp == L"flag:")
		{
			f.get();
			getline(f, flag);
			continue;
		}
		if (tmp == L"again:")
		{
			f.setf(ios::boolalpha);
			f >> again;
			f.unsetf(ios::boolalpha);
			continue;
		}
		if (tmp == L"select:")
		{
			f.setf(ios::boolalpha);
			f >> select;
			f.unsetf(ios::boolalpha);
			continue;
		}
		if (tmp == L"file:")
		{
			f >> l;
			f.get();
			const unsigned int t = l;
			wstring str;
			file = new path[t];
			for (unsigned int j = 0; j < l; j++)
			{
				std::getline(f, str);
				file[j] = str.c_str();
			}
			continue;
		}
		if (tmp == L"begin:")
		{
			f >> len[0];
			f.get();
			const unsigned int t = len[0];
			beg_dat = new wstring[t];
			for (unsigned int j = 0; j < len[0]; j++)
			{
				std::getline(f, beg_dat[j]);
			}
			continue;
		}
		if (tmp == L"end:")
		{
			f >> len[1];
			f.get();
			const unsigned int t = len[1];
			end_dat = new wstring[t];
			for (unsigned int j = 0; j < len[1]; j++)
			{
				std::getline(f, end_dat[j]);
			}
			continue;
		}
		if (tmp == L"location:")
		{
			f.get();
			std::getline(f, location);
			continue;
		}
	}
	f.close();
}
void change(path target, unsigned int id)
{
	wfstream f;
	data raw;
	f.imbue(utf);
	f.open(target.wstring());
	if (!f.is_open())
	{
		out(id, target, L"Fail", L"can't open file");
		return;
	}
	{
		f.seekp(0, ios_base::beg);
		wstring fla;
		std::getline(f, fla);
		if ((fla == flag) && (!again))
		{
			out(id, target, L"Skip", L"Added");
			return;
		}
	}
	f.seekg(0, ios::beg);
	raw.read(f);
	f.close();
	f.open(target.wstring(), ios::out);
	f.seekp(0, ios::beg);
	f.imbue(utf);
	f << flag << endl;
	f << L"#begin_add_begin" << endl;
	for (unsigned int i = 0; i < len[0]; i++)
	{
		f << beg_dat[i] << endl;
	}
	raw.write(f);
	f.seekp(0, ios_base::end);
	f << L"#end_add_begin" << endl;
	for (unsigned int i = 0; i < len[1]; i++)
	{
		f << end_dat[i] << endl;
	}
	f.close();
	out(id, target, L"Ok", L"");
}
inline void out(unsigned int id, path file, const wchar_t *stat, const wchar_t *message)
{
	wcout.width(3);
	wcout << id;
	wcout.width(20);
	wcout << file.filename().c_str();
	wcout.width(7);
	wcout << stat;
	wcout.width(20);
	wcout << message << endl;
}
inline bool check(path p, unsigned int id)
{
	if (file == nullptr)
	{
		return true;
	}
	for (unsigned int i = 0; i < l; i++)
	{
		if (p == file[i])
		{
			out(id, p, L"Skip", L"Selected to skip");
			return false;
		}
	}
	return true;
}
int main()
{
	wcout.imbue(utf);
	read();
	if ((len[0] == 0) & (len[1] == 0))
	{
		cout << "Not set insert string" << endl;
		cout << "Press Enter to exit" << endl;
		cin.get();
		return 1;
	}
	wcout << "Path:" << location << endl
		  << endl;
	wcout.width(3);
	wcout << L"Id";
	wcout.width(20);
	wcout << L"File";
	wcout.width(7);
	wcout << L"State";
	wcout.width(20);
	wcout << L"Message" << endl;
	wcout << L"-------------------------------------------------" << endl;
	if (select)
	{
		for (unsigned int i = 0; i < l; i++)
		{
			change(file[i], i);
		}
	}
	else
	{
		path target;
		directory_iterator dir(location);
		unsigned int id = 1;
		for (auto &t : dir)
		{
			target = t.path();
			if (!t.is_regular_file())
			{
				out(id, target, L"Fail", L"Not a regular file");
				id++;
				continue;
			}
			if (check(target, id))
			{
				change(target, id);
			}
			id++;
		}
	}
	cout << endl;
	cout << "Press Enter to exit" << endl;
	cin.get();
	return 0;
}
