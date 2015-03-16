#include "MainWindow.h"

MainWindow::MainWindow() : ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    
    moaiProjectPath = "";
    settingsFile = QApplication::applicationDirPath() + "Settings/settings.ini";
    loadSettings();
    
    moaiWidget = MOAIWidget::getInstance();
    
    scrollArea = new QScrollArea( this );
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(moaiWidget);
    scrollArea->setAlignment(Qt::AlignCenter);
    setCentralWidget(scrollArea);
    
	createActions();
	createMenus();
    createDocks();

    loadProject();
};

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
};

void MainWindow::showOpenProjectDialog()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Project"), "/", tr("Lua (main.lua)"));
    if (fileName != NULL)
    {
        QFileInfo fileInfo = QFileInfo(fileName);
        moaiProjectPath = fileInfo.dir().path();
        loadProject();
    }
};

void MainWindow::reloadMoai()
{
    moaiWidget->refreshContext();
    loadProject();
};

void MainWindow::createActions()
{
};

void MainWindow::createMenus()
{
    menuView = qFindChild<QMenu*>(this, "menuView");
};

void MainWindow::createDocks()
{
    //logDock = new LogDock( tr("Log"), this );
    //addDockWidget(Qt::BottomDockWidgetArea, logDock);
    //menuView->addAction(logDock->toggleViewAction());
};

void MainWindow::loadSettings()
{
    QSettings settings(settingsFile, QSettings::NativeFormat);
    moaiProjectPath = settings.value("moaiProjectPath", "").toString();
    restoreGeometry(settings.value("main/geometry").toByteArray());
    restoreState(settings.value("main/windowState").toByteArray());
};
 
void MainWindow::saveSettings()
{
    QSettings settings(settingsFile, QSettings::NativeFormat);
    settings.setValue("moaiProjectPath", moaiProjectPath);
    settings.setValue("main/geometry", saveGeometry());
    settings.setValue("main/windowState", saveState());
};

void MainWindow::loadProject()
{
    if (moaiProjectPath != NULL)
    {
        moaiWidget->setWorkingDirectory(moaiProjectPath.toUtf8().constData());
        moaiWidget->runScript("main.lua");
    }
};