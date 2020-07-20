#pragma once

/*/ All exceptions of BearVM are derived from this class.
	This is not the Bear Language 'Exception' type!      /*/
class Exception
{
	const char *Module;
	const char *Message;
public:
	Exception(const char *moduleName, const char *message) noexcept
		: Module(moduleName), Message(message) {}
};
