#ifndef TI_SCANNER_H
#define TI_SCANNER_H

#include <stddef.h>

typedef enum
{
    // one-byte tokens (0x00 - 0x7F)

    TOKEN_DMS           = 0x01, // ►DMS
    TOKEN_Dec           = 0x02, // ►Dec
    TOKEN_Frac          = 0x03, // ►Frac
    TOKEN__STO          = 0x04, // →
    TOKEN_Boxplot       = 0x05, // Boxplot
    TOKEN__LBBRACE      = 0x06, // [
    TOKEN__RBBRACE      = 0x07, // ]
    TOKEN__LCBRACE      = 0x08, // {
    TOKEN__RCBRACE      = 0x09, // }
    TOKEN_r             = 0x0a, // r
    TOKEN__DEGREE       = 0x0b, // °
    TOKEN__SUPER_1      = 0x0c, // ֿ¹
    TOKEN__SUPER_2      = 0x0d, // ֿ²
    TOKEN_T             = 0x0e, // ֿT
    TOKEN__SUPER_3      = 0x0f, // ֿ³

    TOKEN__LRBRACE      = 0x10, // (
    TOKEN__RRBRACE      = 0x11, // )
    TOKEN_round         = 0x12, // round(
    TOKEN_pxl_Test      = 0x13, // pxl-Test(
    TOKEN_augment       = 0x14, // augment(
    TOKEN_rowSwap       = 0x15, // rowSwap(
    TOKEN_row_PLUS      = 0x16, // row+(
    TOKEN_STAR_row      = 0x17, // *row(
    TOKEN_ST_row_PL     = 0x18, // *row+(
    TOKEN_max           = 0x19, // max(
    TOKEN_min           = 0x1a, // min(
    TOKEN_RPr           = 0x1b, // R►Pr(
    TOKEN_RP0           = 0x1c, // R►Pθ(
    TOKEN_PRx           = 0x1d, // P►Rx(
    TOKEN_PRy           = 0x1e, // P►Ry(
    TOKEN_median        = 0x1f, // median(
    
    TOKEN_randM         = 0x20, // randM( 
    TOKEN_mean          = 0x21, // mean( 
    TOKEN_solve         = 0x22, // solve(
    TOKEN_seq           = 0x23, // seq(
    TOKEN_fnInit	    = 0x24, // fnInt(
    TOKEN_nDeriv		= 0x25, // nDeriv(
    // unused             0x26
    TOKEN_fMin			= 0x27, // fMin(
    TOKEN_fMax			= 0x28, // fMax(
    TOKEN__SPACE		= 0x29, // 
    TOKEN__DQUOTE		= 0x2a, // \"
    TOKEN__COMMA		= 0x2b, // ,
    TOKEN_i     		= 0x2c, // i
    TOKEN__BANG			= 0x2d, // !
    TOKEN_CubicReg		= 0x2e, // CubicReg
    TOKEN_QuratReg		= 0x2f, // QuartReg

    TOKEN_0			    = 0x30, // 0
    TOKEN_1		        = 0x31, // 1
    TOKEN_2		        = 0x32, // 2
    TOKEN_3		        = 0x33, // 3
    TOKEN_4			    = 0x34, // 4
    TOKEN_5		        = 0x35, // 5
    TOKEN_6		        = 0x36, // 6
    TOKEN_7		        = 0x37, // 7
    TOKEN_8			    = 0x38, // 8
    TOKEN_9		        = 0x39, // 9
    TOKEN__DOT			= 0x3a, // .
    TOKEN_E		        = 0x3b, // E
    TOKEN_or			= 0x3c, // or
    TOKEN_xor			= 0x3d, // xor
    TOKEN__COLON		= 0x3e, // :
    TOKEN__NEWLINE		= 0x3f, // \n
    
    TOKEN__ERROR,
    TOKEN__EOF
} TokenType;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable"
static char *TokenStrings[] =
{
	// tokens and their strings
	[TOKEN_DMS]         = "►DMS",
	[TOKEN_Dec]         = "►Dec",
	[TOKEN_Frac]        = "►Frac",
	[TOKEN__STO]        = "→",
	[TOKEN_Boxplot]     = "Boxplot",
	[TOKEN__LBBRACE]    = "[",
	[TOKEN__RBBRACE]    = "]",
	[TOKEN__LCBRACE]    = "{",
	[TOKEN__RCBRACE]    = "}",
	[TOKEN_r]           = "r",
	[TOKEN__DEGREE]     = "°",
	[TOKEN__SUPER_1]    = "ֿ¹",
	[TOKEN__SUPER_2]    = "ֿ²",
	[TOKEN_T]           = "ֿT",
	[TOKEN__SUPER_3]    = "ֿ³",
	[TOKEN__LRBRACE]    = "(",
	[TOKEN__RRBRACE]    = ")",
	[TOKEN_round]       = "round(",
	[TOKEN_pxl_Test]    = "pxl-Test(",
	[TOKEN_augment]     = "augment(",
	[TOKEN_rowSwap]     = "rowSwap(",
	[TOKEN_row_PLUS]    = "row+(",
	[TOKEN_STAR_row]    = "*row(",
	[TOKEN_ST_row_PL]   = "*row+(",
	[TOKEN_max]         = "max(",
	[TOKEN_min]         = "min(",
	[TOKEN_RPr]         = "R►Pr(",
	[TOKEN_RP0]         = "R►Pθ(",
	[TOKEN_PRx]         = "P►Rx(",
	[TOKEN_PRy]         = "P►Ry(",
	[TOKEN_median]      = "median(",
	[TOKEN_randM]       = "randM(",
	[TOKEN_mean]        = "mean(",
	[TOKEN_solve]       = "solve(",
	[TOKEN_seq]         = "seq(",
	[TOKEN_fnInit]      = "fnInt(",
	[TOKEN_nDeriv]      = "nDeriv(",
	[TOKEN_fMin]        = "fMin(",
	[TOKEN_fMax]        = "fMax(",
	[TOKEN__SPACE]      = "",
	[TOKEN__DQUOTE]     = "\"",
	[TOKEN__COMMA]      = ",",
	[TOKEN_i]           = "i",
	[TOKEN__BANG]       = "!",
	[TOKEN_CubicReg]    = "CubicReg",
	[TOKEN_QuratReg]    = "QuartReg",
	[TOKEN_0]           = "0",
	[TOKEN_1]           = "1",
	[TOKEN_2]           = "2",
	[TOKEN_3]           = "3",
	[TOKEN_4]           = "4",
	[TOKEN_5]           = "5",
	[TOKEN_6]           = "6",
	[TOKEN_7]           = "7",
	[TOKEN_8]           = "8",
	[TOKEN_9]           = "9",
	[TOKEN__DOT]        = ".",
	[TOKEN_E]           = "E",
	[TOKEN_or]          = "or",
	[TOKEN_xor]         = "xor",
	[TOKEN__COLON]      = ":",
	[TOKEN__NEWLINE]    = "\n",

	[TOKEN__EOF]        = ""
};
#pragma GCC diagnostic pop

typedef struct
{
    TokenType type;
    const char *start;
    int length;
    int line;
} Token;

// initialize the scanner
void initScanner(const char *source);
// scan the next token
Token scanToken();

#endif