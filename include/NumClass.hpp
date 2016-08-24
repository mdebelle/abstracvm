
class Num {

	private:
		int				_iNum;
		float			_fNum;
		double			_dNum;
		eOperandType	_type;
	public:
		Num(int iNum, float _fNum, double _dNum, type);
		~Num(void);

		int				getiNum(void) const;
		float			getfNum(void) const;
		double			getdNum(void) const;
		eOperandType	gettype(void) const;
};
