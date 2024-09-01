#!/bin/bash

LEX_FLAG=0
PARSE_FLAG=0
CODEGEN_FLAG=0
FILE_PATH=""
OUTPUT_FILE="preprocessed"

# Parse command-line arguments
while [[ "$#" -gt 0 ]]; do
    case "$1" in
        --lex)
            LEX_FLAG=1
            ;;
        --parse)
            PARSE_FLAG=1
            ;;
        --codegen)
            CODEGEN_FLAG=1
            ;;
        -h|--help)
            echo "Usage: $0 [--lex] [--parse] [--codegen] file_path"
            exit 0
            ;;
        -*|--*)
            echo "Unknown option: $1"
            exit 1
            ;;
        *)
            if [ -z "$FILE_PATH" ]; then
                FILE_PATH="$1"
            else
                echo "Multiple files provided, but only one is allowed."
                exit 1
            fi
            ;;
    esac
    shift
done

# Check if file path is provided
if [ -z "$FILE_PATH" ]; then
	echo "Error: No file path provided."
	echo "Usage: $0 [--lex] [--parse] [--codegen] file_path"
	exit 1
fi

# 1) Running the preprocessor
PREPROCESSOR="gcc -E -P \"$FILE_PATH\" -o \"$OUTPUT_FILE\""
eval $PREPROCESSOR

# 2) Running the lexer, parser, and assembly generator (TODO)
LEXER_AND_PARSER="./compiler \"$OUTPUT_FILE\""
eval $LEXER_AND_PARSER

# ...
ASSEMBLY_PATH=""
FINAL_OUTPUT_PATH=""

if [ "$LEX_FLAG" -eq 1 ]; then
	echo "Run the lexer, but stop before parsing."
	exit 0
fi

if [ "$PARSE_FLAG" -eq 1 ]; then
	echo "Run the lexer and parser, but stop before assembly generation."
fi

if [ "$CODEGEN_FLAG" -eq 1 ]; then
	echo "Run the lexer, parser, assembly generation, but stop before code emission."
fi

# 3) Assemble and link the assembly file to produce the executable
ASSEMBLE_AND_LINK="gcc $ASSEMBLY_PATH -o $FINAL_OUTPUT_PATH"
eval $ASSEMBLE_AND_LINK
