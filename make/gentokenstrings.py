#!/usr/bin/python3

FILENAME = "/home/sjoerdv/Coding/C/TI-Basic-Interpreter/include/compiler/scanner.h"

src = ""

with open(FILENAME, 'r') as f:
    src = f.read()

srcparts = src.split("typedef enum\n{")[1].split("} TokenType;")[0].split("TOKEN_")[1:-2]
names = []
strings = []

for part in srcparts:
    name = part.split('=')[0].strip()
    string = part.split("//")[1].strip()
    
    names.append(name)
    strings.append(string)

new = "static char *TokenStrings[] =\n{\n\t// tokens and their strings\n"

for name, string in zip(names, strings):
    new += f"\t[TOKEN_{name}]{' ' * (12 - len(name))}= \"{string}\",\n"

new += "\n\t[TOKEN__EOF]        = \"\"\n};"

print(new)
