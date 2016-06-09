<?hh // strict

namespace axolotl\controller;

class LoginController extends PageController{
  private string $redirect = "/";
  public function __construct(array<string> $vars, string $redirect = "/"){
    parent::construct($vars);
    $this->redirect = $redirect;
  }

  public function execute(){
    if(_::POST["__ax_login"] !== null){
      $doctrine =
    }
  }
}
