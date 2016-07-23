<?hh // strict

namespace axolotl\control;

use \HomePageView;
use axolotl\util\_;
use axolotl\util\Doctrine;

class HomePageControl extends LoggedInPageControl{
  public function execute(): void{
    $entityManager = Doctrine::getEntityManager();
    $user = $entityManager->find("\\axolotl\\entities\\User", _::SESSION("uid"));
    (new HomePageView($user))->render();
  }
}
