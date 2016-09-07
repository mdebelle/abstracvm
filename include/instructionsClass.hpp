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
#include "error.hpp"

class instructions {

	private :
		std::string								_line;
		int										_lineNumber;
		bool									_exit;
		bool									_valid;
		eErrorType								_etype;
		std::string								_out;
		std::string								_action;
		std::string								_stype;
		eOperandType							_type;
		std::string								_svalue;
		std::vector<IOperand const *>			_currentStack;

		typedef void							(instructions::*Action)(std::vector<IOperand const *>);
		typedef std::map<std::string, Action>	action_map;
		action_map								_m;

		void									ParseInstruction();
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
		eOperandType							ConvertStringToType(std::string str);

		std::string								getLine(void) const;
		int										getLineNumber(void) const;
		bool									getExit(void) const;
		bool									getValid(void) const;
		eErrorType								geteErrorType(void) const;
		std::string								getOut(void) const;

		std::string								getAction(void) const;
		eOperandType							getType(void) const;
		std::string								getSvalue(void) const;
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



