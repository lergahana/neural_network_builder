#include "chart.h"
#include <cmath>

ChartItem::ChartItem(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{

}

void ChartItem::paint(QPainter* painter)
{
    int padding = 20;
    QRectF chartArea(5, padding, 180, 180);

    // Calculate the range of data values
    qreal minX = std::numeric_limits<qreal>::max();
    qreal maxX = std::numeric_limits<qreal>::min();
    qreal minY = std::numeric_limits<qreal>::max();
    qreal maxY = std::numeric_limits<qreal>::min();

    // Define the chart area
    if (!m_chartPoints.isEmpty()) {
        for (const QPointF& point : m_chartPoints) {
            minX = std::min(minX, point.x());
            maxX = std::max(maxX, point.x());
            minY = std::min(minY, point.y());
            maxY = std::max(maxY, point.y());
        }
    }

    // Set the pen properties
    QPen pen(Qt::black);
    pen.setWidth(2);
    painter->setPen(pen);

    // Draw the x-axis
    painter->drawLine(chartArea.bottomLeft(), chartArea.bottomRight());
    // Draw the y-axis
    painter->drawLine(chartArea.bottomLeft(), chartArea.topLeft());

    // Set the pen properties for the line chart
    pen.setColor(Qt::green);
    painter->setPen(pen);

    // Draw the line chart
    for (int i = 0; i < m_chartPoints.size() - 1; ++i) {
        QPointF p1 = m_chartPoints[i];
        QPointF p2 = m_chartPoints[i + 1];

        // Map data coordinates to chart pixel coordinates
        QPointF mappedP1(chartArea.left() + ((p1.x() - minX) / (maxX - minX)) * chartArea.width(),
                         chartArea.bottom() - ((p1.y() - minY) / (maxY - minY)) * chartArea.height()-padding);
        QPointF mappedP2(chartArea.left() + ((p2.x() - minX) / (maxX - minX)) * chartArea.width(),
                         chartArea.bottom() - ((p2.y() - minY) / (maxY - minY)) * chartArea.height()-padding);

        painter->drawLine(mappedP1, mappedP2);
    }
}


void ChartItem::updateChartData(const QVector<QPointF>& chartPoints)
{
    m_chartPoints = chartPoints;
    update(); // Trigger a repaint of the chart item
}

