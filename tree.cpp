#include "tree.h"
#include "ui_tree.h"
#include <QtWidgets>

Tree::Tree(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Tree)
{
    ui->setupUi(this);
    QFileSystemModel model;
    QTreeView        treeView;
    model.setRootPath(QDir::rootPath());
    treeView.setModel(&model);
    treeView.show();

}

Tree::~Tree()
{
    delete ui;
}
