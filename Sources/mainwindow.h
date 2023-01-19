#pragma once
#include <QtWidgets/QWidget>
#include <QKeyEvent>
#include <QKeySequence>
#include "ui_qa.h"
#include "RPN.h"
#include "PostfixToResult.h"
#include <string>

class mainwindow : public QWidget, public RPN, public PostfixToResult
{
    Q_OBJECT
public:
    mainwindow(QWidget *parent = nullptr);
    ~mainwindow();

private:
    Ui::qaClass* ui;
    void combination_buttons();

    void resultLabel(const std::string& s);
    void keyPressEvent(QKeyEvent *event);
    void appendToDisplay(const std::string& s);
    void clearAll();
    void calculations();
    void clearOne();

    bool isResultStringNumber(const std::string& s) const;
    RPN * rpn;
    PostfixToResult * postfixtoresult;
};
