typedef unsigned char bit8;
typedef unsigned long bit32;
typedef unsigned long long bit64;
#define S(x, n) (x << n) | (x >> (32 - n))
/*-----class-----*/
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
/*-----function-----*/
sha1::sha1()
{
    num[0] = 0x67452301;
    num[1] = 0xEFCDAB89;
    num[2] = 0x98BADCFE;
    num[3] = 0x10325476;
    num[4] = 0xC3D2E1F0;
}
bool sha1::operator==(const sha1& a)
{
    for (unsigned short i = 0; i < 5; i++)
    {
        if ((this->num[i]) != (a.num[i]))
        {
            return false;
        }
    }
    return true;
}
bit32 sha1::f(const bit32& b, const bit32& c, const bit32& d, unsigned int n)
{
    switch (n / 20)
    {
    case 0:
        return (b & c) | ((!b) & d);
    case 1:
    case 3:
        return b ^ c ^ d;
    case 2:
        return (b & c) | (b & d) | (c & d);
    default:
        throw 0;
    }
}
void sha1::getnum(bit8* a, bit64 length)
{
    bit64 l = 0, m_l = 0;
    bit32* n;
    bit32** m;
    //step1,2:
    {
        bit64 bit = 8 * length;
        unsigned int y = bit % 512;
        l = bit + 1;
        if (y != 448)
        {
            if (y > 448)
            {
                l = (l / 512 + 1) * 512 + 448;
            }
            else
            {
                l = 448 - y + l;
            }
        }
        if (l > 512)
        {
            if (l % 512 != 0)
            {
                l = l + (512 - l % 512);
            }
        }
        const bit64 ls = l;
        n = new bit32[ls + 2];
        bit8* n8 = reinterpret_cast<bit8*>(n);
        for (auto i = (bit64)0; i < length; i++)
        {
            n8[i] = a[i];
        }
        n[length + 1] = (n[length + 1]) | ((bit32)0x00000001 << 31);
        for (auto i = length + 1; i < l; i++)
        {
            n[i] = 0x00000000;
        }
        bit64* b = reinterpret_cast<bit64*>(n);
        *(b - 1) = bit;
    }
    {
        const bit64 ls = l / 16;
        if (l % 16 != 0)
        {
            m = new bit32*[ls + 1];
            m_l = ls + 1;
        }
        else
        {
            m = new bit32*[ls];
            m_l = ls;
        }
        m[0] = n;
        for (unsigned int i = 1; i < m_l; i++)
        {
            m[i] = m[i - 1] + 16;
        }
    }
    //step3:
    {
        bit32 temp;
        bit32 w[80];
        bit32 A[5];
        for (auto i = 0ull; i < m_l; i++)
        {
            bit32* block = m[i];
            for (auto t = 0u; t < 16; t++)
            {
                w[t] = block[t];
            }
            for (auto t = 16u; t < 80; t++)
            {
                w[t] = S(w[t - 3] ^ w[t - 8] ^ w[t - 14] ^ w[t - 16], 1);
            }
            for (auto t = 0u; t < 5; t++)
            {
                A[t] = num[t];
            }
            for (auto t = 0u; t < 80; t++)
            {
                temp = S(A[0], 5) + f(A[1], A[2], A[3], t) + A[4] + w[t] + k[t];
                A[4] = A[3];
                A[3] = A[2];
                A[2] = S(A[1], 30);
                A[1] = A[0];
                A[0] = temp;
            }
            for (auto t = 0u; t < 5; t++)
            {
                num[t] = num[t] + A[t];
            }
        }
    }
    delete[] n;
    delete[] m;
}
