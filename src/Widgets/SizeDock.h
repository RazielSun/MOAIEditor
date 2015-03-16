#include <QDockWidget>
#include <QLineEdit>
#include <QPushButton>

#include "ui_sizedock.h"

class SizeDock : public QDockWidget
{
	Q_OBJECT

public:
	SizeDock(const QString & title, QWidget * parent = 0);
	virtual ~SizeDock();

protected:
	void initObjects();
	void clickResize(int w, int h);

private slots:
	void clickResizePad();
	void clickResizePadL();
	void clickResizePhone();
	void clickResizePhoneL();
	void clickResizePhoneH();
	void clickResizePhoneHL();

private:
    Ui::SizeDock *ui;
    
	QLineEdit *widthEdit;
	QLineEdit *heightEdit;
	QLineEdit *dpiEdit;

	int dWidth;
	int dHeight;
	int dDpi;
};