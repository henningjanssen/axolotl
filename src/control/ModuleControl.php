<?hh // strict

namespace axolotl\control;

use \ModuleView;
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
