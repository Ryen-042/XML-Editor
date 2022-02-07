#include "graph_visualize.h"
#include "XML_to_JSON/tree.hpp"
#include "./Minify/Minify.h"
#include "ui_graph_visualize.h"


#include <QFile>
#include <QTextStream>
#include <QStandardItemModel>
#include <QDebug>


graph_visualize::graph_visualize(QWidget *parent, QString str) :
    QWidget(parent),
    ui(new Ui::graph_visualize)
{
    ui->setupUi(this);
    Tree* XML_Tree = new Tree();

    str = QString::fromStdString(Minify(str.toStdString()));
    // make tree from string s
    XML_Tree->parse_and_bulid_xml_tree(str.toStdString());

    vector<User> users = XML_Tree->extractUsers();

    make_graph_matrix_view(users);
    fill_data_in_table_view();
    create_dot_file(users);

    User most_inf = graph->most_influencer_user();
    User most_act = graph->most_active_user();

    ui->most_inf->setText("Most influencer user is: \n\t\tName: " + QString::fromStdString(most_inf.name) + "\n\t\tID: " + QString::number(most_inf.id));
    ui->most_act->setText("\nMost active user is: \n\t\tName: " + QString::fromStdString(most_act.name) + "\n\t\tID: " +QString::number(most_act.id));
}

void graph_visualize::create_dot_file(vector<User> users){
    string result = "digraph Graph {\n\n";
    result += "\tnode [ shape = \"record\"  color = \"red\"]\n\n";
    for(const auto &user : users)
    {
        result += "\t" + to_string(user.id) + " [ label = \"{ " + user.name + +" | id = " + to_string(user.id) +
            " }\" ]\n";
        result += "\t" + to_string(user.id) + " -> {";
        for(size_t i = 0; i < user.followers.size(); i++)
        {
            if(i)
                result += " ,";
            result += to_string(user.followers[i]);
        }
        result += "}\n";
    }
    result += "}\n\n";


    QFile file("graph.dot");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)){
             return;
    }
    QTextStream out(&file);
    QString text = QString::fromStdString(result);
    out << text;
    file.flush();
    file.close();
    system("dot -Tpng -O graph.dot");

    QPixmap mypix("graph.dot.png");

    ui->img->setPixmap(mypix);
}

void graph_visualize::make_graph_matrix_view(vector<User> users){
    graph = new Graph(users.size() + 2,users);
    graph_2D = graph->build_graph();
}

void graph_visualize::fill_data_in_table_view(){
    QStandardItemModel *model;
    QStringList horizontalHeader;
    QStringList verticalHeader;


    // Here we are creating our model

    model = new QStandardItemModel();

    model->setHorizontalHeaderLabels(horizontalHeader);
    model->setVerticalHeaderLabels(verticalHeader);

    ui->tableView->setModel(model); // This is necessary to display the data on table view
    ui->tableView->verticalHeader()->setDefaultSectionSize(10);

    for(size_t i=0;i<graph_2D.size();i++){
        QList<QStandardItem*> items;
        for(size_t j=0;j<graph_2D[i].size();j++){
            if(graph_2D[i][j] == '\n')
                continue;
            QStandardItem* temp = new QStandardItem(QString::number(graph_2D[i][j] - '0'));
            items.append(temp);
        }
        model->appendRow(items);
        ui->tableView->setColumnWidth(i,70);
        ui->tableView->setRowHeight(i,30);
    }
}

graph_visualize::~graph_visualize()
{
    delete ui;
}

