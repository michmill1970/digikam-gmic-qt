/* ============================================================
 *
 * This file is a part of digiKam project
 * https://www.digikam.org
 *
 * Date        : 2019-11-28
 * Description : digiKam Batch Queue Manager plugin for GmicQt.
 *
 * SPDX-FileCopyrightText: 2019-2025 by Gilles Caulier <caulier dot gilles at gmail dot com>
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 *
 * ============================================================ */

#pragma once

// Qt includes

#include <QObject>
#include <QVariant>
#include <QAbstractItemModel>
#include <QStyledItemDelegate>
#include <QUndoCommand>
#include <QSortFilterProxyModel>

namespace DigikamBqmGmicQtPlugin
{

class GmicFilterManager;
class GmicFilterNode;
class GmicFilterModel;

class RemoveGmicFilter : public QUndoCommand
{
public:

    explicit RemoveGmicFilter(GmicFilterManager* const mngr,
                              GmicFilterNode* const parent,
                              int row);
    ~RemoveGmicFilter() override;

    void undo()         override;
    void redo()         override;

protected:

    int                m_row     = 0;
    GmicFilterManager* m_manager = nullptr;
    GmicFilterNode*    m_node    = nullptr;
    GmicFilterNode*    m_parent  = nullptr;
    bool               m_done    = false;
};

//---------------------------------------------------------------------------------

class InsertGmicFilter : public RemoveGmicFilter
{
public:

    explicit InsertGmicFilter(GmicFilterManager* const mngr,
                              GmicFilterNode* const parent,
                              GmicFilterNode* const node,
                              int row);

    void undo() override;
    void redo() override;
};

//---------------------------------------------------------------------------------

class ChangeGmicFilter : public QUndoCommand
{
public:

    enum GmicFilterData
    {
        Command = 0,
        Title,
        Desc
    };

public:

    explicit ChangeGmicFilter(GmicFilterManager* const mngr,
                              GmicFilterNode* const node,
                              const QVariant& newValue,
                              GmicFilterData type);
    ~ChangeGmicFilter()   override;

    void undo()           override;
    void redo()           override;

private:

    class Private;
    Private* const d = nullptr;
};

//---------------------------------------------------------------------------------

/**
 *  Proxy model that filters out the Gmic Commands so only the folders
 *  are left behind.  Used in the add command dialog combobox.
 */
class AddGmicFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:

    explicit AddGmicFilterProxyModel(QObject* const parent = nullptr);

    int columnCount(const QModelIndex& parent = QModelIndex())  const override;

protected:

    bool filterAcceptsRow(int srow, const QModelIndex& sparent) const override;
};

//---------------------------------------------------------------------------------

class TreeProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

public:

    explicit TreeProxyModel(QObject* const parent = nullptr);

    int columnCount(const QModelIndex&)                         const override;

Q_SIGNALS:

    void signalFilterAccepts(bool);

protected:

    bool filterAcceptsRow(int srow, const QModelIndex& sparent) const override;

private:

    void emitResult(bool v);
};

//---------------------------------------------------------------------------------

/**
 * Model-View delegate re-implemented to draw the separator node on the tree-view.
 */
class GmicFilterDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:

    explicit GmicFilterDelegate(TreeProxyModel* const pmodel);
    ~GmicFilterDelegate()                       override = default;

    void paint(QPainter* painter, const QStyleOptionViewItem& option,
                const QModelIndex& index) const override;
};

//---------------------------------------------------------------------------------

/**
 *  Gmic Filter manager, owner of the commands, loads, saves and basic tasks
 */
class GmicFilterManager : public QObject
{
    Q_OBJECT

public:

    explicit GmicFilterManager(const QString& file,
                               QObject* const parent = nullptr);
    ~GmicFilterManager()                                              override;

    void addEntry(GmicFilterNode* const parent,
                  GmicFilterNode* const node,
                  int row = -1);

    void removeEntry(GmicFilterNode* const node);

    void setTitle(GmicFilterNode* const node, const QString& newTitle);
    void setCommand(GmicFilterNode* const node, const QString& newCommand);
    void setComment(GmicFilterNode* const node, const QString& newDesc);
    void changeExpanded();

    void setCurrentPath(const QString& cpath);
    QString currentPath()               const;

    GmicFilterNode*  commands();
    GmicFilterModel* commandsModel();
    QUndoStack*      undoRedoStack()    const;

    void save();
    void load();

Q_SIGNALS:

    void signalEntryAdded(GmicFilterNode* item);
    void signalEntryRemoved(GmicFilterNode* parent, int row, GmicFilterNode* item);
    void signalEntryChanged(GmicFilterNode* item);

public Q_SLOTS:

    void slotImportFilters();
    void slotExportFilters();

private:

    class Private;
    Private* const d = nullptr;

    friend class RemoveGmicFilter;
    friend class ChangeGmicFilter;
};

} // namespace DigikamBqmGmicQtPlugin
