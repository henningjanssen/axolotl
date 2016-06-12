<?hh // strict

namespace axolotl\controller;

use \LoginView;
use \RedirectView;
use axolotl\util\_;
use axolotl\util\Session;

class LoginController extends PageController{
  private string $redirect = "/";
  public function __construct(array<string> $vars, string $redirect = "/"){
    parent::__construct($vars);
    $this->redirect = $redirect;
  }

  public function execute(): void{
    $loginFailed = false;
    if(_::POST("__ax_login") !== null){
      $query = "SELECT * FROM users WHERE username = ?1 OR email = ?1";
    }
    if(Session::loggedIn()){
      (new RedirectView($this->redirect))->render();
    }
    else{
      (new LoginView(
        $loginFailed,
        strval(_::POST("__ax_login")) ?? "",
        strval(_::POST("__ax_pw")) ?? ""
      ))->render();
    }
  }
}
