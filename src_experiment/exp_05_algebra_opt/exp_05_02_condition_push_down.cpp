//
// Created by Sam on 2018/2/13.
//
// Finished by genghanqiang on 2019/10/16
//

#include <algorithm>
#include <relationalalgebra/optimizer.h>

/**
 * 使用关于选择的等价变换规则将条件下推。
 *
 */

/*
 * expr二叉树的节点
 */
typedef struct Node {
    Expression *expr;
    Node *node_left;
    Node *node_right;
} Node;

/*
 * 作为sra_select和sra_join交换时，选择左分支、右分支和不选的结果
 */
typedef enum {
    SRA_JOIN_NO_BRANCH,
    SRA_JOIN_LEFT_BRANCH,
    SRA_JOIN_RIGHT_BRANCH,
} SRAJoinBranch;

/*
 * 建立expr的二叉树
 */
Node *expr_binary_tree_build(Expression *&expr) {
    Node *node_root = (Node *)calloc(1, sizeof(Node));

    if (expr->term != NULL) {
        node_root->expr = expr;
        node_root->node_left = NULL;
        node_root->node_right = NULL;
    } else {
        node_root->expr = expr;

        expr = expr->nextexpr;
        Node *node_left = expr_binary_tree_build(expr);
        expr = expr->nextexpr;
        Node *node_right = expr_binary_tree_build(expr);

        node_root->node_left = node_left;
        node_root->node_right = node_right;
    }


    return node_root;
}

/*
 * 输出建立好的expr的二叉树
 */
void expr_binary_tree_print(Node *node) {
    if (node->expr->term != NULL) {
        printf(" %s ", node->expr->term->val->original_value);
    } else {
        printf("%s", node->expr->getOperatorDesc(node->expr->opType));
    }

    if (node->node_left) {
        expr_binary_tree_print(node->node_left);
    }

    if (node->node_right) {
        expr_binary_tree_print(node->node_right);
    }
}
/*
 * 将expr的二叉树转换成expr
 */

Expression *expr_binary_tree_to_expr(Node *node, Expression *expr) {
    expr = node->expr;
    expr->nextexpr = NULL;

    if (node->node_left) {
        expr->nextexpr = expr_binary_tree_to_expr(node->node_left, expr);
    }

    if (node->node_right) {
        if (expr->nextexpr) {
            expr->nextexpr->nextexpr = expr_binary_tree_to_expr(node->node_right, expr);
        } else {
            expr->nextexpr = expr_binary_tree_to_expr(node->node_right, expr);
        }

    }

    return expr;
}

/*
 * 输出expr
 */
void expr_print(Expression *expr) {
    while (expr) {
        if (expr->term && expr->term->val && expr->term->ref) {
            printf(" %s(%s) ", expr->term->val->original_value, expr->term->ref->tableName);
        } else {
            printf(" %s ", expr->getOperatorDesc(expr->opType));
        }
        expr = expr->nextexpr;
    }
    printf("\n");
}

/*
 * 将expr的二叉树按and拆分
 */
void sra_select_expr_split_binary_tree(Node *node, vector<Node *> &expr_binary_tree_index) {
    if (node->node_left) {
        sra_select_expr_split_binary_tree(node->node_left, expr_binary_tree_index);

        if (node->expr->opType == TOKEN_AND) {
            if (node->node_left && node->node_left->expr->opType != TOKEN_AND) {
                expr_binary_tree_index.push_back(node->node_left);
            }
            node->node_left = NULL;
        }
    }

    if (node->node_right) {
        sra_select_expr_split_binary_tree(node->node_right, expr_binary_tree_index);

        if (node->expr->opType == TOKEN_AND) {
            if (node->node_right && node->node_right->expr->opType != TOKEN_AND) {
                expr_binary_tree_index.push_back(node->node_right);
            }
            node->node_right = NULL;
        }
    }

}

/*
 * 将expr按and拆分
 */
void sra_select_expr_split(Expression *expr, vector<Expression *> &expr_index) {
    vector<Node *> expr_binary_tree_index;
    Node *expr_binary_tree = expr_binary_tree_build(expr);

    sra_select_expr_split_binary_tree(expr_binary_tree, expr_binary_tree_index);
    for(int i = 0; i < expr_binary_tree_index.size(); i++) {
        expr = expr_binary_tree_to_expr(expr_binary_tree_index[i], expr);
        expr_index.push_back(expr);
    }
}

/*
 * 将SRA_SELECT结构拆分成串接的形式，并保存索引
 */

void sra_select_split(SRA_t *sra, vector<SRA_t *> &sra_select_index) {
    switch (sra->t) {
        case SRA_SELECT: {
            // 保存sra_select的下一个sra
            SRA_t *sra_next = sra->select.sra;
            // 保存拆分后的sra_select
            vector<SRA_t *> sra_select_sub_index;
            // 将当前sra_select保存进sra_select集合
            sra_select_sub_index.push_back(sra);
            // 保存拆分后的selec_sra的expr
            vector<Expression *> expr_index;
            // 当前sra_select的expr
            Expression *expr = sra->select.cond;

            sra_select_expr_split(expr, expr_index);

            for (int i = 0; i < expr_index.size(); i++) {
                // 将原始sra_select的cond设为expr集合中的第一个
                if (i == 0) {
                    sra->select.cond = expr_index[i];
                    sra->select.sra = NULL;
                } else {
                    // 将其它的expr用新建的sra_select包裹并将其sra设为null
                    SRA_t *sra_new = SRASelect(NULL, expr_index[i]);
                    sra_select_sub_index.push_back(sra_new);
                }
            }

            // 遍历sra_select_index，将其中的前一个的sra_select的sra设为后一个的sra
            for (int i = 0; i < sra_select_sub_index.size(); i++) {
                // 将sra_select_sub_index中的记录添加到sra_select_index里
                sra_select_index.push_back(sra_select_sub_index[i]);

                if (i == sra_select_sub_index.size() - 1) {
                    sra_select_sub_index[i]->select.sra = sra_next;
                } else {
                    sra_select_sub_index[i]->select.sra = sra_select_sub_index[i + 1];
                }
            }

            sra_select_split(sra_next, sra_select_index);
            break;
        };
        case SRA_TABLE: {
            break;
        };
        case SRA_JOIN: {
            sra_select_split(sra->join.sra1, sra_select_index);
            sra_select_split(sra->join.sra2, sra_select_index);
            break;
        };
        case SRA_PROJECT: {
            sra_select_split(sra->project.sra, sra_select_index);
            break;
        };
        default:{
            break;
        };
    }
}

/*
 * 通过sra获取其在索引中的下标
 */
int get_sra_select_idx_by_sra(SRA_t *sra, vector<SRA_t *> &sra_select_index) {
    for (int i = 0; i < sra_select_index.size(); i++) {
        if (sra_select_index[i] == sra) {
            return i;
        }
    }
    return -1;
}

/*
 * 通过字段名获取其表名
 */

string get_table_name_by_column_name(SRA_t *sra, string column_name, TableManager *tableManager, Transaction *transaction) {
    switch (sra->t) {
        case SRA_SELECT: {
            return get_table_name_by_column_name(sra->select.sra, column_name, tableManager, transaction);
        };
        case SRA_TABLE: {
            TableInfo *table_info = tableManager->table_manager_get_tableinfo(sra->table.ref->table_name, transaction);
            string table_name = "";
            for (int i = 0; i < table_info->fieldsName.size(); i++) {
                if (string(table_info->fieldsName[i]) == column_name) {
                    table_name = table_info->tableName;
                    break;
                }
            }
            return table_name;
        };
        case SRA_JOIN: {
            string table_name = get_table_name_by_column_name(sra->join.sra1, column_name, tableManager, transaction);
            if (table_name == "") {
                return get_table_name_by_column_name(sra->join.sra2, column_name, tableManager, transaction);
            } else {
                return table_name;
            }
        };
        case SRA_PROJECT: {
            return get_table_name_by_column_name(sra->project.sra, column_name, tableManager, transaction);
        }
        default: {
            return "";
        }
    }
}


/*
 * 获取sra_select的表名
 */

void get_sra_select_table_names(SRA_t *sra, vector<string> &table_names, TableManager *tableManager,
                                Transaction *transaction) {
    if (sra->t == SRA_SELECT) {
        Expression *expr = sra->select.cond;

        while (expr) {
            if (expr->term && expr->term->t == TERM_COLREF) {
                if (expr->term->ref->tableName) {
                    table_names.push_back(string(expr->term->ref->tableName));
                } else {
                    string table_name = get_table_name_by_column_name(sra, string(expr->term->ref->columnName), tableManager, transaction);
                    table_names.push_back(table_name);
                }

            }
            expr = expr->nextexpr;
        }
    }
}

/*
 * 获取sra分支所包含的表名
 */

void get_branch_table_names(SRA_t *sra, vector<string> &table_names) {
    switch (sra->t) {
        case SRA_SELECT: {
            if (sra->select.sra) {
                get_branch_table_names(sra->select.sra, table_names);
            }
            break;
        };
        case SRA_TABLE: {
            string table_name = string(sra->table.ref->table_name);
            table_names.push_back(table_name);
            break;
        };
        case SRA_JOIN: {
            if (sra->join.sra1) {
                get_branch_table_names(sra->join.sra1, table_names);
            }
            if (sra->join.sra2) {
                get_branch_table_names(sra->join.sra2, table_names);
            }
            break;
        };
        case SRA_PROJECT: {
            if (sra->project.sra) {
                get_branch_table_names(sra->project.sra, table_names);
            }
            break;
        };
        default:{
            break;
        };
    }
}

/*
 * 检查sra_join的哪条子分支可以交换
 */

SRAJoinBranch check_branch(SRA_t *sra, vector<string> &table_names) {
    if (sra->t == SRA_JOIN) {
        vector<string> left_branch_table_names;
        vector<string> right_branch_table_names;

        get_branch_table_names(sra->join.sra1, left_branch_table_names);
        get_branch_table_names(sra->join.sra2, right_branch_table_names);

        bool all_in_flag = true;
        for (int i = 0; i < table_names.size(); i++) {
            if (count(left_branch_table_names.begin(), left_branch_table_names.end(), table_names[i]) == 0) {
                all_in_flag = false;
                break;
            }
        }
        if (all_in_flag) {
            return SRA_JOIN_LEFT_BRANCH;
        }

        all_in_flag = true;
        for (int i = 0; i < table_names.size(); i++) {
            if (count(right_branch_table_names.begin(), right_branch_table_names.end(), table_names[i]) == 0) {
                all_in_flag = false;
                break;
            }
        }
        if (all_in_flag) {
            return SRA_JOIN_RIGHT_BRANCH;
        }
    }

    return SRA_JOIN_NO_BRANCH;
}


/*
 * 移动sra_select
 */
void sra_select_move(vector<SRA_t *> &sra_select_index, int idx, SRA_t *sra_test, TableManager *tableManager,
                     Transaction *transaction) {
    if (sra_select_index[idx]->t == SRA_SELECT) {
        if (sra_select_index[idx]->select.sra and sra_select_index[idx]->select.sra->t == SRA_SELECT) {
            /*
             * 交换sra_selec, 只需交换其cond并更新索引即可
             */
            
            SRA_Select_t sra_select_temp1 = sra_select_index[idx]->select;
            SRA_Select_t sra_select_temp2 = sra_select_index[idx]->select.sra->select;
            sra_select_index[idx]->select.cond = sra_select_temp2.cond;
            sra_select_index[idx]->select.sra->select.cond = sra_select_temp1.cond;

            sra_select_index[get_sra_select_idx_by_sra(sra_select_index[idx]->select.sra, sra_select_index)] = sra_select_index[idx];
            sra_select_index[idx] = sra_select_index[idx]->select.sra;

            sra_select_move(sra_select_index, idx, sra_test, tableManager, transaction);
        } else if (sra_select_index[idx]->select.sra and sra_select_index[idx]->select.sra->t == SRA_JOIN) {
            /*
             * 交换sra_select和sra_join，重新申请节点内存，设置好信息后覆盖到原内存地址，并更新索引
             */
            
            vector<string> table_names;
            get_sra_select_table_names(sra_select_index[idx], table_names, tableManager, transaction);

            SRAJoinBranch sra_join_branch = check_branch(sra_select_index[idx]->select.sra, table_names);


            if (sra_join_branch == SRA_JOIN_LEFT_BRANCH) {
                JoinCondition_t *sra_join_opt_cond_temp = NULL;
                if (sra_select_index[idx]->select.sra->join.opt_cond) {
                    sra_join_opt_cond_temp = (JoinCondition_t *)calloc(1, sizeof(JoinCondition_t));
                    memmove(sra_join_opt_cond_temp, sra_select_index[idx]->select.sra->join.opt_cond, sizeof(JoinCondition_t));
                }

                SRA_t *sra_join_temp = SRAJoin(sra_select_index[idx]->select.sra, sra_select_index[idx]->select.sra->join.sra2, sra_join_opt_cond_temp);

                Expression *sra_select_cond_temp = NULL;
                if (sra_select_index[idx]->select.cond) {
                    sra_select_cond_temp = (Expression *)calloc(1, sizeof(Expression));
                    memmove(sra_select_cond_temp, sra_select_index[idx]->select.cond, sizeof(Expression));
                }
                SRA_t *sra_select_temp = SRASelect(sra_select_index[idx]->select.sra->join.sra1, sra_select_cond_temp);

                memcpy(sra_select_index[idx]->select.sra, sra_select_temp, sizeof(SRA_t));
                memcpy(sra_select_index[idx], sra_join_temp, sizeof(SRA_t));

                sra_select_index[idx] = sra_select_index[idx]->join.sra1;

                sra_select_move(sra_select_index, idx, sra_test, tableManager, transaction);
            } else if (sra_join_branch == SRA_JOIN_RIGHT_BRANCH) {

                JoinCondition_t *sra_join_opt_cond_temp = NULL;
                if (sra_select_index[idx]->select.sra->join.opt_cond) {
                    sra_join_opt_cond_temp = (JoinCondition_t *)calloc(1, sizeof(JoinCondition_t));
                    memmove(sra_join_opt_cond_temp, sra_select_index[idx]->select.sra->join.opt_cond, sizeof(JoinCondition_t));
                }

                SRA_t *sra_join_temp = SRAJoin(sra_select_index[idx]->select.sra->join.sra1, sra_select_index[idx]->select.sra, sra_join_opt_cond_temp);

                Expression *sra_select_cond_temp = NULL;
                if (sra_select_index[idx]->select.cond) {
                    sra_select_cond_temp = (Expression *)calloc(1, sizeof(Expression));
                    memmove(sra_select_cond_temp, sra_select_index[idx]->select.cond, sizeof(Expression));
                }
                SRA_t *sra_select_temp = SRASelect(sra_select_index[idx]->select.sra->join.sra2, sra_select_cond_temp);

                memcpy(sra_select_index[idx]->select.sra, sra_select_temp, sizeof(SRA_t));
                memcpy(sra_select_index[idx], sra_join_temp, sizeof(SRA_t));

                sra_select_index[idx] = sra_select_index[idx]->join.sra2;

                sra_select_move(sra_select_index, idx, sra_test, tableManager, transaction);

            }

        }
    }
}

/*
 * 将sra_select移动到语法树最优的位置
 */
void sra_select_optimize(SRA_t *sra, vector<SRA_t *> &sra_select_index, TableManager *tableManager,
                         Transaction *transaction) {
    for(int i = 0; i < sra_select_index.size(); i++) {
        sra_select_move(sra_select_index, i, sra, tableManager, transaction);
    }
}


/*输入一个关系代数表达式，输出优化后的关系代数表达式
 * 要求：在查询条件符合合取范式的前提下，根据等价变换规则将查询条件移动至合适的位置。
 * */
SRA_t *
dongmengdb_algebra_optimize_condition_pushdown(SRA_t *sra, TableManager *tableManager, Transaction *transaction) {

    /*初始关系代数语法树sra由三个操作构成：SRA_PROJECT -> SRA_SELECT -> SRA_JOIN，即对应语法树中三个节点。*/

    /*第一步：.等价变换：将SRA_SELECT类型的节点进行条件串接*/

        /*1.1 在sra中找到每个SRA_Select节点 */
        /*1.2 检查每个SRA_Select节点中的条件是不是满足串接条件：多条件且用and连接*/
        /*1.3 若满足串接条件则：创建一组新的串接的SRA_Select节点，等价替换当前的SRA_Select节点*/

    /*第二步：等价变换：条件交换*/
        /*2.1 在sra中找到每个SRA_Select节点*/
        /*2.2 对每个SRA_Select节点做以下处理：
         * 在sra中查找 SRA_Select 节点应该在的最优位置：
         *     若子操作也是SRA_Select，则可交换；
         *     若子操作是笛卡尔积，则可交换，需要判断SRA_Select所包含的属性属于笛卡尔积的哪个子操作
         * 最后将SRA_Select类型的节点移动到语法树的最优位置。
         * */

    // SRA根节点
    SRA_t *sra_root = sra;
    // SRA_SELECT的索引
    vector<SRA_t *> sra_select_index;
    // 拆分sra_select
    sra_select_split(sra_root, sra_select_index);
    // 移动sra_select至最优位置
    printf("\n===before===\n");
    SRA_print(sra_root);
    printf("\n============\n");
    sra_select_optimize(sra_root, sra_select_index, tableManager, transaction);
    printf("\n===after===\n");
    SRA_print(sra_root);
    printf("\n===========\n");


    return sra_root;
}