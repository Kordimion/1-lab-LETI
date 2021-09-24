#include <iostream>

void printTypesMemoryConsumption(std::ostream& out)
{
	out << "Types memory consumption (in bytes)\n";
	out << "int:           " << sizeof(int) << "\n";
	out << "short int:     " << sizeof(short int) << "\n";
	out << "long int:      " << sizeof(long int) << "\n";
	out << "long long int: " << sizeof(long long int) << "\n";
	out << "float:         " << sizeof(float) << "\n";
	out << "double:        " << sizeof(double) << "\n";
	out << "long double:   " << sizeof(long double) << "\n";
	out << "char:          " << sizeof(char) << "\n";
	out << "bool:          " << sizeof(bool) << "\n";
}

char ORDER_BREAK = ' ';

std::string binaryStringView(int value)
{
	std::string res;
	constexpr unsigned int orders = sizeof(value) * 8;
	unsigned int mask = 1U << (orders - 1);
	for (int i = 0; i < orders; ++i)
	{
		if (i != 0 && i % 8 == 0) res += ORDER_BREAK;
		if (i == 1) res += ORDER_BREAK;

		res += (value & mask ? '1' : '0');
		mask >>= 1;
	}
	return res;
}

std::string binaryStringView(float _value)
{
	union {
		int value;
		float num_f;
	};
	num_f = _value;

	constexpr unsigned int orders = sizeof(_value) * 8;
	unsigned int mask = 1U << (orders - 1);
	std::string res;
	for (int i = 0; i < orders; ++i)
	{
		if (i == 1 || i == 9) res += ORDER_BREAK;

		res += (value & mask ? '1' : '0');
		mask >>= 1;
	}
	return res;
}

std::string binaryStringView(double _value)
{
	union {
		long long int value;
		double num_f;
	};
	num_f = _value;

	constexpr unsigned int orders = sizeof(_value) * 8;
	unsigned long long int mask = 1ULL << (orders - 1);
	std::string res;
	for (int i = 0; i < orders; ++i)
	{
		if (i == 1 || i == 12) res += ORDER_BREAK;

		res += (value & mask ? '1' : '0');
		mask >>= 1;
	}
	return res;
}

std::string sectionString(const std::string& sectionName)
{
	return "\n-----------------" + sectionName + '\n';
}

int main()
{
	std::cout << sectionString("Memory consumption of common variable types:");
	printTypesMemoryConsumption(std::cout);

	std::cout << sectionString("Integers:");
	std::cout << 123 << ":  " << binaryStringView(123) << '\n';
	std::cout << -127 << ":  " << binaryStringView(-127) << '\n';

	std::cout << sectionString("Floats");
	std::cout << 3.14f << ":  " << binaryStringView(3.14f) << '\n';
	std::cout << -0.1f << ":  " << binaryStringView(-0.1f) << '\n';

	std::cout << sectionString("Doubles");
	std::cout << 3.14 << ":  " << binaryStringView(3.14) << '\n';
	std::cout << -0.1 << ":  " << binaryStringView(-0.1) << '\n';

	return 0;
}

