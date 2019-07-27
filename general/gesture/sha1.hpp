#ifndef SHA1_HPP
#define SHA1_HPP
typedef unsigned char bit8;
typedef unsigned long bit32;
typedef unsigned long long bit64;
namespace hash
{
    class sha1
    {
    public:
        sha1();
        bool operator==(const sha1& a);
        void getnum(bit8* a, bit64 length);
        bit32 num[5];

    private:
        const bit32 k[4] = { 0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6 };
        bit32 f(const bit32& b, const bit32& c, const bit32& d, unsigned int e);
    };
}
#endif
