<?hh // strict

namespace axolotl\controller;

use \HomePageView;
use axolotl\util\_;
use axolotl\util\Doctrine;

class HomePageController extends LoggedInPageController{
  public function execute(): void{
    $entityManager = Doctrine::getEntityManager();
    $user = $entityManager->find("users", _::SESSION("uid"));
    (new HomePageView($user))->render();
  }
}
