<?hh // strict

namespace axolotl\control;

use \LoginView;
use \RedirectView;
use axolotl\entities\User;
use axolotl\util\_;
use axolotl\util\Doctrine;
use axolotl\util\Session;

class LoginControl extends PageControl{
  private string $redirect = "/";
  public function __construct(array<string, string> $vars, string $redirect = "/"){
    parent::__construct($vars);
    $this->redirect = $redirect;
  }

  public function execute(): void{
    $loginFailed = false;
    if(_::POST("__ax_login") !== null){
      $querystr = "select u from axolotl\\entities\\User u"
        ." where u.username = :user or u.email = :user";
      $entityManager = Doctrine::getEntityManager();
      $query = $entityManager->createQuery($querystr);
      $query->setParameter('user', _::POST("__ax_nick"));
      $result = $query->getResult();
      if(count($result) !== 1){
        $loginFailed = true;
      }
      else{
        $result = $result[0];
        if($result->getPassword() !== hash("sha256", _::POST("__ax_pw"))){
          $loginFailed = true;
        }
        else{
          _::SESSION("uid", $result->getID());
        }
      }
    }
    if(Session::loggedIn()){
      (new RedirectView($this->redirect))->render();
    }
    else{
      (new LoginView(
        $loginFailed,
        strval(_::POST("__ax_nick")) ?? "",
        strval(_::POST("__ax_pw")) ?? ""
      ))->render();
    }
  }
}
