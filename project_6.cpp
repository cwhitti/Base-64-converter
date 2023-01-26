//=============================================================================
// Base64 Encoding Starter Framework
// 2011.02.16 by Abe Pralle
//
// Reads a string of text and prints a resulting string of text where every
// 3 original characters have been transformed into 4 result characters
// consisting of the first three characters reversed followed by a hypen.
//
// Example output:
// Enter text: ABCDEFGHIJKLMNOPQRSTUVWXYZ
// You typed in "ABCDEFGHIJKLMNOPQRSTUVWXYZ" (26 characters)
// Encoded value: CBA-FED-IHG-LKJ-ONM-RQP-UTS-XWV-
//=============================================================================
#include <iostream>
using namespace std;

void encode( char* src, char* dest );
void encodeLeftovers( char* src, char* dest, int leftovers);
void decode(char* src, char* dest);
void decodeLeftovers(char* src, char* dest, int leftovers);
bool tooBig(char* src);

int main()
	{
	// Declare arrays to store original and encoded strings.
	char st[80];
	char encoded[120];
	char decoded[120];

	//initialize variables
	int choice;

	printf("\n");
	printf(" This program is a base-64 encoder and decoder. \n");
	printf(" =============================================== \n");
	printf("\n");
	printf(" Options: \n");
	printf(" --------------\n");
	printf(" | 1 - Encoder | \n");
	printf(" | 2 - Decoder | \n");
	printf(" --------------\n");
	printf("\n");
	printf(" Please enter your choice: ");
	cin >> choice;
	printf("\n");

	if (choice == 1)
		{
		// Read in original string.
		cout << " Enter text to encode: ";
		cin >> st;
		printf("\n");

		//Check if the string is too big
		if (tooBig(st))
			{
				printf("\n");
				printf(" ERROR! String too long.\n");
				printf(" Please keep strings to 80 letters or fewer. \n");
				return 0;
			}

		// Print back out along with the # of characters.
		int len = strlen(st);
		cout << " You typed in \"" << st << "\" (" << len << " characters)" << endl;
		printf("\n");

		// Encode the string - every 3 characters of original becomes
		// 4 characters of result.
		int dest_index = 0;
		int list_pos = 0;

		//Get the length and leftover amount
		int leftovers = len % 3;
		len -= leftovers;

		//loop through groups of 3
		for (int i=0; i<len; i+=3)
			{
				encode( st+i, encoded+dest_index );
				dest_index += 4;
				list_pos += 3;
			}

		 if (leftovers != 0)
		 	{
				encodeLeftovers(st+list_pos, encoded+dest_index, leftovers);
				dest_index += leftovers + 1;
			}
		// Print encoded value.
		cout << " Encoded value: ";
		cout << encoded << endl;
		printf("\n");
		return 0;
		}

	if (choice == 2)
		{
			// Read in original string.
			cout << " Enter text to decode: ";
			cin >> st;
			printf("\n");

			//Check if the string is too big
			if (tooBig(st))
				{
					printf("\n");
					printf(" ERROR! String too long.\n");
					printf(" Please keep strings to 80 letters or fewer. \n");
					return 0;
				}
				
			// Print back out along with the # of characters.
			int len = strlen(st);
			cout << " You typed in \"" << st << "\" (" << len << " characters)" << endl;
			printf("\n");

			// Encode the string - every 3 characters of original becomes
			// 4 characters of result.
			int dest_index = 0;
			int list_pos = 0;

			//Get the length and leftover amount
			int leftovers = len % 4;
			len -= leftovers;

			//loop through groups of 3
			for (int i=0; i<len; i+=4)
				{
					decode( st+i, decoded+dest_index );
					dest_index += 3;
					list_pos += 4;
				}
			// Print encoded value.
			cout << " Decoded value: ";
			cout << decoded << endl;
			printf("\n");
			return 0;
		}
	}


void encode( char* src, char* dest)
	{
		char myAlphabet[ 201 ] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
		// Declare arrays to store original and encoded strings.
		char st[80];
		char ep = '=';
		unsigned char char1, char2, char3, char4;
		unsigned char byte1, byte2, byte3, byte4, byte5, byte6;
		unsigned char byte2A, byte3A, byte4A, byte5A, byte6A;

		//Assign the characters
		char1 = src[0];
		char2 = src[1];
		char3 = src[2];

		//get the first char
		byte1 = (char1 >> 2);

		//get the second char
		byte2 = (char1 << 6);
		byte2A = (byte2 >> 2) + (char2 >>4);

		//get the third char
		byte3 = (char2 << 4);

		//Get the third Char
		byte3A = (byte3 >> 2) + (char3 >> 6);

		//get the fourth char
		byte4 = (char3 <<2);
		byte4A = (byte4 >> 2);

		//Put all of the items in the list
		dest[0] = myAlphabet[ byte1  ];
		dest[1] = myAlphabet[ byte2A ];
		dest[2] = myAlphabet[ byte3A ];
		dest[3] = myAlphabet[ byte4A ];
	}

void encodeLeftovers( char* src, char* dest, int leftovers)
{
		char st[80];
		unsigned char char1, char2, char3;
		unsigned char byte1, byte2, byte2A, byte3, byte3A;

		char myAlphabet[ 201 ] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

		char1 = src[0];
		char2 = src[1];
		char3 = src[3];

		if (leftovers == 1)
		{
			//get the first char
			byte1 = (char1 >> 2);

			//get the second char
			byte2 = (char1 << 6);
			byte2A = (byte2 >> 2);

			dest[0] = myAlphabet[ byte1  ];
			dest[1] = myAlphabet[ byte2A ];
			dest[2] = '=';
			dest[3] = '=';
		}

		else
		{
			//get the first char
			byte1 = (char1 >> 2);

			//get the second char
			byte2 = (char1 << 6);
			byte2A = (byte2 >> 2);

			//get the third char
			byte3 = (char2 << 4);

			//Get the third Char
			byte3A = (byte3 >> 2);

			//Put all of the items in the list
			dest[0] = myAlphabet[ byte1  ];
			dest[1] = myAlphabet[ byte2A ];
			dest[2] = myAlphabet[ byte3A ];
			dest[3] = '=';
		}
}

void decode(char* src, char* dest)
{

	unsigned char byte1, byte2, byte3, byte4;
	unsigned char byte1A, byte2A, byte3A, byte4A;
	unsigned char char1, char2, char3;
	char alphabet[ 201 ] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int alphabetPointer = 0;

	//Set the bytes
	byte1 = src[0];
	byte2 = src[1];
	byte3 = src[2];
	byte4 = src[3];

	for (int i = 0; i<4; i++)
	{
			//get the index valie
			while (src[i] != alphabet[alphabetPointer])
				{
					alphabetPointer += 1;
				}

			//asign byte1
			if (src[i] == byte1)
				{
					byte1A = alphabetPointer;
				}

			//asign byte2
			else if (src[i] == byte2)
				{
					byte2A = alphabetPointer;
				}

			//asign byte3
			else if (src[i] == byte3)
				{
					byte3A = alphabetPointer;
				}

			//asign byte4
			else
				{
					byte4A = alphabetPointer;
				}

				alphabetPointer = 0;

	}

	//get char 1
	char1 = (byte1A << 2) + (byte2A >>4);

	//Set bits to zero if there is a =
	if (byte2 == '=')
		{
			byte2A = 00000000;
		}

	//Set bits to zero if there is a =
	if (byte3 == '=')
		{
			byte3A = 00000000;
		}

	//Set bits to zero if there is a =
	if (byte4 == '=')
		{
			byte4A = 00000000;
		}

	//get char 2
	char2 = (byte2A << 4) + (byte3A >> 2);

	//get char 3
	char3 = (byte3A << 6) + byte4A;

	//Put all of the items in the list
	dest[0] = char1;
	dest[1] = char2;
	dest[2] = char3;
}

bool tooBig(char* src)
{
	return (strlen(src) > 80);
}
