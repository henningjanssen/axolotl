<?hh // partial
//Needs partial-mode as Doctrine is a php-framework

//http://doctrine-orm.readthedocs.io/projects/doctrine-orm/en/latest/reference/advanced-configuration.html

namespace axolotl\util;

require_once realpath(__DIR__.'/../../vendor/autoload.php');

use Doctrine\DBAL\Connection;
use Doctrine\ORM\Configuration;
use Doctrine\ORM\EntityManager;
use Doctrine\ORM\Tools\Setup;

use axolotl\exceptions\BrokenInstallationException;

class Doctrine{
  private static ?Connection $customDriver = null;

  public static function setCustomDriver(Connection $driver): void{
    self::$customDriver = $driver;
  }

  public static function getEntityManager(
    array<string> $entityPaths = array()
  ): EntityManager{
    try{
      $devMode = false;
      $entityPaths[] = realpath(__DIR__."/../entities");
      $dbConf = self::getDBSettings();
      $cache = self::getCache();
      $config = new Configuration();
      $config->setMetadataCacheImpl($cache);
      $annotationDriver = $config->newDefaultAnnotationDriver($entityPaths);
      $pathinfo = pathinfo(__FILE__);
      $annotationDriver->setFileExtension(".".$pathinfo['extension']);
      $config->setMetadataDriverImpl($annotationDriver);
      $config->setQueryCacheImpl($cache);
      $config->setProxyDir(realpath(__DIR__.'/../proxies/'));
      $config->setProxyNamespace('axolotl\proxies');
      $config->setAutogenerateProxyClasses(!$devMode);
      return EntityManager::create(self::$customDriver ?? $dbConf, $config);
    }
    catch(\Doctrine\DBAL\DBALException $dbalex){
      throw new BrokenInstallationException(
        "Can't create doctrine-entitymanager. Errors in config?",
        42,
        $dbalex
      );
    }
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

    if($conf["driver"] !== "pdo_sqlite"){
      $conf["host"] = strval(_::SETTINGS("db_host", "localhost"));
      $conf["dbname"] = strval(_::SETTINGS("db_name"));
    }
    if(_::SETTINGS("db_driver_options") !== null){
      $conf["driverOptions"] = strval(_::SETTINGS("db_driver_options"));
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
        $conf["port"] = intval(_::SETTINGS("db_port", 5432));
        $conf["charset"] = strval(_::SETTINGS("db_charset", "utf8"));
        $conf["default_dbname"] =
          strval(_::SETTINGS("db_default_dbname", "postgres"));
        $conf["sslmode"] = strval(_::SETTINGS("db_sslmode", "prefer"));
        $conf["sslrootcert"] =
          strval(_::SETTINGS("db_sslrootcert", "~/.postgresql/root.crt"));
        $conf["application_name"] =
          strval(_::SETTINGS("db_application_name", "axolotl"));
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

  private static function getCache(): \Doctrine\Common\Cache\Cache{
    $cache = null;
    switch(strval(_::SETTINGS("doctrine_cache", "array"))){
      case "apc":{
        $cache = new \Doctrine\Common\Cache\ApcCache();
      } break;

      case "memcache":{
        $cache = new \Doctrine\Common\Cache\MemcacheCache();
        $memcache = new \Memcache();
        if(boolval(_::SETTINGS("memcache_persistent"))){
          $memcache->pconnect(
            strval(_::SETTINGS("memcache_host", "localhost")),
            intval(_::SETTINGS("memcache_post",
              boolval(_::SETTINGS("memcache_socket", false) ? 0 : 11211)
            )),
            intval(_::SETTINGS("memcache_timeout", 1))
          );
        }
        else{
          $memcache->connect(
            strval(_::SETTINGS("memcache_host", "localhost")),
            intval(_::SETTINGS("memcache_post",
              boolval(_::SETTINGS("memcache_socket", false) ? 0 : 11211)
            )),
            intval(_::SETTINGS("memcache_timeout", 1))
          );
        }
        $cache->setMemcache($memcache);
      } break;

      case "memcached":{
        $cache = new \Doctrine\Common\Cache\MemcacheCache();
        $memcached = new \Memcached();
        $memcached->addServer(
          strval(_::SETTINGS("memcache_host", "localhost")),
          intval(_::SETTINGS("memcache_post",
            boolval(_::SETTINGS("memcache_socket", false) ? 0 : 11211)
          ))
        );
        $cache->setMemcache($memcached);
      } break;

      case "redis":{
        $redis = new \Redis();
        $redis->connect(
          strval(_::SETTINGS("redis_host", "localhost")),
          intval(_::SETTINGS("redis_port", 6379))
        );
        $cache = new \Doctrine\Common\Cache\RedisCache();
        $cache->setRedis($redis);
      } break;

      case "xcache":{
        $cache = new \Doctrine\Common\Cache\XcacheCache();
      } break;

      case "zend":{
        $cache = new \Doctrine\Common\Cache\ZendCache();
      } break;

      //case "array":
      default:{
        $cache = new \Doctrine\Common\Cache\ArrayCache();
      } break;
    }
    $cache->setNamespace("_axolotl_doctrine_");
    return $cache;
  }
}
