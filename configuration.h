#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "common.h"

class Configuration
{
public:
    Configuration();
    static Configuration* instance();
    static void loadConfiguration();
    static QString configuration(QString key);
private:
    static Configuration *inst;
    static QHash<QString, QString> configurationMap;
};

#endif // CONFIGURATION_H
