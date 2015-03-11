#include <QtGui>

#include "MOAIWidget.h"
#include "LogDock.h"

#include "ui_mainwindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow();
    virtual ~MainWindow();

protected:
    void createActions();
	void createMenus();
	void createDocks();

	void loadSettings();
    void saveSettings();

    void loadProject();

private slots:
	void showOpenProjectDialog();
	void reloadMoai();

private:
	QString settingsFile;
	QString moaiProjectPath;

    Ui::MainWindow *ui;
    
	QScrollArea *scrollArea;
	MOAIWidget *moaiWidget;

	QMenu *menuView;
	LogDock *logDock;
	QFileDialog *fileDialog;
};