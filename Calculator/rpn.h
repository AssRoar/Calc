#ifndef RPN_H
#define RPN_H

#include <QObject>
#include <QStack>
#include <math.h>
#include <QDebug>
#include <QStandardItemModel>

class rpn : public QObject
{
    Q_OBJECT
public:
    explicit rpn(QObject *parent = 0);
    ~rpn();
    QStandardItemModel *model;
    void setModel(QStandardItemModel *value);
    QString GetExpression(QString input); //Метод, преобразующий входную строку с выражением в постфиксную запись
    QString logConvertloglog(QString input);

    double Counting(QString input);//Метод, вычисляющий значение выражения, уже преобразованного в постфиксную запись
    static bool IsDelimeter(QString c);//Метод возвращает true, если проверяемый символ - разделитель ("пробел" или "равно")
    static bool IsOperator(QString c);//Метод возвращает true, если проверяемый символ - оператор
    static int GetPriority(QString s);//Метод возвращает приоритет оператора

     double sinn(double x);
     double coss(double x);
     double tgg(double x);
     double ctgg(double x);
     double fabs_my(double x);
     double powMy(double x, double n);
     double powMyint(double x, int n);
     double exp1(double x);
     double my_log(double x);
    bool radianGrad;

signals:
    void signError(QString err);


};

#endif // RPN_H
