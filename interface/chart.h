#ifndef CHART_H
#define CHART_H

#include <QQuickPaintedItem>
#include <QPainter>

class ChartItem : public QQuickPaintedItem
{
    Q_OBJECT

private:
    QVector<QPointF> m_chartPoints;

public:
    ChartItem(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override;

    QVector<QPointF>& chartPoints() { return m_chartPoints; };
    void setChartPoints(QVector<QPointF> chartPoints) { m_chartPoints = chartPoints; };
    void updateChartData(const QVector<QPointF>& chartPoints);
};

#endif // CHART_H
