#ifndef GROUP_H
#define GROUP_H

#include <QWidget>

namespace Ui {
class group;
}

class group : public QWidget
{
    Q_OBJECT

public:
    explicit group(QWidget *parent = nullptr);
    ~group();

private:
    Ui::group *ui;
};

#endif // GROUP_H
