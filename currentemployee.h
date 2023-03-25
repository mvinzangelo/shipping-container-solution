#ifndef CURRENTEMPLOYEE_H
#define CURRENTEMPLOYEE_H

#include <QString>

class currentEmployee
{
public:
    currentEmployee();
    void setFirstName(QString firstName) { this->firstName = firstName; }
    void setLastName(QString lastName) { this->lastName = lastName; }
    QString getFirstName() { return firstName; }
    QString getLastName() { return lastName; }

private:
    QString firstName = "";
    QString lastName = "";
};

#endif // CURRENTEMPLOYEE_H
