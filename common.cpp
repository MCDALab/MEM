#include "common.h"

qreal normal( QList<qreal> list )
{
    qreal sum = 0;
    for( int i = 0; i < list.size(); i++ )
    {
        sum += list.at(i);
    }
    return sum/list.size();
}
