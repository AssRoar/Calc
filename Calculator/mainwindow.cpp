#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsEffect>

void MainWindow::setFormStyle()
{
    // Скрываем элементы управления и рамку окна...
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);

    // Включаем прозрачность главной формы...
    setAttribute(Qt::WA_TranslucentBackground);

    // Задаём параметры прозрачности...
    QGraphicsDropShadowEffect* shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect -> setBlurRadius(9.0);
    shadowEffect -> setColor(QColor(0, 0, 0, 160));
    shadowEffect -> setOffset(4.0);
    ui -> centralWidget -> setGraphicsEffect(shadowEffect);
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    this->setFormStyle();
    setWindowOpacity( 0.95 );


    connect(ui->action,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->btn_clear,SIGNAL(clicked()),ui->lineEdit,SLOT(clear()));//Очистка line

    ui->lineEdit->setText("0");
    model = new QStandardItemModel(100,2,this);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Название переменной"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Значение"));
    ui->tableView->setModel(model);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
    // ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows); // режим выделения строк
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers); // для невозможности изменения
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(dataChangeModel(QModelIndex)));
    connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(getId(QModelIndex)));
    idModel=0;

    connect(&Rpn,SIGNAL(signError(QString)),this, SLOT(messageError(QString)));
    ui->radioButton->setChecked(true);
    Rpn.radianGrad=true;

//    ui->centralWidget->setGraphicsEffect(shadowEffect);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//Сообщение об ошибках
void MainWindow::messageError(QString err)
{
    QMessageBox::warning(this,"Ошибка", err);
}

//Записываем в переменную класса id выбранной записи
void MainWindow::getId(QModelIndex index)
{
    idModel = index.row();
}

void MainWindow::dataChangeModel(QModelIndex index)
{
    disconnect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(dataChangeModel(QModelIndex)));
    if(index.column()==1){
        bool ok = true;
        model->data(index).toDouble(&ok);
        if(!ok)
            model->setData(index,"");
    }
    if(index.column()==0){
        bool ok = true;
        model->data(index).toInt(&ok);
        if(ok)
            model->setData(index,"");

        QRegExp reg("[0-9A-Za-z]{1,5}");
        if(!reg.exactMatch(model->data(index).toString()))
            model->setData(index,"");
        if(model->data(index).toString()=="sin" || model->data(index).toString() == "cos"|| model->data(index).toString() == "tg"
                || model->data(index).toString() == "ctg" || model->data(index).toString() == "exp"|| model->data(index).toString() == "pi")
            model->setData(index,"");

        //Поиск одинаковых переменных
        if(!model->findItems(model->data(index).toString()).isEmpty()){
            if(model->findItems(model->data(index).toString()).at(0)->row()!=index.row())
                model->setData(index,"");
        }
    }

    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(dataChangeModel(QModelIndex)));
}

//=
void MainWindow::on_btn_equal_clicked()
{
    QString virazh = ui->lineEdit->text();

    if(virazh.count()>0){//Если выражение не пустое
        if(virazh.count('[')!=virazh.count(']'))
        {
            messageError("Закройте скобки");
            return;
        }
        if(virazh.count('[')!=virazh.count(']'))
        {
            messageError("Закройте скобки");
            return;
        }

        Rpn.setModel(model);

        QString output = Rpn.GetExpression(virazh); //Преобразовываем выражение в постфиксную запись
        ui->lineEdit_2->setText(output);
        double result = Rpn.Counting(output); //Решаем полученное выражение

        ui->lineEdit_2->setText(ui->lineEdit_2->text() + "=" + QString::number(result, 'g', 17)); //Считываем, и выводи
    }
}

//0
void MainWindow::on_btn_0_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "0");
}
//1
void MainWindow::on_btn_1_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "1");
}
//2
void MainWindow::on_btn_2_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "2");
}
//3
void MainWindow::on_btn_3_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "3");
}
//4
void MainWindow::on_btn_4_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "4");
}
//5
void MainWindow::on_btn_5_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "5");
}
//6
void MainWindow::on_btn_6_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "6");
}
//7
void MainWindow::on_btn_7_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "7");
}
//8
void MainWindow::on_btn_8_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "8");
}
//9
void MainWindow::on_btn_9_clicked()
{
    ui->lineEdit->setText(ui->lineEdit->text() + "9");
}
//^
void MainWindow::on_btn_stepen_clicked()
{
    QString str = ui->lineEdit->text();

    if(str.count()==0){//Если выражение пустое выходим
        QMessageBox::warning(this, "Не надо так", "ъеъ");
        return;
    }

    if(QString(str[str.count()-1])==")"){
        ui->lineEdit->setText(ui->lineEdit->text() + "^");
        return;
    }

    if(rpn::IsOperator(QString(str[str.count()-1]))){
        QMessageBox::warning(this, "Не надо так", "ъеъ");
        return;
    }
    ui->lineEdit->setText(ui->lineEdit->text() + "^");
}
//
void MainWindow::on_btn_razdel_clicked()
{
    QString str = ui->lineEdit->text();

    if(str.count()==0){ //Если выражение пустое выходим
        QMessageBox::warning(this, "Не надо так", "ъеъ");
        return;
    }


    if(QString(str[str.count()-1])==")"){
        ui->lineEdit->setText(ui->lineEdit->text() + "/");
        return;
    }

    if(rpn::IsOperator(QString(str[str.count()-1]))){
        QMessageBox::warning(this, "Не надо так", "ъеъ");
        return;
    }
    ui->lineEdit->setText(ui->lineEdit->text() + "/");
}
//*
void MainWindow::on_btn_umnozh_clicked()
{
    QString str = ui->lineEdit->text();

    if(str.count()==0){ //Если выражение пустое выходим
        QMessageBox::warning(this, "Не надо так", "ъеъ");
        return;
    }

    if(QString(str[str.count()-1])==")"){
        ui->lineEdit->setText(ui->lineEdit->text() + "*");
        return;
    }

    if(rpn::IsOperator(QString(str[str.count()-1]))){
        QMessageBox::warning(this, "Не надо так", "ъеъ");
        return;
    }
    ui->lineEdit->setText(ui->lineEdit->text() + "*");
}
//-
void MainWindow::on_btn_minus_clicked()
{
    QString str = ui->lineEdit->text();

    if(str.count()==0){//Если выражение пустое выходим
        QMessageBox::warning(this, "Не надо так", "ъеъ");
        return;
    }

    if(QString(str[str.count()-1])==")"){
        ui->lineEdit->setText(ui->lineEdit->text() + "-");
        return;
    }

    if(rpn::IsOperator(QString(str[str.count()-1])))
        return;
    ui->lineEdit->setText(ui->lineEdit->text() + "-");
}
//+
void MainWindow::on_btn_plus_clicked()
{
    QString str = ui->lineEdit->text();

    if(str.count()==0){//Если выражение пустое выходим
        QMessageBox::warning(this, "Не надо так", "ъеъ");
        return;
    }

    if(QString(str[str.count()-1])==")"){
        ui->lineEdit->setText(ui->lineEdit->text() + "+");
        return;
    }

    if(rpn::IsOperator(QString(str[str.count()-1]))){
        QMessageBox::warning(this, "Не надо так", "ъеъ");
        return;
    }

    ui->lineEdit->setText(ui->lineEdit->text() + "+");
}
//(
void MainWindow::on_btn_skob1_clicked()
{
    QString str = ui->lineEdit->text();

    if(str.count()>0){
        if(QString(str[str.count()-1])==")"){
            QMessageBox::warning(this, "Не надо так", "ъеъ");
            return;
        }

        if(!rpn::IsOperator(QString(str[str.count()-1]))){
            QMessageBox::warning(this, "Не надо так", "ъеъ");
            return;
        }
    }

    ui->lineEdit->setText(str + "(");
}
//]
void MainWindow::on_btn_skob2_3_clicked()
{
    QString str = ui->lineEdit->text();

    if(str.count()==0){//Если выражение пустое выходим
        QMessageBox::warning(this, "Не надо так", "ъеъ");
        return;
    }

    if(rpn::IsOperator(QString(str[str.count()-1]))){
        QMessageBox::warning(this, "Не надо так", "ъеъ");
        return;
    }

    if(str.count('[')>str.count(']')) //Если количество открывающихся скобок
    {                                        //больше количества открывающихся, то срабатывает
        ui->lineEdit->setText(str + "]");
    }
}
//[
void MainWindow::on_btn_skob2_2_clicked()
{
    QString str = ui->lineEdit->text();

    if(str.count()>0){
        if(QString(str[str.count()-1])=="]"){
            QMessageBox::warning(this, "Не надо так", "ъеъ");
            return;
        }
        if(QString(str[str.count()-1])==")"){
            QMessageBox::warning(this, "Не надо так", "ъеъ");
            return;
        }

        if(!rpn::IsOperator(QString(str[str.count()-1]))){
            QMessageBox::warning(this, "Не надо так", "ъеъ");
            return;
        }
    }

    ui->lineEdit->setText(str + "[");
}
//)
void MainWindow::on_btn_skob2_clicked()
{
    QString str = ui->lineEdit->text();

    if(str.count()==0){//Если выражение пустое выходим
        QMessageBox::warning(this, "Не надо так", "ъеъ");
        return;
    }

    if(rpn::IsOperator(QString(str[str.count()-1]))){
        QMessageBox::warning(this, "Не надо так", "ъеъ");
        return;
    }

    if(str.count('(')>str.count(')')) //Если количество открывающихся скобок
    {                                        //больше количества открывающихся, то срабатывает
        ui->lineEdit->setText(str + ")");
    }
}
//sin(
void MainWindow::on_btn_sin_clicked()
{
    QString str = ui->lineEdit->text();

    if(str.count()>0){
        if (str[str.count()-1].isDigit() || QString(str[str.count()-1]) == ")" || QString(str[str.count()-1])== "."){ //Если цифра
            QMessageBox::warning(this, "Не надо так", "ъеъ");
            return;
        }
        if(!rpn::IsOperator(QString(str[str.count()-1]))){
            QMessageBox::warning(this, "Не надо так", "ъеъ");
            return;
        }
    }

    ui->lineEdit->setText(ui->lineEdit->text() + "sin(");
}
//cos(
void MainWindow::on_btn_cos_clicked()
{
    QString str = ui->lineEdit->text();

    if(str.count()>0){
        if (str[str.count()-1].isDigit() || QString(str[str.count()-1]) == ")" || QString(str[str.count()-1])== "."){ //Если цифра
            QMessageBox::warning(this, "Не надо так", "ъеъ");
            return;
        }
        if(!rpn::IsOperator(QString(str[str.count()-1]))){
            QMessageBox::warning(this, "Не надо так", "ъеъ");
            return;
        }
    }

    ui->lineEdit->setText(ui->lineEdit->text() + "cos(");
}
//tg(
void MainWindow::on_btn_tg_clicked()
{
    QString str = ui->lineEdit->text();

    if(str.count()>0){
        if (str[str.count()-1].isDigit() || QString(str[str.count()-1]) == ")" || QString(str[str.count()-1])== ".") //Если цифра
            return;
        if(!rpn::IsOperator(QString(str[str.count()-1]))){
            QMessageBox::warning(this, "Не надо так", "ъеъ");
            return;
        }
    }

    ui->lineEdit->setText(ui->lineEdit->text() + "tg(");
}
//ctg(
void MainWindow::on_btn_ctg_clicked()
{
    QString str = ui->lineEdit->text();

    if(str.count()>0){
        if (str[str.count()-1].isDigit() || QString(str[str.count()-1]) == ")" || QString(str[str.count()-1])== ".") //Если цифра
            return;
        if(!rpn::IsOperator(QString(str[str.count()-1])))
            return;
    }

    ui->lineEdit->setText(ui->lineEdit->text() + "ctg(");
}
//.
void MainWindow::on_btn_point_clicked()
{
    QString str = ui->lineEdit->text();

    if(str.count()==0)//Если выражение пустое выходим
        return;

    if(rpn::IsOperator(QString(str[str.count()-1])))
        return;
    if(QString(str[str.count()-1])==".")
        return;

    ui->lineEdit->setText(ui->lineEdit->text() + ".");
}
//e
void MainWindow::on_btn_e_clicked()
{
    QString str = ui->lineEdit->text();

    if(str.count()>0){
        if (str[str.count()-1].isDigit() || QString(str[str.count()-1]) == ")" || QString(str[str.count()-1])== ".") //Если цифра
            return;
        if(!rpn::IsOperator(QString(str[str.count()-1])))
            return;
    }

    ui->lineEdit->setText(ui->lineEdit->text() + "exp(1)");
}

//pi
void MainWindow::on_btn_Pi_clicked()
{
    QString str = ui->lineEdit->text();
    if(str.count()>0){
        if (str[str.count()-1].isDigit() || QString(str[str.count()-1]) == ")" || QString(str[str.count()-1])== ".") //Если цифра
            return;

        if(rpn::IsOperator(QString(str[str.count()-1]))){
            ui->lineEdit->setText(ui->lineEdit->text() + "pi");
            return;
        }
    }

    ui->lineEdit->setText(ui->lineEdit->text() + "pi");
}


//Добавить выбранную переменную
void MainWindow::on_btn_addPer_clicked()
{
    QString str = ui->lineEdit->text();

    if(model->data(model->index(idModel,1)).toString() == "")
        QMessageBox::information(this, "Информация" , "Сначало добавьте значение переменной");
    if(str.count()>0){
        if (str[str.count()-1].isDigit() || QString(str[str.count()-1]) == ")" || QString(str[str.count()-1])== ".") //Если цифра
            return;
        if(!rpn::IsOperator(QString(str[str.count()-1])))
            return;
    }

    ui->lineEdit->setText(ui->lineEdit->text() + model->data(model->index(idModel,0)).toString());
}

//±~
void MainWindow::on_btn_plusminus_clicked()
{
    QString str = ui->lineEdit->text();

    if(str.count()==0){//Если выражение пустое
        ui->lineEdit->setText(ui->lineEdit->text() + "~");
        return;
    }

    if(QString(str[str.count()-1])==".")
        return;
    if(QString(str[str.count()-1])==")")
        return;

    if(rpn::IsOperator(QString(str[str.count()-1])))
        ui->lineEdit->setText(ui->lineEdit->text() + "(~");
}

void MainWindow::on_btn_log_clicked()
{
    QString str = ui->lineEdit->text();

    if(str.count()>0){
        if (str[str.count()-1].isDigit() || QString(str[str.count()-1]) == ")" || QString(str[str.count()-1])== ".") //Если цифра
            return;
        if(!rpn::IsOperator(QString(str[str.count()-1])))
            return;
    }

    ui->lineEdit->setText(ui->lineEdit->text() + "log(a,x)");
    int k=0;
    for(int i=0; model->rowCount(); i++)
    {
        if(k==2)
            return;
        if(model->data(model->index(i,0)).toString()==""){
            if(k==0)
                model->setData(model->index(i,0),"a");
            if(k==1)
                model->setData(model->index(i,0),"x");
            k++;
        }
    }
}


//Установка Радиан
void MainWindow::on_radioButton_clicked()
{
    Rpn.radianGrad=true;
}
//Установка Градусов
void MainWindow::on_radioButton_2_clicked()
{
    Rpn.radianGrad=false;
}
