<?hh // strict

namespace axolotl\control;

use \HomePageView;
use axolotl\util\_;
use axolotl\util\Doctrine;

class HomePageControl extends LoggedInPageControl{
  public function execute(): void{
    $entityManager = Doctrine::getEntityManager();
    $user = $entityManager->find("\\axolotl\\entities\\User", _::SESSION("uid"));
    $modules = $entityManager
      ->getRepository('axolotl\entities\Module')
      ->findAll();
    (new HomePageView($user, $modules))->render();
  }
}
