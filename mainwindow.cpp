#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

#include <QDebug>
#include <QPrinter>
#include <QtWidgets>

#include <math.h>


#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"
using namespace QXlsx;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    ui->comboBox->setCurrentIndex(1);
    ui->statusbar->showMessage("Файл не выбран");
    this->setWindowTitle("Probe");
}

MainWindow::~MainWindow()
{
    delete ui;
}

double StatCom(double q, int i, int j)
{
    double zz = 1, z = zz;
    int k = i;
    while (k <= j){ zz *= q*k/(k+1); z += zz; k += 2; }
    return z;
}

double StudentT(double t, int n)
{
    double th = atan(abs(t)/sqrt((double)n)), pi2 = acos((double)-1)/2;

    if (n == 1) return ( 1 - th / pi2 );

    double sth = sin(th), cth = cos(th);

    if (n%2 == 1) return ( 1 - (th + sth * cth * StatCom(cth * cth, 2, n-3)) / pi2 );
    else          return ( 1 - sth * StatCom(cth * cth, 1, n-3) );
}

double AStudentT(int n, double alpha)  // Возвращает табличное значение t-критерия Стьюдента
{                                      // по числу степеней свободы n и уровню значимости alpha
                                       // (alpha = 1-p, где p - доверительная вероятность)
    double v = 0.5, dv = 0.5, t = 0;
    while (dv > 1e-10)
     { t = 1/v-1; dv /= 2;
       if (StudentT(t,n) > alpha) v -= dv;
       else v += dv;
     }
    return t;
}

double MainWindow::interpolation (QVector<double> x, QVector<double> y, double z) {
    // define x by increasing values
   int n = x.size();
    if (z>=x[n-1]) {
        return y[n-1];
    } else if (z<=x[0]) {
        return y[0];
    } else {
        for (int i=0; i<n-1;++i) {
         if (x[i+1]>=z && x[i]<z) {
             return y[i]+(y[i+1]-y[i])/(x[i+1]-x[i])*(z-x[i]);}}}}


double MainWindow::BettaEins(double z) {
    QVector<double> a = {100,250,500,750,1000,1500,2000,3000};
    QVector<double> b = {0.9,0.8,0.65,0.55,0.45,0.35,0.3,0.2};
    return interpolation(a,b,z*100);//z-from t/m2 to MPa
}

double MainWindow::BettaZwei(double z, bool soil) {
    QVector<double> x = {2,4,6,8,10,12};
    QVector<double> y1 = {2.4,1.65,1.2,1.0, 0.85,0.75};
    QVector<double> y2 = {1.5,1.0,0.75,0.6,0.5,0.4};
    if (soil) {
        return interpolation(x,y1,z/10.0);//z-from t/m2 to kPa
    } else {
        return interpolation(x,y2,z/10.0);
    }
}

double MainWindow::BettaI(double z, bool soil) {
    QVector<double> x = {2,4,6,8,10,12};
    QVector<double> y1 = {0.75,0.6,0.55,0.5,0.45,0.4};
    QVector<double> y2 = {1.0,0.75,0.6,0.45,0.4,0.3};
    if (soil) {
        return interpolation(x,y1,z/10.0);//z-from t/m2 to kPa
    } else {
        return interpolation(x,y2,z/10.0);
    }
}

QString MainWindow::QCalculation() {
    QVector <double> heights = {};
    QVector <double> values = {};

    QString res= "", mid = "";

    int n = bodenartProbe.size();
    double UpPoint = Pile_down+NoseLenght-maxSide;
    double DownPoint = Pile_down+NoseLenght+4.0*maxSide;

    double h=0;
    bool Flag = false;
    for (int i = 0; i < n; ++i) {
       h += cellValuesProbe[i][0];
       if (QString::number(h, 'f', 2).toDouble()==QString::number(UpPoint, 'f', 2).toDouble()) {
           Flag=true;
           continue;
       } else if (QString::number(h, 'f', 2).toDouble()==QString::number(DownPoint, 'f', 2).toDouble()) {
           values.push_back(cellValuesProbe[i][1]);
           heights.push_back(cellValuesProbe[i][0]);
           break;
       }   else if (h>UpPoint && Flag==false && h>=DownPoint) {
           values.push_back(cellValuesProbe[i][1]);
           heights.push_back(DownPoint-UpPoint);
           Flag=true;
           break;
       } else if (h>UpPoint && Flag==false) {
           values.push_back(cellValuesProbe[i][1]);
           heights.push_back(h-UpPoint);
           Flag=true;
           continue;
       } else if (h > DownPoint && Flag == true) {
           values.push_back(cellValuesProbe[i][1]);
           heights.push_back(DownPoint-(h-cellValuesProbe[i][0]));
           break;
                }

       if (Flag==true) {
           values.push_back(cellValuesProbe[i][1]);
           heights.push_back(cellValuesProbe[i][0]);
       }
    }


    qq=0;
    if (values.size() > 1) {
        mid="(";
        double heightsum = 0;
        for (int i=0;i<values.size()-1;++i) {
            mid+=QString::number(heights[i], 'f', 2)+"&sdot;"+QString::number(values[i], 'f', 2)+" + ";
            heightsum +=heights[i];
            qq+=heights[i]*values[i];
        }
        heightsum +=heights[values.size()-1];
        qq+=heights[values.size()-1]*values[values.size()-1];
        qq /= heightsum;
        mid+=QString::number(heights[values.size()-1], 'f', 2)+"&sdot;"+QString::number(values[values.size()-1], 'f', 2);
        mid+=")/"+QString::number(heightsum, 'f', 2) + " = " + QString::number(qq, 'f', 2);
    } else {
        mid = QString::number(values[0], 'f', 2);
        qq=values[0];
    }

    res=QString("<p><I>q<sub>s</sub></I>- среднее значение сопротивления грунта, МПа, под наконечником зонда, "
                "полученное из опыта, на участке, расположенном в пределах одного диаметра <I>d=</I>"
                + QString::number(maxSide) + "м выше и четырех диаметров ниже отметки острия проектируемой сваи "
                "(где <I>d</I>  - диаметр круглого или сторона квадратного, или большая сторона прямоугольного сечения сваи, м).</p>"
               "<p>Вычислим среднее значение сопротивления грунта:</p>"
               "<p><I>q<sub>s</sub></I>=" + mid + "МПа</p>");
    return res;

}

//Change this first case
double MainWindow::FirstCase() {
    double res=0.0;
    for (int var = 0; var < maxRow-1; ++var) {
        if (bodenartProbe[var]=="песчаный") {
            double f = cellValuesProbe[var][2];
            res += f*cellValuesProbe[var][0]*BettaI(f,true);
        } else if (bodenartProbe[var]=="пылевато-глинистый") {
            double f = cellValuesProbe[var][2];
            res += f*cellValuesProbe[var][0]*BettaI(f,false);
        }}
    double q=cellValuesProbe[maxRow-2][1];
    return BettaEins(q)*q*A+res*u;
    }

//to change
double MainWindow::SecondCase() {
    double res=0.0, height = 0.0, resout = 0.0;
    int lastrow = bodenartPile.size();
    QString sum="";
    for (int var = 0; var < lastrow; ++var) {
        if (bodenartPile[var]=="песчаный") {
            double f = cellValuesPile[var][2];
            res += f*cellValuesPile[var][0]*BettaI(f,true);
            if (var==lastrow-1) {
            sum+=QString::number(BettaI(f,true), 'f', 2)+"&sdot;"+QString::number(f, 'f', 2)+
                        "&sdot;"+QString::number(cellValuesPile[var][0], 'f', 2);
            } else {
            sum+=QString::number(BettaI(f,true), 'f', 2)+"&sdot;"+QString::number(f, 'f', 2)+
                    "&sdot;"+QString::number(cellValuesPile[var][0], 'f', 2)+" + ";}
        } else if (bodenartPile[var]=="пылевато-глинистый") {
            double f = cellValuesPile[var][2];
            res += f*cellValuesPile[var][0]*BettaI(f,false);
            if (var==lastrow-1) {
            sum+=QString::number(BettaI(f,false), 'f', 2)+"&sdot;"+QString::number(f, 'f', 2)+
                        "&sdot;"+QString::number(cellValuesPile[var][0], 'f', 2);
            } else {
            sum+=QString::number(BettaI(f,false), 'f', 2)+"&sdot;"+QString::number(f, 'f', 2)+
                    "&sdot;"+QString::number(cellValuesPile[var][0], 'f', 2)+" + ";}
        }
     height += cellValuesPile[var][0];
    }

    QString qcalc = QCalculation();
    double q=qq; // to calc q func
    resout=BettaEins(q)*q*A*1000+res*u;
    SingleReport += QString("<body>"
                            "<p><I>z</I>=%1м— глубина погружения нижнего конца сваи от "
                           "уровня природного рельефа.</p>" + qcalc +
     "<p>Предельное сопротивление под нижним концом сваи <I>R<sub>s</sub>="
                            "&beta;<sub>1</sub>q<sub>s</sub></I>=%2 &sdot;"
                            "%3 =&nbsp;%4&nbsp;МПа,</p>"
"<p>где <I>&beta;<sub>1</sub></I>-получено из таблицы 7.16 СП 24 13330 с помощью интерполяции.</p>"
"<p> Среднее значение предельного сопротивления грунта на боковой поверхности "
"сваи по данным зондирования в рассматриваемой точке (тип зонда – II):</p>"
 "<p><I>f = &sum; &beta;<sub>i</sub> f<sub>si</sub> h<sub>i</sub> &frasl; h</I> = ("
                             + sum + ") &frasl; "+QString::number(height, 'f', 2)+
                            " =&nbsp;%5&nbsp;кПа,</p>"
"<p>где значения <I>&beta;<sub>i</sub></I> получены из таблицы 7.16 СП 24 13330 с помощью интерполяции.</p>"
"<p>Частное значение предельного сопротивления забивной сваи в точке зондирования %6:</p>"
"<p><I>F<sub>u</sub> = R<sub>s</sub>&sdot;A + f&sdot; h&sdot; u</I> = "
"%7&sdot;%8 + %5&sdot;%1&sdot;%9 =&nbsp;%10&nbsp;кН =&nbsp;%11&nbsp;т. </p>"
                            "</body>"
).arg(height).arg(QString::number(BettaEins(q), 'f', 2)). //1, 2
arg(QString::number(q, 'f', 2)).arg(QString::number(BettaEins(q)*q, 'f', 2)).//3,4
arg(QString::number(res/height, 'f', 2)).arg(CurrentSheetName)//5,6
.arg(QString::number(BettaEins(q)*q*1000, 'f', 2))//7
.arg(QString::number(A, 'f', 3)).arg(QString::number(u, 'f', 3))//8,9
.arg(QString::number(resout, 'f', 2))//10
.arg(QString::number(resout/9.8, 'f', 2));//11

//    QCalculation();
    return resout; //in kN
    }

double MainWindow::ThirdCase() {
    double res=0.0;
    for (int var = 0; var < maxRow-1; ++var) {
        if (bodenartProbe[var]=="песчаный") {
            double f = cellValuesProbe[var][2];
            res += f*cellValuesProbe[var][0]*BettaI(f,true);
        } else if (bodenartProbe[var]=="пылевато-глинистый") {
            double f = cellValuesProbe[var][2];
            res += f*cellValuesProbe[var][0]*BettaI(f,false);
        }}
    double q=cellValuesProbe[maxRow-2][1];
    return BettaEins(q)*q*A+res*u;
    }

void MainWindow::on_pushButton_clicked()
{
    QString filter = "Excel File (*.xlsx) ;; All File(*.*) ;; Excel File (*.xls)";
    filename = QFileDialog::getOpenFileName(this, tr("Open file name"),
                                                    "C://", filter);
    ui->statusbar->showMessage(QString("Расположение файла: %1").arg(filename));
}

// this example is taken from https://github.com/QtExcel/QXlsx/wiki

void MainWindow::probe_to_pile() {
    int n = bodenartProbe.size();

  cellValuesPile={};
  bodenartPile = {};

    double h=0;
    bool Flag = false;
    for (int i = 0; i < n; ++i) {
       h += cellValuesProbe[i][0];
       if (QString::number(h, 'f', 2).toDouble()==QString::number(Pile_Up, 'f', 2).toDouble()) {
           Flag=true;
           continue;
       } else if (QString::number(h, 'f', 2).toDouble()==QString::number(Pile_down, 'f', 2).toDouble()) {
           cellValuesPile.push_back(cellValuesProbe[i]);
           bodenartPile.push_back(bodenartProbe[i]);
           break;
       }   else if(h>Pile_Up && Flag==false && h>=Pile_down) {
           QVector<double> tempSatz;
           for (int k = 0; k < cellValuesProbe[i].size(); ++k) {
               if (k==0) {
                   tempSatz.push_back(Pile_down-Pile_Up);
               }
               else {
                   tempSatz.push_back(cellValuesProbe[i][k]);
               }
           }
           cellValuesPile.push_back(tempSatz);
           bodenartPile.push_back(bodenartProbe[i]);
           Flag=true;
           break;
       }

       else if(h>Pile_Up && Flag==false) {
           QVector<double> tempSatz;
           for (int k = 0; k < cellValuesProbe[i].size(); ++k) {
               if (k==0) {
                   tempSatz.push_back(h-Pile_Up);
               }
               else {
                   tempSatz.push_back(cellValuesProbe[i][k]);
               }
           }
           cellValuesPile.push_back(tempSatz);
           bodenartPile.push_back(bodenartProbe[i]);
           Flag=true;
           continue;}

        else if (h > Pile_down && Flag == true) {
           QVector<double> tempSatz;
           for (int k = 0; k < cellValuesProbe[i].size(); ++k) {
               if (k==0) {
                   tempSatz.push_back(Pile_down-(h-cellValuesProbe[i][0]));
               }
               else {
                   tempSatz.push_back(cellValuesProbe[i][k]);
               }
           }
           cellValuesPile.push_back(tempSatz);
           bodenartPile.push_back(bodenartProbe[i]);
           break;
                }

       if (Flag==true) {
           cellValuesPile.push_back(cellValuesProbe[i]);
           bodenartPile.push_back(bodenartProbe[i]);
       }
    }
}

QString MainWindow::MakeOutputText() {
    try {


QString output;
output = QString("<style>"
  "H6 {font-family: 'Times New Roman', Times, serif;"
                 "font-weight:bold;margin-top: 0.5em;}"
  "p {font-family: 'Times New Roman', Times, serif; font-size: 12px;"
      "font-weight:normal;border: 1px solid #333;padding: 10px;"
     "word-break: break-all;margin-top: 0.0em;margin-bottom: 0.0em;}"
                "</style>"
                 "<H3><CENTER>ОПРЕДЕЛЕНИЕ НЕСУЩЕЙ СПОСОБНОСТИ СВАЙ ПО РЕЗУЛЬТАТАМ ПОЛЕВЫХ ИССЛЕДОВАНИЙ </CENTER></H3>"
                 "<H7><CENTER><B>Расчет выполнен по СП 24.13330.2011</B></CENTER><H7>"
                 "<H6><CENTER><B><U>Исходные данные</U></B></CENTER><H6>"
                 "<p>Расположение исходного файла: %1</p>"
"<p>Тип зонда: %2</p>"
"<p>Площадь поперечного сечения натурной сваи: %3 м<sup>2</sup></p>"
"<p>Периметр поперечного сечения ствола сваи: %4 м</p>"
"<p>Глубина верха сваи: %5 м</p>"
"<p>Глубина низа сваи: %6 м</p>"
"<p>Длина наконечника: %7 м</p>"
"<p>Максимальная сторона сваи: %8 м</p>"


"<H6><CENTER><B><U>Расчет</U></B></CENTER><H6>"

).arg(filename).arg(ui->comboBox->currentText()).arg(A).arg(u).arg(Pile_Up).
        arg(Pile_down).arg(NoseLenght).arg(maxSide);
//    filename = "C://Qt/Static/5.13.1/Projects/temp.xlsx";
    QXlsx::Document xlsxDoc(filename);

    // ...
    PrivateBedeutung = {};
    int sheetIndexNumber = 0;
foreach( QString curretnSheetName, xlsxDoc.sheetNames() )
    {
        SingleReport = QString(
         "<H6><CENTER><B><I>Вычислим частное значение предельного сопротивления для сваи: %1</I></B></CENTER><H6>")
                .arg(curretnSheetName);
        CurrentSheetName = curretnSheetName;
        // get current sheet
        AbstractSheet* currentSheet = xlsxDoc.sheet( curretnSheetName );
        if ( NULL == currentSheet )
            continue;

        // get full cells of current sheet
        currentSheet->workbook()->setActiveSheet( sheetIndexNumber );
        Worksheet* wsheet = (Worksheet*) currentSheet->workbook()->activeSheet();
        if ( NULL == wsheet )
            continue;
        if (currentSheet->isHidden()) {
            ++sheetIndexNumber;
            continue; }

        Sheet_names.push_back(wsheet->sheetName()); // sheet name
        maxRow = wsheet->dimension().lastRow();
        // begin count column  numbers from 1
        //                         h,t,q,f
        QVector<int> colnumbers = {3,4,5,7};


        while(wsheet->read(maxRow,colnumbers[1]).toString() != "песчаный" &&
              wsheet->read(maxRow,colnumbers[1]).toString() != "пылевато-глинистый") {
            --maxRow;
        }

        int begin=0;
        while(wsheet->read(begin,colnumbers[1]).toString() != "песчаный" &&
              wsheet->read(begin,colnumbers[1]).toString() != "пылевато-глинистый") {
            begin++;
        }
        int newmaxrow=begin;
        //check cells
        //to define (find) max row quantity
        for ( int rn = begin+1; rn <= maxRow; ++rn )
        {
            if (wsheet->read(rn,colnumbers[1]).toString() == "песчаный" ||
                    wsheet->read(rn,colnumbers[1]).toString() == "пылевато-глинистый") {
                    ++newmaxrow;
                 } else {
                     QMessageBox::information(this, "Ошибка в исходном файле",
                                              QString("Исправьте пожалуйста в листе %1 "
                                                      "строчку %2").arg(wsheet->sheetName()).arg(rn));
                     return QString("Ошибка");
            }
        }
        maxRow =newmaxrow;

        //we write blank cellValuesProbe matrix - each row has 4 columns' values
        for (int rc = 0; rc < maxRow-begin+1; rc++)
        {
            QVector<double> tempValue;
            for (int cc = 0; cc < colnumbers.size()-1; cc++)
            {
                tempValue.push_back(0.0);
            }
            cellValuesProbe.push_back(tempValue);
            bodenartProbe.push_back(QString(""));
        }

        // fill cellValuesProbe with values
        for ( int rn = 0; rn < maxRow-begin+1; ++rn )
        {
            for (int cc = 1; cc <= colnumbers.size(); cc++)
            {
                if (wsheet->read(begin+rn,colnumbers[cc-1]).toString() != "" ) {
                    QString val = wsheet->cellAt(rn+begin,colnumbers[cc-1])->
                            value().toString();
                    if (cc !=2) {
                        if (cc==1){if (cellValuesProbe[rn][0]=val.toDouble()) {} else {
                                QMessageBox::warning(this, "Warning", QString("Исправьте пожалуйста в листе %1 "
                                                                              "строчку %2").arg(wsheet->sheetName()).arg(rn));
                            }
                                ;}
                        else {if (cellValuesProbe[rn][cc-2]=val.toDouble()) {} else {
                                QMessageBox::warning(this, "Warning", QString("Исправьте пожалуйста в листе %1 "
                                                                              "строчку %2").arg(wsheet->sheetName()).arg(rn));
                            }
                                ;}}
                    else {
                        bodenartProbe[rn]=val;}
                    }
                }
            }


        maxRow = maxRow-begin+1;

        ++sheetIndexNumber;
        probe_to_pile();
        if (ui->comboBox->currentText()=="I - зонд с наконечником из конуса и кожуха") {
            PrivateBedeutung.push_back(FirstCase());}
        else if (ui->comboBox->currentText()=="II - зонд с наконечником из конуса муфты трения") {
            PrivateBedeutung.push_back(SecondCase());
        } else if (ui->comboBox->currentText()=="III - зонд с наконечником из конуса муфты трения и уширителя") {
            PrivateBedeutung.push_back(ThirdCase());
        }

        output += SingleReport;

    }

output += QString(
 "<H6><CENTER><B><I>Определим несущую способность свай по результатам их испытаний: </I></B></CENTER><H6>"
      "<p><I>F<sub>d</sub>=&gamma;<sub>c</sub>&sdot;F<sub>u,n</sub> &frasl;&gamma;<sub>g</sub></I>,</p>"
 "<p>где <I>&gamma;<sub>c</sub></I> - коэффициент условий работы сваи; в случае вдавливающих или горизонтальных нагрузок равен 1;</p>"
 "<p><I>F<sub>u,n</sub></I> - нормативное значение предельного сопротивления сваи, кН, определяемое в соответствии с 7.3.4-7.3.7, а также 7.3.9-7.3.11;</p>"
 "<p><I>&gamma;<sub>g</sub></I> - коэффициент надежности по грунту.</p>");
int pile_number=PrivateBedeutung.size();
double result_value = PrivateBedeutung[0];
if (pile_number<6) {
    for (auto v: PrivateBedeutung) {
        if (result_value > v) {
            result_value=v;
        }
    }
    output += QString("<p>Поскольку число одинаковых свай, испытанных в одинаковых грунтовых условиях составляет <I>n = </I>"+
          QString::number(pile_number)+", что менее шести, нормативное значение предельного сопротивления сваи "
             "следует принимать равным наименьшему предельному сопротивлению, полученному из результатов испытаний, т.е. <I>F<sub>d</sub>=</I>"
                      +QString::number(gamma_c, 'f', 1)+"&sdot;"+QString::number(result_value, 'f', 2)+ "кН = <b>"+
                      QString::number(gamma_c*result_value, 'f', 2)+"кН</b> = <b>"+QString::number(gamma_c*result_value/9.8, 'f', 2)+ "т</b>, здесь коэффициент надежности по грунту <I>&gamma;<sub>g</sub></I>=1</p>");

    }
else {
    QString pnstr = "";
    if (pile_number==6) {
      pnstr = "шесть";
    } else {
      pnstr = "более шести";
    }

    output += QString("<p>Поскольку число одинаковых свай, испытанных в одинаковых грунтовых условиях составляет <I>n = </I>"+
          QString::number(pile_number)+", что составляет " + pnstr + ", "
             "<I>F<sub>u,n</sub></I> и <I>&gamma;<sub>g</sub></I> следует определять на основании результатов "
        "статистической обработки частных значений предельных сопротивлений свай, "
        "полученных по данным испытаний при значении доверительной вероятности <I>&alpha;=</I>0,95"
        ", руководствуясь требованиями ГОСТ 20522-75.</p>");
         double X_n=0;
         double S=0;
         double t=0;
         double gamma=0;
         QString middle = "(";
         QString middlequadr = "((";

         for (int i=0; i<pile_number-1; ++i) {
                 X_n+=PrivateBedeutung[i];
                 middle += QString::number(PrivateBedeutung[i], 'f', 2) + " + ";
             }
         X_n+=PrivateBedeutung[pile_number-1];
         middle += QString::number(PrivateBedeutung[pile_number-1], 'f', 2) + ") ";
         X_n /=pile_number;
         middle += "&frasl;"+QString::number(pile_number);

         QString X_n_string =  QString::number(X_n, 'f', 2);
         for (int i=0; i<pile_number-1; ++i) {
                 S+=pow((X_n)-PrivateBedeutung[i], 2.0);
                 middlequadr += "("+QString::number(X_n, 'f', 2) + " - " +
                         QString::number(PrivateBedeutung[i], 'f', 2)+")<sup>2</sup> + ";
             }
         S+=pow((X_n)-PrivateBedeutung[pile_number-1], 2.0);
         middlequadr += "("+QString::number(X_n, 'f', 2) + " - " +
         QString::number(PrivateBedeutung[pile_number-1], 'f', 2)+")<sup>2</sup>)";
         S=pow(S/(pile_number-1), 0.5);
         middlequadr += " &frasl;" + QString::number(pile_number-1) + ")<sup>0.5</sup>";


         t=AStudentT(pile_number-1, 1.0- 0.90);
         result_value=gamma_c*(X_n-S*t/pow((double)pile_number, 0.5));

         gamma=t*S/(X_n*pow((double)pile_number, 0.5));
         gamma=1.0/(1-gamma);

    output += QString("<p>Несущую способность свай определим по формуле:</p>"
       "<p><I>F<sub>d</sub>=&gamma;<sub>c</sub>&sdot;F<sub>u,n</sub> &frasl;&gamma;<sub>g</sub>="
       "&gamma;<sub>c</sub>&sdot;(F<sub>u,n</sub> - F<sub>u,n</sub>&sdot;&rho;<sub>&alpha;</sub>)</I>,</p>"
       "<p>где <I>&rho;<sub>&alpha;</sub></I> - показатель точности ее среднего значения, который определяется как:</p>"
      "<p><I>&rho;<sub>&alpha;</sub> = S&sdot; t<sub>&alpha;,n-1</sub> &frasl; (F<sub>u,n,ср</sub>&sdot; n<sup>0.5</sup>)</I> и "
                      "<I>&gamma;<sub>g</sub>=1 &frasl;(1-&rho;<sub>&alpha;</sub>)</I></p>"
     "<p>Для нормально распределенных выборок односторонний нижний предел доверия среднего значения равен: "
     "<I>F=F<sub>u,n,ср</sub> - t<sub>&alpha;,n-1</sub>&sdot;S &frasl;n<sup>0.5</sup></I></p>"

       "<p>Среднее значение частного значения предельных сопротивлений свай равно:</p>"
       "<p><I>F<sub>u,n,ср</sub></I>=" + middle+ " = "+ QString::number(X_n, 'f', 2)+ "кН,</p>"
       "<p>ее смещенная оценка среднеквадратического отклонения равна:</p>"
       "<p><I>S=</I>" +middlequadr+" = "+QString::number(S, 'f', 2) + "кН.</p>"
       "<p><I>t<sub>&alpha;,n</sub></I> - значение для распределения Стьюдента для односторонних областей.</p>"
        "<p><I>t<sub>&alpha;,n-1</sub></I>=" + QString::number(t, 'f', 4)+".</p>"
       "<p>Несущая способность свай по результатам их испытаний равна:</p>"
       "<p><I>F<sub>d</sub>=&gamma;<sub>c</sub>&sdot;(F<sub>u,n,ср</sub> - t<sub>&alpha;,n-1</sub>&sdot;S &frasl;n<sup>0.5</sup>)=</I>"+
        QString::number(gamma_c, 'f', 1)+"&sdot;("+QString::number(X_n, 'f', 2)+ " - " + QString::number(t, 'f', 4)+"&sdot;"
       + QString::number(S, 'f', 2)+" &frasl;" + QString::number(pile_number)+"<sup>0.5</sup>)"
       "= <b>" + QString::number(result_value, 'f', 2) + "кН</b> = <b>" +
                      QString::number(result_value/9.8, 'f', 2) + "т</b>"+
       ", здесь <I>&gamma;<sub>g</sub></I> = " + QString::number(gamma, 'f', 6)+".</p>" );
}
    return output;
    } catch (...) {
        QMessageBox::warning(this, "Warning", "Что-то пошло не так");
    }

}

void MainWindow::PrintToFile(QString text) {
    QDir file(QCoreApplication::applicationDirPath() + "/output.pdf");
    //    QDir file("../output.pdf");
    QString filePath = file.path();

    QPrinter printer(QPrinter::PrinterResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPaperSize(QPrinter::A4);
    printer.setOutputFileName(filePath);
    printer.setPageMargins(12, 16, 12, 20, printer.Millimeter);

    QTextDocument doc;
    doc.setHtml(text);
    doc.setPageSize(printer.pageRect().size()); // This is necessary if you want to hide the page number
    doc.print(&printer);

    QString absolute_file_path = file.canonicalPath();

    QDesktopServices::openUrl(QUrl::fromLocalFile(absolute_file_path));
}

void MainWindow::on_pushButton_2_clicked()
{

//    filename="C:\\НС_стат_зонд_данные_Мякинино_12.xlsx";

    double Side1, Side2;
    Side1=ui->lineEdit->text().toDouble();
    Side2=ui->lineEdit_2->text().toDouble();
    A=QString::number(Side1*Side2/1000000.0, 'f', 3).toDouble();
    u=QString::number(2.0*(Side1+Side2)/1000.0, 'f', 3).toDouble();
    maxSide=QString::number(((Side1 > Side2) ? Side1 : Side2)/1000.0, 'f', 3).toDouble();

    Pile_Up=ui->lineEdit_3->text().toDouble();
    Pile_down=ui->lineEdit_4->text().toDouble();
    NoseLenght=QString::number(ui->lineEdit_5->text().toDouble()/1000.0, 'f', 3).toDouble();
    gamma_c=ui->comboBox_2->currentText().toDouble();

    if  (filename.isEmpty()){
            QMessageBox::warning(this, "Choose a file please", "Файл не выбран");
        } else if (Pile_Up >= Pile_down ){
            QMessageBox::warning(this, "Warning", "Write the correct Pile depth, please");
        } else if (Pile_down-Pile_Up < maxSide ||  Pile_down-Pile_Up < NoseLenght){
        QMessageBox::warning(this, "Warning", "Write the correct datas, please");
    }  else {
    OutText = MakeOutputText();
    PrintToFile(OutText); }

}

