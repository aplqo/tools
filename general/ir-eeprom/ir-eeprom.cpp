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
using std::string;
using std::stoi;

namespace ir_eeprom
{
    uint16_t eeprom;
    void convert(const ptree& p, ofstream& of)
    {
        auto pos = of.tellp();
        of.seekp(of.beg, 0);
        of << static_cast<uint16_t>(eeprom + pos);
        of.seekp(pos);
        ptree rules = p.get_child("config.convert");
        for (auto i : rules)
        {
            auto& rule = i.second;
            of << 0xee << 2;
            string type = rule.get<string>("frame.type");
            if (type == "NEC")
            {
                of << 0x00;
            }
            else if (type == "SIRC")
            {
                of << 0x01;
            }
            of << rule.get<uint8_t>("frame.user");
            of << rule.get<uint8_t>("frame.key");
            of << rule.get<uint8_t>("frame.result");
        }
    }
    void filter(const ptree& p, ofstream& of)
    {
        auto pos = of.tellp();
        of.seekp(of.beg, 2);
        of << static_cast<uint16_t>(eeprom + pos);
        of.seekp(pos);
        ptree rules = p.get_child("config.filter");
        for (auto i : rules)
        {
            auto& rule = i.second;
            uint8_t size = 0;
            auto pSize = of.tellp().operator+(1);
            of << 0xff << 0;
            string type = rule.get<string>("rule.type");
            if (type == "NEC")
            {
                of << 0x00;
            }
            else if (type == "SIRC")
            {
                of << 0x01;
            }
            of << 0x00;
            ptree users = rule.get_child("rule.users");
            for (auto i : users)
            {
                size++;
                of << i.second.get_value<uint8_t>();
            }
            of.seekp(pSize);
            of << size;
            of.seekp(of.end);
        }
    }
    void repeat(const ptree& p, ofstream& of)
    {
        of.seekp(of.beg, 4);
        auto rules = p.get_child("config.repeat");
        for (auto i : rules)
        {
            auto rule = i.second;
            uint8_t size = 0;
            of << 0xcc;
            auto pos = of.tellp();
            of << 0 << 0x01;
            of << rule.get<uint8_t>("frame.user");
            of << rule.get<uint8_t>("frame.repeat");
            ptree keys = rule.get_child("frame.keys");
            for (auto j : keys)
            {
                size++;
                of << j.second.get<uint8_t>("keys.key");
            }
            of.seekp(pos);
            of << size;
            of.seekp(of.end);
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

	ire::eeprom = stoi(argv[2],nullptr, 16);

    ofstream of(argv[3], ios::out | ios::binary);
    ire::convert(p, of);
    ire::filter(p, of);
    ire::repeat(p, of);
    of.flush();
    of.close();

    return 0;
}