#ifndef ZIGBEEPROTOCOL_GLOBAL_H
#define ZIGBEEPROTOCOL_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ZIGBEEPROTOCOL_LIBRARY)
#  define ZIGBEEPROTOCOLSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ZIGBEEPROTOCOLSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // ZIGBEEPROTOCOL_GLOBAL_H
