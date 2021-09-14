#include <argp.h>
#include "comp_common.h"
#include "compiler.h"
#include "tools.h"
#include "cwalk.h"

// ================= arg stuff =======================

const char *argp_program_version = COMP_NAME " " COMP_VERSION;
const char *argp_program_bug_address = EMAIL;

#define ARGS_COUNT 1

/* This structure is used by main to communicate with parse_opt. */
struct arguments
{
	char *args[ARGS_COUNT];	 /* FILE */
	bool verbose;			 /* The -v flag */
	char *outfile;			 /* Argument for -o */
	// char *string1, *string2; /* Arguments for -a and -b */
};

static struct argp_option options[] = {
		// longname, shortname, arg, idk, help
		{"verbose", 'v', 0, 0, "Produce verbose output"},
		{"output", 'o', "OUTFILE", 0, "Output to OUTFILE instead of to standard output"},
		{0}
};

static error_t parse_opt(int key, char *arg, struct argp_state *state)
{
	struct arguments *arguments = state->input;

	switch (key)
	{
	case 'v':
		arguments->verbose = true;
		break;

	case 'o':
		arguments->outfile = arg;
		break;

	case ARGP_KEY_ARG:
	{
		if (state->arg_num >= ARGS_COUNT)
		{
			argp_usage(state);
		}
		arguments->args[state->arg_num] = arg;
		break;
	}
	case ARGP_KEY_END:
	{
		if (state->arg_num < ARGS_COUNT)
		{
			argp_usage(state);
		}
		break;
	}
	default: return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

static char args_doc[] = "FILE";
static char doc[] = COMP_DOC;
static struct argp argp = {options, parse_opt, args_doc, doc};

// ===================================================

static Chunk generate8xp(const char *name, Chunk code)
{
	Chunk bytes;
	initChunk(&bytes);

	#define emit(byte) writeChunk(&bytes, byte, 0);

	// signature
	for (int i = 0; i < SIGNATURE_LEN; i++) emit(SIGNATURE[i]);
	// comment
	for (int i = 0; i < COMMENT_LEN; i++) emit(COMMENT[i]);
	// size
	emit((19 + code.count) & 0xff); emit((20 + code.count) >> 8);
	// ----- checksum start
	// signature
	emit(0x0d); emit(0x00);
	// prgm size + checksum size
	emit((code.count + 2) & 0xff); emit((code.count + 2) >> 8);
	// signature
	emit(0x05);
	// name
	for (int i = 0; i < 8; i++) emit(name[i]);
	// signature
	emit(0x00); emit(0x00);
	// program size + 2
	emit((code.count + 2) & 0xff); emit((code.count + 2) >> 8);
	// program size
	emit(code.count & 0xff); emit(code.count >> 8);
	// program
	for (int i = 0; i < code.count; i++) emit(code.bytes[i]);
	// ------ checksum end
	// checksum
	{
		uint16_t sum = 0;
		sum += 0x0d + 0x00; // signatures
		sum += ((code.count + 2) & 0xff) + ((code.count + 2) >> 8); // prgm size + cs size
		sum += 0x05; // signature
		for (int i = 0; i < 8; i++) sum += name[i]; // name
		sum += 0x00 + 0x00; // signatures
		sum += ((code.count + 2) & 0xff) + ((code.count + 2) >> 8); // prgm size + 2
		sum += (code.count & 0xff) + (code.count >> 8); // prgm size
		for (int i = 0; i < code.count; i++) sum += code.bytes[i]; // program

		emit(sum & 0xff); emit(sum >> 8);
	}

	return bytes;
}

int main(int argc, char **argv)
{
	struct arguments arguments;
	char *name = malloc(8);

	/* Set argument defaults */
	arguments.outfile = NULL;
	arguments.verbose = false;

	/* Where the magic happens */
	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	// if no output file is given the output file is input file 
	// but with the extension ".8px"
	if (arguments.outfile == NULL)
	{
		char *dot, *newname;
		int len;

		dot = strrchr(arguments.args[0], '.');
		if (dot) len = dot - arguments.args[0];
		else len = strlen(arguments.args[0]);
		
		newname = malloc(len + 6);
		
		strncpy(newname, arguments.args[0], len);
		strcpy(newname + len, "." BINARY_EXTENSION);

		arguments.outfile = newname;
	}

	// figure out program name
	{
		// get basename
		const char *basename;
		size_t length;
		cwk_path_get_basename(arguments.outfile, &basename, &length);
		
		// remove extension
		char *dot, *purename;
		int len;

		dot = strrchr(basename, '.');
		if (dot) len = dot - basename;
		else len = strlen(basename);
		
		purename = malloc(len + 1);
		strncpy(purename, basename, (len <= 8) ? len : 8);

		name = toUpper(purename);
	}

	char *src = readFile(arguments.args[0]);
	
	Chunk chunk;
	initChunk(&chunk);
	
	int state = compileFromSrc(src, &chunk, arguments.verbose);
	
	Chunk bytes = generate8xp(name, chunk);

	if (arguments.verbose) printf("byte count: %d\n", bytes.count);

	writeBinFile(arguments.outfile, bytes.bytes, bytes.count);

	return state;
}