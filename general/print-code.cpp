#include <filesystem>
#include <fstream>
#include <iostream>
#include <list>
#include <map>
#include <string>

using std::cout;
using std::endl;
using std::list;
using std::map;
using std::ofstream;
using std::string;
namespace fs = std::filesystem;
using fs::directory_iterator;
using fs::exists;
using fs::is_directory;
using fs::is_regular_file;
using fs::path;

const map<const path, const char*> filetype {
    { ".c", "c" }, { ".cpp", "c++" }, { ".js", "javascript" }, { ".html", "html" },
    { ".kt", "kotlin" }, { ".cs", "csharp" }, { ".hs", "haskell" }, { ".java", "java" },
    { ".go", "go" }, { ".lua", "lua" }, { ".h", "cpp" }
};

class Node
{
public:
    Node(const path& p, unsigned int sec)
        : p { p }
        , sec { sec } {};
    virtual void Write(ofstream& of);
    virtual bool isEmpty() = 0;
    virtual ~Node() {};

protected:
    void print_sec(ofstream& of, string::size_type l);
    const path p;
    const unsigned int sec;

    const static unsigned char section[5];
};
const unsigned char Node::section[5] = { '*', '=', '-', '^', '"' };
void Node::Write(ofstream& of)
{
    const string s = p.filename();
    string::size_type size = s.length();
    print_sec(of, size);
    of << s << endl;
    print_sec(of, size);
    of << endl;
}
void Node::print_sec(ofstream& of, string::size_type l)
{
    for (string::size_type i = 0; i < l; i++)
    {
        of << section[sec];
    }
    of << endl;
}

class File : public Node
{
public:
    File(const path& p, unsigned int sec)
        : Node(p, sec) {};
    void Write(ofstream& of);
    bool isEmpty() { return false; };
};
void File::Write(ofstream& of)
{
    const char* lang = filetype.at(p.extension());
    this->Node::Write(of);
    of << endl;
    of << ".. literalinclude:: " << p.c_str() << endl;
    of << "\t"
       << ":language: " << lang << endl;
    of << "\t"
       << ":linenos:" << endl;
    of << endl;
}

class Directory : public Node
{
public:
    Directory(const path& p)
        : Node(p, 0)
        , root { &(this->p) } {};
    Directory(const path& p, unsigned int sec)
        : Node(p, sec) {};
    void Read();
    void Write(ofstream& of);
    bool isEmpty();
    ~Directory();

private:
    list<Node*> child;
    const path* root;
};
void Directory::Read()
{
    directory_iterator it(p);
    for (auto& i : it)
    {
        if (i.is_regular_file())
        {
            const path tmp = i.path();
            {
                if (filetype.find(tmp.extension()) == filetype.end())
                    continue;
            }
            File* f = new File(tmp, (sec + 1));
            child.push_back(f);
            continue;
        }
        if (i.is_directory())
        {
            Directory* d = new Directory(i, (sec + 1));
            d->Read();
            if (!d->isEmpty())
            {
                child.push_back(d);
            }
            else
            {
                delete d;
            }
            continue;
        }
    }
}
void Directory::Write(ofstream& of)
{
    this->Node::Write(of);
    for (auto i : child)
    {
        i->Write(of);
    }
}
bool Directory::isEmpty()
{
    if (child.empty())
        return true;
    bool result = true;
    for (auto i : child)
    {
        result &= i->isEmpty();
    }
    return result;
}
Directory::~Directory()
{
    if (child.empty())
        return;
    for (auto i : child)
    {
        delete i;
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cout << "Too few arguments." << endl;
        return 1;
    }
    const path p(argv[1]);
    if (!exists(p) && is_directory(p))
    {
        cout << "Wrong directory" << endl;
        return -1;
    }

    Directory d(p);
    d.Read();
    if (d.isEmpty())
    {
        cout << "Empty directory" << endl;
        return -1;
    }

    {
        ofstream o(argv[2]);
        d.Write(o);
        o.close();
    }
    return 0;
}
