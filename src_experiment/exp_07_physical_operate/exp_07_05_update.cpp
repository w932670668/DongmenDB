//
// Created by sam on 2018/9/18.
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
/*TODO: plan_execute_update， update语句执行*/


int ExecutionPlan::executeUpdate(DongmenDB *db, sql_stmt_update *sqlStmtUpdate, Transaction *tx){

    Scan *scan = generateScan(db, sqlStmtUpdate->where, tx);

    int record_num = 0;

    while (scan->next()){
        variant *var = (variant *)calloc(sizeof(variant),1);
        vector<char *> fields = sqlStmtUpdate->fields;
        vector<Expression *> fieldsExpr = sqlStmtUpdate->fieldsExpr;

        for(int i = 0; i < fields.size(); i++) {
            scan->evaluateExpression(fieldsExpr[i], scan, var);
            if(var->type == DATA_TYPE_INT) {
                scan->setInt(string(sqlStmtUpdate->tableName), string(fields[i]), var->intValue);
            } else if(var->type == DATA_TYPE_CHAR) {
                scan->setString(string(sqlStmtUpdate->tableName), string(fields[i]), var->strValue);
            }

            /* 输出原始指定字段的数据
            if(var->type == DATA_TYPE_INT) {
                printf("%s : %d\n", fields[i], scan->getInt(string(sqlStmtUpdate->tableName), string(fields[i])));
            } else if(var->type == DATA_TYPE_CHAR) {
                printf("%s : %s\n", fields[i], scan->getString(string(sqlStmtUpdate->tableName), string(fields[i])).c_str());
            }
            */
            /* 输出要修改的字段的数据
            if(var->type == DATA_TYPE_INT) {
                printf("%s : %d\n", fields[i], var->intValue);
            } else if(var->type == DATA_TYPE_CHAR) {
                printf("%s : %s\n", fields[i], var->strValue);
            }
             */
        }
        record_num += 1;
    }
    return record_num;
};