/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructionsClass.hpp                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdebelle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/19 04:30:28 by mdebelle          #+#    #+#             */
/*   Updated: 2016/08/19 04:30:30 by mdebelle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTIONS_HPP
# define INSTRUCTIONS_HPP

#include <iostream>
#include <vector>
#include <map>
#include "NumClass.hpp"
#include "eOperandType.hpp"

class instructions {

	private :
		std::string								_line;
		int										_lineNumber;
		bool									_exit;
		bool									_valid;
		std::string								_error;
		std::string								_out;

		std::string								_action;

		std::string								_stype;
		eOperandType							_type;
		int										_precision;
		
		std::string								_svalue;
		int										_ivalue;
		float									_fvalue;
		double									_dvalue;

		std::vector<Num>						_currentStack;

		typedef void							(instructions::*Action)(std::vector<Num>);
		typedef std::map<std::string, Action>	action_map;

		action_map								_m;

		void									ParseInstruction();

		bool									IsComment(std::string comp, std::string str, void (*f)(std::string));
		std::string								SplitComment(std::string sep, std::string str);

		bool									isValue(std::string str);
		bool									isSimpleAction(std::string action, std::string str);
		bool									isActionValue(std::string comp, std::string str);



	public:
		instructions(std::string line, int number);
		~instructions();
		
		bool									ExitLoop(bool exit);
		std::vector<Num>						Execute(std::vector<Num>);
		bool									isStackEnought(std::vector<Num>);
		bool									isinlimits(std::vector<Num>);
		void									setErrorLimits(std::string);
		void									setErrorZero(void);
		eOperandType							ConvertStringToType(std::string str);
		int										ConvertTypeToPrecision(eOperandType eOp);
		eOperandType							ConvertPrecisionToType(int eOp);

		std::string								getLine(void) const;
		int										getLineNumber(void) const;
		bool									getExit(void) const;
		bool									getValid(void) const;
		std::string								getError(void) const;
		std::string								getOut(void) const;

		std::string								getAction(void) const;

		std::string								getStype(void) const;
		eOperandType							getType(void) const;
		int										getPrecision(void) const;
		
		std::string								getSvalue(void) const;
		int										getIvalue(void) const;
		float									getFvalue(void) const;
		double									getDvalue(void) const;
		instructions::action_map				getM(void) const;

		void									setActionsMap(void);
		bool									setTypes(std::string);
		bool									setValues(std::string);

		void									ActionPush(std::vector<Num>);
		void									ActionPop(std::vector<Num>);
		void									ActionDump(std::vector<Num>);
		void									ActionAssert(std::vector<Num>);
		void									ActionAdd(std::vector<Num>);
		void									ActionSub(std::vector<Num>);
		void									ActionMul(std::vector<Num>);
		void									ActionDiv(std::vector<Num>);
		void									ActionMod(std::vector<Num>);
		void									ActionPrint(std::vector<Num>);
		void									ActionExit(std::vector<Num>);


};

#endif



