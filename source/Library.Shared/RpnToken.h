#pragma once

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
