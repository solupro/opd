#ifndef OPD_H
#define OPD_H

#include "php.h"

// flags used in the op array list
#define OP1_USED   1<<0
#define OP2_USED   1<<1
#define RES_USED   1<<2

#define NONE_USED  0
#define ALL_USED   0x7

#define OP1_OPLINE   1<<3
#define OP2_OPLINE   1<<4
#define OP1_OPNUM    1<<5
#define OP2_OPNUM    1<<6
#define OP_FETCH     1<<7
#define EXT_VAL      1<<8
#define NOP2_OPNUM   1<<9
#define OP2_BRK_CONT 1<<10
#define OP1_CLASS    1<<11
#define RES_CLASS    1<<12

#define SPECIAL    0xff

// special op-type flags
#define OPD_IS_OPLINE 1<<13
#define OPD_IS_OPNUM  1<<14
#define OPD_IS_CLASS  1<<15
#define OP2_INCLUDE   1<<16

typedef struct _op_usage {
	char *name;
	zend_uint flags;
} op_usage;

/* Input zend_compile.h
 * And replace [^(...)(#define )([^ \t]+).*$]
 * BY     [/=*  \1 *=/  { "\3", ALL_USED },] REMEMBER to remove the two '=' signs
 */
static const op_usage opcodes[] = {
	/*  0 */	{ "NOP", NONE_USED },
	/*  1 */	{ "ADD", ALL_USED },
	/*  2 */	{ "SUB", ALL_USED },
	/*  3 */	{ "MUL", ALL_USED },
	/*  4 */	{ "DIV", ALL_USED },
	/*  5 */	{ "MOD", ALL_USED },
	/*  6 */	{ "SL", ALL_USED },
	/*  7 */	{ "SR", ALL_USED },
	/*  8 */	{ "CONCAT", ALL_USED },
	/*  9 */	{ "BW_OR", ALL_USED },
	/*  10 */	{ "BW_AND", ALL_USED },
	/*  11 */	{ "BW_XOR", ALL_USED },
	/*  12 */	{ "BW_NOT", RES_USED | OP1_USED },
	/*  13 */	{ "BOOL_NOT", RES_USED | OP1_USED },
	/*  14 */	{ "BOOL_XOR", ALL_USED },
	/*  15 */	{ "IS_IDENTICAL", ALL_USED },
	/*  16 */	{ "IS_NOT_IDENTICAL", ALL_USED },
	/*  17 */	{ "IS_EQUAL", ALL_USED },
	/*  18 */	{ "IS_NOT_EQUAL", ALL_USED },
	/*  19 */	{ "IS_SMALLER", ALL_USED },
	/*  20 */	{ "IS_SMALLER_OR_EQUAL", ALL_USED },
	/*  21 */	{ "CAST", ALL_USED },
	/*  22 */	{ "QM_ASSIGN", RES_USED | OP1_USED },
	/*  23 */	{ "ASSIGN_ADD", ALL_USED | EXT_VAL },
	/*  24 */	{ "ASSIGN_SUB", ALL_USED | EXT_VAL },
	/*  25 */	{ "ASSIGN_MUL", ALL_USED | EXT_VAL },
	/*  26 */	{ "ASSIGN_DIV", ALL_USED | EXT_VAL },
	/*  27 */	{ "ASSIGN_MOD", ALL_USED | EXT_VAL },
	/*  28 */	{ "ASSIGN_SL", ALL_USED | EXT_VAL },
	/*  29 */	{ "ASSIGN_SR", ALL_USED | EXT_VAL },
	/*  30 */	{ "ASSIGN_CONCAT", ALL_USED | EXT_VAL },
	/*  31 */	{ "ASSIGN_BW_OR", ALL_USED | EXT_VAL },
	/*  32 */	{ "ASSIGN_BW_AND", ALL_USED | EXT_VAL },
	/*  33 */	{ "ASSIGN_BW_XOR", ALL_USED | EXT_VAL },
	/*  34 */	{ "PRE_INC", OP1_USED | RES_USED },
	/*  35 */	{ "PRE_DEC", OP1_USED | RES_USED },
	/*  36 */	{ "POST_INC", OP1_USED | RES_USED },
	/*  37 */	{ "POST_DEC", OP1_USED | RES_USED },
	/*  38 */	{ "ASSIGN", ALL_USED },
	/*  39 */	{ "ASSIGN_REF", SPECIAL },
	/*  40 */	{ "ECHO", OP1_USED },
	/*  41 */	{ "PRINT", RES_USED | OP1_USED },
	/*  42 */	{ "JMP", OP1_USED | OP1_OPLINE },
	/*  43 */	{ "JMPZ", OP1_USED | OP2_USED | OP2_OPLINE },
	/*  44 */	{ "JMPNZ", OP1_USED | OP2_USED | OP2_OPLINE },
	/*  45 */	{ "JMPZNZ", SPECIAL },
	/*  46 */	{ "JMPZ_EX", ALL_USED | OP2_OPLINE },
	/*  47 */	{ "JMPNZ_EX", ALL_USED | OP2_OPLINE },
	/*  48 */	{ "CASE", ALL_USED },
	/*  49 */	{ "SWITCH_FREE", RES_USED | OP1_USED },
	/*  50 */	{ "BRK", SPECIAL },
	/*  51 */	{ "CONT", ALL_USED },
	/*  52 */	{ "BOOL", RES_USED | OP1_USED },
	/*  53 */	{ "INIT_STRING", RES_USED },
	/*  54 */	{ "ADD_CHAR", ALL_USED },
	/*  55 */	{ "ADD_STRING", ALL_USED },
	/*  56 */	{ "ADD_VAR", ALL_USED },
	/*  57 */	{ "BEGIN_SILENCE", ALL_USED },
	/*  58 */	{ "END_SILENCE", ALL_USED },
	/*  59 */	{ "INIT_FCALL_BY_NAME", SPECIAL },
	/*  60 */	{ "DO_FCALL", SPECIAL },
	/*  61 */	{ "DO_FCALL_BY_NAME", SPECIAL },
	/*  62 */	{ "RETURN", OP1_USED },
	/*  63 */	{ "RECV", RES_USED | OP1_USED },
	/*  64 */	{ "RECV_INIT", ALL_USED },
	/*  65 */	{ "SEND_VAL", OP1_USED },
	/*  66 */	{ "SEND_VAR", OP1_USED },
	/*  67 */	{ "SEND_REF", ALL_USED },
	/*  68 */	{ "NEW", SPECIAL },
#if (PHP_MAJOR_VERSION < 5) || (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION < 1)
	/*  69 */	{ "JMP_NO_CTOR", SPECIAL },
#else
# if (PHP_MAJOR_VERSION > 5) || (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION >= 3)
	/*  69 */	{ "INIT_NS_FCALL_BY_NAME", SPECIAL },
# else
	/*  69 */	{ "UNKNOWN", ALL_USED },
# endif
#endif
	/*  70 */	{ "FREE", OP1_USED },
	/*  71 */	{ "INIT_ARRAY", ALL_USED },
	/*  72 */	{ "ADD_ARRAY_ELEMENT", ALL_USED },
	/*  73 */	{ "INCLUDE_OR_EVAL", ALL_USED | OP2_INCLUDE },
	/*  74 */	{ "UNSET_VAR", ALL_USED },
#ifdef ZEND_ENGINE_2
	/*  75 */	{ "UNSET_DIM", ALL_USED },
	/*  76 */	{ "UNSET_OBJ", ALL_USED },
#else
	/*  75 */	{ "UNSET_DIM_OBJ", ALL_USED },
	/*  76 */	{ "ISSET_ISEMPTY", ALL_USED },
#endif
	/*  77 */	{ "FE_RESET", SPECIAL },
	/*  78 */	{ "FE_FETCH", ALL_USED | OP2_OPNUM },
	/*  79 */	{ "EXIT", ALL_USED },
	/*  80 */	{ "FETCH_R", RES_USED | OP1_USED | OP_FETCH },
	/*  81 */	{ "FETCH_DIM_R", ALL_USED },
	/*  82 */	{ "FETCH_OBJ_R", ALL_USED },
	/*  83 */	{ "FETCH_W", RES_USED | OP1_USED | OP_FETCH },
	/*  84 */	{ "FETCH_DIM_W", ALL_USED },
	/*  85 */	{ "FETCH_OBJ_W", ALL_USED },
	/*  86 */	{ "FETCH_RW", RES_USED | OP1_USED | OP_FETCH },
	/*  87 */	{ "FETCH_DIM_RW", ALL_USED },
	/*  88 */	{ "FETCH_OBJ_RW", ALL_USED },
	/*  89 */	{ "FETCH_IS", ALL_USED },
	/*  90 */	{ "FETCH_DIM_IS", ALL_USED },
	/*  91 */	{ "FETCH_OBJ_IS", ALL_USED },
	/*  92 */	{ "FETCH_FUNC_ARG", RES_USED | OP1_USED | OP_FETCH },
	/*  93 */	{ "FETCH_DIM_FUNC_ARG", ALL_USED },
	/*  94 */	{ "FETCH_OBJ_FUNC_ARG", ALL_USED },
	/*  95 */	{ "FETCH_UNSET", ALL_USED },
	/*  96 */	{ "FETCH_DIM_UNSET", ALL_USED },
	/*  97 */	{ "FETCH_OBJ_UNSET", ALL_USED },
	/*  98 */	{ "FETCH_DIM_TMP_VAR", ALL_USED },
	/*  99 */	{ "FETCH_CONSTANT", ALL_USED },
#if (PHP_MAJOR_VERSION < 5) || (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION < 3)
	/*  100 */	{ "DECLARE_FUNCTION_OR_CLASS", ALL_USED },
#else
	/*  100 */	{ "GOTO", ALL_USED | OP1_OPLINE },
#endif
	/*  101 */	{ "EXT_STMT", ALL_USED },
	/*  102 */	{ "EXT_FCALL_BEGIN", ALL_USED },
	/*  103 */	{ "EXT_FCALL_END", ALL_USED },
	/*  104 */	{ "EXT_NOP", ALL_USED },
	/*  105 */	{ "TICKS", ALL_USED },
	/*  106 */	{ "SEND_VAR_NO_REF", ALL_USED | EXT_VAL },
#ifdef ZEND_ENGINE_2
	/*  107 */	{ "CATCH", ALL_USED | EXT_VAL },
	/*  108 */	{ "THROW", ALL_USED | EXT_VAL },
	
	/*  109 */	{ "FETCH_CLASS", SPECIAL },
	
	/*  110 */	{ "CLONE", ALL_USED },

#if (PHP_MAJOR_VERSION < 5) || (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION <= 2)
	/*  111 */	{ "INIT_CTOR_CALL", ALL_USED },
#else 
# if PHP_VERSION_ID >= 50400
	/*  111 */	{ "RETURN_BY_REF", OP1_USED },
# else 
	/*  111 */	{ "UNKNOWN", ALL_USED },
# endif
#endif
	/*  112 */	{ "INIT_METHOD_CALL", ALL_USED },
	/*  113 */	{ "INIT_STATIC_METHOD_CALL", ALL_USED },
	
	/*  114 */	{ "ISSET_ISEMPTY_VAR", ALL_USED | EXT_VAL },
	/*  115 */	{ "ISSET_ISEMPTY_DIM_OBJ", ALL_USED | EXT_VAL },
	
	/*  116 */	{ "IMPORT_FUNCTION", ALL_USED },
	/*  117 */	{ "IMPORT_CLASS", ALL_USED },
	/*  118 */	{ "IMPORT_CONST", ALL_USED },
	
	/*  119 */	{ "UNKNOWN", ALL_USED },
	/*  120 */	{ "UNKNOWN", ALL_USED },
	
	/*  121 */	{ "ASSIGN_ADD_OBJ", ALL_USED },
	/*  122 */	{ "ASSIGN_SUB_OBJ", ALL_USED },
	/*  123 */	{ "ASSIGN_MUL_OBJ", ALL_USED },
	/*  124 */	{ "ASSIGN_DIV_OBJ", ALL_USED },
	/*  125 */	{ "ASSIGN_MOD_OBJ", ALL_USED },
	/*  126 */	{ "ASSIGN_SL_OBJ", ALL_USED },
	/*  127 */	{ "ASSIGN_SR_OBJ", ALL_USED },
	/*  128 */	{ "ASSIGN_CONCAT_OBJ", ALL_USED },
	/*  129 */	{ "ASSIGN_BW_OR_OBJ", ALL_USED },
	/*  130 */	{ "ASSIGN_BW_AND_OBJ", ALL_USED },
	/*  131 */	{ "ASSIGN_BW_XOR_OBJ", ALL_USED },

	/*  132 */	{ "PRE_INC_OBJ", ALL_USED },
	/*  133 */	{ "PRE_DEC_OBJ", ALL_USED },
	/*  134 */	{ "POST_INC_OBJ", ALL_USED },
	/*  135 */	{ "POST_DEC_OBJ", ALL_USED },

	/*  136 */	{ "ASSIGN_OBJ", ALL_USED },
	/*  137 */	{ "OP_DATA", ALL_USED },
	
	/*  138 */	{ "INSTANCEOF", ALL_USED },
	
	/*  139 */	{ "DECLARE_CLASS", ALL_USED },
	/*  140 */	{ "DECLARE_INHERITED_CLASS", ALL_USED },
	/*  141 */	{ "DECLARE_FUNCTION", ALL_USED },
	
	/*  142 */	{ "RAISE_ABSTRACT_ERROR", ALL_USED },
	
	/*  143 */	{ "DECLARE_CONST", OP1_USED | OP2_USED },
	
	/*  144 */	{ "ADD_INTERFACE", ALL_USED },
	/*  145 */	{ "VERIFY_INSTANCEOF", ALL_USED },
	/*  146 */	{ "VERIFY_ABSTRACT_CLASS", ALL_USED },
	/*  147 */	{ "ASSIGN_DIM", ALL_USED },
	/*  148 */	{ "ISSET_ISEMPTY_PROP_OBJ", ALL_USED },
	/*  149 */	{ "HANDLE_EXCEPTION", NONE_USED },
	/*  150 */	{ "USER_OPCODE", ALL_USED },
	/*  151 */	{ "UNKNOWN", ALL_USED },
	/*  152 */	{ "JMP_SET", ALL_USED | OP2_OPLINE },
	/*  153 */	{ "DECLARE_LAMBDA_FUNCTION", OP1_USED },
	/*  154 */	{ "ADD_TRAIT", ALL_USED },
	/*  155 */	{ "BIND_TRAITS", OP1_USED },
	/*  156 */	{ "SEPARATE", OP1_USED | RES_USED },
	/*  157 */	{ "QM_ASSIGN_VAR", OP1_USED | RES_USED },
	/*  158 */	{ "JMP_SET_VAR", OP1_USED | RES_USED },
	/*  159 */	{ "DISCARD_EXCEPTION", NONE_USED },
	/*  160 */	{ "YIELD", ALL_USED },
	/*  161 */	{ "GENERATOR_RETURN", NONE_USED },
	/*  162 */	{ "FAST_CALL", OP1_USED },
	/*  163 */	{ "FAST_RET", NONE_USED },
#endif
};

#endif