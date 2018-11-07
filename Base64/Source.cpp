#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

char convert_base64(char a)
{
	string base64 = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a',
		'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0','1', '2', '3', '4', '5',
		'6', '7', '8', '9', '+', '/' };
	return base64.at(a);
}

int position_base64(char a)
{
	string base64 = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a',
		'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '0','1', '2', '3', '4', '5',
		'6', '7', '8', '9', '+', '/' };
	return base64.find(a);
}

std::string base64_encode(std::string input)
{
	std::string result;
	int buffer = 0, n = input.size();

	for (int i = 0; i < n; i += 3)
	{
		//tema1:
		//in loc de buffer |=, cast to (int*)input.c_str();
		//alignment error?
		/*
		buffer |= input[i] << 16;
		buffer |= i + 1 < n ? input[i + 1] << 8 : 0;
		buffer |= i + 2 < n ? input[i + 2] : 0;

		printf("%#010x\n", buffer);

		result += convert_base64((buffer >> 18) & 0x3f);
		result += convert_base64((buffer >> 12) & 0x3f);
		result += i + 1 < n ? convert_base64((buffer >> 6) & 0x3f) : '=';
		result += i + 2 < n ? convert_base64(buffer & 0x3f) : '=';
		printf("%s\n", result.c_str());

		printf("flush: %#010x\n", buffer);
		buffer = 0;
		*/

		result += convert_base64((*(input.c_str() + i) & 0xFC) >> 2);
		result += convert_base64(((*(input.c_str() + i) & 0x03) << 4 | ((*(input.c_str() + (i + 1)) & 0xF0)) >> 4));
		result += i + 1 < n ? convert_base64(((*(input.c_str() + (i + 1)) & 0x0F) << 2) | ((*(input.c_str() + (i + 2)) & 0xC0) >> 6)) : '=';
		result += i + 2 < n ? convert_base64((*(input.c_str() + (i + 2)) & 0x3F)) : '=';
	}
	printf("%s\n", result.c_str());
	return result;
}

std::string base64_decode(std::string input)
{
	std::string result;
	int n = input.size();
	for (int i = 0; i < n; i += 4)
	{
		result += (char)((position_base64(*(input.c_str() + i)) << 2) | (position_base64(*(input.c_str() + (i + 1))) << 2 & 0xC0) >> 6);
		if (input[i + 2] != '=')
		{
			result += (char)((position_base64(*(input.c_str() + (i + 1))) & 0x0F) << 4 | (position_base64(*(input.c_str() + (i + 2))) << 2 & 0xF0) >> 4);
			if (input[i + 3] != '=')
			{
				result += (char)((position_base64(*(input.c_str() + (i + 2))) & 0x03) << 6 | (position_base64(*(input.c_str() + (i + 3)))));
			}
		}
	}
	printf("%s\n", result.c_str());

	return result;
}

int main()
{

	base64_decode(base64_encode("Radu"));
	getchar();

	return 0;
}