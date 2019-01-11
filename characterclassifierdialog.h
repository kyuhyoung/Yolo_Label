#ifndef CHARACTERCLASSIFIERDIALOG_H
#define CHARACTERCLASSIFIERDIALOG_H

#include <QDialog>

namespace Ui {
class CharacterClassifierDialog;
}

class CharacterClassifierDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CharacterClassifierDialog(QWidget *parent = nullptr);
    ~CharacterClassifierDialog();

private:
    Ui::CharacterClassifierDialog *ui;
};

#endif // CHARACTERCLASSIFIERDIALOG_H
