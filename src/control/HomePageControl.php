<?php

namespace axolotl\control;

use axolotl\view\HomePageView;
use axolotl\util\_;
use axolotl\util\Doctrine;
use axolotl\util\Session;

class HomePageControl extends LoggedInPageControl{
  public function execute(): void{
    $entityManager = Doctrine::getEntityManager();
    $user = Session::getCurrentUser();
    $modules = $entityManager
      ->getRepository('axolotl\entities\Module')
      ->findAll();
    (new HomePageView($user, $modules))->render();
  }
}
