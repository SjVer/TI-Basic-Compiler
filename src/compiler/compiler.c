#include "compiler.h"
#include "comp_common.h"

typedef struct
{
	Token current;
	Token previous;
	bool hadError;
} Parser;
Parser parser;

// -------- error stuff --------

// displays an error with the given token and message
static void errorAt(Token *token, const char *message)
{
	fprintf(stderr, "[line %d] Error", token->line);

	if (token->type == TOKEN__EOF)
	{
		fprintf(stderr, " at end");
	}
	else if (token->type == TOKEN__ERROR)
	{
		// Nothing.
	}
	else
	{
		fprintf(stderr, " at '%.*s'", token->length, token->start);
	}

	fprintf(stderr, ": %s\n", message);
	parser.hadError = true;
}

// // displays an error at the previous token with the given message
// static void error(const char *message)
// {
// 	errorAt(&parser.previous, message);
// }

// displays an error at the current token with the given message
static void errorAtCurrent(const char *message)
{
	errorAt(&parser.current, message);
}


// -------- token flow stuff --------

// advances to the next token
static void advance()
{
	parser.previous = parser.current;
	parser.current = scanToken();
	if (parser.current.type == TOKEN__ERROR)
		errorAtCurrent(parser.current.start);
}

// checks if the current token is of the given type
static bool check(TokenType type)
{
	return parser.current.type == type;
}

// // consume the next token if it is of the correct type,
// // otherwise throw an error with the given message
// static void consume(TokenType type, const char *message)
// {
// 	if (parser.current.type == type)
// 	{
// 		advance();
// 		return;
// 	}
//
// 	errorAtCurrent(message);
// }

// returns true and advances if the current token is of the given type
static bool match(TokenType type)
{
	if (!check(type))
		return false;
	advance();
	return true;
}


// ------ compilation stuff --------

int compileFromSrc(const char *src, Chunk *chunk, bool verbose)
{
    initScanner(src);
    parser.hadError = false;

    advance();
    while (!match(TOKEN__EOF) && !parser.hadError)
    {
        if (parser.current.type != TOKEN__ERROR && verbose)
            printf("Token: '%s' = %d (0x%x)\n", 
				TokenStrings[parser.current.type],
				parser.current.type, parser.current.type);

		writeChunk(chunk, (uint8_t)parser.current.type, parser.current.line);

		advance();
	}

    return 0;
}