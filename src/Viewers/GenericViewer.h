/**
 * This file is a part of Luminance HDR package.
 * ----------------------------------------------------------------------
 * Copyright (C) 2009 Franco Comida
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * ----------------------------------------------------------------------
 *
 * @author Franco Comida <fcomida@users.sourceforge.net>
 */

#ifndef GENERICVIEWER_H
#define GENERICVIEWER_H

#include <QWidget>
#include <QPixmap>
#include <QVBoxLayout>
#include <QToolBar>
#include <QToolButton>
#include <QStatusBar>
#include <QProgressBar>
#include <QtConcurrentRun>
#include <QFutureWatcher>

#include "SmartScrollArea.h"
#include "Common/PanIconWidget.h"
#include "Common/SelectionTool.h"
#include "Libpfs/frame.h"

class GenericViewer : public QWidget 
{
    Q_OBJECT
public:
    GenericViewer(QWidget *parent = 0, bool ns = false, bool ncf = false);
    virtual ~GenericViewer();

public Q_SLOTS:
    virtual void setLabelPixmap(const QPixmap pix);
    virtual void fitToWindow(bool checked);
    virtual void zoomIn();
    virtual void zoomOut();
    virtual void normalSize();
    virtual bool isFittedToWindow();
    virtual bool hasSelection();
    virtual void setSelectionTool(bool);
    virtual float getScaleFactor();
    virtual const QRect getSelectionRect(void);
    virtual void removeSelection();
    virtual bool needsSaving();
    virtual void setNeedsSaving(bool);
    virtual const QString getFileName();
    virtual void setFileName(const QString);
    virtual int getHorizScrollBarValue();
    virtual int getVertScrollBarValue();
    virtual float getImageScaleFactor();
    virtual void setHorizScrollBarValue(int value);
    virtual void setVertScrollBarValue(int value);
    virtual void zoomToFactor(float factor);
    virtual bool isHDR() = 0;
    virtual void levelsRequested(bool) = 0; // only used by LdrViewer
    virtual QString getFilenamePostFix() = 0; // only used by LdrViewer
    virtual QString getExifComment() = 0; // only used by LdrViewer
    virtual const QImage* getQImage() = 0; // only used by LdrViewer

    //TODO: this function will become virtual when I redevelop (Ldr/Hdr)Viewer
    virtual pfs::Frame* getHDRPfsFrame() { return NULL; }
    //TODO: check this function!
    virtual void updateHDR(pfs::Frame*) { }

protected Q_SLOTS:
    virtual void slotPanIconSelectionMoved(QRect);
    virtual void slotPanIconHidden();
    virtual void slotCornerButtonPressed();
    virtual void route_changed();

protected:
    virtual void closeEvent ( QCloseEvent * event );

    QLabel imageLabel;
    QVBoxLayout *VBL_L;
    QToolBar *toolBar;
    QToolButton *cornerButton;
    SmartScrollArea *scrollArea;
    PanIconWidget *panIconWidget;

    QString filename;
    QImage *m_image;
    int m_cols;
    int m_rows;

    bool NeedsSaving;
    bool noCloseFlag;
    bool isSelectionToolVisible;

Q_SIGNALS:
    void selectionReady(bool isReady);
    void changed(GenericViewer *v);     // emitted when zoomed in/out, scrolled ....
    void levels_closed(bool isReady);   // only used by LdrViewer
    void closeRequested(bool);          // emitted when NoCloseFlag is true

    // SIGNALS
    void S_init();
    void S_setMaximum(int x);
    void S_setValue(int x);
    void S_end();
};

#endif
