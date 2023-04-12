#include "CreatorDomTableView.h"

#include <iostream>
#include <algorithm>
#include <QItemSelectionModel>
#include <QKeyEvent>
#include <QApplication>
#include <QClipboard>
#include <QHeaderView>
#include <QFontMetrics>

#include <math/base/utils.hpp>
#include <interfaces/Globals.h>
#include <GuiGlobals.h>
#include "CreatorLinearDomTableModel.h"

using namespace std;
using namespace crawl;


CreatorDomTableView::CreatorDomTableView(QWidget* parent)
    : QTableView(parent)
{
    horizontalHeader()->setStretchLastSection(true);
    horizontalHeader()->hide();

    hideRow(1);
    setShowGrid(false);
    //setRowHidden(2, true);
    //QHeaderView* vh = verticalHeader();
    verticalHeader()->sectionResizeMode(QHeaderView::Fixed);
    connect(this, &CreatorDomTableView::clicked, this, &CreatorDomTableView::cellClickedSlot);
}

QString CreatorDomTableView::selectionAsDomSequence() const
{
    QString seq;
    QItemSelectionModel* selection = selectionModel();
    QModelIndexList indexes = selection->selectedIndexes();

    if(indexes.size() < 1)
        return "";

    std::sort(indexes.begin(), indexes.end()); // Necessary, otherwise they are in column order

    int prevDomPos = 0; // To determine when to insert '*' or '?'
    int count = 0;
    foreach (const QModelIndex& cell, indexes) {
        if (prevDomPos == 0)
            prevDomPos = cell.row() -1; // Initialise prevDomPos correctly

        const int curDomPos = cell.row();
        if (count++ > 0)
            seq += ", ";

        const int deltaPositions = curDomPos - prevDomPos ;
        if (deltaPositions == 2)
            seq += "?, ";
        else if (deltaPositions > 2)
            seq += "*, ";
        seq += cell.data().toString();

        prevDomPos = curDomPos;
     }
    return seq;
}

void CreatorDomTableView::setLinearDomTableModel(CreatorLinearDomTableModel* model)
{
    m_linearDomTableModel = model;
    fontPointSizeSet(g()->gui()->linearDomTableViewFontPointSize());
    setModel(model);
}

void CreatorDomTableView::fontPointSizeSet(int pointSize)
{
    if (!m_linearDomTableModel) return;
    m_linearDomTableModel->fontPointSizeSet(pointSize);
    QFontMetrics fm(m_linearDomTableModel->font());

    verticalHeader()->setDefaultSectionSize(fm.height());
    g()->gui()->linearDomTableViewFontPointSizeSet(fontPointSize());
}

int CreatorDomTableView::fontPointSize() const
{
    if (!m_linearDomTableModel) return 0;
    return m_linearDomTableModel->fontPointSize();
}

void CreatorDomTableView::fontPointSizeChange(int deltaPointSize)
{
    if (!m_linearDomTableModel) return;
    fontPointSizeSet(fontPointSize() + deltaPointSize);
}

void CreatorDomTableView::selectDomPosSlot(int pos)
{
    QItemSelectionModel* selection = selectionModel();
    selection->clear();
    QModelIndex index = model()->index(pos, 0);
    setCurrentIndex(index);
}

void CreatorDomTableView::cellClickedSlot(const QModelIndex& index)
{
    std::vector<int> domPositions;
    for (const QModelIndex& i : selectedIndexes()) {
        domPositions.push_back(i.row());
    }
    if (domPositions.empty()) {
        domPositions.push_back(index.row());
    }

    emit domPositionsMarkedSig(domPositions);
    emit domPosClickedSig(index.row());
}

void CreatorDomTableView::wheelEvent(QWheelEvent* event)
{
    if (event->modifiers() & Qt::ControlModifier ) {
        const int zoomDelta = cpaf::math::clamp_copy(event->angleDelta().y(), -1, 1);
        fontPointSizeChange(zoomDelta);
        event->accept();
        return;
    }
    QTableView::wheelEvent(event);
}

void CreatorDomTableView::keyPressEvent(QKeyEvent* event)
{
    const auto &&key = event->key();
    const auto &&modifiers = event->modifiers();
    if (key == Qt::Key_C ) {
        if (modifiers & Qt::ControlModifier) {
            if (modifiers & Qt::ShiftModifier) {
                QString seq = "domSeqCreate(\"xx__FIND\", ";
                seq += "\"" + selectionAsDomSequence() + "\", ";
                seq += "\"contains\", 0);\n";
                QApplication::clipboard()->setText(seq);
                event->accept();
                return;
            }
            else if (modifiers & Qt::AltModifier) {
                QString seq = "domFind(";
                seq += "\"" + selectionAsDomSequence() + "\", ";
                seq += "\"contains\");\n";
                QApplication::clipboard()->setText(seq);
                event->accept();
                return;
            }
            else if (event->matches(QKeySequence::Copy)) {
                const QString seq = selectionAsDomSequence();
                QApplication::clipboard()->setText(seq);
                event->accept();
                return;
            }
        }
    }
    else if (key == Qt::Key_Plus) {
        if (modifiers & Qt::ControlModifier) {
            fontPointSizeChange(1);
            event->accept();
            return;
        }
    }
    else if (key == Qt::Key_Minus) {
        if (modifiers & Qt::ControlModifier) {
            fontPointSizeChange(-1);
            event->accept();
            return;
        }
    }

    QTableView::keyPressEvent(event);
}
