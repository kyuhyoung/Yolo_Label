#include "label_img.h"
#include "characterclassifierdialog.h"
#include <QPainter>
#include <QString>

using std::ifstream;

QColor label_img::BOX_COLORS[10] ={  Qt::green,
        Qt::darkGreen,
        Qt::blue,
        Qt::darkBlue,
        Qt::yellow,
        Qt::darkYellow,
        Qt::red,
        Qt::darkRed,
        Qt::cyan,
        Qt::darkCyan};

label_img::label_img(QWidget *parent)
    :QLabel(parent)
    ,m_bSaveCharacter(false)
{
    init();
}

void label_img::mouseMoveEvent(QMouseEvent *ev)
{
    setMousePosition(ev->x(), ev->y());

    showImage();
    emit Mouse_Moved();
}

void label_img::mousePressEvent(QMouseEvent *ev)
{
    setMousePosition(ev->x(), ev->y());

    if(ev->button() == Qt::RightButton)
    {
        removeFocusedObjectBox(m_relative_mouse_pos_in_ui);
        showImage();
    }
    else if(ev->button() == Qt::LeftButton)
    {
        if(m_bLabelingStarted == false)
        {
            m_relatvie_mouse_pos_LBtnClicked_in_ui      = m_relative_mouse_pos_in_ui;
            m_bLabelingStarted                          = true;
        }
        else
        {
            ObjectLabelingBox objBoundingbox;

            objBoundingbox.label    = m_focusedObjectLabel;
            objBoundingbox.box      = getRelativeRectFromTwoPoints(m_relative_mouse_pos_in_ui,
                                                                   m_relatvie_mouse_pos_LBtnClicked_in_ui);

            bool width_is_too_small     = objBoundingbox.box.width()  < 0.01;
            bool height_is_too_small    = objBoundingbox.box.height() < 0.01;

            if(!width_is_too_small && !height_is_too_small)
                m_objBoundingBoxes.push_back(objBoundingbox);

            m_bLabelingStarted              = false;

            if(m_bSaveCharacter == true)
            {
            CharacterClassifierDialog* CCD = new CharacterClassifierDialog();

            if(CCD->exec() == QDialog::Accepted && CCD->getCharacterIndex() != -1)
            {
                std::cout<< "kk" << CCD->getCharacterIndex() <<std::endl;
                QImage characterImage = crop(cvtRelativeToAbsoluteRectInImage(objBoundingbox.box));

                QString strCharacters[] = {"0",
                                        "1",
                                        "2",
                                        "3",
                                        "4",
                                        "5",
                                        "6",
                                        "7",
                                        "8",
                                        "9",
                                        "Ga",
                                        "Na",
                                        "Da",
                                        "Ra",
                                        "Ma",
                                       "Ba",
                                       "Sa",
                                       "A",
                                       "Ja",
                                        "Ha",
                                        "Geo",
                                        "Neo",
                                        "Deo",
                                        "Reo",
                                        "Meo",
                                        "Beo",
                                        "Seo",
                                        "Eo",
                                        "Jeo",
                                        "Heo",
                                        "Go",
                                        "No",
                                        "Do",
                                        "Ro",
                                        "Mo",
                                        "Bo",
                                        "So",
                                        "O",
                                        "Jo",
                                        "Ho" ,
                                        "Gu",
                                        "Nu",
                                        "Du",
                                        "Ru",
                                        "Mu",
                                        "Bu",
                                        "Su",
                                        "U",
                                        "Ju",
                                        "Bae",
                                        "Seoul",
                                        "Busan",
                                        "Daegu",
                                        "Gwangju",
                                        "Incheon",
                                        "Daejeon",
                                        "Ulsan",
                                        "Gyeonggi",
                                        "Gangwon",
                                        "Chungbuk",
                                        "Chungnam",
                                        "Jeonbuk",
                                        "Jeonnam",
                                        "Gyeongbuk",
                                        "Gyeongnam",
                                        "Jeju",
                                        "Ul",
                                        "Bu",
                                        "San",
                                        "Dae",
                                        "Gwang",
                                        "In",
                                        "Cheon",
                                        "Jeon",
                                        "Gyeong",
                                        "Gi",
                                        "Gang",
                                        "Won",
                                        "Chung",
                                        "Nam",
                                        "Buk",
                                        "Je"};

                std::string strImgFile   = m_imgFileName.toStdString();

                strImgFile = strImgFile.substr( strImgFile.find_last_of('/') + 1,
                                                strImgFile.find_last_of('.') - strImgFile.find_last_of('/') - 1);


                characterImage.save(QString("CroppedCharacters/")
                                    + strCharacters[CCD->getCharacterIndex()]
                                    + "/"
                                    + QString().fromStdString(strImgFile)
                                    + "_character_"
                                    + QString::number(m_charNum++)
                                    + ".png");
            };

            delete CCD;
            }

            showImage();
        }
    }

    emit Mouse_Pressed();
}

void label_img::mouseReleaseEvent(QMouseEvent *ev)
{
    emit Mouse_Release();
}

void label_img::init()
{
    m_objBoundingBoxes.clear();
    m_bLabelingStarted              = false;
    m_focusedObjectLabel            = 0;

    QPoint mousePosInUi = this->mapFromGlobal(QCursor::pos());
    bool mouse_is_in_image = QRect(0, 0, this->width(), this->height()).contains(mousePosInUi);

    if  (mouse_is_in_image)
    {
        setMousePosition(mousePosInUi.x(), mousePosInUi.y());
    }
    else
    {
        setMousePosition(0., 0.);
    }
}

void label_img::setMousePosition(int x, int y)
{
    if(x < 0) x = 0;
    if(y < 0) y = 0;

    if(x > this->width())   x = this->width() - 1;
    if(y > this->height())  y = this->height() - 1;

    m_relative_mouse_pos_in_ui = cvtAbsoluteToRelativePoint(QPoint(x, y));
}

void label_img::openImage(const QString &qstrImg, bool &ret)
{
    QImage img(qstrImg);

    if(img.isNull())
    {
        m_inputImg = QImage();
        ret = false;
    }
    else
    {
        ret = true;

        m_objBoundingBoxes.clear();

        m_imgFileName       = qstrImg;
        m_charNum           = 0 ;
        m_inputImg          = img.copy();
        m_inputImg          = m_inputImg.convertToFormat(QImage::Format_RGB888);

        m_bLabelingStarted  = false;

        QPoint mousePosInUi     = this->mapFromGlobal(QCursor::pos());
        bool mouse_is_in_image  = QRect(0, 0, this->width(), this->height()).contains(mousePosInUi);

        if  (mouse_is_in_image)
        {
            setMousePosition(mousePosInUi.x(), mousePosInUi.y());
        }
        else
        {
            setMousePosition(0., 0.);
        }
    }
}

void label_img::showImage()
{
    if(m_inputImg.isNull()) return;

    QImage imageOnUi = m_inputImg.scaled(this->width(), this->height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);

    QPainter painter(&imageOnUi);

    int penThick = 3;

    QColor crossLineColor(255, 187, 0);

    drawCrossLine(painter, crossLineColor, penThick);
    drawFocusedObjectBox(painter, Qt::magenta, penThick);
    drawObjectBoxes(painter, penThick);

    this->setPixmap(QPixmap::fromImage(imageOnUi));
}

void label_img::loadLabelData(const QString& labelFilePath)
{
    ifstream inputFile(labelFilePath.toStdString());

    if(inputFile.is_open())
    {
        double          inputFileValue;
        QVector<double> inputFileValues;

        while(inputFile >> inputFileValue)
            inputFileValues.push_back(inputFileValue);

        for(int i = 0; i < inputFileValues.size(); i += 5)
        {
            try {
                ObjectLabelingBox objBox;

                objBox.label = static_cast<int>(inputFileValues.at(i));

                double midX     = inputFileValues.at(i + 1);
                double midY     = inputFileValues.at(i + 2);
                double width    = inputFileValues.at(i + 3);
                double height   = inputFileValues.at(i + 4);

                double leftX    = midX - width/2.;
                double topY     = midY - height/2.;

                objBox.box.setX(leftX); // translation: midX -> leftX
                objBox.box.setY(topY); // translation: midY -> topY
                objBox.box.setWidth(width);
                objBox.box.setHeight(height);

                m_objBoundingBoxes.push_back(objBox);
            }
            catch (const std::out_of_range& e) {
                std::cout << "loadLabelData: Out of Range error.";
            }
        }
    }
}

void label_img::setFocusObjectLabel(int nLabel)
{
    m_focusedObjectLabel = nLabel;
}

void label_img::setFocusObjectName(QString qstrName)
{
    m_foucsedObjectName = qstrName;
}

void label_img::setSaveCharacter(bool b)
{
    m_bSaveCharacter = b;
}

bool label_img::isOpened()
{
    return !m_inputImg.isNull();
}

QImage label_img::crop(QRect rect)
{
    return m_inputImg.copy(rect);
}

void label_img::drawCrossLine(QPainter& painter, QColor color, int thickWidth)
{
    if(m_relative_mouse_pos_in_ui == QPointF(0., 0.)) return;

    QPen pen;
    pen.setWidth(thickWidth);

    pen.setColor(color);
    painter.setPen(pen);

    QPoint absolutePoint = cvtRelativeToAbsolutePoint(m_relative_mouse_pos_in_ui);

    //draw cross line
    painter.drawLine(QPoint(absolutePoint.x(),0), QPoint(absolutePoint.x(), this->height() - 1));
    painter.drawLine(QPoint(0,absolutePoint.y()), QPoint(this->width() - 1, absolutePoint.y()));
}

void label_img::drawFocusedObjectBox(QPainter& painter, Qt::GlobalColor color, int thickWidth)
{
    if(m_bLabelingStarted == true)
    {
        QPen pen;
        pen.setWidth(thickWidth);

        pen.setColor(color);
        painter.setPen(pen);

        //relative coord to absolute coord

        QPoint absolutePoint1 = cvtRelativeToAbsolutePoint(m_relatvie_mouse_pos_LBtnClicked_in_ui);
        QPoint absolutePoint2 = cvtRelativeToAbsolutePoint(m_relative_mouse_pos_in_ui);

        painter.drawRect(QRect(absolutePoint1, absolutePoint2));
    }
}

void label_img::drawObjectBoxes(QPainter& painter, int thickWidth)
{
    QPen pen;
    pen.setWidth(thickWidth);

    for(ObjectLabelingBox boundingbox: m_objBoundingBoxes)
    {
        pen.setColor(m_drawObjectBoxColor.at(boundingbox.label));
        painter.setPen(pen);

        painter.drawRect(cvtRelativeToAbsoluteRectInUi(boundingbox.box));
    }
}

void label_img::removeFocusedObjectBox(QPointF point)
{
    int     removeBoxIdx = -1;
    double  nearestBoxDistance   = 99999999999999.;

    for(int i = 0; i < m_objBoundingBoxes.size(); i++)
    {
        QRectF objBox = m_objBoundingBoxes.at(i).box;

        if(objBox.contains(point))
        {
            double distance = objBox.width() + objBox.height();
            if(distance < nearestBoxDistance)
            {
                nearestBoxDistance = distance;
                removeBoxIdx = i;
            }
        }
    }

    if(removeBoxIdx != -1)
    {
        m_objBoundingBoxes.remove(removeBoxIdx);
    }
}

QRectF label_img::getRelativeRectFromTwoPoints(QPointF p1, QPointF p2)
{
    double midX    = (p1.x() + p2.x()) / 2.;
    double midY    = (p1.y() + p2.y()) / 2.;
    double width   = fabs(p1.x() - p2.x());
    double height  = fabs(p1.y() - p2.y());

    QPointF topLeftPoint(midX - width/2., midY - height/2.);
    QPointF bottomRightPoint(midX + width/2., midY + height/2.);

    return QRectF(topLeftPoint, bottomRightPoint);
}

QRect label_img::cvtRelativeToAbsoluteRectInUi(QRectF rectF)
{
    return QRect(static_cast<int>(rectF.x() * this->width() + 0.5),
                 static_cast<int>(rectF.y() * this->height()+ 0.5),
                 static_cast<int>(rectF.width() * this->width()+ 0.5),
                 static_cast<int>(rectF.height()* this->height()+ 0.5));
}

QRect label_img::cvtRelativeToAbsoluteRectInImage(QRectF rectF)
{
    return QRect(static_cast<int>(rectF.x() * m_inputImg.width()),
                 static_cast<int>(rectF.y() * m_inputImg.height()),
                 static_cast<int>(rectF.width() * m_inputImg.width()),
                 static_cast<int>(rectF.height()* m_inputImg.height()));
}

QPoint label_img::cvtRelativeToAbsolutePoint(QPointF p)
{
    return QPoint(static_cast<int>(p.x() * this->width() + 0.5), static_cast<int>(p.y() * this->height() + 0.5));
}

QPointF label_img::cvtAbsoluteToRelativePoint(QPoint p)
{
    return QPointF(static_cast<double>(p.x()) / this->width(), static_cast<double>(p.y()) / this->height());
}
