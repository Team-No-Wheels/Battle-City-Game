#pragma once

#include <string>

/** Type of tokens in an RPN expression
 */
enum class RpnToken
{
	Invalid,
	Integer,
	Float,
	String,
	Variable,
	Operator,
	Function,
	Subscript
};

/** Represents an entry in an RPN the parser / evaluator stack
*/
struct StackEntry
{
	std::string mToken;
	RpnToken mTokenType;
};
