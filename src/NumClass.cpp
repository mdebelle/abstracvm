
#include "NumClass.hpp"

Num::Num(int iNum, float _fNum, double _dNum, type);
Num::~Num(void);

int				Num::getiNum(void) const { return int; }
float			Num::getfNum(void) const { return float; }
double			Num::getdNum(void) const { return double; }
eOperandType	Num::gettype(void) const { return eOperandType; }
