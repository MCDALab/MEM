#ifndef LANGUAGE_H
#define LANGUAGE_H

#include "common.h"

class Language
{
public:
    Language();
    static Language* instance();
    static void loadLanguage( QString lang );
    static QString language(QString key);
    static QString actual();
private:
    static Language *inst;
    static QHash<QString, QString> languageMap;
    static QString actual_lang;
};

#endif // LANGUAGE_H
