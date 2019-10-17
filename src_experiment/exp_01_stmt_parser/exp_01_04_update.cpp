//
// Created by Sam on 2018/2/13.
//
// Finished by genghanqiang on 2019/10/09
//


#include <dongmensql/sqlstatement.h>
#include <parser/StatementParser.h>

/**
 * 在现有实现基础上，实现update from子句
 *
 * 支持的update语法：
 *
 * UPDATE <table_name> SET <field1> = <expr1>[, <field2 = <expr2>, ..]
 * WHERE <logical_expr>
 *
 * 解析获得 sql_stmt_update 结构
 */

sql_stmt_update *UpdateParser::parse_sql_stmt_update() {
    char *tableName;
    vector<char*> fields; //set fields 被更新的字段列表
    vector<Expression*> fieldsExpr;  //set fields expression 新值(表达式)列表
    SRA_t *where;

    // 匹配关键字update
    if (!this->matchToken( TOKEN_RESERVED_WORD, "update")) {
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

    // 匹配关键字set
    token = this->parseNextToken();
    if (!this->matchToken( TOKEN_RESERVED_WORD, "set")) {
        strcpy(this->parserMessage, "invalid sql: should be set.");
        return NULL;
    }

    // 获取field
    token = this->parseNextToken();
    if (!token || token->type != TOKEN_WORD) {
        strcpy(this->parserMessage, "invalid sql: missing field name.");
        return NULL;
    }

    char *field = new_id_name();
    strcpy(field, token->text);
    fields.push_back(field);
    this->parseEatToken();

    // 匹配=
    token = this->parseNextToken();
    if (!token || token->type != TOKEN_EQ) {
        strcpy(this->parserMessage, "invalid sql: missing =.");
        return NULL;
    }
    this->parseEatToken();

    // 获取fieldExpr
    Expression *expr = this->parseExpressionRD();
    fieldsExpr.push_back(expr);

    token = this->parseNextToken();


    while (token && token->type == TOKEN_COMMA) {
        this->parseEatToken();
        token = this->parseNextToken();
        if (!token || token->type != TOKEN_WORD) {
            strcpy(this->parserMessage, "invalid sql: missing field.");
            return NULL;
        }

        char *field = new_id_name();
        strcpy(field, token->text);
        fields.push_back(field);
        this->parseEatToken();

        // 匹配=
        token = this->parseNextToken();
        if (!token || token->type != TOKEN_EQ) {
            strcpy(this->parserMessage, "invalid sql: missing =.");
            return NULL;
        }
        this->parseEatToken();

        // 获取fieldExpr
        Expression *expr = this->parseExpressionRD();
        if (!expr) {
            return NULL;
        }
        fieldsExpr.push_back(expr);
        token = this->parseNextToken();
    }

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



    // 返回sql_stmt_update结构
    sql_stmt_update *sqlStmtUpdate = (sql_stmt_update *)calloc(sizeof(sql_stmt_update),1);
    sqlStmtUpdate->tableName = tableName;
    sqlStmtUpdate->fields = fields;
    sqlStmtUpdate->fieldsExpr = fieldsExpr;
    sqlStmtUpdate->where = where;

    return sqlStmtUpdate;
};
