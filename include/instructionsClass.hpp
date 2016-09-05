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

#include <map>
#include <vector>
#include "eOperandType.hpp"
#include "NumClass.hpp"

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

		std::vector<IOperand const *>			_currentStack;

		typedef void							(instructions::*Action)(std::vector<IOperand const *>);
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
		std::vector<IOperand const *>			Execute(std::vector<IOperand const *>);
		bool									isStackEnought(std::vector<IOperand const *>);
		bool									isinlimits(std::vector<IOperand const *>);
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

		void									ActionPush(std::vector<IOperand const *>);
		void									ActionPop(std::vector<IOperand const *>);
		void									ActionDump(std::vector<IOperand const *>);
		void									ActionAssert(std::vector<IOperand const *>);
		void									ActionAdd(std::vector<IOperand const *>);
		void									ActionSub(std::vector<IOperand const *>);
		void									ActionMul(std::vector<IOperand const *>);
		void									ActionDiv(std::vector<IOperand const *>);
		void									ActionMod(std::vector<IOperand const *>);
		void									ActionPrint(std::vector<IOperand const *>);
		void									ActionExit(std::vector<IOperand const *>);

};

#endif



