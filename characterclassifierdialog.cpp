#include "characterclassifierdialog.h"
#include "ui_characterclassifierdialog.h"

#include <QTextEncoder>

CharacterClassifierDialog::CharacterClassifierDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CharacterClassifierDialog)
{
    ui->setupUi(this);


    const char* strCharacters[] = {"0",
                            "1",
                            "2",
                            "3",
                            "4",
                            "5",
                            "6",
                            "7",
                            "8",
                            "9",
                            "가",
                            "나",
                            "다",
                            "라",
                            "마",
                           "바",
                           "사",
                           "아",
                           "자",
                           "하",
                           "거",
                           "너",
                           "더",
                           "러",
                           "머",
                           "버",
                           "서",
                           "어",
                           "저",
                           "허",
                           "고",
                           "노",
                           "도",
                           "로",
                           "모",
                           "보",
                           "소",
                           "오",
                           "조",
                           "호",
                           "구",
                           "누",
                           "두",
                           "루",
                           "무",
                           "부",
                           "수",
                           "우",
                           "주",
                           "배",
                            "서울",
                            "부산",
                            "대구",
                            "광주",
                            "인천",
                            "대전",
                            "울산",
                            "경기",
                            "강원",
                            "충북",
                            "충남",
                            "전북",
                            "전남",
                            "경북",
                            "경남",
                            "제주",
                            "울",
                            "부",
                            "산",
                            "대",
                            "광",
                            "인",
                            "천",
                            "전",
                            "경",
                            "기",
                            "강",
                            "원",
                            "청",
                            "남",
                            "북",
                            "제"
                            };

    for(const char* item: strCharacters)
        ui->listWidget->addItem(QString::fromLocal8Bit(item));

    //this->setStyleSheet("");
}

CharacterClassifierDialog::~CharacterClassifierDialog()
{
    delete ui;
}

int CharacterClassifierDialog::getCharacterIndex()
{
    return ui->listWidget->currentIndex().row();
}

void CharacterClassifierDialog::on_listWidget_itemClicked(QListWidgetItem *item)
{

}

void CharacterClassifierDialog::on_buttonBox_accepted()
{

}
