<?php

require_once __DIR__.'/../axl-autoload.php';

$entityManager = \axolotl\util\Doctrine::getEntityManager();
$user = new \axolotl\entities\User();
$user->setUsername("admin");
$user->setPassword(password_hash("admin", PASSWORD_BCRYPT));
$user->setLanguage("en");

$entityManager->persist($user);
$entityManager->flush();
