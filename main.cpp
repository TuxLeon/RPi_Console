// main.cpp
#include <QtCore>
#include <QDebug>
#include <QThread>

#include "Consolereader.h"
#include "PCA9685.h"
#include "LinkedList.h"
#include "ServoUnit.h"


//Longrunner Servo von 120-680 mit 0-180° Drehwinkel
//Mittelposition 400-410
const uint8_t MAX_COUNT = 56;
const uint16_t MAX_POS = 680;
const uint16_t MIN_POS = 120;
const uint8_t STEP_SIZE = 1;
const uint8_t TIMER_INTERVAL = 10;


class Task : public QObject
{
    Q_OBJECT
public:
    Task(QObject *parent = 0) : QObject(parent) {
        active_servo = 0;
        counter = 0;
        cycleFinished = 0;
    }
    void init(void){
        // myPwmHandler->setPWM(5,0,120);
        ptrServo = _servos.get(active_servo);
    }
    void addServo(uint8_t index, ServoUnit* newServo){
        _servos.add(index, newServo);
    }

public slots:
    void run()
    {
        /*
        // Do processing here
        if((counter*STEP_SIZE) >= MAX_POS || cycleFinished == 1){
            cycleFinished = 1;
        }
        else{
            qDebug() << "next" << endl;
            myPwmHandler->setPWM(servo,0,100+(counter*STEP_SIZE));
            counter++;
        }
        */
    }

    void KeyPressed(char ch){
        qDebug() << "Input : " << ch << endl;
        if(ch == 'w'){
            counter += STEP_SIZE;
            ptrServo->setPos(counter);
        }
        if(ch == 'x'){
            counter -= STEP_SIZE;
            ptrServo->setPos(counter);
        }
        if(ch == 'q'){
            qDebug() << "Bye bye" << endl;
            emit finished();
        }
        if(ch == '0'){
            active_servo = 0;
            ptrServo = _servos.get(active_servo);
            counter = ptrServo->getPos();
            qDebug() << "Active Servo: " << active_servo << " pos=" << counter;
        }
        if(ch == '1'){
            active_servo = 1;
            ptrServo = _servos.get(active_servo);
            counter = ptrServo->getPos();
            qDebug() << "Active Servo: " << active_servo << " pos=" << counter;
        }
        if(ch == '2'){
            active_servo = 2;
            ptrServo = _servos.get(active_servo);
            counter = ptrServo->getPos();
            qDebug() << "Active Servo: " << active_servo << " pos=" << counter;
        }
        if(ch == '3'){
            active_servo = 3;
            ptrServo = _servos.get(active_servo);
            counter = ptrServo->getPos();
            qDebug() << "Active Servo: " << active_servo << " pos=" << counter;
        }

        qDebug() << "Servo Pos["<< active_servo << "] :" << counter << endl;
    }

    void ssTimer(){
        timer = new QTimer(this);
        QObject::connect(timer, SIGNAL(timeout()), this, SLOT(run()));
        timer->start(TIMER_INTERVAL);
        qDebug() << "1sec singleshot timer" << endl;
    }

signals:
    void finished();

private:
    uint8_t counter;
    PCA9685* myPwmHandler;
    QTimer *timer;
    uint8_t cycleFinished;
    uint8_t active_servo;
    ServoUnit* ptrServo;
    LinkedList<ServoUnit*> _servos;
};

#include "main.moc"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // Task parented to the application so that it
    // will be deleted by the application.
    Task *task = new Task(&a);

    // Create PWM driver
    PCA9685* myPwmHandler = new PCA9685(1, 0x40);

    // Create Servo Instances
    ServoUnit servo1( 1, 90, 180, 0, myPwmHandler);
    ServoUnit servo2( 2, 90, 180, 0, myPwmHandler);
    ServoUnit servo3( 4, 90, 180, 0, myPwmHandler);
    ServoUnit servo4( 5, 90, 180, 0, myPwmHandler);
    ServoUnit servo5( 6, 90, 180, 0, myPwmHandler);
    ServoUnit servo6( 7, 90, 180, 0, myPwmHandler);
    // longRuner instance
    ServoUnit servo7( 8, 90, 180, 0, myPwmHandler);

    qDebug() << "add Servo: 0" << "ptr=" << &servo1;
    task->addServo(0, &servo1);
    task->addServo(1, &servo2);
    task->addServo(2, &servo3);
    task->addServo(3, &servo4);
    task->addServo(4, &servo5);
    task->addServo(5, &servo6);

    task->addServo(6, &servo7);

    task->init();

    //Console input reader
    ConsoleReader *consoleReader = new ConsoleReader();
    QObject::connect (consoleReader, SIGNAL (KeyPressed(char)), task, SLOT(KeyPressed(char)));
    consoleReader->start();

    // This will cause the application to exit when
    // the task signals finished.
    QObject::connect(task, SIGNAL(finished()), &a, SLOT(quit()));

    //Initialize Servo
    task->init();

    // This will run the task from the application event loop.
    // Increment servo position
    QTimer::singleShot(1000, task, SLOT(ssTimer()));

    return a.exec();
}
