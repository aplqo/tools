/*
ir-eeprom
Version: v1.0.1
*/
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <fstream>
#include <iostream>
#include <string>

namespace bt = boost::property_tree;
using bt::ptree;
using bt::xml_parser::read_xml;
using std::cout;
using std::endl;
using std::ios;
using std::ofstream;
using std::stoi;
using std::string;

namespace ir_eeprom
{
    uint16_t eeprom;
    enum type
    {
        NEC = 0,
        SIRC = 1
    };
    static uint8_t get(const ptree& p, const char* path)
    {
        string&& s = p.get<string>(path);
        return stoi(s, nullptr, 16);
    }
    void convert(const ptree& p, ofstream& of)
    {
        {
            uint16_t pos = of.tellp();
            uint16_t e_pos = pos + eeprom;
            e_pos = (e_pos >> 8) | (e_pos << 8);
            of.seekp(0, of.beg);
            of.write(reinterpret_cast<const char*>(&e_pos), 2);
            of.seekp(pos, of.beg);
        }
        ptree rules = p.get_child("config.convert");
        for (auto i : rules)
        {
            ptree group = i.second;
            uint8_t user = get(group, "user");
            uint8_t type;
            {
                string typ = group.get<string>("type");
                if (typ == "NEC")
                {
                    type = NEC;
                }
                else if (typ == "SIRC")
                {
                    type = SIRC;
                }
            }
            for (auto j : group.get_child("rules"))
            {
                of.put(0xee);
                of.put(2);
                of.put(type);
                of.put(user);
                auto& rule = j.second;
                of.put(get(rule, "key"));
                of.put(get(rule, "result"));
            }
        }
    }
    void filter(const ptree& p, ofstream& of)
    {
        {
            uint16_t pos = of.tellp();
            uint16_t e_pos = pos + eeprom;
            e_pos = (e_pos >> 8) | (e_pos << 8);
            of.seekp(2, of.beg);
            of.write(reinterpret_cast<const char*>(&e_pos), 2);
            of.seekp(pos, of.beg);
        }
        ptree rules = p.get_child("config.filter");
        for (auto i : rules)
        {
            auto& rule = i.second;
            uint8_t size = 0;
            auto pSize = of.tellp().operator+(1);
            of.put(0xff);
            of.put(0);
            string type = rule.get<string>("type");
            if (type == "NEC")
            {
                of.put(NEC);
            }
            else if (type == "SIRC")
            {
                of.put(SIRC);
            }
            of.put(0x00);
            ptree users = rule.get_child("users");
            for (auto i : users)
            {
                size++;
                of.put(stoi(i.second.get_value<string>(), nullptr, 16));
            }
            of.seekp(pSize);
            of.put(size);
            of.seekp(0, of.end);
        }
    }
    void repeat(const ptree& p, ofstream& of)
    {
        auto rules = p.get_child("config.repeat");
        for (auto i : rules)
        {
            auto rule = i.second;
            uint8_t size = 1;
            of.put(0xcc);
            auto pos = of.tellp();
            of.put(0);
            of.put(0x01);
            of.put(get(rule, "user"));
            of.put(get(rule, "repeat"));
            ptree keys = rule.get_child("keys");
            for (auto j : keys)
            {
                size++;
                of.put(stoi(j.second.get_value<string>(), nullptr, 16));
            }
            of.seekp(pos);
            of.put(size);
            of.seekp(0, of.end);
        }
    }
}
namespace ire = ir_eeprom;

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        cout << "Too few arguments" << endl;
        return -1;
    }
    ptree p;
    read_xml(argv[1], p);

    ire::eeprom = stoi(argv[2], nullptr, 16);

    ofstream of(argv[3], ios::out | ios::binary);
    of.seekp(0x04);
    ire::repeat(p, of);
    ire::filter(p, of);
    ire::convert(p, of);
    of.flush();
    of.close();

    return 0;
}