#ifndef CARD_H
#define CARD_H

#include <QWidget>

namespace Ui {
class card;
}

class card : public QWidget
{
    Q_OBJECT

public:
    explicit card(QWidget *parent = nullptr);
    ~card();

private:
    Ui::card *ui;
};

#endif // CARD_H
