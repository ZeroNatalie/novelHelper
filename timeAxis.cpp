#include "timeAxis.h"
void TimeAxisWidget::drawTitle(QPainter *painter)
{
    painter->save();

    QFont font;
    font.setBold(true);
    font.setPointSize(16);
    painter->setFont(font);

    painter->setPen(baseColor);
    painter->drawText(itemMargin, itemMargin, width() - 2 * itemMargin, 40, Qt::AlignCenter, title);

    painter->restore();
}

void TimeAxisWidget::drawLine(QPainter *painter)
{
    painter->save();
    painter->setPen(QPen(lineColor, 6));
    int startY = itemMargin + 50;
    int endY = startY + itemInfos.size() * itemHeight;
    painter->drawLine(width() / 2.0, startY, width() / 2.0, endY);
    painter->restore();

    //设置下固定高度
    this->setFixedHeight(endY + itemMargin);
}

void TimeAxisWidget::drawInfo(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QFont font;
    font.setPointSize(12);
    painter->setFont(font);

    int startY = itemMargin + 50;
    int centerX = this->width() / 2.0;
    int spacer = itemMargin + 10;

    //追个绘制时间轴信息集合,偶数行左侧绘制时间右侧绘制信息
    for (int i = 0; i < itemInfos.size(); i++) {
        painter->setBrush(Qt::white);
        painter->setPen(QPen(baseColor, 2));

        if (i % 2 == 0) {
            //绘制时间
            QRectF textRect(0, startY, centerX - spacer, itemHeight);
            painter->drawText(textRect, Qt::AlignRight | Qt::AlignVCenter, itemInfos.at(i).time);
            //绘制信息边框
            QRectF infoRect(centerX + spacer, textRect.center().y() - infoHeight / 2.0, centerX - spacer - itemMargin - infoHeight / 2.0, infoHeight);
            drawInfoRight(painter, infoRect, infoHeight);
            //绘制信息背景
            painter->setBrush(baseColor);
            drawInfoRight(painter, infoRect.adjusted(infoPadding, infoPadding, 0, -infoPadding), infoHeight - infoPadding * 2);
            //绘制信息文字
            painter->setPen(Qt::white);
            painter->drawText(infoRect.adjusted(infoPadding, infoPadding, 0, -infoPadding), Qt::AlignCenter, itemInfos.at(i).info);
        } else {
            //绘制时间
            QRectF textRect(centerX + spacer, startY, centerX - spacer, itemHeight);
            painter->drawText(centerX + spacer, startY, centerX - spacer, itemHeight, Qt::AlignLeft | Qt::AlignVCenter, itemInfos.at(i).time);
            //绘制信息边框
            QRectF infoRect(itemMargin + infoHeight / 2.0, textRect.center().y() - infoHeight / 2.0, centerX - spacer - itemMargin - infoHeight / 2.0, infoHeight);
            drawInfoLeft(painter, infoRect, infoHeight);
            //绘制信息背景
            painter->setBrush(baseColor);
            drawInfoLeft(painter, infoRect.adjusted(0, infoPadding, -infoPadding, -infoPadding), infoHeight - infoPadding * 2);
            //绘制信息文字
            painter->setPen(Qt::white);
            painter->drawText(infoRect.adjusted(0, infoPadding, -infoPadding, -infoPadding), Qt::AlignCenter, itemInfos.at(i).info);
        }

        //绘制垂直线对应的圆
        painter->setPen(Qt::NoPen);
        painter->setBrush(baseColor);
        painter->drawEllipse(centerX - 8, startY + itemHeight / 2.0 - 8, 16, 16);
        painter->setBrush(Qt::white);
        painter->drawEllipse(centerX - 4, startY + itemHeight / 2.0 - 4, 8, 8);

        //Y轴往下移一个高度
        startY += itemHeight;
    }

    painter->restore();
}
