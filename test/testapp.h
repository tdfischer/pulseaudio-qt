#ifndef TESTAPP_H
#define TESTAPP_H

#include <QCoreApplication>

#include "pulse-qt.h"
#include "context.h"

class TestApp : public QCoreApplication {
    
    Q_OBJECT
    
    public:
        TestApp(int argc, char** argv);
        virtual ~TestApp();
        
    public slots:
        void showSinks();
        void getSinks();
        
    private:
        Context* m_cxt;
};
#endif
