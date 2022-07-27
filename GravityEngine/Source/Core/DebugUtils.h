#pragma once
#ifdef _DEBUG

#define verify(x, errorMessage) \
if(!(x)) \
{ \
	std::cout << "Error in file " << __FILE__ << ", line " << __LINE__ << ": " << std::endl << errorMessage << std::endl; __debugbreak(); \
}

#define validate(x) \
if (!(x)) \
{ \
	__debugbreak(); \
}

#define THROW_ERROR() __debugbreak()

#else

#define verify(...)
#define THROW_ERROR()

#endif