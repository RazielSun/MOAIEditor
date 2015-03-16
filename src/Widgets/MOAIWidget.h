#include <QGLWidget>
#include <QTimer>

#include <host-modules/aku_modules.h>

#include "ParticlePresets.h"

class MOAIWidget : public QGLWidget
{
	Q_OBJECT

public:
	MOAIWidget( QWidget* parent = 0, int width = 320, int height = 480 );
	virtual ~MOAIWidget();

	static MOAIWidget* getInstance ( int width = 320, int height = 480 );

	void refreshContext();

	void openWindow ( const char* title, int width, int height );
    void setSimStep ( double newStep );

	void setWorkingDirectory( char const* path );
	void runScript( const char* filename );
	void runString( const char* script );

protected:
	virtual void initializeGL();
	virtual void resizeGL(int w, int h);
	virtual void paintGL();
    
    virtual void keyPressEvent ( QKeyEvent* event );
    virtual void keyReleaseEvent ( QKeyEvent* event );
    virtual void mousePressEvent ( QMouseEvent* event );
    virtual void mouseReleaseEvent ( QMouseEvent* event );
    virtual void mouseMoveEvent ( QMouseEvent* event );
    virtual void wheelEvent(QWheelEvent* event);
	
	void setCallbacks();
	void setDevices();
	void setTimer();
	void setLua();
    
protected slots:
    void simStep();

private:
    void onMouseButton(Qt::MouseButton button, bool pressedDown);
    void onKey(QKeyEvent* event, bool pressedDown);
    
	AKUContextID context;
    QTimer* timer;

	static MOAIWidget* instance_;

	bool _glReady;
	bool _windowReady;
};