<?hh // strict

require_once realpath(__DIR__.'/../../vendor/autoload.php');

namespace axolotl\util;

use Doctrine\ORM\Tools\Setup;
use Doctrine\ORM\EntityManager;

class Doctrine{
  public static function getEntityManager(): EntityManager{
    //TODO: read stuff from config-file
    $devMode = false;
    $entityPaths = array(
      realpath(__DIR__."/../entities")
    );
    $dbConf = array(
      'driver' => 'pdo_mysql',
      'user' => '',
      'password' => '',
      'dbname' => "axolotl"
    );
    //TODO: some validity checks
    $config = Setup::createAnnotationMetadataConfiguration(
      $entityPaths, $devMode
    );
    return EntityManager::create($dbConf, $config);
  }
}
