#ifndef LIMITWIDGET_H
#define LIMITWIDGET_H

#include <QWidget>

namespace Ui {
class limitWidget;
}

class limitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit limitWidget(QWidget *parent = nullptr);
    ~limitWidget();

private:
    Ui::limitWidget *ui;
};

#endif // LIMITWIDGET_H
