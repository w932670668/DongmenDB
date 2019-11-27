//
// Created by Sam on 2018/2/13.
//
// Finished by genghanqiang on 2019/10/09
//

#include <dongmensql/sqlstatement.h>
#include <parser/StatementParser.h>

/**
 * 在现有实现基础上，实现delete from子句
 *
 *  支持的delete语法：
 *
 *  DELETE FROM <table_name>
 *  WHERE <logical_expr>
 *
 * 解析获得 sql_stmt_delete 结构
 */

sql_stmt_delete *DeleteParser::parse_sql_stmt_delete(){
    char *tableName;
    SRA_t *where;

    //匹配关键字delete
    if (!this->matchToken( TOKEN_RESERVED_WORD, "delete")) {
        return NULL;
    }

    // 获取表名
    Token *token = this->parseNextToken();
    if (token && token->type == TOKEN_WORD) {
        tableName = new_id_name();
        strcpy(tableName, token->text);
    } else {
        strcpy(this->parserMessage, "invalid sql: missing table name.");
        return NULL;
    }
    this->parseEatToken();

    // 匹配where
    token = this->parseNextToken();
    TableReference_t *ref = TableReference_make(tableName, NULL);
    SRA_t *sra = SRATable(ref);
    if (this->matchToken( TOKEN_RESERVED_WORD, "where")) {
        // 匹配where子句
        Expression *expr = this->parseExpressionRD();
        if (!expr) {
            return NULL;
        }
        sra = SRASelect(sra, expr);
    }

    where = sra;

    // 返回sql_stmt_delete结构
    sql_stmt_delete *sqlStmtDelete = (sql_stmt_delete *)calloc(sizeof(sql_stmt_delete),1);
    sqlStmtDelete->tableName = tableName;
    sqlStmtDelete->where = where;

    return sqlStmtDelete;
};