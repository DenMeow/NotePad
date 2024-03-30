#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this -> setCentralWidget(ui->textEdit); //закрепляет виджет по размерам окна
    QWidget::setWindowTitle(way); //устанавливаем начальное название блокнота
    //стандартные настройки цвета и размера шрифта
    QString styleSheet = QString("Background-color: %1; color:%2")
            .arg(QColor(Qt::white).name())
            .arg(QColor(Qt::black).name());
    ui -> textEdit -> setStyleSheet(styleSheet);
    ui -> textEdit -> setFont(QFont("Helvetical[Cronyx]",14));
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_Menu_create_triggered()//меню - создать пустой блокнот
{
    if(!saved_noteBook)
    {
        QMessageBox::StandardButton reply;//заводим переменную для QMessageBox
        reply = QMessageBox::question(this, "Блокнот", "Вы хотите сохранить изменения в файле?", QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel, QMessageBox::Yes);
        if (reply == QMessageBox::Yes)//если пользователь нажал Yes
        {
            on_Menu_save_triggered(); //функция сохранить
            if(file1.isEmpty())
            {
                return;
            }
            else
            {
                ui -> textEdit -> clear(); //чистим поле

                //Устанавливаем дефолтные значения блокнота
                fileName = "";
                QWidget::setWindowTitle("Блокнот.txt");
                way = "Блокнот.txt";
                saved_noteBook = true;
                file1 = "";
            }
        }
        else if (reply == QMessageBox::Cancel)
        {
            return; //возвращаем пользователя к работе с блокнотом
        }
        else
        {
            ui -> textEdit -> clear(); //чистим поле

            //Устанавливаем дефолтные значения блокнота
            fileName = "";
            QWidget::setWindowTitle("Блокнот.txt");
            way = "Блокнот.txt";
            saved_noteBook = true;
            file1 = "";
        }
    }
    else
    {
        ui -> textEdit -> clear(); //чистим поле

        //Устанавливаем дефолтные значения блокнота
        fileName = "";
        file1 ="";
        QWidget::setWindowTitle("Блокнот.txt");
        way = "Блокнот.txt";
        saved_noteBook = true;
    }
}

void MainWindow::openT()//функция обычного открытия файла
{
    fileName = QFileDialog::getOpenFileName(this, tr("Открыть документ"), "C:/Users/student.A-424/Desktop/", tr("Text files (*.txt)"));//открываем диалог открытия файла

    if (fileName.isEmpty()) // файл не выбран
    {
        return;
    }
    else
    {
        file1 = fileName;
        ui->textEdit->clear(); //очистка поля редактора

        QFile file;//класс файлов
        file.setFileName(fileName); //связываем с файлом на диске

        file.open(QIODevice::ReadOnly); //открываем файл только на чтение

        QByteArray ba; //массив для передачи файлов
        ba.clear();
        long long int size; //для размера файла

        size = file.size(); //размер файла

        ba=file.read(size);

        ui->textEdit->append(QString(ba)); //копирование в поле редактора

        file.close(); //закрываем файл

        QFileInfo fileInfo(file.fileName());
        QString fileName(fileInfo.fileName());
        QWidget::setWindowTitle(fileName); //выводим название блокнота
        way = fileName; //присваим ИМЯ блокнота

        saved_noteBook = true;
    }
}
void MainWindow::on_Menu_open_triggered() //меню - открытия блокнота
{
    if(!saved_noteBook) //если были внесены изменения в блокнот
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Блокнот", "Вы хотите сохранить изменения в файле?", QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel, QMessageBox::Yes);
        if (reply == QMessageBox::Yes)
        {
            if(file1.isEmpty())
            {
                on_Menu_save_triggered(); //функция - сохранить
                return;
            }
            else
            {
                on_Menu_save_triggered(); //функция - сохранить
                openT();

            }
        }
        else if (reply == QMessageBox::Cancel)
        {
            return;
        }
        else
        {
            openT();
        }
    }
    else
    {
        openT();
    }
}

void MainWindow::on_Menu_save_triggered()// меню - сохранения
{
    if(file1.isEmpty())
    {
        on_Menu_save_as_triggered();
    }
    else
    {
        saved_noteBook = true;
        QFile file;//класс файлов
        file.setFileName(file1); //связываем с файлом на диске

        file.open(QIODevice::WriteOnly); //открываем файл только на запись

        file.write(ui->textEdit->toPlainText().toUtf8()); //запись в файл через цепочку преобразований

        file.close(); //закрываем файл
//        QFileInfo fileInfo(file.fileName());
//        QString fileName(fileInfo.fileName());
        QWidget::setWindowTitle(way); //выводим название блокнота
//        way = fileName;
    }
}

void MainWindow::on_Menu_save_as_triggered() //меню - сохранить блокнот как
{
    QString fileName; //имя блокнота

    fileName = QFileDialog::getSaveFileName(this, tr("Сохранение"),"C:/Users/student.A-424/Desktop/", tr("Text files (*.txt)"));
    file1 = fileName;

    if (fileName.isEmpty())//файл не выбран
    {
        return;
    }
    else
    {

        QFile file;//класс файлов
        file.setFileName(fileName); //связываем с файлом на диске

        file.open(QIODevice::WriteOnly); //открываем файл только на запись

        file.write(ui->textEdit->toPlainText().toUtf8()); //запись в файл через цепочку преобразований

        file.close(); //закрываем файл
        QFileInfo fileInfo(file.fileName());
        QString fileName(fileInfo.fileName());
        QWidget::setWindowTitle(fileName); //выводим название блокнота
        way = fileName;

        saved_noteBook = true;
    }
}

void MainWindow::on_Menu_exit_triggered()//меню - выход из блокнота
{
    closeT();
}

void MainWindow::closeT()//функция выхода
{
    correct_exit = false;
    if(!correct_exit)
    {
        if(!saved_noteBook)
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Блокнот", "Вы хотите сохранить изменения в файле?", QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel, QMessageBox::Yes);
            if (reply == QMessageBox::Yes)
            {
                QString fileName;

                fileName = QFileDialog::getSaveFileName(this, tr("Сохранение"), "C:/Users/student.A-424/Desktop/", tr("Text files (*.txt)"));

                if (fileName.isEmpty())//файл не выбран
                {
                    correct_exit = true;
                    return;
                }
                else
                {
                    QFile file;//класс файлов
                    file.setFileName(fileName); //связываем с файлом на диске

                    file.open(QIODevice::WriteOnly); //открываем файл только на запись

                    file.write(ui->textEdit->toPlainText().toUtf8()); //запись в файл через цепочку преобразований

                    file.close(); //закрываем файл
                    QWidget::close();
                }

            }
            else if (reply == QMessageBox::Cancel)
            {
                correct_exit = true;
                return; //игнорируем сигнал
            }
            else
            {
                QWidget::close(); //принимаем сигнал
            }
        }
        else
        {
            QWidget::close();//закрыть блокнот
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event) //обработчик закрытия формы
{
    if(correct_exit)
    {
        if(!saved_noteBook)
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Блокнот", "Вы хотите сохранить изменения в файле?", QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel, QMessageBox::Yes);
            if (reply == QMessageBox::Yes)
            {
                QString fileName;

                fileName = QFileDialog::getSaveFileName(this, tr("Сохранение"),"C:/Users/student.A-424/Desktop/", tr("Text files (*.txt)"));

                if (fileName.isEmpty())//файл не выбран
                {
                    event -> ignore();
                }
                else
                {
                    QFile file;//класс файлов
                    file.setFileName(fileName); //связываем с файлом на диске

                    file.open(QIODevice::WriteOnly); //открываем файл только на запись

                    file.write(ui->textEdit->toPlainText().toUtf8()); //запись в файл через цепочку преобразований

                    file.close(); //закрываем файл
                }

            }
            else if (reply == QMessageBox::Cancel)
            {
                event -> ignore(); //игнорируем сигнал
            }
            else
            {
                event -> accept(); //принимаем сигнал
            }
        }
        else
        {
            QWidget::close();//закрыть блокнот
        }
    }
}

void MainWindow::on_textEdit_textChanged() //проверка любых изменений в блокноте
{
    saved_noteBook = false;
    QWidget::setWindowTitle("*" + way);
}

//<<ДОП фичи>>
void MainWindow::on_Menu_font_triggered() //меню - шрифты
{
    bool ok;

    QFont font1 = QFontDialog::getFont(&ok,QFont("Helvetical[Cronyx]",14), this); //вызов окна с выбором шрифта


    if(ok)
    {
        ui -> textEdit -> setFont(font1); //установка шрифта
    }
    qDebug()<< font1; //вывод в консоль информацию про шрифт
}

void MainWindow::on_Menu_cut_triggered() //меню - вырезать
{
    ui->textEdit->cut();
}

void MainWindow::on_Menu_copy_triggered() //меню - копировать
{
    ui->textEdit->copy();
}

void MainWindow::on_Menu_paste_triggered() //меню - вставить
{
    ui->textEdit->paste();
}

void MainWindow::on_Menu_undo_triggered() //меню - отменить
{
    ui -> textEdit ->undo();
}

void MainWindow::on_Menu_redo_triggered() //меню - удалить
{
    ui -> textEdit -> redo();
}

void MainWindow::on_data_triggered() //меню - дата и время
{
    QString data = QDateTime::currentDateTime().toString("dd.MM.yyyy HH:mm:ss");
    ui -> textEdit -> insertPlainText(data);
}

void MainWindow::on_all_triggered() //меню - выделить все
{
    ui -> textEdit -> selectAll();
}

void MainWindow::on_color_triggered()//меню - цвет фона
{
    m_backgroundColor = QColorDialog::getColor(QColor(Qt::white),this,"Выберите цвет фона");
    QString styleSheet = QString("background-color: %1; color:%2")
            .arg(m_backgroundColor.name())
            .arg(m_foregroundColor.name());

    ui -> textEdit ->setStyleSheet(styleSheet);
}

void MainWindow::on_color_t_triggered()//меню - цвет текста
{
    m_foregroundColor = QColorDialog::getColor(QColor(Qt::white),this,"Выберите цвет текста");
    QString styleSheet = QString("background-color: %1; color:%2")
            .arg(m_backgroundColor.name())
            .arg(m_foregroundColor.name());

    ui -> textEdit ->setStyleSheet(styleSheet);
}

void MainWindow::on_action_triggered() //меню - вернуть все
{
    QString styleSheet = QString("Background-color: %1; color:%2")
            .arg(QColor(Qt::white).name())
            .arg(QColor(Qt::black).name());
    ui -> textEdit -> setStyleSheet(styleSheet);
    ui -> textEdit -> setFont(QFont("Helvetical[Cronyx]",14));
}

