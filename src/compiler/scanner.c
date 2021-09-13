#include "scanner.h"
#include "comp_common.h"
#include <unistd.h>

typedef struct
{
	const char *start;
	const char *current;
	int line;
} Scanner;

Scanner scanner;

void initScanner(const char *source)
{
	scanner.start = source;
	scanner.current = source;
	scanner.line = 1;
}

static bool isAtEnd()
{
	return *scanner.current == '\0';
}

// static bool match(char expected)
// {
// 	if (isAtEnd())
// 		return false;
// 	if (*scanner.current != expected)
// 		return false;
// 	scanner.current++;
// 	return true;
// }

static char advance()
{
	scanner.current++;
	return scanner.current[-1];
}

static char peek()
{
	return *scanner.current;
}

static char peekNext()
{
	if (isAtEnd())
		return '\0';
	return scanner.current[1];
}

static Token makeToken(TokenType type)
{
	Token token;
	token.type = type;
	token.start = scanner.start;
	// token.length = (int)(scanner.current - scanner.start);
	token.length = strlen(TokenStrings[type]);
	token.line = scanner.line;
	return token;
}

static Token errorToken(const char *message)
{
	Token token;
	token.type = TOKEN__ERROR;
	token.start = message;
	token.length = (int)strlen(message);
	token.line = scanner.line;
	return token;
}

// matches keywords
static TokenType getKeyWord()
{
    TokenType type = TOKEN__ERROR;
    bool stop = false;
    int lastLength = 0;

    while (!stop)
    {       
        // loop through all the tokens. If we find a match we check if
        // the length of the match is larger than the lenght of a previous
        // match (if there is one). This is to make sure that we dont miss
        // tokens like "abcd" if token "ab" also exists. If we don't find
        // a match after the entire loop we return the last found match.

        bool found = false;

        for(TokenType i = 0; i < TOKEN__ERROR; i++)
        {
            if (TokenStrings[i] == NULL)
                continue;

            size_t len = utf8len(TokenStrings[i]);

            // printf("comparing '%.*s' and '%s' (type %d)\n",
            //     len, scanner.current, TokenStrings[i], i);

            if (
                strncmp(scanner.current, TokenStrings[i], len) == 0
                && len > lastLength
            )
            {
                // printf("match!\n");
                type = i;
                lastLength = len;
                found = true;
                break;
            }

        }

        if (!found)
        {
            // printf("breaking\n");
            break; // no matches: break
        }
    }

    return type;
    // switch (scanner.start[0])
	// {
	// case 'C': return checkKeyword(1, 2, "ls", TOKEN_CLASS);
	// case 'E': // 'Exit' or 'Else'
	// 	if (scanner.current - scanner.start > 1)
	// 	{
	// 		switch (scanner.start[1])
	// 		{
	// 			case 'x': return checkKeyword(2, 2, "it", TOKEN_EXIT);
	// 			case 'l': return checkKeyword(2, 2, "se", TOKEN_ELSE);
	// 		}
	// 	}
	// case 'f': return checkKeyword(1, 4, "alse", TOKEN_FALSE);
	// case 'F': // 'Fun' or 'For' or 'Foreach'
	// 	if (scanner.current - scanner.start > 1)
	// 	{
	// 		switch (scanner.start[1])
	// 		{
	// 		// case 'o': return checkKeyword(2, 1, "r", TOKEN_FOR);
	// 		case 'o': // 'For' or 'Foreach'
	// 			if (scanner.current - scanner.start > 2 && scanner.start[2] == 'r')
	// 			{
	// 				if (scanner.current - scanner.start > 3)
	// 					return checkKeyword(3, 4, "each", TOKEN_FOREACH);
	// 				else
	// 					return checkKeyword(3, 0, "", TOKEN_FOR);
	// 			}
    //
	// 		case 'u': return checkKeyword(2, 1, "n", TOKEN_FUN);
	// 		}
	// 	}
	// case 'I': return checkKeyword(1, 1, "f", TOKEN_IF);
	// case 'n': return checkKeyword(1, 3, "ull", TOKEN_NULL);
	// // case 'P': return checkKeyword(1, 4, "rint", TOKEN_PRINT);
	// case 'P': // 'Print' or 'PrintLn'
	// 	if (scanner.current - scanner.start > 4)
	// 	{
	// 		if (scanner.current - scanner.start > 5)
	// 			return checkKeyword(5, 2, "Ln", TOKEN_PRINT_LN);
	// 		else
	// 			return checkKeyword(5, 0, "", TOKEN_PRINT);
	// 	}
	// case 'R': return checkKeyword(1, 5, "eturn", TOKEN_RETURN);
	// case 's': return checkKeyword(1, 4, "uper", TOKEN_SUPER);
	// case 't': // 'this' or 'true'
	// 	if (scanner.current - scanner.start > 1)
	// 	{
	// 		switch (scanner.start[1])
	// 		{
	// 		case 'h': return checkKeyword(2, 2, "is", TOKEN_THIS);
	// 		case 'r': return checkKeyword(2, 2, "ue", TOKEN_TRUE);
	// 		}
	// 	}
	// case 'V': return checkKeyword(1, 2, "ar", TOKEN_VAR);
	// case 'W': return checkKeyword(1, 4, "hile", TOKEN_WHILE);
	// case 'U': return checkKeyword(1, 2, "se", TOKEN_USE);
	// }
	// return TOKEN_IDENTIFIER;
}

static void skipWhitespace()
{
	for (;;)
	{
		char c = peek();
		switch (c)
		{
		case ' ':
		case '\r':
		case '\t':
			advance();
			break;
		case '\n':
			scanner.line++;
			advance();
			break;
		case '#':
			if (peekNext() == '*')
			{
				// while (peek() != '*' && peekNext() != '#' && !isAtEnd())
				for (;;)
				{
					if (peek() == '*' && peekNext() == '#')
					{
						advance();
						advance();
						break;
					}
					else if (isAtEnd()) break;
					else if (peek() == '\n') scanner.line++;
					advance();
				}
			}
			else
			{
				while (peek() != '\n' && !isAtEnd())
					advance();
			}
			break;
		// case '/':
		// 	if (peekNext() == '/')
		// 	{
		// 		// A comment goes until the end of the line.
		// 		while (peek() != '\n' && !isAtEnd())
		// 			advance();
		// 	}
		// 	else
		// 	{
		// 		return;
		// 	}
		// 	break;
		default:
			return;
		}
	}
}

Token scanToken()
{
	skipWhitespace();

	scanner.start = scanner.current;

	if (isAtEnd())
		return makeToken(TOKEN__EOF);

    TokenType type = getKeyWord();

    if (type == TOKEN__ERROR)
        return errorToken("Unexpected token.");

    for(int i = 0; i < strlen(TokenStrings[type]); i++)
        advance();

    return makeToken(type);
}
