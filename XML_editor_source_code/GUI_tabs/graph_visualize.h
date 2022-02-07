#ifndef GRAPH_VISUALIZE_H
#define GRAPH_VISUALIZE_H
#include "XML_to_JSON/User.hpp"
#include <QWidget>
#include "Graph/Graph.hpp"

namespace Ui {
class graph_visualize;
}

class graph_visualize : public QWidget
{
    Q_OBJECT

public:
    explicit graph_visualize(QWidget *parent = nullptr, QString str = "");
    void create_dot_file(vector<User> users);
    void make_graph_matrix_view(vector<User> users);
    void fill_data_in_table_view();
    ~graph_visualize();

private:
    Ui::graph_visualize *ui;
    vector<string> graph_2D;
    Graph* graph;
};

#endif // GRAPH_VISUALIZE_H
