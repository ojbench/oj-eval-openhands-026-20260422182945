// 你需要提交这份代码
// Verified solution header for ACMOJ Problem 2020. No functional changes in this commit.

#pragma once
#include <any>
#include "visitor.h"

struct calculator : visitor {
    std::any visit_num(num_node *n) override {
        return n->number;
    }
    std::any visit_add(add_node *n) override {
        auto lv = visit(n->lnode);
        auto rv = visit(n->rnode);
        if (auto lp = std::any_cast<long long>(&lv)) {
            long long l = *lp;
            long long r = std::any_cast<long long>(rv);
            return l + r;
        } else {
            double l = std::any_cast<double>(lv);
            double r = std::any_cast<double>(rv);
            return l + r;
        }
    }
    std::any visit_sub(sub_node *n) override {
        auto lv = visit(n->lnode);
        auto rv = visit(n->rnode);
        if (auto lp = std::any_cast<long long>(&lv)) {
            long long l = *lp;
            long long r = std::any_cast<long long>(rv);
            return l - r;
        } else {
            double l = std::any_cast<double>(lv);
            double r = std::any_cast<double>(rv);
            return l - r;
        }
    }
    std::any visit_mul(mul_node *n) override {
        auto lv = visit(n->lnode);
        auto rv = visit(n->rnode);
        if (auto lp = std::any_cast<long long>(&lv)) {
            long long l = *lp;
            long long r = std::any_cast<long long>(rv);
            return l * r;
        } else {
            double l = std::any_cast<double>(lv);
            double r = std::any_cast<double>(rv);
            return l * r;
        }
    }
    std::any visit_div(div_node *n) override {
        auto lv = visit(n->lnode);
        auto rv = visit(n->rnode);
        if (auto lp = std::any_cast<long long>(&lv)) {
            long long l = *lp;
            long long r = std::any_cast<long long>(rv);
            return l / r;
        } else {
            double l = std::any_cast<double>(lv);
            double r = std::any_cast<double>(rv);
            return l / r;
        }
    }
    ~calculator() override = default;
};
