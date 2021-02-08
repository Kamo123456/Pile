#ifndef TREE_H
#define TREE_H

#include <QDialog>

namespace Ui {
class Tree;
}

class Tree : public QDialog
{
    Q_OBJECT

public:
    explicit Tree(QWidget *parent = nullptr);
    ~Tree();

private:
    Ui::Tree *ui;
};

#endif // TREE_H
