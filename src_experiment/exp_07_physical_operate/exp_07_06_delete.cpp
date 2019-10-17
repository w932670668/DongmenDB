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

/*执行delete语句的物理计划，返回删除的记录条数
 * 返回大于等于0的值，表示删除的记录条数；
 * 返回小于0的值，表示删除过程中出现错误。
 * */

int ExecutionPlan::executeDelete(DongmenDB *db, sql_stmt_delete *sqlStmtDelete, Transaction *tx){

    // 创建Scan，获取满足关系代数的记录
    Scan *scan = generateScan(db, sqlStmtDelete->where, tx);

    // 总记录条数
    int record_num = 0;

    while (scan->next()) {
        // 删除记录
        scan->deleteRecord();
        record_num += 1;
    }

    scan->close();
    return record_num;
};