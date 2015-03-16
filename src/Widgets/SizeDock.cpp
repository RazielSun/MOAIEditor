#include "SizeDock.h"

SizeDock::SizeDock(const QString & title, QWidget * parent) : QDockWidget(title, parent), ui(new Ui::SizeDock)
{
    ui->setupUi(this);
    
	dWidth = 320;
	dHeight = 480;
	dDpi = 100;

	initObjects();
};

SizeDock::~SizeDock()
{
	delete ui;
};

void SizeDock::initObjects()
{
    widthEdit = this->findChild<QLineEdit*>("widthEdit");
    heightEdit = this->findChild<QLineEdit*>("heightEdit");
    dpiEdit = this->findChild<QLineEdit*>("dpiEdit");
};

void SizeDock::clickResize(int w, int h)
{
    printf( "w:%d h:%d", w, h );
};

// SLOTS

void SizeDock::clickResizePad() { clickResize(368, 512); };
void SizeDock::clickResizePadL() { clickResize(512, 368); };
void SizeDock::clickResizePhone() { clickResize(320, 480); };
void SizeDock::clickResizePhoneL() { clickResize(480, 320); };
void SizeDock::clickResizePhoneH() { clickResize(320, 568); };
void SizeDock::clickResizePhoneHL() { clickResize(568, 320); };