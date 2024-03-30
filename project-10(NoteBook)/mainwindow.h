#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog> //библиотека с диалоговым окнами для работы с файлами
#include <QHBoxLayout>
#include <QMessageBox> //библиотека информотивного окна
#include<QCloseEvent> //бибилиотека с событием закрытия окна
#include <QFontDialog> //библиотека шрифтов
#include<QDateTime> //библиотека дата и время
#include<QTextEdit>
#include<QDebug> //библиотека для консоли
#include <QColorDialog> //библиотека с диалоговым окном для работы с цветом

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Menu_open_triggered();

    void closeT();

    void closeEvent(QCloseEvent *event); //будем изменять обработчик закрытия формы

    void on_textEdit_textChanged();

    void on_Menu_save_triggered();

    void on_Menu_save_as_triggered();

    void on_Menu_exit_triggered();

    void on_Menu_create_triggered();

    void on_Menu_font_triggered();

    void on_Menu_cut_triggered();

    void on_Menu_copy_triggered();

    void on_Menu_paste_triggered();

    void on_Menu_undo_triggered();

    void on_Menu_redo_triggered();

    void on_data_triggered();

    void on_all_triggered();

    void openT();

    void on_color_triggered();

    void on_color_t_triggered();

    void on_action_triggered();

private:
    Ui::MainWindow *ui;
    QString file1 = ""; //глобальная переменная для пути файла
    bool correct_exit = true; //переменная для определения выхода из программы
    QString fileName = "";
    QString way = "Блокнот.txt"; //глобальная переменна отвечающая за название файла
    bool saved_noteBook = true; //глобальная логическая переменная отвечающаю за проверку изменений в блокноте
                               //false - меняли содержимое блокнота
                               //true - не меняли
    QColor m_backgroundColor = Qt::white;
    QColor m_foregroundColor = Qt::black;

};
#endif // MAINWINDOW_H

