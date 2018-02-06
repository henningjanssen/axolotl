<?php
  require_once realpath(__DIR__."/../src/util/Doctrine.php");

  use axolotl\util\Doctrine;
  use Doctrine\ORM\Tools\Console\ConsoleRunner;

  $entityManager = Doctrine::getEntityManager();

  return ConsoleRunner::createHelperSet($entityManager);
