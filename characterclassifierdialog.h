#ifndef CHARACTERCLASSIFIERDIALOG_H
#define CHARACTERCLASSIFIERDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QListWidget>

namespace Ui {
class CharacterClassifierDialog;
}

class CharacterClassifierDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CharacterClassifierDialog(QWidget *parent = nullptr);
    ~CharacterClassifierDialog();

    int getCharacterIndex();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

    void on_buttonBox_accepted();
    void onOKButtonClicked(){ this->setResult(QDialog::Accepted); this->close();}
    void onCancelButtonClicked(){ this->setResult(QDialog::Rejected);this->close();}

private:
    Ui::CharacterClassifierDialog *ui;
};

#endif // CHARACTERCLASSIFIERDIALOG_H
