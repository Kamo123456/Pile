#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDir>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString filename = "", CurrentSheetName = "";
    QVector <QString> Sheet_names;
    QVector<double> PrivateBedeutung; //All data
    // Private Bedeutung
    QVector< QVector<double> > cellValuesProbe;
    QVector<QString> bodenartProbe;
    QVector< QVector<double> > cellValuesPile;
    QVector<QString> bodenartPile;
    int maxRow;
    double qq;

    double FirstCase();
    double SecondCase();
    double ThirdCase();

    double BettaEins(double);
    double BettaZwei(double, bool);
    double BettaI(double, bool);


    QString MakeOutputText();

    void probe_to_pile();
    QString QCalculation();
    void PrintToFile(QString);


    // General report
    QString OutText;

    //Single report
    QString SingleReport;


//    double A;
//    double u;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
    double A;
    double u;
    double maxSide;
    double Pile_Up;
    double Pile_down;
    double NoseLenght = 0.0;
    double gamma_c;
    double interpolation (QVector<double>, QVector<double>, double);

};
#endif // MAINWINDOW_H
