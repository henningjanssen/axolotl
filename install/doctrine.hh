<?hh // partial
  require_once '../vendor/autoload.php';

  $entityManager = \axolotl\util\Doctrine::getEntityManager();
  $tool = new \Doctrine\ORM\Tools\SchemaTool($entityManager);
  $classes = array(
    'axolotl\entities\User',
    'axolotl\entities\Module'
  );
  $tool->createSchema($classes);
