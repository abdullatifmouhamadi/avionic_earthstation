#include "config.h"

/**
 * Constructeur
 * @brief Config::Config
 */
Config::Config()
{
}

/**
 * On parse le fichier de configuration "../earthstation/config/config.ini"
 * @brief Config::parseFileConfig
 */
void Config::parseFileConfig()
{
  QSettings m_settings("../earthstation/config/config.ini", QSettings::IniFormat);
  m_typeConnexion = m_settings.value("link_aircraft/type", "serial").toString();
}

/**
 * Récupération d'un élément de configuration par la clé.
 * @brief Config::getConfigByKey
 * @param key
 * @return Qstring value
 */
QString Config::getConfigByKey(QString key)
{
  QSettings m_settings("../earthstation/config/config.ini", QSettings::IniFormat);
  return m_settings.value(key, "").toString();
}
