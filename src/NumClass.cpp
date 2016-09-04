
#include "NumClass.hpp"

Num::Num(int iNum, float fNum, double dNum, eOperandType type) :
	_iNum(iNum), _fNum(fNum), _dNum(dNum), _type(type)
{

	switch (_type) {
		case eOperandType::e_int8: case eOperandType::e_int16: case eOperandType::e_int32:
			_str = std::to_string(iNum);
			break ;
		case eOperandType::e_float:
			_str = std::to_string(_fNum);
			break ;
		case eOperandType::e_double:
			_str = std::to_string(_dNum);
			break ;
		default:
			return;
	}
	return;
}
Num::Num(std::string str, eOperandType type) :
	_str(str), _type(type)
{
	std::string::size_type sz;
	_dNum = std::stod(str, &sz);
	_fNum = std::stof(str, &sz);
	_iNum = _fNum;

	return;
}
Num::~Num(void){
	return;
}

int				Num::getiNum(void) const { return _iNum; }
float			Num::getfNum(void) const { return _fNum; }
double			Num::getdNum(void) const { return _dNum; }
std::string		Num::getStr(void) const { return _str; }
eOperandType	Num::gettype(void) const { return _type; }


