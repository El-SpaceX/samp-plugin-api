#include "main.hpp"

namespace utils
{

	constexpr auto cellMin = std::numeric_limits<cell>::min();
	constexpr auto cellMax = std::numeric_limits<cell>::max();
	constexpr auto floatMin = std::numeric_limits<float>::min();
	constexpr auto floatMax = std::numeric_limits<float>::max();

	inline cell StringToAmxCell(std::string& value)
	{
		try
		{
			return std::stoi(value);
		}
		catch (...)
		{
		}
		return cellMin;
	}
	
	inline cell StringToAmxFloat(std::string& value)
	{
		float v = floatMin;
		try
		{
			v = std::stof(value);
		}
		catch (...)
		{
		}
		return amx_ftoc(v);
	}
}