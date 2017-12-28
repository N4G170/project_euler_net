#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <map>
#include <string>

#include "json.h"

/**
 * \brief Tries to load(from file) application configuration into config_json var
 */
int ProgramConfigReader(int argc, char *argv[], Json::Value& config_json);

#endif // CONFIGPARSER_H
