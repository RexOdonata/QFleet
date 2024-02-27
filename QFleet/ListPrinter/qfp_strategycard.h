#ifndef QFP_STRATEGYCARD_H
#define QFP_STRATEGYCARD_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class QFP_StrategyCard; }
QT_END_NAMESPACE

class QFP_StrategyCard : public QDialog
{
    Q_OBJECT

public:
    QFP_StrategyCard(QWidget *parent = nullptr);
    ~QFP_StrategyCard();

private:
    Ui::QFP_StrategyCard *ui;
};
#endif // QFP_STRATEGYCARD_H
