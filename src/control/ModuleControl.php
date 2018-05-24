<?php

namespace axolotl\control;

use axolotl\view\ModuleView;
use axolotl\util\_;
use axolotl\util\Doctrine;

class ModuleControl extends LoggedInPageControl{
  public function execute(): void{
    $entityManager = Doctrine::getEntityManager();
    $modules = $entityManager
      ->getRepository('axolotl\entities\Module')
      ->findAll();
    (new ModuleView($modules))->render();
  }
}
