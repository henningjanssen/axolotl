<?hh // partial
  require_once realpath(__DIR__."/../src/util/Doctrine.class.hh");

  use axolotl\Doctrine;
  use Doctrine\ORM\Tools\Console\ConsoleRunner;

  $entityManager = Doctrine::getEntityManager();

  return ConsoleRunner::createHelperSet($entityManager);
