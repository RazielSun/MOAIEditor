#include "LogDock.h"

LogDock::LogDock(const QString & title, QWidget * parent) : QDockWidget(title, parent)
{
	createTextView();

	resize(width(), 120);
};

LogDock::~LogDock()
{
	//
};

void LogDock::createTextView()
{
	textViewer = new QTextEdit;
    textViewer->setReadOnly(true);
    setWidget(textViewer);
};