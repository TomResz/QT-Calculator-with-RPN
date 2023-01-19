#include "mainwindow.h"

mainwindow::mainwindow(QWidget* parent) : QWidget(parent), ui(new Ui::qaClass), rpn(new RPN) , postfixtoresult(new PostfixToResult) // constructor
{
    ui->setupUi(this);
    combination_buttons();
}    

mainwindow::~mainwindow() // destructor
{
    delete rpn;
    delete postfixtoresult;
    delete ui;
}
void mainwindow::combination_buttons() // wlaczenie przyciskow, tak aby mozna bylo wrzucac poszczegolne elementy na input display
{
    connect(ui->pushButton_0, &QPushButton::clicked, [=]() { appendToDisplay("0");  });
    connect(ui->pushButton_1, &QPushButton::clicked, [=]() {appendToDisplay("1");  });
    connect(ui->pushButton_2, &QPushButton::clicked, [=]() {appendToDisplay("2");  });
    connect(ui->pushButton_3, &QPushButton::clicked, [=]() {appendToDisplay("3");  });
    connect(ui->pushButton_4, &QPushButton::clicked, [=]() {appendToDisplay("4");  });
    connect(ui->pushButton_5, &QPushButton::clicked, [=]() {appendToDisplay("5");  });
    connect(ui->pushButton_6, &QPushButton::clicked, [=]() {appendToDisplay("6");  });
    connect(ui->pushButton_7, &QPushButton::clicked, [=]()  {appendToDisplay("7");  });
    connect(ui->pushButton_8, &QPushButton::clicked, [=]()  {appendToDisplay("8");  });
    connect(ui->pushButton_9, &QPushButton::clicked, [=]()  {appendToDisplay("9");  });
    connect(ui->pushButton_add, &QPushButton::clicked, [=]()  {appendToDisplay(" + "); });
    connect(ui->pushButton_dot, &QPushButton::clicked, [=]()  {appendToDisplay(".");  });
    connect(ui->pushButton_subtraction, &QPushButton::clicked, [=]()  {appendToDisplay(" - "); });
    connect(ui->pushButton_devide, &QPushButton::clicked, [=]()  {appendToDisplay(" / "); });
    connect(ui->pushButton_multiplicattion, &QPushButton::clicked, [=]()  {appendToDisplay(" * "); });
    connect(ui->pushButton_arcctg, &QPushButton::clicked, [=]()  {appendToDisplay(" arcctg(");  });
    connect(ui->pushButton_arcos, &QPushButton::clicked, [=]()  {appendToDisplay(" arccos(");   });
    connect(ui->pushButton_arctg, &QPushButton::clicked, [=]()  {appendToDisplay(" arctg(");  });
    connect(ui->pushButton_arsin, &QPushButton::clicked, [=]()  {appendToDisplay(" arcsin(");    });
    connect(ui->pushButton_cos, &QPushButton::clicked, [=]()  {appendToDisplay(" cos(");   });
    connect(ui->pushButton_cot, &QPushButton::clicked, [=]()  {appendToDisplay(" ctg("); });
    connect(ui->pushButton_clear, &QPushButton::clicked, [=]()  { clearAll(); });
    connect(ui->pushButton_tan, &QPushButton::clicked, [=]()  {appendToDisplay(" tg(");  });
    connect(ui->pushButton_sqrt, &QPushButton::clicked, [=]()  {appendToDisplay(" sqrt(");   });
    connect(ui->pushButton_sin, &QPushButton::clicked, [=]()  {appendToDisplay(" sin(");   });
    connect(ui->pushButton_power, &QPushButton::clicked, [=]()  {appendToDisplay(" ^ ");  });
    connect(ui->pushButton_left, &QPushButton::clicked, [=]()  {appendToDisplay("(");  });
    connect(ui->pushButton_right, &QPushButton::clicked, [=]()  {appendToDisplay(")");  });
    connect(ui->pushButton_clearone, &QPushButton::clicked, [=]()  {clearOne(); });
    connect(ui->pushButton_equal, &QPushButton::clicked, [=]() { calculations(); });
}

void mainwindow::resultLabel(const std::string& s)
{
    ui->label->setText(QString::fromStdString(s));
}
void mainwindow::appendToDisplay(const std::string& s) // wrzucanie symboli na ekran
{
    ui->display->setText(ui->display->text().append(QString::fromStdString(s))); // dodawanie po kolei elementow na wyswietlacz
}

void mainwindow::clearOne() // usuwanie pojedynczych elementow z wyswietlacza, domyslnie jest usuwa jeden char
{
    int length = ui->display->text().size(); 
    if (length > 0){    ui->display->setText(ui->display->text().chopped(1));   }
    else {   return; }
}
bool mainwindow::isResultStringNumber(const std::string& s) const
{
    auto result = double();
    auto i = std::istringstream(s);
    i >> result;
    return !i.fail() && i.eof();
}
void mainwindow::clearAll() // przycisk CA
{
    ui->display->setText("");
    ui->label->setText("");

}
void mainwindow::calculations() // tu bedzie po kolei odbywal sie proces obliczen
{
    std::string stringFromDisplay(ui->display->text().toUtf8().data()); // expression from display to std::string
    if (stringFromDisplay.size() == 0) 
    {
        return;
    }
    else 
    {
        clearAll();
        rpn->setter(stringFromDisplay);
        std::string statusString = rpn->resultToString(0); // sprawdzanie czy podane wyrazenie jest poprawne
        if (statusString != "correct")
        {
            resultLabel(statusString);
            rpn->clear();
        }
        else
        {
            auto postfixVec = rpn->infixToPostfix();
            double result = postfixtoresult->toResult(postfixVec);
            std::string resultString = postfixtoresult->resultToString(result);
            if (isResultStringNumber(resultString))
            {
                appendToDisplay(resultString); // string do wyswietlacza
            }
            resultLabel(stringFromDisplay+" = "+resultString);
            rpn->clear();
            postfixtoresult->clear();
        }
    }

}

void mainwindow::keyPressEvent(QKeyEvent *event) // wprowadzanie danych na wyswietlacz z klawiatury ( liczby i operatory podstawowe tj. + - * ^ /)
{
    switch (event->key())
    {
    case Qt::Key_0: appendToDisplay("0");
        break;
    case Qt::Key_1: appendToDisplay("1");
        break;
    case Qt::Key_2: appendToDisplay("2");
        break;
    case Qt::Key_3: appendToDisplay("3");
        break;
    case Qt::Key_4: appendToDisplay("4");
        break;
    case Qt::Key_5: appendToDisplay("5");
        break;
    case Qt::Key_6: appendToDisplay("6");
        break;
    case Qt::Key_7: appendToDisplay("7");
        break;
    case Qt::Key_8: appendToDisplay("8");
        break;
    case Qt::Key_9: appendToDisplay("9");
        break;
    case Qt::Key_Plus: appendToDisplay(" + ");
        break;
    case Qt::Key_Minus: appendToDisplay(" - ");
        break;
    case Qt::Key_Asterisk: appendToDisplay(" * ");
        break;
    case Qt::Key_Slash: appendToDisplay(" / ");
        break;
    case Qt::Key_AsciiCircum: appendToDisplay(" ^ ");
        break;
    case Qt::Key_Period: appendToDisplay(".");
        break;
    case Qt::Key_Comma: appendToDisplay(".");
        break;
    case Qt::Key_ParenLeft: appendToDisplay("(");
        break;
    case Qt::Key_ParenRight: appendToDisplay(")");
        break;
    case Qt::Key_Backspace: clearOne(); // backspace
        break;
    case Qt::Key_Equal: calculations(); // =
        break;
    case Qt::Key_Return: calculations(); // enter
        break;
    case Qt::Key_C: clearAll(); // key c
        break;
    }
}