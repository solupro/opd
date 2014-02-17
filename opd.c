#include <stdio.h>
#include "opd.h"
#include "sapi/embed/php_embed.h"
#include "ext/standard/url.h"

#define BUFFER_LEN 40

#if PHP_VERSION_ID >= 50399
# define OPD_ZNODE znode_op
# define OPD_ZNODE_ELEM(node,var) node.var
# define OPD_TYPE(t) t##_type
# define OPD_EXTENDED_VALUE(o) extended_value
#else
# define OPD_ZNODE znode
# define OPD_ZNODE_ELEM(node,var) node.u.var
# define OPD_TYPE(t) t.op_type
# define OPD_EXTENDED_VALUE(o) o.u.EA.type
#endif

#if PHP_VERSION_ID >= 50500
# define VAR_NUM(v) ((zend_uint)(EX_TMP_VAR_NUM(0, 0) - EX_TMP_VAR(0, v)))
#else
# define VAR_NUM(v) ((v)/(sizeof(temp_variable)))
#endif

static char *format_zval(zval *z) {
    static char buffer[BUFFER_LEN];
    char *new_str;
    int new_len;

    switch(Z_TYPE_P(z)) {
        case IS_NULL:
            return "NULL";
        case IS_LONG:
        case IS_BOOL:
            snprintf(buffer, BUFFER_LEN, "%d", z->value.lval);
            return buffer;
        case IS_DOUBLE:
            snprintf(buffer, BUFFER_LEN, "%f", z->value.dval);
            return buffer;
        case IS_STRING:
            new_str = php_url_encode(z->value.str.val, z->value.str.len, &new_len);
            snprintf(buffer, BUFFER_LEN, "\"%s\"", new_str);
            efree(new_str);
            return buffer;
        case IS_ARRAY:
        case IS_OBJECT:
        case IS_RESOURCE:
        case IS_CONSTANT:
        case IS_CONSTANT_ARRAY:
            return "";
        default:
            return "unknow";
    }
}

static char *format_znode(OPD_ZNODE n, unsigned int node_type, zend_uint base_address) {
    static char buffer[BUFFER_LEN];
    
    switch(node_type) {
    /*
        case IS_UNUSED:
            snprintf(buffer, BUFFER_LEN, "%s", " IS_UNUSED ");
            return buffer;
            break;
    */
        case IS_CONST:
#if PHP_VERSION_ID >= 50399
            return format_zval(n.zv);
#else  
            return format_zval(&n.u.constant);
#endif
            break;
#ifdef ZEND_ENGINE_2
        case IS_VAR:
            snprintf(buffer, BUFFER_LEN, "$%d", VAR_NUM(OPD_ZNODE_ELEM(n, var)));
            return buffer;
            break;
        case IS_TMP_VAR:
            snprintf(buffer, BUFFER_LEN, "~$%d", VAR_NUM(OPD_ZNODE_ELEM(n, var)));
            return buffer;
            break;
#if (PHP_MAJOR_VERSION > 5) || (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION >= 1)
        case IS_CV:
            snprintf(buffer, BUFFER_LEN, "!%d", VAR_NUM(OPD_ZNODE_ELEM(n, var)));
            return buffer;
            break;
#endif
        case OPD_IS_OPNUM:
            snprintf(buffer, BUFFER_LEN, "->%d", OPD_ZNODE_ELEM(n, opline_num));
            return buffer;
            break;
        case OPD_IS_OPLINE:
            snprintf(buffer, BUFFER_LEN, "->%d", (OPD_ZNODE_ELEM(n, opline_num) - base_address) / sizeof(zend_op));
            return buffer;
            break;
        case OPD_IS_CLASS:
            snprintf(buffer, BUFFER_LEN, ":%d", VAR_NUM(OPD_ZNODE_ELEM(n, var)));
            return buffer;
            break;
#else
        case IS_TMP_VAR: /* 2 */
            snprintf(buffer, BUFFER_LEN, "~%d", n.u.var);
            return buffer;
            break;
        case IS_VAR: /* 4 */
            snprintf(buffer, BUFFER_LEN, "$%d", n.u.var);
            return buffer;
            break;           
        case OPD_IS_OPNUM:
        case OPD_IS_OPLINE:
            snprintf(buffer, BUFFER_LEN, "->%d", n.u.opline_num);
            return buffer;
            break;
        case OPD_IS_CLASS:
            snprintf(buffer, BUFFER_LEN, ":%d", n.u.var);
            return buffer;
            break;
#endif
        default:
            return "";
            break;
    }
}

static char *opname(zend_uchar opcode) {
    return opcodes[opcode].name;
}

static zend_uint vld_get_special_flags(const zend_op *op, zend_uint base_address) {
    zend_uint flags = 0;

    switch (op->opcode) {
        case ZEND_FE_RESET:
            flags = ALL_USED;
#if (PHP_MAJOR_VERSION > 5) || (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION >= 1)
            flags |= OP2_OPNUM;
#elif (PHP_MAJOR_VERSION > 4) || (PHP_MAJOR_VERSION == 4 && PHP_MINOR_VERSION > 3) || (PHP_MAJOR_VERSION == 4 && PHP_MINOR_VERSION == 3 && PHP_RELEASE_VERSION >= 11)
            flags |= NOP2_OPNUM;
#endif
            break;

        case ZEND_ASSIGN_REF:
            flags = OP1_USED | OP2_USED;
            if (op->OPD_TYPE(result) != IS_UNUSED) {
                flags |= RES_USED;
            }
            break;

        case ZEND_DO_FCALL_BY_NAME:
        case ZEND_DO_FCALL:
            flags = OP1_USED | RES_USED | EXT_VAL;
            /*flags = ALL_USED | EXT_VAL;
            op->op2.op_type = IS_CONST;
            op->op2.u.constant.type = IS_LONG;*/
            break;

        case ZEND_INIT_FCALL_BY_NAME:
            flags = OP2_USED;
            if (op->OPD_TYPE(op1) != IS_UNUSED) {
                flags |= OP1_USED;
            }
            break;

        case ZEND_JMPZNZ:
            flags = OP1_USED | OP2_USED | EXT_VAL | OP2_OPNUM;
//          op->result = op->op1;
            break;

#if (PHP_MAJOR_VERSION < 5) || (PHP_MAJOR_VERSION == 5 && PHP_MINOR_VERSION < 1)
        case ZEND_JMP_NO_CTOR:
            flags = OP2_USED | OP2_OPNUM;
            if (op->OPD_TYPE(op1) != IS_UNUSED) {
                flags |= OP1_USED;
            }
            break;
#endif

#ifdef ZEND_ENGINE_2
        case ZEND_FETCH_CLASS:
            flags = EXT_VAL|RES_USED|OP2_USED|RES_CLASS;
            break;
#endif

        case ZEND_NEW:
            flags = RES_USED|OP1_USED;
#ifdef ZEND_ENGINE_2
            flags |= OP1_CLASS;
#endif
            break;

        case ZEND_BRK:
        case ZEND_CONT:
            flags = OP2_USED|OP2_BRK_CONT;
            break;

    }
    return flags;
}

#define NUM_KNOWN_OPCODES (sizeof(opcodes)/sizeof(opcodes[0]))

static void dump_op(zend_op *ops, int num, zend_uint base_address) {
    const zend_op op = ops[num];
    unsigned int flags, op1_type, op2_type, res_type;

    if (op.opcode >= NUM_KNOWN_OPCODES) {
        flags = ALL_USED;
    } else {
        flags = opcodes[op.opcode].flags;
    }

    op1_type = op.OPD_TYPE(op1);
    op2_type = op.OPD_TYPE(op2);
    res_type = op.OPD_TYPE(result);

    if (flags == SPECIAL) {
        flags = vld_get_special_flags(&op, base_address);
    } else {
        if (flags & OP1_OPLINE) {
            op1_type = OPD_IS_OPLINE;
        }
        if (flags & OP2_OPLINE) {
            op2_type = OPD_IS_OPLINE;
        }
    }
    if (flags & OP1_OPNUM) {
        op1_type = OPD_IS_OPNUM;
    }
    if (flags & OP2_OPNUM) {
        op2_type = OPD_IS_OPNUM;
    }
    if (flags & OP1_CLASS) {
        op1_type = OPD_IS_CLASS;
    }
    if (flags & RES_CLASS) {
        res_type = OPD_IS_CLASS;
    }

    char *op1_info, *op2_info, *res_info;

    op1_info = estrdup(format_znode(op.op1, op1_type, base_address));        
    op2_info = estrdup(format_znode(op.op2, op2_type, base_address));        
    res_info = estrdup(format_znode(op.result, res_type, base_address));        

    printf("%d\t%d\t%s\t%s\t%s\t%s\n", num, op.lineno,         \
        opname(op.opcode), op1_info, op2_info, res_info);

    efree(op1_info);   
    efree(op2_info);   
    efree(res_info);   
}

static void dump_op_array(zend_op_array *op_array) {
    zend_uint base_address = (zend_uint) &(op_array->opcodes[0]);
    if (op_array) {
        int i;
        printf("%s\t%s\t%s\t%s\t%s\t%s\n", "opnum", "line", "opcode", "op1", "op2", "result");
        for (i = 0; i < op_array->last; i++) {
            dump_op(op_array->opcodes, i, base_address);
        }
    }    
}

int main(int argc, char *argv[]) {
    zend_op_array *op_array;
    zend_file_handle file_handle;

    if (argc != 2) {
        printf("usage: opd <script>\n");
        return 1;
    }

    PHP_EMBED_START_BLOCK(argc, argv);
    printf("Script: %s\n", argv[1]);
    file_handle.filename = argv[1];
    file_handle.free_filename = 0;
    file_handle.type = ZEND_HANDLE_FILENAME;
    file_handle.opened_path = NULL;
    op_array = zend_compile_file(&file_handle, ZEND_INCLUDE TSRMLS_CC);
    if (!op_array) {
        printf("Error parsing script: %s\n", file_handle.filename);
        return 1;
    }
    dump_op_array(op_array);
    PHP_EMBED_END_BLOCK();

    return 0;
}
