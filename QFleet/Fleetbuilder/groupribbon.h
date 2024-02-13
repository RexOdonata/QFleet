#ifndef GROUPRIBBON_H
#define GROUPRIBBON_H

#include <QWidget>

namespace Ui {
class groupRibbon;
}

class groupRibbon : public QWidget
{
    Q_OBJECT

public:
    explicit groupRibbon(QWidget *parent = nullptr);
    ~groupRibbon();

private:
    Ui::groupRibbon *ui;
};

#endif // GROUPRIBBON_H
