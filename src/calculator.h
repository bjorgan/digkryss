/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>

class QLineEdit;
class Button;

class Calculator : public QWidget {
	Q_OBJECT
	public:
		Calculator(int displayHeight, int displayWidth, QWidget *parent = 0);
		double getDisplayedAmount();
	private slots:
		void digitClicked();
		void unaryOperatorClicked();
		void additiveOperatorClicked();
		void multiplicativeOperatorClicked();
		void equalClicked();
		void pointClicked();
		void backspaceClicked();
		void clearAll();
	private:
		Button *createButton(const QString &text, const char *member);
		void abortOperation();
		bool calculate(double rightOperand, const QString &pendingOperator);
		double sumInMemory;
		double sumSoFar;
		double factorSoFar;
		QString pendingAdditiveOperator;
		QString pendingMultiplicativeOperator;
		bool waitingForOperand;
		QLineEdit *display;
		enum { NumDigitButtons = 10 };
		Button *digitButtons[NumDigitButtons];
};

#include <QToolButton>

class Button : public QToolButton {
	Q_OBJECT
	public:
		explicit Button(const QString &text, QWidget *parent = 0);
		QSize sizeHint() const Q_DECL_OVERRIDE;
};

#endif
