#ifndef BATTLEGROUP_H
#define BATTLEGROUP_H

#include <QWidget>

namespace Ui {
class battlegroup;
}

class battlegroup : public QWidget
{
    Q_OBJECT

public:
    explicit battlegroup(QWidget *parent = nullptr);
    ~battlegroup();

private:
    Ui::battlegroup *ui;
};

#endif // BATTLEGROUP_H
