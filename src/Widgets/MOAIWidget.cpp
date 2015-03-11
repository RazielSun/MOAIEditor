#include <QDebug>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>

#include "MOAIWidget.h"

namespace InputDeviceID
{
    enum
    {
        DEVICE,
        TOTAL
    };
}

namespace InputDeviceSensorID
{
    enum
    {
        KEYBOARD,
        POINTER,
        MOUSE_LEFT,
        MOUSE_MIDDLE,
        MOUSE_RIGHT,
        MOUSE_WHEEL,
        TOTAL
    };
}

//

void openWindowHandler( const char* title, int width, int height )
{
    MOAIWidget* instance = MOAIWidget::getInstance();
    if ( instance != NULL )
    {
        instance->openWindow( title, width, height );
    }
}

void setSimStepHandler( double newStep )
{
    MOAIWidget* instance = MOAIWidget::getInstance();
    if ( instance != NULL )
    {
        instance->setSimStep( newStep );
    }
}

//

MOAIWidget* MOAIWidget::instance_ = 0;

MOAIWidget::MOAIWidget(QWidget* parent) : QGLWidget(parent)
{
	_glReady = false;
	_windowReady = false;

	refreshContext();
	setMouseTracking(true);
	setTimer();
}

MOAIWidget::~MOAIWidget()
{
	_windowReady = false;
    _glReady = false;

    AKUModulesAppFinalize();
    AKUAppFinalize();
}

MOAIWidget* MOAIWidget::getInstance ()
{
    if ( instance_ == NULL )
    {
        instance_ = new MOAIWidget();
    }
    return instance_;
}

//

void MOAIWidget::initializeGL()
{
	_glReady = true;
	// Set the clear color to black
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
};

void MOAIWidget::resizeGL(int w, int h)
{
	if (_windowReady)
	{
		AKUSetScreenSize(w, h);
        AKUSetViewSize(w, h);
	}
};

void MOAIWidget::paintGL()
{
	if (_windowReady)
	{
		AKURender();
	}
	else if (_glReady)
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}  
};

//

void MOAIWidget::openWindow ( const char* title, int width, int height )
{
    show();
    glInit();
    
    AKUDetectGfxContext();

    setWindowTitle( QString ( title ));

    resize( width, height );

    _windowReady = true;
}

void MOAIWidget::setSimStep ( double newStep )
{
    if (timer)
    {
        timer->setInterval( newStep * 1000 );
    }
}

//

void MOAIWidget::simStep()
{
	if (_windowReady)
	{
		AKUModulesUpdate();
	}
};

void MOAIWidget::refreshContext()
{
	context = AKUGetContext();
	if (context)
	{
		AKUDeleteContext(context);
	}
    
	AKUAppInitialize();
	AKUModulesAppInitialize();

	context = AKUCreateContext();
	AKUModulesContextInitialize();

	ParticlePresets();

	setCallbacks();
	setDevices();
	setLua();

	_windowReady = false;
};

void MOAIWidget::setCallbacks()
{
	//AKUSetFunc_EnterFullscreenMode ( enterFullscreenAKUCB );
    //AKUSetFunc_ExitFullscreenMode ( exitFullscreenAKUCB );
    AKUSetFunc_OpenWindow( openWindowHandler );
    AKUSetFunc_SetSimStep( setSimStepHandler );
};

void MOAIWidget::setDevices()
{
	AKUSetInputConfigurationName( "MOAIEditor" );

    AKUReserveInputDevices( InputDeviceID::TOTAL );
    AKUSetInputDevice( InputDeviceID::DEVICE, "device" );

    AKUReserveInputDeviceSensors( InputDeviceID::DEVICE, InputDeviceSensorID::TOTAL );
    AKUSetInputDeviceKeyboard( InputDeviceID::DEVICE, InputDeviceSensorID::KEYBOARD, "keyboard" );
    AKUSetInputDevicePointer( InputDeviceID::DEVICE, InputDeviceSensorID::POINTER, "pointer" );
    AKUSetInputDeviceButton( InputDeviceID::DEVICE, InputDeviceSensorID::MOUSE_LEFT, "mouseLeft" );
    AKUSetInputDeviceButton( InputDeviceID::DEVICE, InputDeviceSensorID::MOUSE_MIDDLE, "mouseMiddle" );
    AKUSetInputDeviceButton( InputDeviceID::DEVICE, InputDeviceSensorID::MOUSE_RIGHT, "mouseRight" );
    AKUSetInputDeviceWheel( InputDeviceID::DEVICE, InputDeviceSensorID::MOUSE_WHEEL, "wheel" );
}

void MOAIWidget::setTimer()
{
	timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    connect(timer, SIGNAL(timeout()), this, SLOT(simStep()));
    timer->start(AKUGetSimStep() * 1000);
};

void MOAIWidget::setLua()
{
	runString("os.setlocale('C')");
	AKUModulesRunLuaAPIWrapper();
	runString("MOAIEnvironment.setValue('horizontalResolution', 100 ) MOAIEnvironment.setValue('verticalResolution', 100)");
};

void MOAIWidget::setWorkingDirectory( char const* path )
{
	AKUSetWorkingDirectory( path );
}

void MOAIWidget::runScript( const char* filename )
{
	AKULoadFuncFromFile( filename );
    AKUCallFunc();
}

void MOAIWidget::runString( const char* script )
{
	AKULoadFuncFromString( script );
    AKUCallFunc();
}

//

void MOAIWidget::keyPressEvent ( QKeyEvent* event )
{
    onKey( event, true );
}

void MOAIWidget::keyReleaseEvent ( QKeyEvent* event )
{
    onKey( event, false );
}

void MOAIWidget::mousePressEvent ( QMouseEvent* event )
{
    onMouseButton( event->button(), true);
}

void MOAIWidget::mouseReleaseEvent ( QMouseEvent* event )
{
    onMouseButton( event->button(), false);
}

void MOAIWidget::mouseMoveEvent ( QMouseEvent* event )
{
    AKUEnqueuePointerEvent( InputDeviceID::DEVICE, InputDeviceSensorID::POINTER, event->x(), event->y());
}

void MOAIWidget::wheelEvent(QWheelEvent* event)
{
    AKUEnqueueWheelEvent ( InputDeviceID::DEVICE, InputDeviceSensorID::MOUSE_WHEEL, event->delta ());
}

void MOAIWidget::onMouseButton(Qt::MouseButton button, bool pressedDown)
{
    if ( button == Qt::LeftButton )
    {
        AKUEnqueueButtonEvent ( InputDeviceID::DEVICE, InputDeviceSensorID::MOUSE_LEFT, pressedDown );
    }
    else if ( button == Qt::MiddleButton )
    {
        AKUEnqueueButtonEvent ( InputDeviceID::DEVICE, InputDeviceSensorID::MOUSE_MIDDLE, pressedDown);
    }
    else if ( button == Qt::RightButton )
    {
        AKUEnqueueButtonEvent ( InputDeviceID::DEVICE, InputDeviceSensorID::MOUSE_RIGHT, pressedDown);
    }
}

void MOAIWidget::onKey(QKeyEvent* event, bool pressedDown)
{
    int eventKey = event->key();
    if ( eventKey == Qt::Key_Control )
    {
        AKUEnqueueKeyboardControlEvent( InputDeviceID::DEVICE, InputDeviceSensorID::KEYBOARD, pressedDown );
    }
    else if ( eventKey == Qt::Key_Alt || eventKey == Qt::Key_AltGr )
    {
        AKUEnqueueKeyboardAltEvent( InputDeviceID::DEVICE, InputDeviceSensorID::KEYBOARD, pressedDown );
    }
    else if ( eventKey == Qt::Key_Shift )
    {
        AKUEnqueueKeyboardShiftEvent( InputDeviceID::DEVICE, InputDeviceSensorID::KEYBOARD, pressedDown );
    }
    else
    {
        AKUEnqueueKeyboardEvent( InputDeviceID::DEVICE, InputDeviceSensorID::KEYBOARD, eventKey, pressedDown );
    }
}