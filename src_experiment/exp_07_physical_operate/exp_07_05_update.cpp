//
// Created by sam on 2018/9/18.
//
// Finished by genghanqiang on 2019/10/09
//

#include <physicalplan/ExecutionPlan.h>
#include <physicalplan/TableScan.h>
#include <physicalplan/Select.h>
#include <physicalplan/Project.h>
#include <physicalplan/Join.h>
/*执行 update 语句的物理计划，返回修改的记录条数
 * 返回大于等于0的值，表示修改的记录条数；
 * 返回小于0的值，表示修改过程中出现错误。
 * */


int ExecutionPlan::executeUpdate(DongmenDB *db, sql_stmt_update *sqlStmtUpdate, Transaction *tx){

    // 创建Scan，获取满足关系代数的记录
    Scan *scan = generateScan(db, sqlStmtUpdate->where, tx);

    // 总记录条数
    int record_num = 0;

    while (scan->next()){
        // 创建结果变量
        variant *var = (variant *)calloc(sizeof(variant),1);
        // 获取字段名
        vector<char *> fields = sqlStmtUpdate->fields;
        // 获取字段表达式
        vector<Expression *> fieldsExpr = sqlStmtUpdate->fieldsExpr;

        for(int i = 0; i < fields.size(); i++) {
            // 计算字段表达式的值
            scan->evaluateExpression(fieldsExpr[i], scan, var);

            // 根据字段类型设置字段的值
            if(var->type == DATA_TYPE_INT) {
                scan->setInt(string(sqlStmtUpdate->tableName), string(fields[i]), var->intValue);
            } else if(var->type == DATA_TYPE_CHAR) {
                scan->setString(string(sqlStmtUpdate->tableName), string(fields[i]), var->strValue);
            }
        }
        record_num += 1;
    }

    scan->close();
    return record_num;
};