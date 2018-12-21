#include "label_img.h"
#include <QPainter>

#define _USE_MATH_DEFINES

#include <math.h>

using std::ifstream;
using std::atan2;
using std::cos;

double Distance(QPointF p1, QPointF p2)
{
    double diffX = p1.x() - p2.x();
    double diffY = p1.y() - p2.y();

    diffX = pow(diffX, 2.0);
    diffY = pow(diffY, 2.0);

    return sqrt(diffX + diffY);
}

double Deg(QPointF p1,QPointF p2)
{
    double deg = atan2(p1.y() - p2.y(), p1.x() - p2.x());
    if(deg < 0) deg += M_PI * 2.0;
    return deg;
}

QPointF Move(QPointF center, double length, double theta)
{
    QPointF movedPoint;
    movedPoint.setX(center.x() - length * cos(theta));
    movedPoint.setY(center.y() - length * sin(theta));

    return movedPoint;
}
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
{
    init();
}

void label_img::mouseMoveEvent(QMouseEvent *ev)
{
    std::cout<< "moved"<< std::endl;

    setMousePosition(ev->x(), ev->y());

    showImage();
    emit Mouse_Moved();
}

void label_img::mousePressEvent(QMouseEvent *ev)
{
    std::cout<< "clicked"<< std::endl;

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
            m_bLabelingStarted = true;
            m_focusedLicensePlatePoints.push_back(m_relative_mouse_pos_in_ui);
        }
        else
        {
            m_focusedLicensePlatePoints.push_back(m_relative_mouse_pos_in_ui);

            if(m_focusedLicensePlatePoints.size() == 4)
            {
                LicensePlateModel lpm;

                double centerX = 0.0,
                       centerY = 0.0;

                for(QPointF licensePlatePoint: m_focusedLicensePlatePoints)
                {
                    centerX += licensePlatePoint.x();
                    centerY += licensePlatePoint.y();
                }

                centerX /= 4.0;
                centerY /= 4.0;

                lpm.center = QPointF(centerX, centerY);

                lpm.lengthCenterToLeftUpper     = Distance(lpm.center, m_focusedLicensePlatePoints[0]);
                lpm.lengthCenterToRightUpper    = Distance(lpm.center, m_focusedLicensePlatePoints[1]);
                lpm.lengthCenterToRightLower    = Distance(lpm.center, m_focusedLicensePlatePoints[2]);
                lpm.lengthCenterToLeftLower     = Distance(lpm.center, m_focusedLicensePlatePoints[3]);

                lpm.degCenterToLeftUpper     = Deg(lpm.center, m_focusedLicensePlatePoints[0]);
                lpm.degCenterToRightUpper    = Deg(lpm.center, m_focusedLicensePlatePoints[1]);
                lpm.degCenterToRightLower    = Deg(lpm.center, m_focusedLicensePlatePoints[2]);
                lpm.degCenterToLeftLower     = Deg(lpm.center, m_focusedLicensePlatePoints[3]);

//                std::cout<< "lpm.degCenterToLeftUpper: " << lpm.degCenterToLeftUpper * 180.0/3.141592 << std::endl;
//                std::cout<< "lpm.degCenterToRightUpper: " << lpm.degCenterToRightUpper* 180.0/3.141592 << std::endl;
//                std::cout<< "lpm.degCenterToLeftLower: " << lpm.degCenterToLeftLower* 180.0/3.141592 << std::endl;
//                std::cout<< "lpm.degCenterToRightLower: " << lpm.degCenterToRightLower* 180.0/3.141592 << std::endl;

                m_LicensePlateModels.push_back(lpm);
                m_focusedLicensePlatePoints.clear();
            }

            showImage();
        }
    }

    emit Mouse_Pressed();
}

void label_img::mouseReleaseEvent(QMouseEvent *ev)
{
    std::cout<< "released"<< std::endl;
    emit Mouse_Release();
}

void label_img::init()
{
    m_LicensePlateModels.clear();
    m_focusedLicensePlatePoints.clear();

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

        m_LicensePlateModels.clear();
        m_focusedLicensePlatePoints.clear();

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

    QImage imageOnUi = m_inputImg.scaled(this->width(), this->height());

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

        for(int i = 0; i < inputFileValues.size(); i += 10)
        {
            try {
                LicensePlateModel lpm;

                lpm.center.setX(inputFileValues.at(i));
                lpm.center.setY(inputFileValues.at(i + 1));

                lpm.lengthCenterToLeftUpper = inputFileValues.at(i + 2);
                lpm.lengthCenterToRightUpper = inputFileValues.at(i + 3);
                lpm.lengthCenterToRightLower =inputFileValues.at(i + 4);
                lpm.lengthCenterToLeftLower = inputFileValues.at(i + 5);

                lpm.degCenterToLeftUpper =inputFileValues.at(i + 6);
                lpm.degCenterToRightUpper =inputFileValues.at(i + 7);
                lpm.degCenterToRightLower=inputFileValues.at(i + 8);
                lpm.degCenterToLeftLower=inputFileValues.at(i + 9);

                m_LicensePlateModels.push_back(lpm);
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

    std::cout <<"absolutePoint.x() = "<< absolutePoint.x() << std::endl;
    //draw cross line
    painter.drawLine(QPoint(absolutePoint.x(),0), QPoint(absolutePoint.x(), this->height() - 1));
    painter.drawLine(QPoint(0,absolutePoint.y()), QPoint(this->width() - 1, absolutePoint.y()));

    std::cout << "draw Cross Line" << std::endl;
}

void label_img::drawFocusedObjectBox(QPainter& painter, Qt::GlobalColor color, int thickWidth)
{
    if(m_bLabelingStarted == true)
    {
        QPen pen;
        pen.setWidth(thickWidth);

        pen.setColor(color);
        painter.setPen(pen);

        for(QPointF licensePlatePointF: m_focusedLicensePlatePoints)
        {
            QPoint licensePlatePoint = cvtRelativeToAbsolutePoint(licensePlatePointF);
            painter.drawEllipse(licensePlatePoint.x(), licensePlatePoint.y(), 2, 2);
        }

        if(m_focusedLicensePlatePoints.size() >= 2)
        {
            for(int i = 1; i < m_focusedLicensePlatePoints.size(); i++)
            {
                QPoint licensePlatePoint1 = cvtRelativeToAbsolutePoint(m_focusedLicensePlatePoints[i]);
                QPoint licensePlatePoint2 = cvtRelativeToAbsolutePoint(m_focusedLicensePlatePoints[i - 1]);

                painter.drawLine(licensePlatePoint1, licensePlatePoint2);
            }

            if(m_focusedLicensePlatePoints.size() == 4)
            {
                QPoint licensePlatePointBegin = cvtRelativeToAbsolutePoint(m_focusedLicensePlatePoints[0]);
                QPoint licensePlatePointLast = cvtRelativeToAbsolutePoint(m_focusedLicensePlatePoints.last());
                painter.drawLine(licensePlatePointBegin, licensePlatePointLast);
            }
        }



        //relative coord to absolute coord

//        QPoint absolutePoint1 = cvtRelativeToAbsolutePoint(m_relatvie_mouse_pos_LBtnClicked_in_ui);
//        QPoint absolutePoint2 = cvtRelativeToAbsolutePoint(m_relative_mouse_pos_in_ui);

//        painter.drawRect(QRect(absolutePoint1, absolutePoint2));
    }
}

void label_img::drawObjectBoxes(QPainter& painter, int thickWidth)
{
    QPen pen;

    pen.setWidth(thickWidth);
    pen.setColor(Qt::GlobalColor::green);
    painter.setPen(pen);

    for(LicensePlateModel licensePlateModel: m_LicensePlateModels)
    {
        QPoint center = cvtRelativeToAbsolutePoint(licensePlateModel.center);
        painter.drawEllipse(center, 2, 2);

        QPointF leftUpperPointf     = Move(licensePlateModel.center, licensePlateModel.lengthCenterToLeftUpper, licensePlateModel.degCenterToLeftUpper);
        QPointF rightUpperPointf    = Move(licensePlateModel.center, licensePlateModel.lengthCenterToRightUpper, licensePlateModel.degCenterToRightUpper);

        QPointF leftLowerPointf     = Move(licensePlateModel.center, licensePlateModel.lengthCenterToLeftLower, licensePlateModel.degCenterToLeftLower);
        QPointF rightLowerPointf    = Move(licensePlateModel.center, licensePlateModel.lengthCenterToRightLower, licensePlateModel.degCenterToRightLower);

        QPoint leftUpperPoint     = cvtRelativeToAbsolutePoint(leftUpperPointf);
        QPoint rightUpperPoint    = cvtRelativeToAbsolutePoint(rightUpperPointf);

        QPoint leftLowerPoint     = cvtRelativeToAbsolutePoint(leftLowerPointf);
        QPoint rightLowerPoint    = cvtRelativeToAbsolutePoint(rightLowerPointf);


//        painter.drawEllipse(leftUpperPoint, 5, 5);
//        painter.drawEllipse(rightUpperPoint, 5, 5);

//        painter.drawEllipse(rightLowerPoint, 5, 5);


        painter.drawLine(leftUpperPoint, rightUpperPoint);
        painter.drawLine(rightUpperPoint, rightLowerPoint);
        painter.drawLine(rightLowerPoint, leftLowerPoint);
        painter.drawLine(leftLowerPoint, leftUpperPoint);


//        painter.drawRect(cvtRelativeToAbsoluteRectInUi(boundingbox.box));
    }
}

void label_img::removeFocusedObjectBox(QPointF point)
{
    int     removeBoxIdx = -1;
    double  nearestBoxDistance   = 99999999999999.;

//    for(int i = 0; i < m_objBoundingBoxes.size(); i++)
//    {
//        QRectF objBox = m_objBoundingBoxes.at(i).box;

//        if(objBox.contains(point))
//        {
//            double distance = objBox.width() + objBox.height();
//            if(distance < nearestBoxDistance)
//            {
//                nearestBoxDistance = distance;
//                removeBoxIdx = i;
//            }
//        }
//    }

//    if(removeBoxIdx != -1)
//    {
//        m_objBoundingBoxes.remove(removeBoxIdx);
//    }
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
