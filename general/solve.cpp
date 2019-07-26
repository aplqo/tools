/*
Solve 
Not tested
 */
#include <iostream>
using namespace std;
char gtm[] = {"ABCDEFGHI"};
/*----------类和结构体----------*/
class ys;
class gt;
class qk;
struct g_mval
{
	unsigned int gm_x, gm_y;
	unsigned int qns;
	unsigned int *val;
	bool er, suc;
};
class ys
{
public:
	ys();
	ys(ys &a);
	void jbpc(); //基本排除
	//-------加入其他排除函数
	bool refesh(); //刷新表格
	void refresh_tm();
	bool check(g_mval &c); //检查错误
	void pr();
	bool err, succ;
	bool base;
	~ys();
	bool *knz;		   //每格的可能值
	unsigned int *tm;  //题目
	unsigned int *gks; //各格可能值数量
	unsigned char num; //未知值数量
};
class qk : public ys
{
public:
	qk(ys &a, unsigned int x, unsigned int y, unsigned int z, gt *yq);
	~qk();

private:
	gt *sc; //
	unsigned int g;
};
class gt
{
public:
	gt(g_mval a, ys *b, qk *c, bool se);
	void pd();
	~gt();
	g_mval va;
	unsigned int su_val;
	ys *y_ys;
	qk *y_qk;
	bool select;
};
/*-----成员函数-----*/
/*---ys类---*/
ys::ys()
{
	unsigned char i, j, h;
	knz = new bool[9][9][9];
	tm = new unsigned int[9][9];
	gks = new unsigned int[9][9];
	for (i = 0; i < 9; i++) //初始化可能值为true
	{
		for (j = 0; j < 9; j++)
		{
			for (h = 0; h < 9; h++)
			{
				knz[i][j][h] = true;
			}
		}
	}
	for (i = 0; i < 9; i++) //初始化可能值数
	{
		for (j = 0; j < 9; j++)
		{
			gks[i][j] = 9;
		}
	}
	cout << "输入题目" << endl;
	for (i = 0; i < 9; i++)
	{
		cout << gtm[i] << "=";
		cin >> tm[i][0] >> tm[i][1] >> tm[i][2] >> tm[i][3] >> tm[i][4] >> tm[i][5] >> tm[i][6] >> tm[i][7] >> tm[i][8];
	}
	base = true;
}
ys::ys(ys &a)
{
	unsigned char xa, ya, za;
	this->knz = new bool[9][9][9];
	this->tm = new unsigned int[9][9];
	this->gks = new unsigned int[9][9];
	for (xa = 0; xa < 9; xa++)
	{
		for (ya = 0; ya < 9; ya++)
		{
			this->tm[xa][ya] = a.tm[xa][ya];
			this->gks[xa][ya] = a.gks[xa][ya];
			for (za = 0; za < 9; za++)
			{
				this->knz[xa][ya][za] = a.knz[xa][ya][za];
			}
		}
	}
	this->num = a.num;
	this->base = false;
}
ys::refresh()
{
	unsigned char a, b, c;
	for (a = 0; a < 9; a++)
	{
		for (b = 0; b < 9; b++)
		{
			if (*gks[a][b] == 1)
			{
				continue;
			}
			*gks[a][b] = 9;
			for (c = 0; c < 9; c++)
			{
				if (!*knz[a][b][c])
				{
					*gks[a][b]--;
				}
			}
		}
	}
	num = 81;
	for (a = 0; a < 9; a++)
	{
		for (b = 0; b < 9; b++)
		{
			switch (*gks[a][b])
			{
			case 0:
				err = true;
				goto e;
			case 1:
				num--;
				break;
			}
		}
	}
e:;
	return err | succ;
}
ys::refresh_tm()
{
	unsigned int x, y, z;
	if (err | succ)
	{
		return;
	}
	for (x = 0; x < 9; x++)
	{
		for (y = 0; y < 9; y++)
		{
			if (gks[x][y] != 1)
			{
				continue;
			}
			for (z = 0; z < 9; z++)
			{
				if (knz[x][y][z])
				{
					tm[x][y] = z;
					break;
				}
			}
		}
	}
}
ys::check(g_mval &c)
{
	unsigned int a, b, d;
	unsigned int lx, ly, lk = 9;
	for (a = 0; a < 9; a++)
	{
		for (b = 0; b < 9; b++)
		{
			if (*kns[a][b] == 0)
			{
				this->err = true;
				c.er = true;
				return this->err | this->succ;
			}
			if (*kns[a][b] < lk)
			{
				lx = a;
				ly = b;
				lk = *kns[a][b];
			}
		}
	}
	if (num == 0)
	{
		c.suc = true;
		c.a = NULL;
		return this->err | this->succ;
	}
	c.x = lx;
	c.y = ly;
	c.qns = lk;
	c.er = false;
	c.a = new unsigned int[lk];
	for (d = 0; d < 9; d++)
	{
		if (knz[lx][ly][d])
		{
			*(c.a[d]) = d;
		}
	}
	return this->err | this->succ;
}
ys::jbpc()
{
	unsigned int a, b, d;
	unsigned int gx, gy, lz, lx, ly;
	for (a = 0; a < 9; a++)
	{
		for (b = 0; b < 9; b++)
		{
			switch (*gks[a][b])
			{
			case 0:
				err = true;
				return;
			case 1:
				break;
			default:
				continue;
			}
			lz = *tm[a][b];
			lx = a / 3 * 3;
			ly = b / 3 * 3;
			gx = lx + 3;
			gy = ly + 3;
			for (d = 0; d < 9; d++)
			{
				if (*kns[a][d][lz])
				{
					*kns[a][d][lz] = false;
					*gks[a][d]--;
				}
				if (*kns[d][b][lz])
				{
					*kns[d][b][lz] = false;
					*gks[d][b]--;
				}
				for (; lx < gx; lx++)
				{
					for (; ly < gy; ly++)
					{
						if (*kns[lx][ly][lz])
						{
							*kns[lx][ly][lz] = false;
							*gks[lx][ly]--;
						}
					}
				}
			}
		}
	}
}
ys::pr()
{
	g_mval a;
	if (check(a))
	{
		return;
	}
	if (base)
	{
		gt b(a, this, NULL, true);
	}
	else
	{
		gt b(a, NULL, this, false);
	}
	b.pd();
}
ys::~ys()
{
	delete[] knz;
	delete[] tm;
	delete[] gks;
}
/*---gt类---*/
gt::gt(g_mval a, ys *b, qk *c, bool se);
{
	va = a;
	su_val = 0;
	select = se;
	y_ys = b;
	y_qk = c;
}
gt::pd()
{
	unsigned int a;
	for (a = 0; a < va.qns; a++)
	{
		qk *b = new qk(va, va.gm_x, va.gm_y, va.val[a], this);
		b->refresh();
		b->refresh_tm();
		b->jbpc();
		b->pr();
		delete b;
	}
}
gt::~gt()
{
	if (va.suc)
	{
		if (select)
		{
			ys->succ = true;
			ys->tm[va.gm_x][va.gm_y] = su_val;
			ys->refresh();
		}
		else
		{
			qk->succ = true;
			qk->tm[va.gm_x][va.gm_y] = su_val;
			qk->refresh();
		}
	}
	else
	{
		if (select)
		{
			ys->err = true;
			ys->gks[va.gm_x][va.gm_y] = 0;
		}
		else
		{
			qk->err = true;
			qk->gks[va.gm_x][va.gm_y] = 0;
		}
	}
}

/*---qk类---*/
qk::qk(ys &a, unsigned int x, unsigned int y, unsigned int z, gk *yq)
{
	this->ys(a);
	this->knz[x][y][z] = true;
	g = z;
	sc = yq;
}
qk::~qk()
{
	bool *a;
	unsigned int *b, *c;
	if (succ)
	{
		sc->va.suc = true;
		sc->su_val = g;
		if (sc->select)
		{
			sc->y_ys->knz = a;
			sc->y_ys->tm = b;
			sc->y_ys->gks = c;
			sc->y_ys->knz = this->knz;
			sc->y_ys->tm = this->tm;
			sc->y_ys->gks = this->gks;
			sc->y_ys->num = this->num;
			this->knz = a;
			this->tm = b;
			this->gks = c;
		}
		else
		{
			sc->y_qk->knz = a;
			sc->y_qk->tm = b;
			sc->y_qk->gks = c;
			sc->y_qk->knz = this->knz;
			sc->y_qk->tm = this->tm;
			sc->y_qk->gks = this->gks;
			sc->y_qk->num = this->num;
			this->knz = a;
			this->tm = b;
			this->gks = c;
		}
	}
}
int main()
{
	ys ma_a;
	unsigned int ls;
	ma_a.refresh();
	ma_a.refresh_tm();
	ma_a.pr();
	if (ma_a.succ)
	{
		cout << "" << endl;
		for (ls = 0; ls < 9; ls++)
		{
			cout << (ma_a.tm)[0][ls] << (ma_a.tm)[1][ls] << (ma_a.tm)[2][ls] << (ma_a.tm)[3][ls] << (ma_a.tm)[4][ls] << (ma_a.tm)[5][ls] << (ma_a.tm)[6][ls] << (ma_a.tm)[7][ls] << (ma_a.tm)[8][ls] << endl;
		}
	}
	else
	{
		cout << "" << endl;
	}
	return 0;
}