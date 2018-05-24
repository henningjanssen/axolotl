<?php
  require_once __DIR__.'/../axl-autoload.php';

  $entityManager = \axolotl\util\Doctrine::getEntityManager();
  $tool = new \Doctrine\ORM\Tools\SchemaTool($entityManager);
  $classes = $entityManager->getMetadataFactory()->getAllMetadata();
  $tool->createSchema($classes);
