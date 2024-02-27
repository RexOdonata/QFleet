#include "qfp_strategycard.h"
#include "./ui_qfp_strategycard.h"

QFP_StrategyCard::QFP_StrategyCard(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QFP_StrategyCard)
{
    ui->setupUi(this);
}

QFP_StrategyCard::~QFP_StrategyCard()
{
    delete ui;
}

