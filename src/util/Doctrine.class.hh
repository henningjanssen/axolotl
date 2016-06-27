<?hh // partial
//Needs partial-mode as Doctrine is a php-framework

namespace axolotl\util;

require_once realpath(__DIR__.'/../../vendor/autoload.php');

use Doctrine\DBAL\Connection;
use Doctrine\ORM\Tools\Setup;
use Doctrine\ORM\EntityManager;

class Doctrine{
  private static ?Connection $customDriver = null;

  public static function setCustomDriver(Connection $driver): void{
    self::$customDriver = $driver;
  }

  public static function getEntityManager(
    array<string> $entityPaths = array()
  ): EntityManager{
    $devMode = false;
    $entityPaths[] = realpath(__DIR__."/../entities");
    $dbConf = self::getDBSettings();
    $config = Setup::createAnnotationMetadataConfiguration(
      $entityPaths, $devMode
    );
    return EntityManager::create(self::$customDriver ?? $dbConf, $config);
  }

  private static function getDBSettings(): array<arraykey,mixed>{
    $conf = array(
      "driver" => _::SETTINGS("doctrine_driver")
    );
    if(_::SETTINGS("db_socket") !== null){
      $conf["db_socket"] = strval(_::SETTINGS("db_socket"));
      return $conf;
    }
    $conf["user"] = strval(_::SETTINGS("db_user"));
    $conf["password"] = strval(_::SETTINGS("db_password"));

    if($conf["doctrine_driver"] !== "pdo_sqlite"){
      $conf["host"] = strval(_::SETTINGS("db_host", "localhost"));
      $conf["dbname"] = strval(_::SETTINGS("db_name"));
    }
    if(_::SETTINGS("db_driver_options") !== null){
      $conf["driverOptions"] = strval(_::SETTINGS("driverOptions"));
    }

    switch(strval($conf["driver"])){
      case "pdo_sqlite":
        $conf["path"] = strval(_::SETTINGS("db_path"));
        $conf["memory"] = boolval(_::SETTINGS("db_memory"));
      break;

      case "pdo_mysql":
      case "drizzle_pdo_mysql":
      case "mysqli":
        $conf["port"] = intval(_::SETTINGS("db_port"), 3306);
        $conf["charset"] = strval(_::SETTINGS("db_charset", "utf8"));
      break;

      case "pdo_pgsql":
        $conf["port"] = intval(_::SETTINGS("db_port"), 5432);
        $conf["charset"] = strval(_::SETTINGS("db_charset", "utf8"));
        $conf["default_dbname"] =
          strval(_::SETTINGS("db_default_dbname", "postgres"));
        $conf["sslmode"] = strval(_::SETTINGS("db_sslmode"));
        $conf["sslrootcert"] = strval(_::SETTINGS("db_sslrootcert"));
        $conf["application_name"] =
          strval(_::SETTINGS("db_application_nam", "axolotl"));
      break;

      case "pdo_oci":
      case "oci8":
        $conf["port"] = intval(_::SETTINGS("db_port", 1521));
        $conf["servicename"] =
          strval(_::SETTINGS("db_servicename", $conf["dbname"]));
        $conf["service"] = _::SETTINGS("db_servicename") === null;
        $conf["pooled"] = boolval(_::SETTINGS("db_pooled", false));
        $conf["charset"] = strval(_::SETTINGS("db_charset", "utf8"));
        if(_::SETTINGS("db_instancename") !== null){
          $conf["instancename"] = _::SETTINGS("db_instancename");
        }
      break;

      case "pdo_sqlsrv":
      case "sqlsrv":
        $conf["port"] = intval(_::SETTINGS("db_port", 1433));
      break;

      case "sqlanywhere":
        $conf["server"] = _::SETTINGS("db_server");
        $conf["port"] = _::SETTINGS("db_port");
        $conf["persistent"] = boolval(_::SETTINGS("db_persistent", false));
      break;
    }
    return $conf;
  }
}
