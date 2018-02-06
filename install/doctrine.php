<?php
  require_once __DIR__.'../axl-autoload.php';

  $entityManager = \axolotl\util\Doctrine::getEntityManager();
  $tool = new \Doctrine\ORM\Tools\SchemaTool($entityManager);
  $classes = array(
    'axolotl\entities\User',
    'axolotl\entities\Module'
  );
  $tool->createSchema($classes);
