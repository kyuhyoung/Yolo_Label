#include "characterclassifierdialog.h"
#include "ui_characterclassifierdialog.h"

CharacterClassifierDialog::CharacterClassifierDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CharacterClassifierDialog)
{
    ui->setupUi(this);
}

CharacterClassifierDialog::~CharacterClassifierDialog()
{
    delete ui;
}
