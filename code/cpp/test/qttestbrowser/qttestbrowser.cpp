/*
 * Copyright (C) 2015 The Qt Company Ltd.
 * Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies)
 * Copyright (C) 2009 Girish Ramakrishnan <girish@forwardbias.in>
 * Copyright (C) 2006 George Staikos <staikos@kde.org>
 * Copyright (C) 2006 Dirk Mueller <mueller@kde.org>
 * Copyright (C) 2006 Zack Rusin <zack@kde.org>
 * Copyright (C) 2006 Simon Hausmann <hausmann@kde.org>
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

//#include "config.h"

#include "launcherapplication.h"
#include "launcherwindow.h"
#include "urlloader.h"

//#if HAVE(QTTESTSUPPORT)
//#include "QtTestSupport.h"
//#endif

WindowOptions windowOptions;

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QFontDatabase>
#include <QRegExp>

int launcherMain(const QApplication& app)
{
#ifndef NDEBUG
    int retVal = app.exec();

//#if HAVE(QTTESTSUPPORT)
//    WebKit::QtTestSupport::garbageCollectorCollect();
//#endif

    QWebSettings::clearMemoryCaches();
    return retVal;
//#else
    return app.exec();
#endif
}


int main(int argc, char **argv)
{
    LauncherApplication app(argc, argv);

    if (app.isRobotized()) {
        LauncherWindow* window = new LauncherWindow();
        UrlLoader loader(window->page()->mainFrame(), app.urls().at(0), app.robotTimeout(), app.robotExtraTime());
        loader.loadNext();
        window->show();
        return launcherMain(app);
    }

    QStringList urls = app.urls();

    if (urls.isEmpty()) {
        QString defaultIndexFile = QString("%1/%2").arg(QDir::homePath()).arg(QLatin1String("index.html"));
        if (QFile(defaultIndexFile).exists())
            urls.append(QString("file://") + defaultIndexFile);
        else
            urls.append("https://www.hargrovescycles.co.uk/100-s2-hiper-lens-sunglasses.html");
    }

    LauncherWindow* window = 0;
    foreach (QString url, urls) {
        LauncherWindow* newWindow;
        if (!window)
            newWindow = window = new LauncherWindow(&windowOptions);
        else
            newWindow = window->newWindow();

        newWindow->load(url);
    }

    window->show();
    return launcherMain(app);
}

///#include "qttestbrowser.moc"
