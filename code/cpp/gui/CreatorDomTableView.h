#pragma once

#include <vector>
#include <QTableView>

class CreatorLinearDomTableModel;

class CreatorDomTableView : public QTableView
{
    Q_OBJECT
public:
    CreatorDomTableView(QWidget* parent = nullptr);

    QString     selectionAsDomSequence  () const;
    void        setLinearDomTableModel  (CreatorLinearDomTableModel *model);

    void        fontPointSizeSet        (int pointSize);
    int         fontPointSize           () const;
    void        fontPointSizeChange     (int deltaPointSize);

signals:
    void        domPosClickedSig        (int domPos); // Only connect to either of these two. Currently domPosClickedSig() is used
    void        domPositionsMarkedSig   (std::vector<int> domPositions);

public slots:
    void        selectDomPosSlot            (int pos);

private slots:
    void        cellClickedSlot         (const QModelIndex& index);

protected:
    void        wheelEvent              (QWheelEvent* event) override;
    void        keyPressEvent           (QKeyEvent * event) override;

private:
    CreatorLinearDomTableModel* m_linearDomTableModel;
};

