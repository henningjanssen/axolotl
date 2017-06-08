<?hh // strict

namespace axolotl\control;

use \LoginView;
use \RedirectView;
use axolotl\entities\User;
use axolotl\exceptions\EntityNotFoundException;
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
      try{
        $user = User::getByLogin(strval(_::POST("username")));
        if(!password_verify(strval(_::POST("password")), $user->getPassword())){
          $loginFailed = true;
        }
        else{
          _::SESSION("uid", $user->getID());
          $entityManager = Doctrine::getEntityManager();
          $user->setLastActivity();
          $entityManager->persist($user);
          $entityManager->flush();
        }
      }
      catch(EntityNotFoundException $enfex){
        $loginFailed = true;
      }
    }
    if(Session::loggedIn()){
      (new RedirectView($this->redirect))->render();
    }
    else{
      (new LoginView(
        $loginFailed,
        strval(_::POST("username")) ?? "",
        strval(_::POST("password")) ?? ""
      ))->render();
    }
  }
}
