#include "configuration.h"

Configuration * Configuration::inst = NULL;
QHash<QString, QString> Configuration::configurationMap;

Configuration::Configuration()
{
}

void Configuration::loadConfiguration()
{
    QSettings settings (QCoreApplication::applicationDirPath()+"/conf.ini", QSettings::IniFormat );
    settings.beginGroup("configuration");
    foreach( QString key, settings.allKeys()) {
        configurationMap[key] = settings.value(key).toString();
    }
}

QString Configuration::configuration(QString key)
{
    return configurationMap[key];
}
