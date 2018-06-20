#ifndef CONFIG_H
#define CONFIG_H

#include <QString>
#include <QSettings>

class Config
{
public:
  Config();
  void parseFileConfig();
  QString getConfigByKey(QString key);

private:
  QString m_typeConnexion;
};

#endif // CONFIG_H
