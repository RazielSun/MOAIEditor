#include <QDockWidget>
#include <QTextEdit>

class LogDock : public QDockWidget
{
	Q_OBJECT

public:
	LogDock(const QString & title, QWidget * parent = 0);
	virtual ~LogDock();

protected:
	void createTextView();

private:
	QTextEdit *textViewer;
};